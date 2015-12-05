#ifndef DESCRIPTOR_DECLARATION_H
#define DESCRIPTOR_DECLARATION_H


static inline void descriptor_table_gdt_entry_set(uint32 index, uint32 base, uint32 lmt, uint16 acc, uint8 flags);
static inline void descriptor_table_gdt_init(void);
void descriptor_table_init(void);

#endif
