#include <esp_task_wdt.h>
#include "driver/rtc_io.h"

#define BOTON_BOOT 0 
#define TIEMPO_RESET 10
#define FACTOR_ESCALADO_TIEMPO 1000
#define WAKEUP_GPIO GPIO_NUM_8

volatile short int pulses=0;
volatile RTC_DATA_ATTR short pulsesGlobal=0;
volatile bool modeSleep = false; 
volatile bool botonPulsado = false; 

void IRAM_ATTR gestorInterrupciones()
{
  pulses++;
  pulsesGlobal++;
  botonPulsado=true;

  if(pulses>=10){
    pulses=0;
    modeSleep = true;

  }

}



void setup() {
  Serial.begin(115200);
  Serial.printf("%lu Microcontrolador reiniciado\n", millis()); 

  pinMode(WAKEUP_GPIO, INPUT_PULLUP); 
  pinMode(BOTON_BOOT, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(BOTON_BOOT), gestorInterrupciones, FALLING); 

    esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO,1);
    rtc_gpio_pulldown_en(WAKEUP_GPIO);
    rtc_gpio_pullup_dis(WAKEUP_GPIO);
}

void loop() {
  if (botonPulsado) {
    Serial.printf("%lu Botón pulsado : %d \n", millis(),pulsesGlobal);
    botonPulsado = false;
  }  
  if (modeSleep) {
    Serial.printf("%lu Botón pulsado entrando modo sleep \n", millis());
    esp_deep_sleep_start();
    modeSleep = false;
  }  
}