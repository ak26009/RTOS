Task 1 resume task 2

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t t1,t2;

void task1(void *data)
{
  while(1)
  {
    for(int i=0 ; i<5 ; i++)
    {
      printf("In task 1\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
      vTaskResume(t2);
    }
    vTaskDelete(NULL);
  }
}

void task2(void *data)
{
  vTaskSuspend(NULL); 
  while(1)
  { 
    for(int i=0 ; i<5 ; i++)
    {
      printf("In task 2\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
    vTaskDelete(NULL);
  }
}

void app_main(void)
{
  xTaskCreatePinnedToCore(task1,"ak",2048,NULL,6,&t1,1);
  xTaskCreatePinnedToCore(task2,"ak1",2048,NULL,8,&t2,1);
}
