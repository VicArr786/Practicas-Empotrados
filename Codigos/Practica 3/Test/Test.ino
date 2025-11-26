const int PIN_LED= 4;   
const int PIN_BOOT= 0; 
const int FREQ_MIN_HZ= 2;  
const int FREQ_MAX_HZ= 5;

hw_timer_t* timer = nullptr;
volatile bool ledState = false;
volatile bool btnEvent = false;       
volatile uint32_t lastBtnMs = 0;
const uint32_t DEBOUNCE_MS = 150;

int currentHz = FREQ_MIN_HZ;
volatile uint32_t penultimaPulsacion=0;



void setBlinkFrequency(int hz) {
  if (hz < 2) hz = 2;
  uint64_t half_us = 500000 / hz;
  timerAlarm(timer, half_us, true, 0); 
}


void ARDUINO_ISR_ATTR onTimer() {
  ledState = !ledState;
  digitalWrite(PIN_LED, ledState );
}


void ARDUINO_ISR_ATTR onBoot() {
  uint32_t now = millis();
  if (now - lastBtnMs >= DEBOUNCE_MS) {
    penultimaPulsacion = lastBtnMs;
    btnEvent = true;
    lastBtnMs = now;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_BOOT, INPUT_PULLUP); 
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  setBlinkFrequency(currentHz);

  attachInterrupt(PIN_BOOT, onBoot, FALLING);
  float period_ms = 1000.0f / currentHz;
  float half_ms   = period_ms / 2.0f;
  Serial.printf("Boton Presionado -> Hz = %d | Tiempo transcurido %d \n" ,currentHz,lastBtnMs-penultimaPulsacion );
}

void loop() {
  if (btnEvent) {
    btnEvent = false;
    currentHz=(currentHz==FREQ_MIN_HZ)?FREQ_MAX_HZ:FREQ_MIN_HZ;
    if (currentHz > FREQ_MAX_HZ) {
      currentHz = FREQ_MIN_HZ;  
    }
    setBlinkFrequency(currentHz);
    float period_ms = 1000.0f / currentHz;
    float half_ms   = period_ms / 2.0f;
    Serial.printf("Boton Presionado -> Hz = %d | Tiempo transcurido %d \n" ,currentHz,lastBtnMs-penultimaPulsacion );
  }
}
