
#define LED_VERDE 5

#define LED_ROJO 4
#define BOTON_BOOT 0 

int estadoBotonPrevio = HIGH;   
bool estadoLed = LOW;           

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BOTON_BOOT, INPUT_PULLUP);
  digitalWrite(LED_VERDE, estadoLed);
}

void loop() {
    
  digitalWrite(LED_ROJO, HIGH);
  delay(200);
  digitalWrite(LED_ROJO, LOW);
  delay(200);

  int estadoBoton = digitalRead(BOTON_BOOT);

  if (estadoBotonPrevio == HIGH && estadoBoton == LOW) {
    estadoLed = !estadoLed;
    digitalWrite(LED_VERDE, estadoLed);
  }

  estadoBotonPrevio = estadoBoton; 
}


