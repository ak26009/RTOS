Message Buffer

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

MessageBufferHandle_t msg;
TaskHandle_t t1,t2;

void task1(void *data)
{
    xMessageBufferSend(msg,"Hello from task1",sizeof("Hello from task1"),portMAX_DELAY);
    printf("Message sending to task 2\n");
    vTaskDelay(pdMS_TO_TICKS(3000));
    vTaskDelete(t1);
}

void task2(void *data)
{
    char rbuff[100];
    xMessageBufferReceive(msg,rbuff,sizeof(rbuff),portMAX_DELAY);
    printf("Message received\n");
    vTaskDelay(pdMS_TO_TICKS(500));
    printf("%s\n",rbuff);
    vTaskDelete(t2);
}

void app_main(void)
{
    msg = xMessageBufferCreate(100);
    xTaskCreatePinnedToCore(task1,"op",2048,NULL,6,&t1,1);
    xTaskCreatePinnedToCore(task2,"op1",2048,NULL,8,&t2,1);
}
