#define PIN_POT 6
#define PIN_AWM 8

typedef struct
{
  int i_limite;
  int i_valor_asociado;
} Nivel;

typedef struct
{
  Nivel *niveles;
  short int si_numero_niveles;
} Leds, *PLeds;

// Niveles globales (no se destruyen al salir de setup)
Nivel niveles_defecto[] = {
  {255, 1023},
  {510, 2047},
  {765, 3071}
};

bool crearLeds(PLeds *st_leds, int n_niveles, Nivel *niveles)
{
  if (st_leds == NULL || niveles == NULL) {
    Serial.printf("Error, estructura no pasada correctamente\n");
    return false;
  }

  Leds *estructura_nueva = (Leds*)malloc(sizeof(Leds));
  if (estructura_nueva == NULL) {
    Serial.printf("Error, sin memoria para Leds\n");
    return false;
  }

  estructura_nueva->si_numero_niveles = n_niveles;
  estructura_nueva->niveles = niveles;    // usamos array global, no se libera

  *st_leds = estructura_nueva;
  return true;
}

Nivel seleccionarNivel(PLeds st_leds, int valor)
{

  Nivel nulo = {valor,valor };//limite / valor asociado

  return nulo; 
}

void matarLeds(PLeds *st_leds, bool niveles_dinamicos)
{
  if (st_leds == NULL || *st_leds == NULL) {
    Serial.printf("Error, estructura no pasada correctamente\n");
    return;
  }

  if (niveles_dinamicos) {
    free((*st_leds)->niveles);
  }
  free(*st_leds);
  *st_leds = NULL;
}

volatile bool flagLectura = false;
adc_continuous_data_t *resultadoLectura = NULL;

void ISR_lectura_analog(void)
{
  flagLectura = true;
}

Leds *miLed = NULL;

uint8_t pines_adc[] = {PIN_POT};

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_POT, ANALOG);
  pinMode(PIN_AWM, OUTPUT);

  analogContinuousSetWidth(12);
  analogContinuousSetAtten(ADC_11db);
  analogContinuous(
      pines_adc,
      1,
      100,
      1000,
      ISR_lectura_analog);

  crearLeds(&miLed, 3, niveles_defecto);

  // Core ESP32 3.x: configurar PWM en PIN_AWM
  ledcAttach(PIN_AWM, 1000, 12);


  analogContinuousStart();
}

void loop()
{
  if (flagLectura == true)
  {
    flagLectura = false;
    if (analogContinuousRead(&resultadoLectura, 0) == true)
    {
      int valor_ADC = resultadoLectura[0].avg_read_raw;
      Nivel n = seleccionarNivel(miLed, valor_ADC);

      ledcWrite(PIN_AWM, n.i_valor_asociado);
      neopixelWrite(RGB_BUILTIN,n.i_valor_asociado/16,0,0);

      float voltaje = valor_ADC * (3.3f / 4095.0f);
      Serial.printf("ADC: %d (%.3f V) | Ciclo: %d\n",
                    valor_ADC, voltaje, n.i_valor_asociado);
    }
  }
}
