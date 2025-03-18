# TMP61 temperature sensor library where the sensor is used in voltage divider configuration.
Example: STM32 using HAL ADC polling

Initialize sensor object. TMP61 is used with 10k Ohm bias resistor and 3V3 bias voltage. ADC resolution is 12-bit.

```
TMP61 temp;
TMP61_init(&temp, TMP61_ADC_RES_12_BIT, 3300, 10000);
```

ADC coversion with polling method.
```
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, 100);
uint16_t tempAdcRaw = HAL_ADC_GetValue(&hadc1);
HAL_ADC_PollForConversion(&hadc1, 100);
uint16_t vrefAdcRaw = HAL_ADC_GetValue(&hadc1);
uint16_t vref_mV = __HAL_ADC_CALC_VREFANALOG_VOLTAGE(vrefRaw, ADC_RESOLUTION12b);
HAL_ADC_Stop(&hadc1);
```
Convert to temperature in Celsius.

```
float temperature_C = TMP61_get_temperature(&temp, tempAdcRaw, vref_mV);
```
