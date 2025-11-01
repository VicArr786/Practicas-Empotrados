#define LED_VERDE 5
#define LED_ROJO 4
#define BOTON_BOOT 0 

 
bool estadoLed = LOW;    
volatile int vecespulsado=0;
volatile long l_ultimaActivacion=0;

void IRAM_ATTR inter(){
  vecespulsado++;
  long l_activacionNueva = millis();
 
  Serial.printf("[%d]PULSADOR ACTIVO, vecesactivado : %d \n " ,l_activacionNueva-l_ultimaActivacion ,vecespulsado);

 l_ultimaActivacion = l_nuevaActivacion;
}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, estadoLed);
  attachInterrupt(BOTON_BOOT , inter,FALLING );
  Serial.begin(9600,SERIAL_8N1);
}


void loop() {
    
  digitalWrite(LED_ROJO, HIGH);
  delay(200);
  digitalWrite(LED_ROJO, LOW);
  delay(200);
  
}
