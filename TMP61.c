/*
 * TMP61.c
 *
 *  Created on: Mar 17, 2025
 *      Author: knap-linux
 */

#include "TMP61.h"

void TMP61_init(TMP61 *self, TMP61_AdcRes adcRes, const uint32_t voltageBias_mV, const uint32_t resistanceBias_Ohm)
{
    if (self == NULL) return;
    if (adcRes < TMP61_ADC_RES_8_BIT)
    {
        self->m_state = TMP61_STATE_ERROR;
        return;
    }
    if (voltageBias_mV == 0 || resistanceBias_Ohm == 0)
    {
        self->m_state = TMP61_STATE_ERROR;
        return;
    }

	self->m_adcRes = adcRes;
	self->m_voltageBias_mV = voltageBias_mV;
	self->m_resistanceBias_Ohm = resistanceBias_Ohm;
	self->m_state = TMP61_STATE_INIT;
}

float TMP61_get_temperature(TMP61 *self, const uint32_t adcReading, const uint32_t voltageVref_mV)
{
	if (self->m_state != TMP61_STATE_INIT) return 0.0;

	// calculate divider voltage out
	uint32_t voltage_mV = ((float)adcReading / (float)self->m_adcRes) * voltageVref_mV;
	// calculate resistance (voltage divider)
	uint32_t resistance_Ohm = (voltage_mV * self->m_resistanceBias_Ohm) / (self->m_voltageBias_mV - voltage_mV);
	// get temperature, use 2nd order polynomial approximation
	float temperature_C = resistance_Ohm * resistance_Ohm * TMP61_COEF_0 + resistance_Ohm * TMP61_COEF_1 + TMP61_COEF_2;
	return temperature_C;
}
