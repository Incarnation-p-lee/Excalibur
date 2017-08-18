#ifndef SRC_VFS_DECLARATION_H
#define SRC_VFS_DECLARATION_H

bool vfs_node_file_p(s_vfs_node_t *vfs_node);
bool vfs_node_illegal_p(s_vfs_node_t *vfs_node);
bool vfs_node_legal_p(s_vfs_node_t *vfs_node);
char * vfs_node_name(s_vfs_node_t *vfs_node);
s_vfs_node_t * vfs_dir_node_create(char *name, f_readdir_t readdir, f_finddir_t finddir);
s_vfs_node_t * vfs_file_node_create(char *name, f_read_t read, f_write_t write);
s_vfs_node_t * vfs_node_next(s_vfs_node_t *vfs_node);
s_vfs_node_t * vfs_readdir(s_vfs_node_t *vfs_node, uint32 index);
s_vfs_node_t * vfs_sub_list_first(s_vfs_node_t *vfs_node);
static inline bool vfs_node_closable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_findable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_readable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_unfindable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_dir_unreadable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_directory_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_file_ip(s_vfs_node_t *vfs_node);
static inline bool vfs_node_illegal_ip(s_vfs_node_t *vfs_node);
static inline bool vfs_node_legal_ip(s_vfs_node_t *vfs_node);
static inline bool vfs_node_not_directory_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_openable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_readable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unclosable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unopenable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unreadable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_unwritable_p(s_vfs_node_t *vfs_node);
static inline bool vfs_node_writable_p(s_vfs_node_t *vfs_node);
static inline char * vfs_node_name_i(s_vfs_node_t *vfs_node);
static inline s_linked_list_t * vfs_node_list(s_vfs_node_t *vfs_node);
static inline s_linked_list_t * vfs_node_sub_list(s_vfs_node_t *vfs_node);
static inline s_vfs_node_t * vfs_dir_node_create_i(char *name, f_readdir_t readdir, f_finddir_t finddir);
static inline s_vfs_node_t * vfs_file_node_create_i(char *name, f_read_t read, f_write_t write);
static inline s_vfs_node_t * vfs_list_to_node(s_linked_list_t *linked_list);
static inline s_vfs_node_t * vfs_node_next_i(s_vfs_node_t *vfs_node);
static inline s_vfs_node_t * vfs_node_root(void);
static inline s_vfs_node_t * vfs_root_node_initialize(void);
static inline s_vfs_node_t * vfs_sub_list_first_i(s_vfs_node_t *vfs_node);
static inline uint32 vfs_node_flags_i(s_vfs_node_t *vfs_node);
static inline uint32 vfs_node_inode_i(s_vfs_node_t *vfs_node);
static inline uint32 vfs_node_length_i(s_vfs_node_t *vfs_node);
static inline void vfs_initrd_initialize(s_vfs_node_t *root);
static inline void vfs_node_flags_add_i(s_vfs_node_t *vfs_node, uint32 flags);
static inline void vfs_node_flags_set_i(s_vfs_node_t *vfs_node, uint32 flags);
static inline void vfs_node_inode_set_i(s_vfs_node_t *vfs_node, uint32 inode);
static inline void vfs_node_length_set_i(s_vfs_node_t *vfs_node, uint32 length);
static inline void vfs_node_sub_list_insert_after(s_vfs_node_t *vfs_node, s_vfs_node_t *inserted);
static inline void vfs_node_sub_list_set(s_vfs_node_t *vfs_node, s_linked_list_t *list);
static inline void vfs_sub_list_add_i(s_vfs_node_t *vfs_node, s_vfs_node_t *added);
uint32 vfs_close(s_vfs_node_t *vfs_node);
uint32 vfs_node_flags(s_vfs_node_t *vfs_node);
uint32 vfs_node_inode(s_vfs_node_t *vfs_node);
uint32 vfs_node_length(s_vfs_node_t *vfs_node);
uint32 vfs_open(s_vfs_node_t *vfs_node);
uint32 vfs_read(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
uint32 vfs_write(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
void vfs_initialize(void);
void vfs_node_flags_add(s_vfs_node_t *vfs_node, uint32 flags);
void vfs_node_inode_set(s_vfs_node_t *vfs_node, uint32 inode);
void vfs_node_length_set(s_vfs_node_t *vfs_node, uint32 length);
void vfs_sub_list_add(s_vfs_node_t *vfs_node, s_vfs_node_t *added);

#endif
