#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "growR303.h"

static void task(void *arg)
{
    static const char *TASK_TAG = "Main";
    esp_log_level_set(TASK_TAG, ESP_LOG_INFO);

    growr303_init();

    uint8_t match_id;
    err_t err;

    while (1) {

        ESP_LOGI(TASK_TAG, "Adding finger image. Place finger on sensor.");
        while(false == is_finger_on_sensor());
        ESP_LOGI(TASK_TAG, "Sensor detected a finger");

        if(gen_char_file(GROW_R303_CHAR_BUF_1) == ERR_OK){
            ESP_LOGI(TASK_TAG, "Char File 1 generated.");
        }

        // Wait for finger to be lifted off
        ESP_LOGI(TASK_TAG, "Lift the finger off the sensor");
        while(true == is_finger_on_sensor());

        // Place finger again
        ESP_LOGI(TASK_TAG, "Place the same finger on the sensor");
        do {
            err = gen_finger_img();
            vTaskDelay(1000 / portTICK_PERIOD_MS);    
        } while(err != ERR_OK);

        if(gen_char_file(GROW_R303_CHAR_BUF_2) == ERR_OK){
            ESP_LOGI(TASK_TAG, "Char File 2 generated.");
        }

        // Wait for finger to be lifted off
        ESP_LOGI(TASK_TAG, "Lift the finger off the sensor");
        do {
            err = gen_finger_img();
            vTaskDelay(1000 / portTICK_PERIOD_MS);    
        } while(err == ERR_OK);

        if(gen_tmplt_file() == ERR_OK)
        {
            if(save_tmplt_file(GROW_R303_CHAR_BUF_1, 1) == ERR_OK)
            {
                ESP_LOGI(TASK_TAG, "Finger image saved");
            }
        }

        while(1) {
            err = ERR_UNKOWN;
            ESP_LOGI(TASK_TAG, "Place finger for verification");
            do {
                err = gen_finger_img();
                vTaskDelay(1000 / portTICK_PERIOD_MS);    
            } while(err != ERR_OK);

            if(gen_char_file(GROW_R303_CHAR_BUF_1) == ERR_OK){
                ESP_LOGI(TASK_TAG, "Char File 1 generated.");
            }

            if(gen_tmplt_file() == ERR_OK)
            {
                if(search_tmplt(GROW_R303_CHAR_BUF_1, &match_id) == ERR_OK)
                {
                    ESP_LOGI(TASK_TAG, "Matched");
                }
                else 
                    ESP_LOGI(TASK_TAG, "Does not match");
            }
            do {
                err = gen_finger_img();
                vTaskDelay(1000 / portTICK_PERIOD_MS);    
            } while(err == ERR_OK);

            vTaskDelay(3000 / portTICK_PERIOD_MS);
            ESP_LOGI(TASK_TAG, "Looop end");
        }
    }
}

void app_main(void)
{
    xTaskCreate(task, "task", 4096, NULL, 10, NULL);
}
