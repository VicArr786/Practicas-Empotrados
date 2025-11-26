#include <cmath>
#define ROJO 0
#define VERDE 1
#define AZUL 2
#define COLORES_MAX 3
#define FRECTIMERLED 1000000


volatile float colorCurrent =0;//0rojo 1verde 2 azul
volatile bool changeColor = 1;

hw_timer_t *temporizadorLed=NULL;

void IRAM_ATTR ISR_TiempoPasado(){
  colorCurrent+=0.01;
  if(colorCurrent >= 1){
    colorCurrent = ROJO;
  }
  changeColor=1;  
}


void cambiarColor(float color){
   const float theta = color * 2.0f * PI;

  float r = 127.5f * (sinf(theta) + 1.0f);
  float g = 127.5f * (sinf(theta + 2.0f * PI / 3.0f) + 1.0f);
  float b = 127.5f * (sinf(theta + 4.0f * PI / 3.0f) + 1.0f);

  // Si tu LED es GRB, usa (g, r, b)
  neopixelWrite(RGB_BUILTIN, (uint8_t)r, (uint8_t)g, (uint8_t)b);
  
}

void setup() {
  Serial.begin(115200);
  temporizadorLed=timerBegin(FRECTIMERLED);
  if(temporizadorLed != nullptr){
    timerAttachInterrupt(temporizadorLed,&ISR_TiempoPasado);
    timerAlarm(temporizadorLed,30000,true,0);
  }
}

void loop() {
  if (changeColor==1){
    cambiarColor(colorCurrent);
    changeColor=false;
  }

}
