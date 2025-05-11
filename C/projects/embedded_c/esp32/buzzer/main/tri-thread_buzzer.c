#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_rom_sys.h"
#include "esp_system.h"

#define BUZZER_PIN 32 // GPI32
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0

// Declare a semaphore handle for the mutex.
SemaphoreHandle_t buzzer_mutex;

// Declare a queue handle for passing frequency and duration values.
QueueHandle_t buzzer_queue;

// Define a struct for frequency and duration.
typedef struct {
    int frequency;
    int duration;
} buzzer_data_t;

// Configure LEDC timer and channel settings.
void ledc_configuration() {
    // Configure LEDC timer settings.
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER,
        .freq_hz = 1000,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    // Apply the LEDC timer configuration.
    ledc_timer_config(&ledc_timer);

    // Configure LEDC channel settings.
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = BUZZER_PIN,
        .duty = 0,
        .hpoint = 0,
    };

    // Apply the LEDC channel configuration.
    ledc_channel_config(&ledc_channel);
}

// The buzzer_task function generates random frequency and duration values and sends them to the buzzer_control_task.
void buzzer_task(void *arg) {
    // Get the task number from the argument passed to the function.
    int task_num = (int) arg;

    // Calculate the delay period based on the task's number.
    const int delay_period_ms = task_num * 1000;

    // Convert the delay period from milliseconds to ticks.
    TickType_t delay_period_ticks = pdMS_TO_TICKS(delay_period_ms);

    // Main loop of the task.
    while (1) {
        // Generate random frequency and duration values.
        buzzer_data_t buzzer_data;

        buzzer_data.frequency = rand() % 1000 + 1;
        buzzer_data.duration = rand() % 1000 + 1;

        // Acquire the buzzer mutex to protect access to shared variables.
        xSemaphoreTake(buzzer_mutex, portMAX_DELAY);

        // Send a message containing the frequency and duration values to the buzzer control task.
        xQueueSendToBack(buzzer_queue, &buzzer_data, 1000);

        // Release the buzzer mutex to allow other tasks to access the shared variables.
        xSemaphoreGive(buzzer_mutex);

        // Wait for the calculated delay period before generating a new frequency and duration.
        vTaskDelay(delay_period_ticks);
    }
}

// The buzzer_control_task function sets the PWM frequency and duty cycle for the buzzer based on received frequency and duration values.
void buzzer_control_task(void *arg) {
    // Configure the LEDC timer and channel settings.
    ledc_configuration();

    // Main loop of the task.
    while (1) {
        // Wait for a message containing frequency and duration values.
        buzzer_data_t buzzer_data;

        xQueueReceive(buzzer_queue, &buzzer_data, portMAX_DELAY);

        // Set the PWM frequency and duty cycle for the buzzer.
        ledc_set_freq(LEDC_HIGH_SPEED_MODE, LEDC_TIMER, buzzer_data.frequency);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL, (1 << LEDC_TIMER_13_BIT) - 1);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL);

        // Use the buzzer for the specified duration.
        vTaskDelay(pdMS_TO_TICKS(buzzer_data.duration));

        // Turn off the buzzer.
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL, 0);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL);
    }
}

void app_main(void) {
    // Create the mutex for buzzer access. This is a binary semaphore used for mutual exclusion.
    buzzer_mutex = xSemaphoreCreateMutex();

    // Initialize the queue for receiving frequency and duration values.
    buzzer_queue = xQueueCreate(10, sizeof(buzzer_data_t));

    // Create three tasks: two buzzer tasks and one buzzer control task.
    xTaskCreate(buzzer_task, "Buzzer Task 1", 2048, (void *) 1, 2, NULL);
    xTaskCreate(buzzer_task, "Buzzer Task 2", 2048, (void *) 2, 1, NULL);
    xTaskCreate(buzzer_control_task, "Buzzer Control Task", 2048, NULL, 3, NULL);
}