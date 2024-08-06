#include "coulomb_estimator.h"

CoulombEst_HandleTypeDef CoulombEst_InitIntegral(INA228_HandleTypeDef* sens, float int_time){
    CoulombEst_HandleTypeDef out;
    out.count=0;
    out.curr_val=0.0;
    out.prev_val=0.0;
    out.integ_time=int_time;
    out.sensor = sens;
    out.flag = 0;
    return out;
}

void CoulombEst_addSampleFromSens(CoulombEst_HandleTypeDef *ce){
    ce->prev_val=ce->curr_val;
    INA228_ReadCurrent(ce->sensor, &(ce->curr_val));

    if(!(ce->flag)){
        ce->flag=1;
        return;
    }

    ce->integral+=(ce->curr_val+ce->prev_val) * ce->integ_time / 2.0 ;
}