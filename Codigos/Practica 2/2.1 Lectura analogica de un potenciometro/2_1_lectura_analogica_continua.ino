#define PIN_LECTURA_ANALOGICA_1 6
#define FRECSAMPLEO 1000//Hz
#define MPC 100//conversiones por lectura

uint8_t pines_adc[] = {PIN_LECTURA_ANALOGICA_1};

adc_continuous_data_t *resultado = NULL;
volatile bool bandera_conversion_terminada = false;

void ARDUINO_ISR_ATTR ISSRATTR_rutinaGestionADC() 
{
  bandera_conversion_terminada = true;
}

void setup()
{
  Serial.begin(115200);

  pinMode(PIN_LECTURA_ANALOGICA_1,ANALOG);

  analogContinuousSetWidth(12); // 12 bits, porque es el máximo de resolución permitida
  analogContinuousSetAtten(ADC_11db);
  analogContinuous
  (
    pines_adc
    , 1
    , MPC
    , FRECSAMPLEO
    , ISSRATTR_rutinaGestionADC 
  );

  analogContinuousStart();
} 

void loop() 
{
  if(bandera_conversion_terminada)
  {
    bandera_conversion_terminada = false;
    if(analogContinuousRead(&resultado,0)==true)
    {
      int raw_ADC = resultado[0].avg_read_raw;
      //Serial.printf("[%d] :  %d\n",millis(),raw_ADC);
            Serial.printf("%d  %d\n",millis(),raw_ADC);

      delay(100);
    }

  }
}
