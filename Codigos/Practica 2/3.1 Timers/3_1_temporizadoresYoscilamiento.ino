#define FRECTIMERLED 1000000
#define FRECTIMEROSC 1000000
#define PINLED 4
#define PINLA 5

volatile bool flagLed = false;
volatile bool flagLa = false;

bool estadoLed = false;
bool estadoLa = false;

void IRAM_ATTR ISR_timerLed()  
{ 
  flagLed=!flagLed;
} 

void IRAM_ATTR ISR_timerLa()  
{ 
  flagLa=!flagLa;
} 
hw_timer_t *temporizadorLed = NULL;
hw_timer_t *temporizadorLA = NULL;


 

void setup() 
{   
  Serial.begin(115200);

  pinMode(PINLED,OUTPUT);
  pinMode(PINLA,OUTPUT);

  temporizadorLed = timerBegin(FRECTIMERLED);             
  if (temporizadorLed != nullptr) 
  { 
    timerAttachInterrupt(temporizadorLed, &ISR_timerLed); //registra ISR_Timer 
    timerAlarm(temporizadorLed, 1000000, true, 0);      
    //establece la periodicidad de la INT 
    timerStart(temporizadorLed); 
  } 

  temporizadorLA = timerBegin(FRECTIMEROSC);             
  if (temporizadorLA != nullptr) 
  { 
    timerAttachInterrupt(temporizadorLA, &ISR_timerLa); //registra ISR_Timer 
    timerAlarm(temporizadorLA, 1140, true, 0);      
    //establece la periodicidad de la INT 
    timerStart(temporizadorLA); 
  } 

} 

unsigned long l_inicio = micros();

void loop() 
{ 
  if(flagLed)
  {
    estadoLed=!estadoLed;
    Serial.printf("%d ms --> Estado led: %d\n",l_inicio-micros(),estadoLed);
    digitalWrite(PINLED,estadoLed);
    flagLed=0;
  }

   if(flagLa)
  {
    estadoLa=!estadoLa;
    digitalWrite(PINLA,estadoLa);
    flagLa=0;
  }

} 