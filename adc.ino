void initADC(){
	adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
}

uint32_t getADCValue(){
	return adc1_get_raw(ADC1_CHANNEL_0);
}