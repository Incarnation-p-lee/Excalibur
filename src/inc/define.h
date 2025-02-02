#ifndef HAVE_DEFINED_DEFINE_H
#define HAVE_DEFINED_DEFINE_H

#define true                      1
#define false                     0

#define CHAR_NULL                 ((char)0x0)
#define CHAR_ZERO                 0x30
#define CHAR_a                    0x61
#define CHAR_SLASH                '/'

#define printf_vga_clear          screen_monitor_clear

#define kassert(ex)               assert_complain(#ex, __FILE__, __FUNCTION__, __LINE__, (bool)(ex))
#define kassert_not_reached(msg)  assert_complain(msg, __FILE__, __FUNCTION__, __LINE__, false)
#define KERNEL_PANIC(msg)         kassert_not_reached(msg)

#define BIT_SET                   1
#define BIT_CLEAR                 0
#define FRAME_BITMAP_SET          BIT_SET
#define FRAME_BITMAP_CLEAR        BIT_CLEAR
#define PAGE_SIZE                 0x1000
#define PAGE_MASK                 (PAGE_SIZE - 1)

#define PTR_INVALID               (void *)(-1)
#define INDEX_INVALID             (-1)
#define LIMIT_INVALID             (-1)
#define SIZE_INVALID              (uint32)(-1)
#define ADDR_INVALID              (ptr_t)(-1)
#define MEMORY_INVALID            0u
#define FRAME_INVALID             ADDR_INVALID
#define INODE_INVALID             (-1)
#define COUNT_INVALID             (-1)

#define IS_SIZE_INVALID_P(s)      ((s) == SIZE_INVALID ? true : false)

#define ARRAY_CNT_OF(a)           (sizeof(a) / sizeof(a[0]))
#define BIT_WIDTH(t)              (sizeof(t) * 8)
#define U32_BIT_GET(x, idx)       ((uint32)(x) >> (idx) & 0x1)
#define U32_BITS_GET(x, s, len)   (((uint32)(x) >> (s)) & ((0x1 << (len)) - 1))
#define U8_BIT_GET(x, idx)        ((uint8)(x) >> (idx) & 0x1)
#define U8_BIT_SET(x, idx)        ((x) = (uint8)(x) | (uint8)(0x1 << (idx)))
#define U8_BIT_CLEAR(x, idx)      ((x) = (uint8)(x) & ~(uint8)(0x1 << (idx)))

#define PAGE_ALIGNED_P(p)         (((ptr_t)p & PAGE_MASK) == 0 ? true : false)
#define PAGE_UNALIGNED_P(p)       (!PAGE_ALIGNED_P(p))
#define PAGE_ALIGN(p)             ((p) = ((p) & ~PAGE_MASK) + PAGE_SIZE)

#define RETURN_IF_TRUE(x)         if ((x)) { return ; }
#define RETURN_IF_FALSE(x)        if (!(x)) { return ; }

#define CONTAINER_OF(p, t, m)     ((t *)((ptr_t)(p) - (ptr_t)(&((t *)0)->m)))

#endif

