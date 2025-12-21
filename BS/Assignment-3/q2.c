Counting Semaphore

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

TaskHandle_t t1,t2,t3,t4;
SemaphoreHandle_t sem;

void task1(void *d)
{
        printf("task 1\n");
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("Task1 entered critical section\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task1 exiting\n");
        xSemaphoreGive(sem);
        vTaskDelete(t1);
    
}

void task2(void *d)
{
        printf("task 2\n");
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("Task2 entered critical section\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task2 exiting\n");
        xSemaphoreGive(sem);
        vTaskDelete(t2);

}

void task3(void *d)
{
        printf("task 3\n");
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("Task3 entered critical section\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task3 exiting\n");
        xSemaphoreGive(sem);
        vTaskDelete(t3);
}

void task4(void *d)
{
        printf("task 4\n");
        xSemaphoreTake(sem, portMAX_DELAY);
        printf("Task4 entered critical section\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Task4 exiting\n");
        xSemaphoreGive(sem);
        vTaskDelete(t4);
}

void app_main(void)
{
    sem =  xSemaphoreCreateCounting(2,2);
    xTaskCreatePinnedToCore( task1,"ak",2048,NULL,7,&t1,1);
    xTaskCreatePinnedToCore( task2,"ak1",2048,NULL,8,&t2,1);
    xTaskCreatePinnedToCore( task3,"ak2",2048,NULL,9,&t3,1);
    xTaskCreatePinnedToCore( task4,"ak4",2048,NULL,12,&t4,1);
}
