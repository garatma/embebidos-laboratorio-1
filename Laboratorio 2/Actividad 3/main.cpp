#include <LiquidCrystal.h>
#include <avr/io.h>
#include <stdbool.h>
// #include <stdint.h>
// #include "Arduino.h"
#include "teclado.h"
#include "fnqueue.h"

char m[64] = "Sistemas Embebidos, 2do Cuatrimestre - Laboratorio 2, comision 8";
bool input = false;
int8_t brillo = 0.8;
int16_t tiempos_guardados [10];

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void up_mca()
{
}
void up_mp()
{
}
void up_mvt()
{
}
void up_mad()
{
}

void down_mca()
{
}
void down_mp()
{
}
void down_mvt()
{
}
void down_mad()
{
}

void select_mca()
{
}
void select_mp()
{
}
void select_mvt()
{
}
void select_mad()
{
}

void inicio()
{
    input = true;
    key_up_callback(&up_mca, TECLA_UP);
    key_up_callback(&down_mca, TECLA_DOWN);
    key_up_callback(&select_mca, TECLA_SELECT);
}

void mensaje_bienvenida()
{
    int8_t i;
    lcd.autoscroll();
    lcd.setCursor(16,0);

    for ( i = 0; i < 24; i++)
    {
        lcd.print(m[i]);
        delay(180);
    }
    lcd.setCursor(0,0);
    for ( i = 24; i < 64; i++)
    {
        lcd.print(m[i]);
        delay(180);
    }

    lcd.noAutoscroll();
    delay(1000);
    lcd.clear();
}

int main()
{
    init();
    pinMode(10, OUTPUT);
    lcd.begin(16,2);
    analogWrite(10, 255*0.8); // 100% = 255
    int16_t brillo = 10;

    teclado_init();
    key_up_callback(&inicio, TECLA_UP);
    key_up_callback(&inicio, TECLA_DOWN);
    key_up_callback(&inicio, TECLA_SELECT);

    while ( !input )
        mensaje_bienvenida();

    lcd.clear();
    lcd.print("chau");
    lcd.noAutoscroll();

    while (1)
        fnqueue_run();

    return 0;
}
