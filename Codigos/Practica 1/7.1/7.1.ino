
#define LED_VERDE 5
#define LED_ROJO 4
#define BOTON_BOOT 0 

 
bool estadoLed = LOW;    

void IRAM_ATTR inter(){

    estadoLed = !estadoLed;
    digitalWrite(LED_VERDE, estadoLed);

}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, estadoLed);
  attachInterrupt(BOTON_BOOT , inter,FALLING );
}


void loop() {
    
  digitalWrite(LED_ROJO, HIGH);
  delay(200);
  digitalWrite(LED_ROJO, LOW);
  delay(200);




  
}


