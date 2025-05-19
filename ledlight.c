/* --------------------------------------------------------------
   Application: LED Timing Violation Demo
   Class: Real Time Systems - Su 2025
   Behavior:
     - Console Print Task (high priority) runs in tight loop (no delay)
     - LED Blink Task (low priority) tries to blink every 550ms
     - LED will miss its timing due to being starved by print task
---------------------------------------------------------------*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

#define TASK_STACK_SIZE 2048
#define BLINK_TASK_PRIORITY 1
#define PRINT_TASK_PRIORITY 2  // Higher than LED

// -------- LED Blink Task Function (low priority) --------
void led_blink_task(void *pvParameters) {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_PIN, 1);
        printf("LED ON at %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(250));  // ON for 250ms

        gpio_set_level(LED_PIN, 0);
        printf("LED OFF at %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(300));  // OFF for 300ms
    }
}

// -------- Console Print Task (CPU hog) --------
void console_print_task(void *pvParameters) {
    while (1) {
        printf("Telemetry OK at %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        // ❌ No delay — this hogs the CPU at priority 2
    }
}

// -------- Main Entry Point --------
void app_main() {
    // Create the low-priority LED task
    xTaskCreate(led_blink_task, "LED Blink Task", TASK_STACK_SIZE, NULL,
                BLINK_TASK_PRIORITY, NULL);

    // Create the high-priority CPU-hogging task
    xTaskCreate(console_print_task, "Console Print Task", TASK_STACK_SIZE, NULL,
                PRINT_TASK_PRIORITY, NULL);
}
