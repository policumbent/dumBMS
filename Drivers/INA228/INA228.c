/**
 * @author Medeossi Erik
 * @date 30/11/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#include "INA228.h"

/// @brief Initializes the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @param hi2c Pointer to the I2C handle structure.
/// @param addr Device address.
/// @param average Averaging mode (number of samples) for measurements.
/// @param busConvTime Bus voltage conversion time setting.
/// @param shuntConvTime Shunt voltage conversion time setting.
/// @param mode Operating mode of the INA228.
/// @param rShuntValue Shunt resistor value in ohms.
/// @param iMax Maximum expected current through the shunt resistor.
/// @return HAL status.
HAL_StatusTypeDef INA228_Init(INA228_HandleTypeDef *hina228, I2C_HandleTypeDef *hi2c, uint16_t addr, uint16_t average, uint16_t busConvTime, uint16_t shuntConvTime, uint16_t mode, float rShuntValue, float iMax)
{
    hina228->hi2c = hi2c;
    hina228->addr = addr;
    hina228->average = average;
    hina228->busConvTime = busConvTime;
    hina228->shuntConvTime = shuntConvTime;
    hina228->mode = mode;
    hina228->rShuntValue = rShuntValue;
    hina228->iMax = iMax;

    // Calculation of calibration value
    hina228->calibrationValue = (uint16_t)(0.00512 / (hina228->rShuntValue * (1 << hina228->average)));

    if (INA228_Reset(hina228) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/// @brief Resets the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @return HAL status.
HAL_StatusTypeDef INA228_Reset(INA228_HandleTypeDef *hina228)
{
    uint16_t reset = INA228_RESET;
    uint8_t data[2];

    data[0] = reset >> 8;
    data[1] = reset & 0xff;

    if (HAL_I2C_Mem_Write(hina228->hi2c, hina228->addr, CONFIG_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}
/// @brief Configures the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @return HAL status.
HAL_StatusTypeDef INA228_Config(INA228_HandleTypeDef *hina228)
{
    uint16_t config = (hina228->average << 9) | (hina228->busConvTime << 6) | (hina228->shuntConvTime << 3) | hina228->mode;
    uint8_t data[2];

    data[0] = config >> 8;
    data[1] = config & 0xff;

    // Write config register
    if (HAL_I2C_Mem_Write(hina228->hi2c, hina228->addr, CONFIG_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Write calibration register
    data[0] = hina228->calibrationValue >> 8;
    data[1] = hina228->calibrationValue & 0xff;

    if (HAL_I2C_Mem_Write(hina228->hi2c, hina228->addr, CALIBRATION_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/// @brief Reads the shunt voltage from the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @param voltage Pointer to the variable to store the shunt voltage (in Volts).
/// @return HAL status.
HAL_StatusTypeDef INA228_ReadShuntVoltage(INA228_HandleTypeDef *hina228, float *voltage)
{
    uint16_t shuntVoltageRaw;
    uint8_t data[2];

    // Read shunt voltage register
    if (HAL_I2C_Mem_Read(hina228->hi2c, hina228->addr, SHUNT_VOLTAGE_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    shuntVoltageRaw = (data[0] << 8) | data[1];

    // Calculate shunt voltage in volts
    *voltage = (float)shuntVoltageRaw * hina228->shuntVoltageLSB;

    return HAL_OK;
}

/// @brief Reads the current from the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @param current Pointer to the variable to store the current (in Amperes).
/// @return HAL status.
HAL_StatusTypeDef INA228_ReadCurrent(INA228_HandleTypeDef *hina228, float *current)
{
    uint16_t currentRaw;
    uint8_t data[2];

    // Read current register
    if (HAL_I2C_Mem_Read(hina228->hi2c, hina228->addr, CURRENT_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    currentRaw = (data[0] << 8) | data[1];

    // Calculate current in Amps
    *current = (float)currentRaw * hina228->currentLSB;

    return HAL_OK;
}

/// @brief Reads the power from the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @param power Pointer to the variable to store the power (in Watts).
/// @return HAL status.
HAL_StatusTypeDef INA228_ReadPower(INA228_HandleTypeDef *hina228, float *power)
{
    uint16_t powerRaw;
    uint8_t data[2];

    // Read power register
    if (HAL_I2C_Mem_Read(hina228->hi2c, hina228->addr, POWER_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    powerRaw = (data[0] << 8) | data[1];

    // Calculate power in Watts
    *power = (float)powerRaw * hina228->powerLSB;

    return HAL_OK;
}

/// @brief Reads the bus voltage from the INA228 device.
/// @param hina228 Pointer to the INA228 handle structure.
/// @param voltage Pointer to the variable to store the bus voltage (in Volts).
/// @return HAL status.
HAL_StatusTypeDef INA228_ReadBusVoltage(INA228_HandleTypeDef *hina228, float *voltage)
{
    uint16_t busVoltageRaw;
    uint8_t data[2];

    // Read bus voltage register
    if (HAL_I2C_Mem_Read(hina228->hi2c, hina228->addr, BUS_VOLTAGE_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    busVoltageRaw = (data[0] << 8) | data[1];

    // Calculate bus voltage in Volts
    *voltage = (float)busVoltageRaw * hina228->busVoltageLSB;

    return HAL_OK;
}