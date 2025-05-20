/* --------------------------------------------------------------
   Application: Spacecraft Telemetry Stable Operation Demo
   Class: Real Time Systems - Su 2025
   Behavior:
     - Telemetry Broadcast Task (high priority) prints every ~1 second
     - Thruster Status Task (low priority) toggles LED every ~550ms
     - Both tasks use vTaskDelay with pdMS_TO_TICKS
---------------------------------------------------------------*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define THRUSTER_LED_PIN GPIO_NUM_4

#define TASK_STACK_SIZE 2048
#define THRUSTER_TASK_PRIORITY 1
#define TELEMETRY_TASK_PRIORITY 2

// -------- Thruster Status Indicator Task --------
void thruster_status_task(void *pvParameters) {
    gpio_reset_pin(THRUSTER_LED_PIN);
    gpio_set_direction(THRUSTER_LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(THRUSTER_LED_PIN, 1);
        printf("Thruster Indicator ON at %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(250));  // ON for 250ms

        gpio_set_level(THRUSTER_LED_PIN, 0);
        printf("Thruster Indicator OFF at %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(300));  // OFF for 300ms
    }
}

// -------- Telemetry Broadcast Task --------
void telemetry_broadcast_task(void *pvParameters) {
    while (1) {
        printf("Telemetry OK — Time = %lu ms\n",
               (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(1000));  // Every 1 second
    }
}

// -------- Main Entry Point --------
void app_main() {
    xTaskCreate(thruster_status_task, "Thruster Status Task", TASK_STACK_SIZE, NULL,
                THRUSTER_TASK_PRIORITY, NULL);

    xTaskCreate(telemetry_broadcast_task, "Telemetry Task", TASK_STACK_SIZE, NULL,
                TELEMETRY_TASK_PRIORITY, NULL);
}
