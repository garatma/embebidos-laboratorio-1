/*
 * (1) encendido,
 * (2) titilando a 0.5 Hz,
 * (3) titilando a 1 Hz,
 * (4) titilando a 2 Hz,
 * (5) medio segundo encendido y un segundo apagado,
 * (6) apagado.
 */

// variables:
int8_t modo = 1;   // para controlar cómo prender y apagar el led.

void encendido()
{
    digitalWrite(13, HIGH);
    Serial.println(0);
}

// prende el led, espera lo especificado por el primer parámetro. apaga el led
// y espera lo especificado por el segundo parámetro. notifica la frecuencia.
void ciclo(float encendido, float apagado)
{
    digitalWrite(13, HIGH);
    delay(encendido*1000);
    digitalWrite(13, LOW);
    delay(apagado*1000);
    Serial.println(1.0/(encendido+apagado));
}

void apagado()
{
    digitalWrite(13, LOW);
    Serial.println(0);
}

void setup()
{
    // inicializar la comunicación serial.
    Serial.begin(9600);

    // inicializar el 13 como salida.
    pinMode(13, OUTPUT);
}

void loop()
{

    // procesar si se recibieron datos.
    if ( Serial.available() > 0 )
    {
        // si se especifica un nuevo modo, cambiar el actual. el -'0' es para 
        // convertir de caracter a entero.
        modo = Serial.read() - '0';
    }

    // determinar qué modo ejecutar.
    switch (modo)
    {
        case 1:
            encendido();
            break;

        case 2:
            ciclo(1,1);
            break;

        case 3:
            ciclo(0.5,0.5);
            break;

        case 4:
            ciclo(0.25,0.25);
            break;

        case 5:
            ciclo(0.5,1);
            break;

        default:
            apagado();
            break;
    }

}
