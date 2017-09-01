static inline void
fs_ext2_descriptor_table_append(s_ext2_dspr_table_t *dspr_table,
    s_ext2_dspr_t *dspr)
{
    uint32 index;
    s_ext2_dspr_t **dspr_array;

    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(!fs_ext2_descriptor_table_full_p(dspr_table));

    dspr_array = fs_ext2_descriptor_table_dspr_array(dspr_table);
    index = fs_ext2_descriptor_table_index(dspr_table);

    dspr_array[index++] = dspr;

    fs_ext2_descriptor_table_index_set(dspr_table, index);
}

// static inline void
// fs_ext2_descriptor_block_group_append(s_ext2_dspr_t *dspr,
//     s_ext2_bg_info_t *bg_info)
// {
//     uint32 index;
//     s_ext2_bg_info_t **block_group_array;
// 
//     /* bg_info == NULL is allowed here */
//     kassert(fs_ext2_descriptor_legal_p(dspr));
// 
//     block_group_array = fs_ext2_descriptor_block_group_array(dspr);
//     index = fs_ext2_descriptor_index(dspr);
// 
//     block_group_array[index++] = bg_info;
// 
//     fs_ext2_descriptor_index_set(dspr, index);
// }

static inline s_ext2_dspr_t *
fs_ext2_descriptor_create(e_disk_id_t device_id, s_disk_pt_t *pt,
    s_ext2_bg_info_t *bg_info)
{
    uint32 size;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;

    kassert(disk_partition_legal_p(pt));
    kassert(fs_ext2_bg_info_valid_p(bg_info));
    kassert(device_id < disk_descriptor_limit());

    size = EXT2_BLOCK_GROUP_MAX;
    bytes_count = sizeof(dspr->bg_data_array[0]) * size;

    dspr = kmalloc(sizeof(*dspr));
    dspr->bg_data_array = kmalloc(bytes_count);

    dspr->device_id = device_id;
    dspr->disk_pt = pt;
    dspr->bg_info = bg_info;
    dspr->index = 0;
    dspr->size = size;

    return dspr;
}

static inline void
fs_ext2_descriptor_destroy(s_ext2_dspr_t **dspr)
{
    kassert(dspr);
    kassert(*dspr);

    kfree((*dspr)->bg_data_array);
    kfree((*dspr)->bg_info);
    kfree(*dspr);

    *dspr = NULL;
}

static inline s_ext2_bg_info_t *
fs_ext2_bg_info_create(s_disk_buf_t *disk_buf, e_disk_id_t device_id,
    uint32 sector_offset)
{
    uint32 offset;
    f_disk_read_t read;
    s_ext2_bg_info_t *bg_info;

    kassert(sector_offset);
    kassert(disk_buffer_legal_p(disk_buf));

    offset = EXT2_SBLOCK_OFFSET;
    bg_info = kmalloc(sizeof(*bg_info));
    read = disk_descriptor_read(device_id);

    read(disk_buf, device_id, sector_offset, offset + sizeof(*bg_info));
    disk_buffer_copy(bg_info, disk_buf, offset, sizeof(*bg_info));

    return bg_info;
}

static inline void
fs_ext2_bg_info_destroy(s_ext2_bg_info_t **bg_info)
{
    kassert(bg_info);
    kassert(*bg_info);

    kfree(*bg_info);

    *bg_info = NULL;
}

static inline s_vfs_node_t *
fs_ext2_descriptor_vfs_tree_build(s_ext2_dspr_t *dspr)
{
    s_vfs_node_t *ext2_root;

    kassert(fs_ext2_descriptor_legal_p(dspr));

    ext2_root = vfs_dir_node_create(FS_DIR_ROOT, (void *)1, (void *)1);
    vfs_node_inode_set(ext2_root, EXT2_ROOT_DIR_INODE);

    return ext2_root;
}

/*
 * INITIALIZE the rest block groups without primary block. Depending upon the
 * revision of Ext2 used, some or all block groups may also contain a backup
 * copy of the Superblock and the Block Group Descriptor Table.
 */
// static inline s_ext2_dspr_t *
// fs_ext2_descriptor_initialize(s_disk_pt_t *disk_pt, e_disk_id_t device_id,
//     s_disk_buf_t *buf, s_ext2_bg_info_t *group_primary)
// {
//     s_ext2_dspr_t *dspr;
//     s_ext2_bg_info_t *bg_info;
//     uint32 sector_offset, sector_limit, sector_step;
// 
//     kassert(group_primary);
//     kassert(disk_buffer_legal_p(buf));
//     kassert(disk_partition_legal_p(disk_pt));
//     kassert(device_id < disk_descriptor_limit());
// 
//     dspr = fs_ext2_descriptor_create(device_id, disk_pt);
//     fs_ext2_descriptor_block_group_append(dspr, group_primary);
// 
//     sector_offset = disk_partition_sector_offset(disk_pt);
//     sector_limit = sector_offset + disk_partition_sector_count(disk_pt);
//     sector_step = fs_ext2_block_group_sector_count(group_primary, device_id);
// 
//     sector_offset += sector_step; /* skip primary block bg_info */
// 
//     while (sector_offset < sector_limit) {
//         bg_info = fs_ext2_block_group_create(buf, device_id, sector_offset);
// 
//         if (fs_ext2_block_group_invalid_p(bg_info)) {
//             fs_ext2_block_group_destroy(&bg_info);
//         }
// 
//         fs_ext2_descriptor_block_group_append(dspr, bg_info);
//         sector_offset += sector_step;
//     }
// 
//     return dspr;
// }

static inline s_bitmap_t *
fs_ext2_bitmap_place(s_disk_buf_t *buf, e_disk_id_t device_id,
    uint32 sector_offset, uint32 bytes_count)
{
    uint8 *array;
    s_bitmap_t *bitmap;
    f_disk_read_t read;

    kassert(bytes_count);
    kassert(sector_offset);
    kassert(disk_buffer_legal_p(buf));

    array = kmalloc(bytes_count);
    read = disk_descriptor_read(device_id);

    read(buf, device_id, sector_offset, bytes_count);
    disk_buffer_copy(array, buf, 0, bytes_count);
    bitmap_place(array, bytes_count, bytes_count * 8);

    return bitmap;
}

static inline s_ext2_bg_data_t *
fs_ext2_block_group_data_normal_create(s_ext2_bg_info_t *bg_info,
    s_disk_buf_t *buf, uint32 sector_offset, uint32 sector_bytes)
{
    uint32 sector, bytes_count;
    uint32 block_bytes, b_bitmap_addr;
    uint32 i_count, i_table_addr, i_bitmap_addr;

    kassert(bg_info);
    kassert(disk_buffer_legal_p(buf));

    b_bitmap_addr = fs_ext2_bg_info_block_bitmap_addr(bg_info);
    i_bitmap_addr = fs_ext2_bg_info_inode_bitmap_addr(bg_info);
    i_table_addr = fs_ext2_bg_info_inode_table_addr(bg_info);
    i_count = fs_ext2_bg_info_inode_count(bg_info);
    block_bytes = fs_ext2_block_group_block_size(bg_info);

    bytes_count = sizeof(s_ext2_inode_t) * i_count;
    sector = sector_offset + i_bitmap_addr * block_bytes / sector_bytes;
}

static inline s_ext2_bg_data_t *
fs_ext2_block_group_data_no_info_create(
{


}

static inline void
fs_ext2_block_group_data_initialize(s_ext2_dspr_t *dspr, s_disk_pt_t *pt,
    e_disk_id_t device_id)
{
    s_disk_buf_t *buf;
    s_ext2_bg_info_t *info;
    uint32 sector_offset, sector_limit, sector_step;

    kassert(fs_ext2_descriptor_legal_p(dspr));
    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));

    info = fs_ext2_descriptor_block_group_info(dspr);
    sector_offset = disk_partition_sector_offset(pt);
    sector_limit = sector_offset + disk_partition_sector_count(pt);
    sector_step = fs_ext2_block_group_sector_count(info, device_id);

    buf = disk_buffer_create(EXT2_BUFFER_MAX);

    while (sector_offset < sector_limit) {
        info = fs_ext2_bg_info_create(buf, device_id, sector_offset);

        if (fs_ext2_bg_info_valid_p(info)) {
        } else {
        }

        fs_ext2_bg_info_destroy(&info);
        sector_offset += sector_step;
    }

    disk_buffer_destroy(&buf);
}

static inline s_ext2_dspr_t *
fs_ext2_partition_initialize(s_disk_pt_t *pt, e_disk_id_t device_id)
{
    s_disk_buf_t *buf;
    uint32 bytes_count;
    s_ext2_dspr_t *dspr;
    s_ext2_bg_info_t *bg_info;
    uint32 sector_bytes, sector_offset;

    kassert(disk_partition_legal_p(pt));
    kassert(disk_partition_used_p(pt));
    kassert(device_id < disk_descriptor_limit());

    dspr = NULL;
    bytes_count = EXT2_SBLOCK_OFFSET;
    sector_bytes = disk_descriptor_sector_bytes(device_id);
    sector_offset = disk_partition_sector_offset(pt);
    bytes_count += ((sizeof(*bg_info) / sector_bytes) + 1) * sector_bytes;

    buf = disk_buffer_create(bytes_count);
    bg_info = fs_ext2_bg_info_create(buf, device_id, sector_offset);

    if (fs_ext2_bg_info_invalid_p(bg_info)) {
        fs_ext2_bg_info_destroy(&bg_info);
    } else {
        dspr = fs_ext2_descriptor_create(device_id, pt, bg_info);
        fs_ext2_block_group_data_initialize(dspr, pt, device_id);
    }

    disk_buffer_destroy(&buf);

    return dspr;
}

static inline void
fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id,
    s_ext2_dspr_table_t *dspr_table)
{
    uint32 i, limit;
    s_ext2_dspr_t *dspr;
    s_disk_pt_t *disk_pt;
    s_vfs_node_t *vfs_node;
    s_disk_pt_table_t *disk_pt_table;

    kassert(vfs_node_legal_p(root));
    kassert(fs_ext2_descriptor_table_legal_p(dspr_table));
    kassert(device_id < disk_descriptor_limit());

    disk_pt_table = disk_descriptor_pt_table(device_id);

    i = 0;
    limit = DISK_PT_TABLE_SIZE;

    while (i < limit) {
        dspr = NULL;
        disk_pt = disk_partition_table_entry(disk_pt_table, i);

        if (disk_partition_used_p(disk_pt)) {
            dspr = fs_ext2_partition_initialize(disk_pt, device_id);
        }

        if (dspr) {
            fs_ext2_descriptor_table_append(dspr_table, dspr);
        }

        if (dspr && disk_partition_bootable_p(disk_pt)) {
            vfs_node = fs_ext2_descriptor_vfs_tree_build(dspr);
            vfs_sub_list_add(root, vfs_node);
        }

        i++;
    }
}

static inline void
fs_ext2_descriptor_table_initialize(s_ext2_dspr_table_t *dspr_table)
{
    uint32 bytes_count;

    kassert(dspr_table);

    bytes_count = sizeof(dspr_table->dspr_array[0]) * EXT2_DESCCRIPTOR_MAX;

    dspr_table->dspr_array = kmalloc(bytes_count);
    dspr_table->index = 0;
    dspr_table->size = EXT2_DESCCRIPTOR_MAX;
}

static inline void
fs_ext2_initialize_i(s_vfs_node_t *root)
{
    uint32 i, limit;
    s_ext2_dspr_table_t *dspr_table;

    kassert(vfs_node_legal_p(root));

    dspr_table = fs_ext2_descriptor_table_obtain();
    fs_ext2_descriptor_table_initialize(dspr_table);

    i = DEVICE_START;
    limit = disk_descriptor_limit();

    while (i < limit) {
        if (disk_descriptor_is_active_p(i)) {
            fs_ext2_device_initialize(root, i, dspr_table);
        }

        i++;
    }

    fs_ext2_descriptor_table_print(dspr_table);
}

void
fs_ext2_initialize(s_vfs_node_t *root)
{
    if (vfs_node_illegal_p(root)) {
        return;
    } else {
        fs_ext2_initialize_i(root);
    }
}

