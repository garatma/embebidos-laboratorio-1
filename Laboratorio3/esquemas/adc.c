struct adc_channel_cfg
{
    void (* callback)();
    int16_t valor;
    bool activo;
    bool hay_conversion;
}

struct adc_channel_cfg adc[max_canales];

int8_t canal_actual;
bool no_convirtiendo = true;

bool adc_init(struct adc_cfg * cfg)
{
    adc[cfg -> canal] = *cfg;
    adc[cfg -> canal].activo = true;
    canal_actual = cfg->canal;

    // si no hay conversion iniciar
    if ( no_convirtiendo )
    {
        no_convirtiendo = false;
        // iniciar conversion
    }
}

void adc_loop()
{
    // para cada canal de adc
    for ( int8_t i = 0; i < 6; i++ )
        if ( adc[i].hay_conversion  == true )
        {
            adc[i].callback();
            adc[i].hay_conversion=false;
        }
}

ISR(ADC_vect)
{
    adc[canal_actual].valor = ADC;
    adc[canal_actual].hay_conversion = true;
    proximo = obtener_proximo();
    if ( proximo == primer_canal )
        fnqueue_add(adc_loop);
    canal_actual = proximo;
    ADCSRA |= (1 << ADSC);	// iniciar conversión.
}
