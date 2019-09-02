#include <stdbool.h>
#include <LiquidCrystal.h>
#include <stdint.h>
#include "Arduino.h"
#include "teclado.h"
#include "fnqueue.h"

// these constants won't change.  But you can change the size of
// your LCD using them:
const uint16_t numRows = 2;
const uint16_t numCols = 16;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Key message
char msgs_down[5][17] =
{
    " Right Key:  OK ",
    " Up Key:     OK ",
    " Down Key:   OK ",
    " Left Key:   OK ",
    " Select Key: OK "
};
char msgs_up[5][17] =
{
    " Right Key:  NO ",
    " Up Key:     NO ",
    " Down Key:   NO ",
    " Left Key:   NO ",
    " Select Key: NO "
};

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
  key_down_callback(&tecla_right_down, 3);
  key_up_callback(&tecla_right_up, 3);


  key_down_callback(&tecla_up_down, 0);
  key_up_callback(&tecla_up_up, 0);


  key_down_callback(&tecla_down_down, 1);
  key_up_callback(&tecla_down_up, 1);


  key_down_callback(&tecla_left_down, 2);
  key_up_callback(&tecla_left_up, 2);


  key_down_callback(&tecla_select_down, 4);
  key_up_callback(&tecla_select_up, 4);
}

int main()
{
  init();
  // inicializar pin 10 como salida
    pinMode(10, OUTPUT);
  

    // set up the LCD's number of columns and rows:
    lcd.begin(numCols,numRows);
    analogWrite(10, 100); // ¿reemplazar por código AVR?
    lcd.setCursor(0, 0);
    lcd.print("Key Pad Test");
    lcd.setCursor(0, 1);
    lcd.print("Sist.Emb. 2019");
    //delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Press any key...");

  teclado_init();
  callback_init();

  while (1)
  {
    fnqueue_run();
    //lcd.setCursor(0, 1);
    //lcd.print("Press key...");
  }
  return 0;
}



