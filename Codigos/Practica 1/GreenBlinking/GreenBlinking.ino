#define pinRojo 5
#define pinVerde  
void setup() {
  pinMode(pinRojo,OUTPUT);
  pinMod`e(pinVerde,OUTPUT);

}

void loop() {
  digitalWrite(pinRojo,HIGH);
  delay(500);
  digitalWrite(pinRojo,LOW);
  delay(500);
  digitalWrite(pinVerde,HIGH);
  delay(500);
  digitalWrite(pinVerde,LOW);
  delay(500);

}
