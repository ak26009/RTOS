Message Queue

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t msgq;
TaskHandle_t t1,t2,t3,t4;

void temp_task(void *data)
{   
    printf("in temp_task\n");
    int t_d=0;
    while(1){
        t_d++;
        xQueueSend(msgq,&t_d,portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(2000));
}
}


void power_task(void *data)
{   
        printf("in pwr_tsk\n");
 int p_d=100;
    while(1){
        p_d++;
        xQueueSend(msgq,&p_d,portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(2000));
}
}
void proc1(void *data){
        printf("in proc1\n");

while(1){
        int r_b;
        xQueueReceive(msgq,&r_b,portMAX_DELAY);
        printf("%d\n",r_b);
        vTaskDelay(pdMS_TO_TICKS(2000));
}
}
void proc2(void *data){
    printf("in proc2\n");
while(1){
        int r_b;
        xQueueReceive(msgq,&r_b,portMAX_DELAY);
        printf("%d\n",r_b);
        vTaskDelay(pdMS_TO_TICKS(2000));
}
}

void app_main(void)
{
    msgq = xQueueCreate( 4,64 );
    xTaskCreatePinnedToCore(temp_task, "sender", 2048, NULL, 5, &t1,1);
    xTaskCreatePinnedToCore(power_task, "receiver", 2048, NULL, 12, &t2,1);
    xTaskCreatePinnedToCore(proc1, "receiver", 2048, NULL, 10, &t3,1);
    xTaskCreatePinnedToCore(proc2, "receiver", 2048, NULL, 9, &t4,1);
}
