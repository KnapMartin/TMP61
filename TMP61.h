/*
 * TMP61.h
 *
 *  Created on: Mar 17, 2025
 *      Author: knap-linux
 */

#ifndef INC_TMP61_H_
#define INC_TMP61_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define TMP61_COEF_0 (float)-4.948869300752372e-07
#define TMP61_COEF_1 (float)0.02626742751078931
#define TMP61_COEF_2 (float)-188.33938786524962

typedef enum
{
	TMP61_ST_NONE = -1,
	TMP61_STATE_INIT,
	TMP61_STATE_ERROR,
} TMP61_State;

typedef enum
{
	TMP61_ADC_RES_NONE = -1,
	TMP61_ADC_RES_8_BIT = 255,
	TMP61_ADC_RES_10_BIT = 1023,
	TMP61_ADC_RES_12_BIT = 4095,
	TMP61_ADC_RES_14_BIT = 16383,
	TMP61_ADC_RES_16_BIT = 65535,
} TMP61_AdcRes;

typedef struct
{
	TMP61_State m_state;
	TMP61_AdcRes m_adcRes;
	uint32_t m_voltageBias_mV;
	uint32_t m_resistanceBias_Ohm;
} TMP61;

void TMP61_init(TMP61 *self, TMP61_AdcRes adcRes, const uint32_t voltageBias_mV, const uint32_t resistanceBias_Ohm);
float TMP61_get_temperature(TMP61 *self, const uint32_t adcReading, const uint32_t vref_mV);

#ifdef __cplusplus
}
#endif


#endif /* INC_TMP61_H_ */
