static inline s_ext2_dir_t *
fs_ext2_dir_create(uint32 size)
{
    s_ext2_dir_t *dir;

    kassert(size > sizeof(s_ext2_dir_t));

    dir = kmalloc(size + 1);

    ((char *)dir)[size] = CHAR_NULL;

    return dir;
}

/*
 * Will return NULL if illegal s_ext2_dir_t
 */
static inline s_ext2_dir_t *
fs_ext2_dir_block_buffer_create(s_block_buf_t *buf, uint32 offset)
{
    uint32 size;
    s_ext2_dir_t dir_tmp, *dir;

    kassert(block_buffer_legal_p(buf));
    kassert(offset + sizeof(dir_tmp) < block_buffer_limit(buf));

    PANIC_IF_INV_SIZE(block_buffer_copy(&dir_tmp, buf, offset, sizeof(dir_tmp)));

    if (fs_ext2_dir_illegal_p(&dir_tmp)) {
        return NULL;
    }

    size = fs_ext2_dir_size(&dir_tmp);
    dir = fs_ext2_dir_create(size);

    PANIC_IF_INV_SIZE(block_buffer_copy(dir, buf, offset, size));

    return dir;
}

static inline void
fs_ext2_vfs_node_child_add(s_stack_t *stack, s_ext2_dir_t *dir,
    s_vfs_node_t *vfs_parent)
{
    uint32 inode_nmbr;
    s_vfs_node_t *vfs_node;

    kassert(stack_legal_p(stack));
    kassert(fs_ext2_dir_legal_p(dir));
    kassert(vfs_node_legal_p(vfs_parent));

    inode_nmbr = fs_ext2_dir_inode_nmbr(dir);

    if (fs_ext2_dir_type_directory_p(dir)) {
        vfs_node = vfs_dir_node_create(fs_ext2_dir_name(dir), (void *)1, (void *)1);
    } else if (fs_ext2_dir_type_regular_p(dir)) {
        vfs_node = vfs_file_node_create(fs_ext2_dir_name(dir), (void *)1, (void *)1);
    } else {
        KERNEL_PANIC("Directory entry type unsupported.\n");
    }

    vfs_node_inode_set(vfs_node, inode_nmbr);
    vfs_sub_list_add(vfs_parent, vfs_node);

    stack_push(stack, vfs_node);
}

static inline void
fs_ext2_inode_direct_block_children_add(s_ext2_dspr_t *dspr,
    s_vfs_node_t *vfs_node, s_ext2_inode_t *inode, s_stack_t *stack,
    s_block_buf_t *buf)
{
    s_ext2_dir_t *dir;
    uint64 block_count;
    f_disk_read_t read;
    e_dev_id_t id;
    uint32 i, b_addr, b_bytes, sector, off;

    kassert(inode);
    kassert(stack_legal_p(stack));
    kassert(block_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(vfs_node_legal_p(vfs_node) && vfs_node_directory_p(vfs_node));

    i = 0;
    id = fs_ext2_dspr_id(dspr);
    read = disk_descriptor_read(id);
    b_bytes = fs_ext2_dspr_block_size(dspr);
    block_count = fs_ext2_inode_direct_block_count(inode, b_bytes);

    while (i < block_count) {
        b_addr = fs_ext2_inode_direct_block_addr(inode, i++);
        kassert(b_addr);

        sector = fs_ext2_dspr_block_addr_to_sector(dspr, b_addr);
        PANIC_IF_INV_SIZE(read(buf, id, sector, b_bytes));

        off = 0;

        while (off < b_bytes) {
            dir = fs_ext2_dir_block_buffer_create(buf, off);

            if (dir == NULL) {
                return;
            }

            off += fs_ext2_dir_size(dir);
            fs_ext2_vfs_node_child_add(stack, dir, vfs_node);
        }
    }
}

static inline void
fs_ext2_vfs_node_children_add(s_ext2_dspr_t *dspr, s_vfs_node_t *vfs_node,
    s_stack_t *stack, s_block_buf_t *buf)
{
    s_ext2_inode_t *inode;

    kassert(stack_legal_p(stack));
    kassert(block_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(vfs_node_legal_p(vfs_node));
    kassert(vfs_node_directory_p(vfs_node));

    inode = fs_ext2_dspr_inode_create(dspr, buf, vfs_node_inode(vfs_node));

    fs_ext2_inode_direct_block_children_add(dspr, vfs_node, inode, stack, buf);
    // To-Do: take care of indirected block

    fs_ext2_dspr_inode_destroy(&inode);
}

static inline void
fs_ext2_dspr_vfs_tree_dfs_build(s_ext2_dspr_t *dspr, s_stack_t *stack,
    s_block_buf_t *buf)
{
    s_vfs_node_t *vfs_node;

    kassert(stack_legal_p(stack));
    kassert(block_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));

    while (!stack_empty_p(stack)) {
        vfs_node = stack_pop(stack);

        if (fs_ext2_vfs_node_implicit_dir_p(vfs_node)) {
            continue;
        } else if (vfs_node_directory_p(vfs_node)) {
            fs_ext2_vfs_node_children_add(dspr, vfs_node, stack, buf);
        }
    }
}

static inline s_vfs_node_t *
fs_ext2_dspr_vfs_tree_build(s_ext2_dspr_t *dspr)
{
    s_stack_t *stack;
    s_block_buf_t *buf;
    s_vfs_node_t *ext2_root;

    kassert(fs_ext2_dspr_legal_p(dspr));

    stack = stack_create();
    buf = block_buffer_create(EXT2_BUFFER_MAX);

    ext2_root = vfs_dir_node_create(FS_DIR_ROOT, (void *)1, (void *)1);
    vfs_node_inode_set(ext2_root, EXT2_ROOT_DIR_INODE);

    stack_push(stack, ext2_root);

    fs_ext2_dspr_vfs_tree_dfs_build(dspr, stack, buf);

    stack_destroy(&stack);
    block_buffer_destroy(&buf);

    fs_ext2_vfs_node_tree_print(ext2_root);

    return ext2_root;
}

static inline s_ext2_inode_t *
fs_ext2_dspr_inode_create(s_ext2_dspr_t *dspr, s_block_buf_t *buf,
    uint32 inode_addr)
{
    e_dev_id_t id;
    uint32 bytes_offset;
    f_disk_read_t read;
    s_ext2_inode_t *inode;
    uint32 cpy_bytes, read_bytes, sector;

    kassert(block_buffer_legal_p(buf));
    kassert(fs_ext2_dspr_legal_p(dspr));
    kassert(inode_addr != EXT2_INODE_ADDR_NULL);

    inode = kmalloc(sizeof(*inode));

    sector = fs_ext2_dspr_inode_addr_to_sector(dspr, inode_addr, &bytes_offset);
    id = fs_ext2_dspr_id(dspr);
    read = disk_descriptor_read(fs_ext2_dspr_id(dspr));

    read_bytes = read(buf, id, sector, sizeof(*inode) + bytes_offset);

    if (IS_SIZE_INVALID_P(read_bytes)) {
        KERNEL_PANIC("Failed to read data from device.\n");
    }

    cpy_bytes = block_buffer_copy(inode, buf, bytes_offset, sizeof(*inode));

    if (IS_SIZE_INVALID_P(cpy_bytes)) {
        KERNEL_PANIC("Unable to create array of bitmap.\n");
    }

    return inode;
}

static inline void
fs_ext2_dspr_inode_destroy(s_ext2_inode_t **inode)
{
    kassert(inode);
    kassert(*inode);

    kfree(*inode);
    *inode = NULL;
}

