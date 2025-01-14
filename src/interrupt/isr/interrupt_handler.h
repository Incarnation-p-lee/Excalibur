#ifndef HAVE_DEFINED_INTERRUPT_HANDLER_H
#define HAVE_DEFINED_INTERRUPT_HANDLER_H

static isr_handler_t isr_handler_array[] = {
    [DIV_BY_Z]           = &isr_0_divide_by_zero_handler,
    [BRK_EXPT]           = &isr_3_breakpoint_handler,
    [INV_OPC_EXPT]       = &isr_6_invalid_opcode_handler,
    [STK_FAL]            = &isr_12_stack_fault_handler,
    [PAGE_FAL]           = &isr_14_paging_fault_handler,

    [IRQ_0_TIMER]        = &irq_0_timer_handler,
    [IRQ_1_KEYBOARD]     = &irq_1_keyboard_handler,
    [IRQ_7_PS]           = &irq_7_handler,

    [IRQ_14_ATA_PRIMARY] = &irq_14_ata_channel_primary,
};

#endif

