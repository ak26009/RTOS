MESSAGE QUEUUU


#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"

StreamBufferHandle_t stream_buf;
TaskHandle_t t1,t2,t3;

void sender_task(void *data)
{   
    printf("Sender created!\n");
        xStreamBufferSend(stream_buf,"Atharva",strlen("Atharva"),portMAX_DELAY);
        xStreamBufferSend(stream_buf,"Kadam",strlen("Kadam"),portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(2000));
   vTaskDelete(NULL);   
}


void receiver_task(void *data)
{
    printf("Receive waiting !!\n");
        char rx_buffer[50];
        xStreamBufferReceive(stream_buf, rx_buffer, sizeof(rx_buffer), portMAX_DELAY);
        printf("Received: %s\n", rx_buffer);
        vTaskDelete(NULL);  
}

void app_main(void)
{
    stream_buf = xStreamBufferCreate(50, 12);

    xTaskCreatePinnedToCore(sender_task, "sender", 2048, NULL, 5, &t1,1);
    xTaskCreatePinnedToCore(receiver_task, "receiver", 2048, NULL, 12, &t2,1);
}
