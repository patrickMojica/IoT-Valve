/*
	Patrick Mojica
	20250128AD Portland, OR, USA, Earth
	Arhizome Technologies LLC
	IoT-Valve Demo
*/
	

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

// Define the button and LED device labels
#define BUTTON1_NODE DT_ALIAS(button1)
#define LED0_NODE DT_ALIAS(led0)

// Get the device pointers for the button and LED
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(BUTTON1_NODE, gpios);
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

// Button press callback
static void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    static bool led_is_on = false;

    // Toggle the LED state
    led_is_on = !led_is_on;
    gpio_pin_set(led0.port, led0.pin, led_is_on);
}

// Main function
int main(void) {
    int ret;

    // Check if the button and LED devices are ready
    if (!device_is_ready(button1.port) || !device_is_ready(led0.port)) {
        printk("Error: Device not ready\n");
        return 0;
    }

    // Configure the button as input
    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
    if (ret < 0) {
        printk("Error: Failed to configure button\n");
        return 0;
    }

    // Configure the LED as output
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Error: Failed to configure LED\n");
        return 0;
    }

    // Set up a callback for button presses
    static struct gpio_callback button_cb;
    gpio_init_callback(&button_cb, button_pressed, BIT(button1.pin));
    gpio_add_callback(button1.port, &button_cb);

    // Enable interrupt on the button pin
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret < 0) {
        printk("Error: Failed to configure button interrupt\n");
        return 0;
    }

    printk("Press Button 1 to toggle GPIO P0.27\n");

    while (1) {
        // Sleep to save power
        k_sleep(K_MSEC(100));
    }
	return 0;
}