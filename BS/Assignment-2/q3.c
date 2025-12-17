task 1 resume -> task 2 resume -> task3 resume -> task 1


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t t1,t2,t3;

void task1(void *data)
{
  while(1)
  {
      printf("In task 1\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
      vTaskResume(t2);
      vTaskSuspend(NULL);
  }
}

void task2(void *data)
{
  vTaskSuspend(NULL);
  while(1)
  { 
      printf("In task 2\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
      vTaskResume(t3);
      vTaskSuspend(NULL);
  }
}

void task3(void *data)
{
  vTaskSuspend(NULL);
  while(1)
  {
      printf("In task 3\n");
      vTaskDelay(pdMS_TO_TICKS(2000));
      vTaskResume(t1);
      vTaskSuspend(NULL);
  }
}

void app_main(void)
{
  xTaskCreatePinnedToCore(task1,"ak",2048,NULL,3,&t1,1);
  xTaskCreatePinnedToCore(task2,"ak1",2048,NULL,6,&t2,1);
  xTaskCreatePinnedToCore(task3,"ak2",2048,NULL,7,&t3,1);
}
