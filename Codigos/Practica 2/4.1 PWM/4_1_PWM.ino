#define LEDPIN 4
#define FRECBASE 100
#define RESOLUCION 12
#define BOTON_BOOT 0

volatile int vecesPulsado = 4;

void IRAM_ATTR IRS_botonPulsado()
{
  vecesPulsado -=1;
  vecesPulsado=(vecesPulsado==0)?4:vecesPulsado;
//  Serial.printf("Porcentaje: %lf, Valor a pasar como duty cicle:%d\n",(vecesPulsado/4),(vecesPulsado/4) * (pow(2,RESOLUCION)-1));
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
  // put your main code here, to run repeatedly:
  ledcWrite(LEDPIN,(vecesPulsado/4) * pow(2,RESOLUCION));
  delay(1);

}
