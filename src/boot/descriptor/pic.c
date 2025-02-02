/*
 * End of interrupt
 */
void
pic_send_eoi(uint32 irq)
{
    kassert(irq < 16);

    if (irq >= 8) {
        io_bus_byte_write(PIC_SLAVE_CMD, PIC_CMD_EOI);
    }

    io_bus_byte_write(PIC_MASTER_CMD, PIC_CMD_EOI);
}

static inline void
pic_remap(void)
{
    uint8 mask_master;
    uint8 mask_slave;

    asm volatile ("cli\n\t"); /* disable maskable interrupt */

    /* Save current IRQ mask */
    mask_master = io_bus_byte_read(PIC_MASTER_DATA);
    mask_slave = io_bus_byte_read(PIC_SLAVE_DATA);

    /* Initialize Master and Slave PIC */
    io_bus_byte_write(PIC_MASTER_CMD, PIC_CMD_INIT);
    io_bus_byte_write(PIC_SLAVE_CMD, PIC_CMD_INIT);

    /* Set Master and Slave PIC offset */
    io_bus_byte_write(PIC_MASTER_DATA, PIC_MASTER_REMAP_OFFSET);
    io_bus_byte_write(PIC_SLAVE_DATA, PIC_SLAVE_REMAP_OFFSET);

    /* Tell Master PIC there is a slave PIC at IRQ2 */
    io_bus_byte_write(PIC_MASTER_DATA, 4);
    /* Tell Slave PIC its cascade identity 0x2 */
    io_bus_byte_write(PIC_SLAVE_DATA, 2);

    io_bus_byte_write(PIC_MASTER_DATA, PIC_8086);
    io_bus_byte_write(PIC_SLAVE_DATA, PIC_8086);

    /* Restore saved IRQ mask */
    io_bus_byte_write(PIC_MASTER_DATA, mask_master);
    io_bus_byte_write(PIC_SLAVE_DATA, mask_slave);

    asm volatile ("sti\n\t"); /* enable maskable interrupt */
}

