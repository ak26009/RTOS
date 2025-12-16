#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t t1,t2;

void my_fun1(void *data)
{   
    int para = *((int*)data);
    while(1)
    {
    UBaseType_t a;
    a = uxTaskPriorityGet(t1);
    printf("In my fun 1 prior = %d data = %d\n",a,para);
    vTaskDelay(pdMS_TO_TICKS(2000));
    } 
    vTaskDelete(t1);
}

void my_fun2(void *data)
{
    int para = *((int*)data);
    while(1)
    {
        UBaseType_t b;
        b = uxTaskPriorityGet(t2);
        printf("In my fun 2 prior = %d data = %d\n",b,para);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    vTaskDelete(t2); 
}

void app_main(void)
{
    TaskHandle_t mainTask = xTaskGetCurrentTaskHandle();    
    UBaseType_t pri = uxTaskPriorityGet(mainTask);
    
    static int one = 10 ;
    static int two = 20;

    printf("app_main priority = %u\n", pri);
    xTaskCreatePinnedToCore(my_fun1,"ak",1024,(void*)&one,7,&t1,1);
    xTaskCreatePinnedToCore(my_fun2,"pr",1024,(void*)&two,8,&t2,1);
}
