#define pinRojo 5
#define pinVerde 5
void setup() {

  pinMode(pinVerde,OUTPUT);

}

void loop() {

  digitalWrite(pinVerde,HIGH);
  delay(500);
  digitalWrite(pinVerde,LOW);
  delay(500);

}
