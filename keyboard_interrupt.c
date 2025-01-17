#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

// IRQ number for the keyboard
#define KEYBOARD_IRQ 1

// Interrupt handler function
static irqreturn_t keyboard_irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "Avinash: Keyboard interrupt received!\n");
    return IRQ_HANDLED; // Successfully handled the interrupt
}

// Module initialization
static int __init keyboard_interrupt_init(void)
{
    int result;
    printk(KERN_INFO "Avinash: Initializing the Keyboard Interrupt Driver\n");

    // Request the IRQ line for keyboard interrupt
    result = request_irq(KEYBOARD_IRQ, keyboard_irq_handler, IRQF_SHARED,
                         "keyboard_interrupt_driver", (void *)keyboard_irq_handler);
    if (result) {
        printk(KERN_ERR "Avinash: Failed to request IRQ %d, error: %d\n", KEYBOARD_IRQ, result);
        return result;
    }

    printk(KERN_INFO "Avinash: Keyboard Interrupt Driver successfully loaded\n");
    return 0;
}

// Module cleanup function
static void __exit keyboard_interrupt_exit(void)
{
    free_irq(KEYBOARD_IRQ, (void *)keyboard_irq_handler); // Release the IRQ
    printk(KERN_INFO "Avinash: Keyboard Interrupt Driver unloaded\n");
}

// Register module initialization and exit functions
module_init(keyboard_interrupt_init);
module_exit(keyboard_interrupt_exit);

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Avinash");
MODULE_DESCRIPTION("Keyboard Interrupt Driver");
