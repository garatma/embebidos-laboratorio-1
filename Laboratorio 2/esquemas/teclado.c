volatile key;

key_up_callback(*handler,tecla)
{
	// implementación
	estructura.callback = handler;
}

key_down_callback(*handler,tecla)
{
	// implementación
	estructura.callback = handler;
}

teclado_init()
{
	// implementación
}

ISR(ADC_vect()
{
	key = ADC;
	fnqueue_add(procesar());
}

procesar()
{
	// implementación
	// ver qué tecla se apretó
	// ejecutar estructura.callback
}