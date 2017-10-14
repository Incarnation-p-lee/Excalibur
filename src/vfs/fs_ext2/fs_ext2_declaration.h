#ifndef SRC_VFS_FS_EXT2_DECLARATION_H
#define SRC_VFS_FS_EXT2_DECLARATION_H

static inline bool fs_ext2_bgd_map_legal_p(s_ext2_bgd_map_t *map);
static inline bool fs_ext2_dir_illegal_p(s_ext2_dir_t *dir);
static inline bool fs_ext2_dir_legal_p(s_ext2_dir_t *dir);
static inline bool fs_ext2_dir_type_directory_p(s_ext2_dir_t *dir);
static inline bool fs_ext2_dir_type_regular_p(s_ext2_dir_t *dir);
static inline bool fs_ext2_dspr_illegal_p(s_ext2_dspr_t *dspr);
static inline bool fs_ext2_dspr_legal_p(s_ext2_dspr_t *dspr);
static inline bool fs_ext2_dspr_table_full_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_dspr_table_illegal_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_dspr_table_legal_p(s_ext2_dspr_table_t *dspr_table);
static inline bool fs_ext2_inode_is_dir_p(s_ext2_inode_t *inode);
static inline bool fs_ext2_superblock_invalid_p(s_ext2_spbk_t *spbk);
static inline bool fs_ext2_superblock_valid_p(s_ext2_spbk_t *spbk);
static inline bool fs_ext2_vfs_node_implicit_dir_p(s_vfs_node_t *vfs_node);
static inline bool fs_ext2_vfs_node_obvious_dir_p(s_vfs_node_t *vfs_node);
static inline char * fs_ext2_dir_name(s_ext2_dir_t *dir);
static inline e_disk_id_t fs_ext2_dspr_device_id(s_ext2_dspr_t *dspr);
static inline s_bitmap_t * fs_ext2_bitmap_place(s_disk_buf_t *buf, e_disk_id_t device_id, uint32 sector, uint32 bytes_count);
static inline s_disk_pt_t * fs_ext2_dspr_disk_pt(s_ext2_dspr_t *dspr);
static inline s_ext2_bgd_map_t * fs_ext2_bgd_map_create(s_disk_buf_t *buf, e_disk_id_t device_id, s_ext2_dspr_t *dspr, s_ext2_bgd_t *bgd);
static inline s_ext2_bgd_map_t * fs_ext2_dspr_bgd_map(s_ext2_dspr_t *dspr, uint32 i);
static inline s_ext2_bgd_map_t ** fs_ext2_dspr_bgd_map_array(s_ext2_dspr_t *dspr);
static inline s_ext2_bgd_t * fs_ext2_bgd_table_create(s_disk_buf_t *buf, e_disk_id_t device_id, uint32 sector_offset, uint32 size);
static inline s_ext2_bgd_t * fs_ext2_dspr_bgd(s_ext2_dspr_t *dspr, uint32 i);
static inline s_ext2_bgd_t * fs_ext2_dspr_bgd_table(s_ext2_dspr_t *dspr);
static inline s_ext2_dir_t * fs_ext2_dir_create(uint32 size);
static inline s_ext2_dir_t * fs_ext2_dir_disk_buffer_create(s_disk_buf_t *buf, uint32 offset);
static inline s_ext2_dspr_t * fs_ext2_dspr_create(e_disk_id_t device_id, s_disk_pt_t *pt, s_ext2_spbk_t *superblock, s_ext2_bgd_t *bgd_table);
static inline s_ext2_dspr_t * fs_ext2_dspr_table_entry(s_ext2_dspr_table_t *dspr_table, uint32 i);
static inline s_ext2_dspr_t * fs_ext2_partition_initialize(s_disk_pt_t *pt, e_disk_id_t device_id);
static inline s_ext2_dspr_t ** fs_ext2_dspr_table_dspr_array(s_ext2_dspr_table_t *dspr_table);
static inline s_ext2_dspr_table_t * fs_ext2_dspr_table_obtain(void);
static inline s_ext2_inode_t * fs_ext2_dspr_inode_create(s_ext2_dspr_t *dspr, s_disk_buf_t *buf, uint32 inode_addr);
static inline s_ext2_spbk_t * fs_ext2_dspr_superblock(s_ext2_dspr_t *dspr);
static inline s_ext2_spbk_t * fs_ext2_superblock_create(s_disk_buf_t *buf, e_disk_id_t device_id, uint32 sector_offset);
static inline s_vfs_node_t * fs_ext2_dspr_vfs_tree_build(s_ext2_dspr_t *dspr);
static inline uint16 fs_ext2_inode_type(s_ext2_inode_t *inode);
static inline uint16 fs_ext2_superblock_signature(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_bgd_block_bitmap_addr(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_bgd_dir_count(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_bgd_inode_bitmap_addr(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_bgd_inode_table_addr(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_bgd_unalloc_block_count(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_bgd_unalloc_inode_count(s_ext2_bgd_t *bgd);
static inline uint32 fs_ext2_block_addr_to_sector(uint32 block_addr, uint32 block_bytes, uint32 sector_offset, uint32 sector_bytes);
static inline uint32 fs_ext2_dir_inode_nmbr(s_ext2_dir_t *dir);
static inline uint32 fs_ext2_dir_size(s_ext2_dir_t *dir);
static inline uint32 fs_ext2_dspr_bg_count(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_bgd_inode_table_addr(s_ext2_dspr_t *dspr, uint32 i);
static inline uint32 fs_ext2_dspr_block_addr_to_sector(s_ext2_dspr_t *dspr, uint32 b_addr);
static inline uint32 fs_ext2_dspr_block_size(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_group_block_count(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_group_inode_count(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_inode_addr_to_sector(s_ext2_dspr_t *dspr, uint32 inode_addr, uint32 *bytes_offset);
static inline uint32 fs_ext2_dspr_sector_bytes(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_sector_offset(s_ext2_dspr_t *dspr);
static inline uint32 fs_ext2_dspr_table_index(s_ext2_dspr_table_t *dspr_table);
static inline uint32 fs_ext2_dspr_table_limit(s_ext2_dspr_table_t *dspr_table);
static inline uint32 fs_ext2_dspr_table_size(s_ext2_dspr_table_t *dspr_table);
static inline uint32 fs_ext2_inode_bytes_size_high(s_ext2_inode_t *inode);
static inline uint32 fs_ext2_inode_bytes_size_low(s_ext2_inode_t *inode);
static inline uint32 fs_ext2_inode_dir_entry_count(s_ext2_inode_t *inode);
static inline uint32 fs_ext2_inode_direct_block_addr(s_ext2_inode_t *inode, uint32 i);
static inline uint32 fs_ext2_inode_hard_link_count(s_ext2_inode_t *inode);
static inline uint32 fs_ext2_superblock_block_group_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_block_nmbr(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_block_size(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_group_block_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_group_inode_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_major_version(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_reserved_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_total_block_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_unallocated_block_count(s_ext2_spbk_t *spbk);
static inline uint32 fs_ext2_superblock_unallocated_inode_count(s_ext2_spbk_t *spbk);
static inline uint64 fs_ext2_inode_bytes_size(s_ext2_inode_t *inode);
static inline uint64 fs_ext2_inode_direct_block_count(s_ext2_inode_t *inode, uint32 block_bytes);
static inline uint8 fs_ext2_dir_type(s_ext2_dir_t *dir);
static inline void fs_ext2_bgd_map_b_bitmap_is_dirty_set(s_ext2_bgd_map_t *map, bool is_dirty);
static inline void fs_ext2_bgd_map_block_bitmap_set(s_ext2_bgd_map_t *map, s_bitmap_t *bitmap);
static inline void fs_ext2_bgd_map_destroy(s_ext2_bgd_map_t **map);
static inline void fs_ext2_bgd_map_i_bitmap_is_dirty_set(s_ext2_bgd_map_t *map, bool is_dirty);
static inline void fs_ext2_bgd_map_inode_bitmap_set(s_ext2_bgd_map_t *map, s_bitmap_t *bitmap);
static inline void fs_ext2_bgd_print(s_ext2_bgd_t *bgd, uint32 i);
static inline void fs_ext2_bgd_table_destroy(s_ext2_bgd_t **bgd_table);
static inline void fs_ext2_device_initialize(s_vfs_node_t *root, e_disk_id_t device_id, s_ext2_dspr_table_t *dspr_table);
static inline void fs_ext2_dspr_bgd_bitmap_destroy(s_ext2_dspr_t *dspr);
static inline void fs_ext2_dspr_bgd_map_set(s_ext2_dspr_t *dspr, uint32 i, s_ext2_bgd_map_t *map);
static inline void fs_ext2_dspr_destroy(s_ext2_dspr_t **dspr);
static inline void fs_ext2_dspr_device_id_set(s_ext2_dspr_t *dspr, e_disk_id_t device_id);
static inline void fs_ext2_dspr_disk_pt_set(s_ext2_dspr_t *dspr, s_disk_pt_t *disk_pt);
static inline void fs_ext2_dspr_inode_destroy(s_ext2_inode_t **inode);
static inline void fs_ext2_dspr_map_array_initialize(s_ext2_dspr_t *dspr, s_disk_buf_t *buf, e_disk_id_t device_id);
static inline void fs_ext2_dspr_print(s_ext2_dspr_t *dspr);
static inline void fs_ext2_dspr_table_append(s_ext2_dspr_table_t *dspr_table, s_ext2_dspr_t *dspr);
static inline void fs_ext2_dspr_table_index_set(s_ext2_dspr_table_t *dspr_table, uint32 index);
static inline void fs_ext2_dspr_table_initialize(s_ext2_dspr_table_t *dspr_table);
static inline void fs_ext2_dspr_table_print(s_ext2_dspr_table_t *dspr_table);
static inline void fs_ext2_dspr_table_size_set(s_ext2_dspr_table_t *dspr_table, uint32 size);
static inline void fs_ext2_dspr_vfs_tree_dfs_build(s_ext2_dspr_t *dspr, s_stack_t *stack, s_disk_buf_t *buf);
static inline void fs_ext2_initialize_i(s_vfs_node_t *root);
static inline void fs_ext2_inode_direct_block_children_add(s_ext2_dspr_t *dspr, s_vfs_node_t *vfs_node, s_ext2_inode_t *inode, s_stack_t *stack, s_disk_buf_t *buf);
static inline void fs_ext2_superblock_destroy(s_ext2_spbk_t **superblock);
static inline void fs_ext2_superblock_print(s_ext2_spbk_t *superblock);
static inline void fs_ext2_vfs_node_child_add(s_stack_t *stack, s_ext2_dir_t *dir, s_vfs_node_t *vfs_parent);
static inline void fs_ext2_vfs_node_children_add(s_ext2_dspr_t *dspr, s_vfs_node_t *vfs_node, s_stack_t *stack, s_disk_buf_t *buf);
static inline void fs_ext2_vfs_node_tree_print(s_vfs_node_t *vfs_root);
void fs_ext2_initialize(s_vfs_node_t *root);

#endif
