#define pinRojo 5
#define pinVerde 4 
void setup() {
  pinMode(pinRojo,OUTSPUT);
  pinMode(pinVerde,OUTPUT);

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
