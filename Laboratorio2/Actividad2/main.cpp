#include <stdbool.h>
#include <LiquidCrystal.h>
#include <stdint.h>
#include "Arduino.h"
#include "fnqueue.h"
#include "teclado.h"

// these constants won't change.  But you can change the size of
// your LCD using them:
const uint16_t numRows = 2;
const uint16_t numCols = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void tecla_right_down()
{
	lcd.setCursor(0, 1);
	lcd.print(" Right Key:  OK ");
}
void tecla_right_up()
{
	lcd.setCursor(0, 1);
	lcd.print(" Right Key:  NO ");
}

void tecla_up_down()
{
	lcd.setCursor(0, 1);
	lcd.print(" Up Key:     OK ");
}
void tecla_up_up()
{
	lcd.setCursor(0, 1);
	lcd.print(" Up Key:     NO ");
}

void tecla_down_down()
{
	lcd.setCursor(0, 1);
	lcd.print(" Down Key:   OK ");
}
void tecla_down_up()
{
	lcd.setCursor(0, 1);
	lcd.print(" Down Key:   NO ");
}

void tecla_left_down()
{
	lcd.setCursor(0, 1);
	lcd.print(" Left Key:   OK ");
}
void tecla_left_up()
{
	lcd.setCursor(0, 1);
	lcd.print(" Left Key:   NO ");
}

void tecla_select_down()
{
	lcd.setCursor(0, 1);
	lcd.print(" Select Key: OK ");
}
void tecla_select_up()
{
	lcd.setCursor(0, 1);
	lcd.print(" Select Key: NO ");
}

void callback_init()
{
	key_down_callback(&tecla_up_down, TECLA_UP);
	key_up_callback(&tecla_up_up, TECLA_UP);

	key_down_callback(&tecla_down_down, TECLA_DOWN);
	key_up_callback(&tecla_down_up, TECLA_DOWN);

	key_down_callback(&tecla_left_down, TECLA_LEFT);
	key_up_callback(&tecla_left_up, TECLA_LEFT);

	key_down_callback(&tecla_select_down, TECLA_SELECT);
	key_up_callback(&tecla_select_up, TECLA_SELECT);

	key_down_callback(&tecla_right_down, TECLA_RIGHT);
	key_up_callback(&tecla_right_up, TECLA_RIGHT);
}

int main()
{
	init();
	// inicializar pin 10 como salida
	pinMode(10, OUTPUT);

	// set up the LCD's number of columns and rows:
	lcd.begin(numCols,numRows);
	analogWrite(10,255);
	lcd.setCursor(0, 0);
	lcd.print("Key Pad Test");
	lcd.setCursor(0, 1);
	lcd.print("Press any key..");

	teclado_init();
	callback_init();

	while (1)
		fnqueue_run();
	return 0;
}
