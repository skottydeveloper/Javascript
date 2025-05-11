/* This program demonstrates the use of FreeRTOS tasks and mutexes to control access to a buzzer.
   Two tasks with different priorities are created to generate a 1 kHz square wave signal on the buzzer.
   A mutex is used to ensure that only one task has access to the buzzer at a time. */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define BUZZER_PIN 32 // GPI32

// Define constants for task properties.
#define STACK_SIZE 2048
#define TASK1_PRIORITY 2
#define TASK2_PRIORITY 1
#define TASK1_CORE 0
#define TASK2_CORE 1

// Declare a semaphore handle for the mutex.
SemaphoreHandle_t buzzer_mutex;

/* The buzzer_task function generates a 1 kHz square wave signal on the buzzer.
   It runs in a separate FreeRTOS task and uses a mutex to ensure exclusive access to the buzzer. */
void buzzer_task(void *arg) {
    // Get the task number from the argument passed to the function.
    int task_num = (int) arg;

    // Calculate the delay period based on the task's number.
    int delay_period = (task_num) * 1000 / portTICK_PERIOD_MS;

    // Determine the "esp_rom_delay" value based on the task number.
    int esp_rom_delay = (task_num > 1) ? 250 : 125;

    // Array to store the pin levels (high and low).
    int pin_levels[] = {1, 0};

    // Main loop of the task.
    while (1) {
        // Attempt to take the mutex, waiting indefinitely until it's available.
        if (xSemaphoreTake(buzzer_mutex, portMAX_DELAY) == pdTRUE) {
            // Generate square wave signal at 1 kHz.
            for (int i = 0; i < 1000; i++) {
                // Loop through the pin levels array (high and low)
                for (int j = 0; j < sizeof(pin_levels) / sizeof(pin_levels[0]); j++) {
                    // Set the buzzer pin to the current level from the pin_levels array
                    gpio_set_level(BUZZER_PIN, pin_levels[j]);

                    // Delay for the specified "esp_rom_delay" value.
                    esp_rom_delay_us(esp_rom_delay);
                }
            }

            // Release the mutex after using the buzzer, allowing other tasks to take control of it.
            xSemaphoreGive(buzzer_mutex);

            // Wait for the calculated delay period before trying to take the mutex again.
            vTaskDelay(delay_period);
        }
    }
}

void app_main(void) {
    // Configure buzzer pin as output.
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);

    // Create the mutex for buzzer access. This is a binary semaphore used for mutual exclusion.
    buzzer_mutex = xSemaphoreCreateMutex();

    // Create and pin Task 1 to Core 0 with a higher priority.
    xTaskCreatePinnedToCore(buzzer_task, "Buzzer Task 1", STACK_SIZE, (void *) 1, TASK1_PRIORITY, NULL, TASK1_CORE);

    // Create and pin Task 2 to Core 1 with a lower priority.
    xTaskCreatePinnedToCore(buzzer_task, "Buzzer Task 2", STACK_SIZE, (void *) 2, TASK2_PRIORITY, NULL, TASK2_CORE);
}