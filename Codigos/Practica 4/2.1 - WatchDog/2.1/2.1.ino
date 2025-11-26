#include <esp_task_wdt.h>

#define BOTON_BOOT 0 
#define TIEMPO_RESET 10
#define FACTOR_ESCALADO_TIEMPO 1000

volatile bool botonPulsado = false; 

void IRAM_ATTR gestorInterrupciones()
{
  botonPulsado = true;
}

void resetearWatchDog()
{
  Serial.printf("%lu WatchDog reseteado\n", millis());
  esp_task_wdt_reset();
}

void setup() {
  Serial.begin(115200);
  Serial.printf("%lu Microcontrolador reiniciado\n", millis()); 

  pinMode(BOTON_BOOT, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(BOTON_BOOT), gestorInterrupciones, FALLING); 

  // Configuración WDT
  esp_task_wdt_config_t twdt_config =
  {
    .timeout_ms     = TIEMPO_RESET * FACTOR_ESCALADO_TIEMPO,
    .idle_core_mask = 0,
    .trigger_panic  = true
  };

  esp_task_wdt_reconfigure(&twdt_config);
  esp_task_wdt_add(NULL); 
}

void loop() {
  if (botonPulsado) {
    Serial.printf("%lu Botón pulsado (xestionado en loop)\n", millis());
    
    resetearWatchDog(); 
    
    botonPulsado = false;
  }


  
}