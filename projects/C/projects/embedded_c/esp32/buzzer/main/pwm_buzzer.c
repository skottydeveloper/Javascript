#include <stdio.h>

#include "esp_system.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Buzzer, LEDC, and PWM configuration constants.
#define BUZZER_PIN 32
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define PWM_FREQUENCY 1000

// Task configuration constants.
#define TASK_STACK_SIZE 2048
#define TASK_PRIORITY_1 1
#define TASK_PRIORITY_2 2
#define BUZZER_ON_DURATION_MS 1000
#define TASK_DELAY_MULTIPLIER_MS_1 250
#define TASK_DELAY_MULTIPLIER_MS_2 125

// Declare a semaphore handle for the mutex.
SemaphoreHandle_t buzzer_mutex;

// The buzzer_task function is designed to be run in a separate FreeRTOS task.
void buzzer_task(void *arg) {
    // Get the task number from the argument passed to the function.
    int task_num = (int)arg;

    // Main loop of the task.
    while (1) {
        // Try to take the mutex for buzzer access. Wait indefinitely until it is available.
        if (xSemaphoreTake(buzzer_mutex, portMAX_DELAY) == pdTRUE) {
            // Set the duty cycle based on the task number.
            int duty = (task_num == 1) ? 4186 : 2093;

            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL);

            // Determine the "esp_rom_delay" value based on the task number.
            int esp_rom_delay = (task_num > 1) ? TASK_DELAY_MULTIPLIER_MS_2 : TASK_DELAY_MULTIPLIER_MS_1;

            // Use the buzzer for a specific duration (1 second).
            vTaskDelay(pdMS_TO_TICKS(BUZZER_ON_DURATION_MS));

            // Turn off the buzzer.
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL, 0);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL);

            // Release the mutex after using the buzzer, allowing other tasks to take control of it.
            xSemaphoreGive(buzzer_mutex);

            // Wait for the calculated delay period before trying to take the mutex again.
            vTaskDelay(esp_rom_delay);
        }
    }
}

void app_main(void) {
    // Configure LEDC timer settings.
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,      // Set the LEDC speed mode.
        .duty_resolution = LEDC_TIMER_13_BIT,    // Set the duty resolution (13 bits).
        .timer_num = LEDC_TIMER,                 // Set the LEDC timer number.
        .freq_hz = PWM_FREQUENCY,                // Set the PWM frequency (1000 Hz).
        .clk_cfg = LEDC_AUTO_CLK,                // Set the LEDC clock source to auto.
    };

    // Apply the LEDC timer configuration.
    ledc_timer_config(&ledc_timer);

    // Configure LEDC channel settings.
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,  // Set the LEDC speed mode.
        .channel = LEDC_CHANNEL,             // Set the LEDC channel number.
        .timer_sel = LEDC_TIMER,             // Set the LEDC timer number.
        .intr_type = LEDC_INTR_DISABLE,      // Disable LEDC interrupt.
        .gpio_num = BUZZER_PIN,              // Set the GPIO pin for the buzzer.
        .duty = 0,                           // Set the initial duty cycle to 0 (off).
        .hpoint = 0,                         // Set the initial hpoint value (not used in this case).
    };

    // Apply the LEDC channel configuration.
    ledc_channel_config(&ledc_channel);

    // Create the mutex for buzzer access. This is a binary semaphore used for mutual exclusion.
    buzzer_mutex = xSemaphoreCreateMutex();

    /* Create two tasks with different priorities. Task 1 has a higher priority (2) than Task 2 (1).
    The task with a higher priority will have a higher chance of getting access to the buzzer first. */
    xTaskCreate(buzzer_task, "Buzzer Task 1", TASK_STACK_SIZE, (void *)1, TASK_PRIORITY_1, NULL);
    xTaskCreate(buzzer_task, "Buzzer Task 2", TASK_STACK_SIZE, (void *)2, TASK_PRIORITY_2, NULL);
}