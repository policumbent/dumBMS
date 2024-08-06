#include "../../Drivers/INA228/INA228.h"

typedef struct {
    INA228_HandleTypeDef* sensor;
    float integral;
    float curr_val;    //current value read from sensor
    float prev_val;    //previous value read from sensor
    float integ_time;  //time between previous and current values
    long int count;

    int flag;
} CoulombEst_HandleTypeDef;


CoulombEst_HandleTypeDef CoulombEst_InitIntegral(INA228_HandleTypeDef* sens, float int_time);
void CoulombEst_addSampleFromSens(CoulombEst_HandleTypeDef *ce);
