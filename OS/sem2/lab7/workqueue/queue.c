#include <linux/module.h> // module_init, ...
#include <linux/kernel.h> // printk
#include <linux/init.h> //__init, __exit
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/time.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("chudik");

#define SHARED_IRQ 1
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param( irq, int, S_IRUGO );
static struct timeval time;
struct workqueue_struct *wq;
void hardwork_function(struct work_struct *work);

DECLARE_WORK( hardwork, hardwork_function );

/* Bottom Half Function */
void hardwork_function(struct work_struct *work) {
    printk(KERN_INFO "[WQ] data: %d", work->data);
	    do_gettimeofday(&time);
	    printk("TIME: %.2lu:%.2lu:%.2lu: \r\n",
			   (time.tv_sec / 3600) % (24),
			   (time.tv_sec / 60) % (60),
			  time.tv_sec % 60);
    return;
}

static irqreturn_t my_interrupt( int irq, void *dev_id ) {
    if (irq == 1) {
        irq_counter++;
        printk( KERN_INFO "[INTERRUPT] In the ISR: counter = %d\n", irq_counter );
        queue_work( wq, &hardwork );
        return IRQ_HANDLED;
    }   
    else {
        return IRQ_NONE;
    }
}

static int __init my_wokqueue_init(void) {
	if( request_irq( irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_interrupt ) )
    	return -1;
    printk( KERN_INFO "[INTERRUPT] Successfully loading ISR handler on IRQ %d\n", irq );
    //wq = create_workqueue( "my_queue" );
    wq = alloc_workqueue("my_queue", WQ_UNBOUND, 0);    
    if ( wq ) {
        printk(KERN_INFO "[MODULE] Workqueue created.\n");
    }
    else {
        printk(KERN_INFO "[MODULE] Workqueue is not created.\n");
    }

	printk(KERN_INFO "[MODULE] Module is now loaded.\n");
	return 0;
}

static void __exit my_wokqueue_exit(void) {
    flush_workqueue( wq );
    destroy_workqueue( wq );
	synchronize_irq( irq );
   	free_irq( irq, &my_interrupt );
   	printk( KERN_INFO "[INTERRUPT] Successfully unloading, irq_counter = %d\n", irq_counter );
	printk(KERN_INFO "[MODULE] Module is now unloaded.\n");
  	return;
}

module_init(my_wokqueue_init);
module_exit(my_wokqueue_exit);
