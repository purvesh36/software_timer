
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* Define two timers */
static struct k_timer timer1;
static struct k_timer timer2;

/* Define a counter to track 30 seconds */
static int counter = 0;

/* Timer 1 callback function */
void timer1_expiry_function(struct k_timer *timer_id)
{
    printk("Timer 1 expired! Running function A... [%d sec]\n", counter + 1);
    counter++;

    /* After 30 seconds, stop Timer 1 and start Timer 2 */
    if (counter >= 30)
    {
        printk("Stopping Timer 1 and starting Timer 2...\n");
        k_timer_stop(&timer1);
        k_timer_start(&timer2, K_NO_WAIT, K_SECONDS(2));
    }
}

/* Timer 2 callback function */
void timer2_expiry_function(struct k_timer *timer_id)
{
    printk("Timer 2 expired! Running function B...\n");
}

void main(void)
{
    printk("Starting controlled function timer example...\n");

    /* Initialize the timers */
    k_timer_init(&timer1, timer1_expiry_function, NULL);
    
    k_timer_init(&timer2, timer2_expiry_function, NULL);

    /* Start Timer 1 immediately (fires every 1 second) */
    k_timer_start(&timer1, K_NO_WAIT, K_SECONDS(1));

    while (1)
    {
        k_sleep(K_FOREVER); /* Keep main thread alive */
    }
}