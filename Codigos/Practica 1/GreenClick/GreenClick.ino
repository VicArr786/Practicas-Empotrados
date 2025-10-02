#define LED_ROJO 4
#define LED_VERDE 5
#define BOTON_BOOT 0  

void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BOTON_BOOT, INPUT); 
}

void loop() {
  
  digitalWrite(LED_ROJO, HIGH);
  delay(200);
  digitalWrite(LED_ROJO, LOW);
  delay(200);

  int estadoBoton = digitalRead(BOTON_BOOT);
  

  if (estadoBoton == LOW) {
    digitalWrite(LED_VERDE, HIGH); 
  } else {
    digitalWrite(LED_VERDE, LOW); 
  }
}



