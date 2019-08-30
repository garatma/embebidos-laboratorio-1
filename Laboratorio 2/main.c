void tecla_uno_up()
{
	// implementación
	// mostrar en el display: tecla uno up
}

void tecla_uno_down()
{
	// implementación
	// mostrar en el display: tecla uno down
}

key_up_callback(tecla_uno_up,1);
key_down_callback(tecla_uno_down,1);

int main()
{
	// inicializar estructuras
	teclado_init();
	while (1)
	{
		fnqueue_run();
	}
}