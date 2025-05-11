#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define GPIO_BUZZER_PIN 32 // GPI32

// Define notes and frequencies.
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define REST 0

static const int melody[] = {
    NOTE_E5, -1, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5, REST, NOTE_G5,
    REST, REST, REST, NOTE_G4, REST, REST, REST, NOTE_C5, -1, NOTE_G4,
    REST, NOTE_E4, REST, NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, REST, NOTE_F5, NOTE_G5, REST, NOTE_E5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, REST, NOTE_C5, -1, NOTE_G4, REST, NOTE_E4, REST,
    NOTE_A4, REST, NOTE_B4, REST, NOTE_AS4, NOTE_A4, REST, NOTE_G4, NOTE_E5, NOTE_G5,
    NOTE_A5, REST, NOTE_F5, NOTE_G5, REST, NOTE_E5, REST, NOTE_C5, NOTE_D5, NOTE_B4, REST
};

static const int durations[] = {
    5, 5, 5, 2, 5, 2, 5, 5, 2, 7,
    7, 7, 7, 5, 5, 5, 5, 5, 5, 2,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
};

_Static_assert(sizeof(melody) == sizeof(durations), "size of durations and melody arrays don't match");

void playNoteTask(void *parameters) {
    // Extract the note duration from the task parameter.
    const int noteDuration = *((int*)parameters); 

    // Wait for the note duration.
    vTaskDelay(pdMS_TO_TICKS(noteDuration)); 

    // Stop PWM.
    ledc_stop(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0); 

    // Delete the task.
    vTaskDelete(NULL); 
}

void playTone(int frequency, int duration) {
    if (frequency != REST) {
        // Set PWM frequency.
        ledc_set_freq(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, frequency); 

        // Set duty cycle to 50%.
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 255 / 2); 

        // Update PWM duty cycle.
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0); 

        // Create task to stop PWM after note duration.
        xTaskCreate(playNoteTask, "playNoteTask", 1024, (void*)&duration, 1, NULL);
    }
}

void playMarioTheme() {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        int noteDuration = durations[i] * 50;

        playTone(melody[i], noteDuration);

        // Add a brief pause between notes.
        vTaskDelay((noteDuration + 50) / portTICK_PERIOD_MS); 
    }
}

void app_main(void) {
    // Configure buzzer pin as output.
    gpio_set_direction(GPIO_BUZZER_PIN, GPIO_MODE_OUTPUT);

    ledc_timer_config_t timerConfig = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 1000, // 1 kHz.
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_USE_APB_CLK, // Use the APB clock as the source.
    };

    ledc_timer_config(&timerConfig);

    ledc_channel_config_t channelConfig = {
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .gpio_num = GPIO_BUZZER_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_sel = LEDC_TIMER_0,
        .hpoint = 0,
        .intr_type = LEDC_INTR_DISABLE
    };

    ledc_channel_config(&channelConfig);

    while (1) {
        playMarioTheme();

        // Wait for 3 seconds.
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}