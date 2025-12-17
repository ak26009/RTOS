#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TimerHandle_t tim1;
TaskHandle_t t1;

void tim_callb(TimerHandle_t t1)
{
  printf("Timer fireee!!\n");
}

void task1(void *data)
{
  
  while(1)
  {
      printf("In task 1\n");
      xTimerStart(tim1,portMAX_DELAY);
      vTaskDelete(t1);
  }
}

void app_main(void)
{
  tim1 = xTimerCreate("time",pdMS_TO_TICKS(2000),pdFALSE,0,tim_callb);
  xTaskCreatePinnedToCore(task1,"ak",2048,NULL,3,&t1,1);
}
