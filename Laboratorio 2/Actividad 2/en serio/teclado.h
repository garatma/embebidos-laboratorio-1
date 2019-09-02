#define TECLA_UP 		0	// tecla up del LCD Keypad Shield.
#define TECLA_DOWN 		1 	// tecla down del LCD Keypad Shield.
#define TECLA_LEFT 		2 	// tecla left del LCD Keypad Shield.
#define TECLA_RIGHT 	3 	// tecla right del LCD Keypad Shield.
#define TECLA_SELECT 	4	// tecla select del LCD Keypad Shield.
#define CANTIDAD_TECLAS 5	// cantidad de teclas en el teclado.

void key_down_callback(void (*handler)(), int8_t tecla);
void key_up_callback(void (*handler)(), int8_t tecla);
void teclado_init();
const uint16_t adc_key_val[CANTIDAD_TECLAS] = {30, 150, 360, 535, 760};

typedef struct estructura_teclado {
	volatile int8_t last_key; // última tecla apretada.

	void (*handlers_up[CANTIDAD_TECLAS])(); // arreglo de handlrs para key_up.
	void (*handlers_down[CANTIDAD_TECLAS])(); // arreglo de handlrs para
											  // key_down.
} * estado_teclado ;
