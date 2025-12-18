Binary Semaphore

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

TaskHandle_t t1,t2;
SemaphoreHandle_t sem;

void adc(void *d)
{
    printf("ADC : IN Adc waitingh for the data\n");
    printf("Sending Data\n");
    xSemaphoreGive(sem);
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Back to ADC\n");
    vTaskDelete(t1);
}

void proc(void *d)
{
    printf("Waiting for the Data\n");
    xSemaphoreTake( sem,portMAX_DELAY);
    printf("Data Received\n");
    printf("Processing\n");
    vTaskDelete(t2);
}

void app_main(void)
{
    sem = xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore( adc,"ak",2048,NULL,7,&t1,1);
    xTaskCreatePinnedToCore( proc,"ak1",2048,NULL,9,&t2,1);

}
