// (1) encendido,
// (2) titilando a 0.5 Hz,
// (3) titilando a 1 Hz,
// (4) titilando a 2 Hz,
// (5) medio segundo encendido y un segundo apagado,
// (6) apagado.
int modo = 1;
int led = 13;

// prende el led.
void encendido()
{
    digitalWrite(led, HIGH);
    Serial.println(0);
}

// prende el led, espera lo especificado por el primer parámetro. apaga el led
// y espera lo especificado por el segundo parámetro.
void ciclo(int encendido, int apagado)
{
    digitalWrite(led, HIGH);
    delay(encendido);
    digitalWrite(led, LOW);
    delay(apagado);
    Serial.println(1/(encendido+apagado));
}

// apaga el led.
void apagado()
{
    digitalWrite(led, LOW);
    Serial.println(0);
}

void setup()
{
    // inicializar la comunicación serial.
    Serial.begin(9600);

    // inicializar el led como salida.
    pinMode(led, OUTPUT);
}

void loop()
{

    // procesar si se recibieron datos.
    if ( Serial.available() > 0 ) 
    {
        // si se especifica un nuevo modo, cambiar el actual.
        modo = Serial.read();
    }

    // determinar qué modo ejecutar.
    switch (modo)
    {
        case 1:
            encendido();
            break;
        
        case 2:
            ciclo(1000,1000);
            break;

        case 3:
            ciclo(500,500);
            break;

        case 4:
            ciclo(250,250);
            break;

        case 5:
            ciclo(500,1000);
            break;
            
        default:
            apagado();
            break;
    }
    
}