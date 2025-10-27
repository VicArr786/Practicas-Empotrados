#define LEDPIN 4
#define FRECBASE 100
#define RESOLUCION 12
#define BOTON_BOOT 0

volatile int vecesPulsado = 5;

const float arrTiempos[] = {1.00, 0.80, 0.60, 0.40, 0.20, 0.0};

void IRAM_ATTR IRS_botonPulsado()
{
  vecesPulsado -=1;
  vecesPulsado=(vecesPulsado==-1)?4:vecesPulsado;
  Serial.printf("[%d] Estado contador: %d, duty asignado: %f\n",millis(), vecesPulsado,*(arrTiempos+vecesPulsado));
}

void setup()
{
  Serial.begin(115200);
  pinMode(BOTON_BOOT,INPUT_PULLUP);

  attachInterrupt
  (
    BOTON_BOOT
    ,IRS_botonPulsado
    ,FALLING
  );

  ledcAttach(LEDPIN,FRECBASE,RESOLUCION);

}

void loop()
{
  ledcWrite(LEDPIN,4095*arrTiempos[vecesPulsado]);
  delay(1);
}
