#ifndef SRC_MEMORY_DECLARATION_H
#define SRC_MEMORY_DECLARATION_H

static inline bool frame_bitmap_mask_clear_p(ptr_t mask, uint32 i);
static inline bool frame_bitmap_mask_set_p(ptr_t frame_bitmap, uint32 i);
static inline bool kernel_heap_footer_illegal_p(s_kernel_heap_footer_t *footer);
static inline bool kernel_heap_footer_legal_p(s_kernel_heap_footer_t *footer);
static inline bool kernel_heap_header_illegal_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_header_is_hole_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_header_is_not_hole_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_header_legal_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_header_magic_invalid_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_header_magic_valid_p(s_kernel_heap_header_t *header);
static inline bool kernel_heap_hole_legal_p(void *hole_addr);
static inline bool kernel_heap_illegal_p(s_kernel_heap_t *heap);
static inline bool kernel_heap_is_user_p(s_kernel_heap_t *heap);
static inline bool kernel_heap_is_writable_p(s_kernel_heap_t *heap);
static inline bool kernel_heap_legal_p(s_kernel_heap_t *heap);
static inline ptr_t frame_allocate(void);
static inline ptr_t frame_bitmap_frame_obtain(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx, uint32 bit_idx);
static inline ptr_t frame_bitmap_mask(s_frame_bitmap_t *frame_bitmap, uint32 i);
static inline ptr_t kernel_heap_addr_end(s_kernel_heap_t *heap);
static inline ptr_t kernel_heap_addr_start(s_kernel_heap_t *heap);
static inline ptr_t kernel_heap_hole_size(s_kernel_heap_header_t *header);
static inline ptr_t kernel_heap_hole_usable_limit(s_kernel_heap_header_t *header);
static inline ptr_t kernel_heap_hole_usable_size(s_kernel_heap_header_t *header);
static inline ptr_t kernel_heap_last_hole_addr(s_kernel_heap_t *heap);
static inline ptr_t kernel_heap_size(s_kernel_heap_t *heap);
static inline ptr_t page_entry_frame(s_page_entry_t *page_entry);
static inline s_frame_bitmap_t * frame_bitmap_create(ptr_t memory_limit);
static inline s_kernel_heap_footer_t * kernel_heap_header_to_footer(s_kernel_heap_header_t *header);
static inline s_kernel_heap_footer_t * kernel_heap_header_to_left_footer(s_kernel_heap_header_t *header);
static inline s_kernel_heap_header_t * kernel_heap_footer_right_unify(s_kernel_heap_footer_t *footer);
static inline s_kernel_heap_header_t * kernel_heap_footer_to_header(s_kernel_heap_footer_t *footer);
static inline s_kernel_heap_header_t * kernel_heap_footer_to_right_header(s_kernel_heap_footer_t *footer);
static inline s_kernel_heap_header_t * kernel_heap_header_left_unify(s_kernel_heap_header_t *header);
static inline s_kernel_heap_header_t * kernel_heap_hole_make(void *hole_addr, uint32 size);
static inline s_kernel_heap_header_t * kernel_heap_minimal_hole_obtain(s_kernel_heap_t *heap, uint32 request_size, ptr_t *usable_addr);
static inline s_ordered_array_t * kernel_heap_ordered_array(s_kernel_heap_t *heap);
static inline s_page_directory_t * page_directory_create(void);
static inline s_page_entry_t * page_allocate(ptr_t addr, bool is_user, bool is_writable);
static inline s_page_entry_t * page_directory_page_entry_get(s_page_directory_t *page_dirt, ptr_t addr);
static inline s_page_entry_t * page_directory_page_obtain(s_page_directory_t *page_dirt, ptr_t addr);
static inline s_page_entry_t * page_entry_get(ptr_t addr);
static inline s_page_entry_t * page_table_page_entry(s_page_table_t *page_table, uint32 i);
static inline s_page_table_t * page_directory_page_table(s_page_directory_t *page_dirt, uint32 i);
static inline s_page_table_t * page_table_create(void);
static inline sint32 kernel_heap_compare(void *a, void *b);
static inline uint32 frame_bitmap_frame_bit_index(s_frame_bitmap_t *frame_bitmap, ptr_t frame);
static inline uint32 frame_bitmap_frame_mask_index(s_frame_bitmap_t *frame_bitmap, ptr_t frame);
static inline uint32 frame_bitmap_limit(s_frame_bitmap_t *frame_bitmap);
static inline uint32 kernel_heap_hole_rear_size(s_kernel_heap_header_t *header, uint32 req_size);
static inline uint32 memory_byte_to_dword_fill(uint8 val);
static inline uint32 memory_dword_copy(uint32 *to, uint32 *from, uint32 len);
static inline uint32 memory_word_to_dword_fill(uint16 val);
static inline void * kernel_heap_allocate(s_kernel_heap_t *heap, uint32 req_size);
static inline void * kernel_heap_realloc(s_kernel_heap_t *heap, void *val, uint32 new_size);
static inline void * memory_dword_set(uint32 *base, uint32 val, uint32 len);
static inline void * memory_physical_aligned_allocate(uint32 sz);
static inline void * memory_physical_allocate(uint32 sz);
static inline void * memory_physical_allocate_i(uint32 sz, bool is_page_aligned);
static inline void * memory_word_set(uint16 *base, uint16 val, uint32 len);
static inline void frame_bitmap_mask_clear(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx, uint32 bit_idx);
static inline void frame_bitmap_mask_set(s_frame_bitmap_t *frame_bitmap, uint32 mask_idx, uint32 bit_idx);
static inline void kernel_heap_addr_end_set(s_kernel_heap_t *heap, ptr_t addr_end);
static inline void kernel_heap_block_make(void *hole_addr, uint32 size);
static inline void kernel_heap_contract(s_kernel_heap_t *heap, uint32 new_size);
static inline void kernel_heap_expand(s_kernel_heap_t *heap, uint32 expand_size);
static inline void kernel_heap_free(s_kernel_heap_t *heap, void *val);
static inline void kernel_heap_header_is_hole_set(s_kernel_heap_header_t *header, bool is_hole);
static inline void kernel_heap_hole_remove(s_kernel_heap_t *heap, s_kernel_heap_header_t *header);
static inline void kernel_heap_hole_split(s_kernel_heap_header_t *header, uint32 req_size, s_ordered_array_t *ordered);
static inline void kernel_heap_initialize_i(s_kernel_heap_t *heap, ptr_t addr_start, ptr_t addr_end, ptr_t addr_limit);
static inline void kmemory_copy_i(void *to, void *from, uint32 len);
static inline void kmemset_i(void *base, uint8 val, uint32 len);
static inline void kmemset_u16_i(void *base, uint16 val, uint32 len);
static inline void memory_byte_copy(uint8 *to, uint8 *from, uint32 len);
static inline void memory_byte_set(uint8 *base, uint8 val, uint32 len);
static inline void page_align_i(ptr_t *addr);
static inline void page_directory_page_table_phys_set(s_page_directory_t *page_dirt, uint32 i, ptr_t page_table_phys);
static inline void page_directory_page_table_set(s_page_directory_t *page_dirt, uint32 i, s_page_table_t *page_table);
static inline void page_directory_switch(s_page_directory_t *page_dirt);
static inline void page_enabled_range_print(ptr_t addr_start, ptr_t addr_end);
static inline void page_entry_attribute_present_set(s_page_entry_t *page_entry, bool is_presented);
static inline void page_entry_attribute_rw_set(s_page_entry_t *page_entry, bool is_writable);
static inline void page_entry_attribute_us_set(s_page_entry_t *page_entry, bool is_user);
static inline void page_entry_frame_set(s_page_entry_t *page_entry, ptr_t frame);
static inline void page_entry_initialize(s_page_entry_t *page_entry, ptr_t frame, bool is_user, bool is_writable);
static inline void page_free(ptr_t addr);
void * kmalloc(uint32 request_size);
void * krealloc(void *ptr, uint32 new_size);
void kernel_heap_initialize(void);
void kfree(void *ptr);
void kmemory_copy(void *to, void *from, uint32 len);
void kmemset(void *base, uint8 v, uint32 len);
void kmemset_u16(void *base, uint16 val, uint32 len);
void memory_physical_placement_set(ptr_t addr_phys);
void page_align(ptr_t *addr);
void page_initialize(void);

#endif
