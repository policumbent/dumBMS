/**
 * @author Medeossi Erik
 * @date 30/11/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#ifndef INA228_H
#define INA228_H

#ifdef STM32F0
#include "stm32f0xx_hal.h" /* Import HAL library */
#elif defined(STM32F1)
#include "stm32f1xx_hal.h" /* Import HAL library */
#elif defined(STM32F2)
#include "stm32f2xx_hal.h" /* Import HAL library */
#elif defined(STM32F3)
#include "stm32f3xx_hal.h" /* Import HAL library */
#elif defined(STM32F4)
#include "stm32f4xx_hal.h" /* Import HAL library */
#elif defined(STM32F7)
#include "stm32f7xx_hal.h" /* Import HAL library */
#elif defined(STM32G0)
#include "stm32g0xx_hal.h" /* Import HAL library */
#elif defined(STM32G4)
#include "stm32g4xx_hal.h" /* Import HAL library */
#elif defined(STM32H7)
#include "stm32h7xx_hal.h" /* Import HAL library */
#elif defined(STM32L0)
#include "stm32l0xx_hal.h" /* Import HAL library */
#elif defined(STM32L1)
#include "stm32l1xx_hal.h" /* Import HAL library */
#elif defined(STM32L5)
#include "stm32l5xx_hal.h" /* Import HAL library */
#elif defined(STM32L4)
#include "stm32l4xx_hal.h" /* Import HAL library */
#elif defined(STM32H7)
#include "stm32h7xx_hal.h" /* Import HAL library */
#else
#endif

#include "main.h"

#define CONFIG_REG 0x00
#define SHUNT_VOLTAGE_REG 0x01
#define BUS_VOLTAGE_REG 0x02
#define POWER_REG 0x03
#define CURRENT_REG 0x04
#define CALIBRATION_REG 0x05

#define INA228_RESET 0x8000
// Define for the operating modes of the INA228 chip
#define INA228_MODE_POWER_DOWN 0x0000        // Shutdown mode
#define INA228_MODE_SHUNT_TRIGGER 0x0001     // Shunt voltage trigger mode
#define INA228_MODE_BUS_TRIGGER 0x0002       // Bus voltage trigger mode
#define INA228_MODE_SHUNT_BUS_TRIGGER 0x0003 // Shunt and bus voltage trigger mode (continuous counting)

// Number of samples
#define INA228_AVERAGING_1 0x0000  // Number of samplings: 1
#define INA228_AVERAGING_4 0x0200  // Number of samplings: 4
#define INA228_AVERAGING_16 0x0400 // Number of samplings: 16
#define INA228_AVERAGING_64 0x0600 // Number of samplings: 64

// Definition for the bus voltage conversion time
#define INA228_BUS_CONV_TIME_140us 0x0000  // 140µs
#define INA228_BUS_CONV_TIME_204us 0x0040  // 204µs
#define INA228_BUS_CONV_TIME_332us 0x0080  // 332µs
#define INA228_BUS_CONV_TIME_588us 0x00C0  // 588µs
#define INA228_BUS_CONV_TIME_1100us 0x0100 // 1.1ms
#define INA228_BUS_CONV_TIME_2116us 0x0140 // 2.116ms
#define INA228_BUS_CONV_TIME_4156us 0x0180 // 4.156ms
#define INA228_BUS_CONV_TIME_8244us 0x01C0 // 8.244ms

// Definition for the shunt voltage conversion time
#define INA228_SHUNT_CONV_TIME_140us 0x0000  // 140µs
#define INA228_SHUNT_CONV_TIME_204us 0x0008  // 204µs
#define INA228_SHUNT_CONV_TIME_332us 0x0010  // 332µs
#define INA228_SHUNT_CONV_TIME_588us 0x0018  // 588µs
#define INA228_SHUNT_CONV_TIME_1100us 0x0020 // 1.1ms
#define INA228_SHUNT_CONV_TIME_2116us 0x0028 // 2.116ms
#define INA228_SHUNT_CONV_TIME_4156us 0x0030 // 4.156ms
#define INA228_SHUNT_CONV_TIME_8244us 0x0038 // 8.244ms

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint16_t addr;
    uint16_t average;
    uint16_t busConvTime;
    uint16_t shuntConvTime;
    uint16_t mode;
    float rShuntValue;
    float iMax;
    float shuntVoltageLSB;
    float currentLSB;
    float powerLSB;
    float busVoltageLSB;
    uint16_t calibrationValue;
} INA228_HandleTypeDef;

HAL_StatusTypeDef INA228_Init(INA228_HandleTypeDef *hina228, I2C_HandleTypeDef *hi2c, uint16_t addr, uint16_t average, uint16_t busConvTime, uint16_t shuntConvTime, uint16_t mode, float rShuntValue, float iMax);
HAL_StatusTypeDef INA228_Reset(INA228_HandleTypeDef *hina228);
HAL_StatusTypeDef INA228_Config(INA228_HandleTypeDef *hina228);
HAL_StatusTypeDef INA228_ReadShuntVoltage(INA228_HandleTypeDef *hina228, float *voltage);
HAL_StatusTypeDef INA228_ReadCurrent(INA228_HandleTypeDef *hina228, float *current);
HAL_StatusTypeDef INA228_ReadPower(INA228_HandleTypeDef *hina228, float *power);
HAL_StatusTypeDef INA228_ReadBusVoltage(INA228_HandleTypeDef *hina228, float *voltage);
#endif