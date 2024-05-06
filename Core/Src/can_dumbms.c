#include "can_dumbms.h"


typedef struct {
    CAN_TxHeaderTypeDef tx_header;
    uint8_t data[POLICANBENT_DUMBMS1_DATA_LENGTH];
} msg_bat_data_t;

typedef struct {
    CAN_TxHeaderTypeDef tx_header;
    uint8_t data[POLICANBENT_DUMBMS1_ERROR_LENGTH];
} msg_bat_err_t;


msg_bat_data_t msg_bat_data;
msg_bat_err_t msg_bat_err;

uint32_t can_last_time_ms;
uint32_t can_curr_time_ms;

uint8_t can_id_selected; /* if 0: use DUMBMS1 IDs; if 1: use DUMBMS2 IDs */


static void can_tx_header_init(CAN_TxHeaderTypeDef *tx_header,
                               uint32_t std_id,
                               uint32_t dlc);

/**
 * @brief Initializes the CAN transmission headers (with the right ID), starts
 *        CAN peripheral
 */
void can_init() {
    can_id_selected = HAL_GPIO_ReadPin(CAN_ID_Selector_GPIO_Port, CAN_ID_Selector_Pin);

    if (!can_id_selected) {
        can_tx_header_init(&msg_bat_data.tx_header,
                           POLICANBENT_DUMBMS1_DATA_FRAME_ID,
                           POLICANBENT_DUMBMS1_DATA_LENGTH);

        can_tx_header_init(&msg_bat_err.tx_header,
                           POLICANBENT_DUMBMS1_ERROR_FRAME_ID,
                           POLICANBENT_DUMBMS1_ERROR_LENGTH);
    } else {
        can_tx_header_init(&msg_bat_data.tx_header,
                           POLICANBENT_DUMBMS2_DATA_FRAME_ID,
                           POLICANBENT_DUMBMS2_DATA_LENGTH);

        can_tx_header_init(&msg_bat_err.tx_header,
                           POLICANBENT_DUMBMS2_ERROR_FRAME_ID,
                           POLICANBENT_DUMBMS2_ERROR_LENGTH);
    }

    HAL_CAN_Start(&hcan1);
    can_last_time_ms = HAL_GetTick();
}

/**
 * @brief Encodes and sends the batteries voltages on the CAN Bus
 */
void can_send_bat_status() {
    can_curr_time_ms = HAL_GetTick();
    
    if (can_curr_time_ms - can_last_time_ms < CAN_SENDING_PERIOD) {
        return;
    }

    struct policanbent_dumbms1_data_t data_frame;
    data_frame.bat0_voltage = policanbent_dumbms1_data_bat0_voltage_encode(bat_get_cell_volt(0));
    data_frame.bat1_voltage = policanbent_dumbms1_data_bat1_voltage_encode(bat_get_cell_volt(1));
    data_frame.bat2_voltage = policanbent_dumbms1_data_bat2_voltage_encode(bat_get_cell_volt(2));
    data_frame.bat3_voltage = policanbent_dumbms1_data_bat3_voltage_encode(bat_get_cell_volt(3));
    data_frame.bat4_voltage = policanbent_dumbms1_data_bat4_voltage_encode(bat_get_cell_volt(4));

    policanbent_dumbms1_data_pack(msg_bat_data.data, &data_frame, POLICANBENT_DUMBMS1_DATA_LENGTH);

    uint32_t mailbox;

    HAL_CAN_AddTxMessage(&hcan1, &msg_bat_data.tx_header, msg_bat_data.data, &mailbox);

    can_last_time_ms = can_curr_time_ms;
}

/**
 * @brief Encodes and sends the error frame on the CAN Bus if any undervoltage
 *        is detected
 * @param bat_undervolt_arr: is a MAX_BATTERY_N long array, which stores the
 *        undervoltage flags for each LiPo
 */
void can_send_bat_err(uint8_t *bat_undervolt_arr) {
    struct policanbent_dumbms1_error_t data_frame;
    data_frame.bat0_under_volt = policanbent_dumbms1_error_bat0_under_volt_encode(bat_undervolt_arr[0]);
    data_frame.bat1_under_volt = policanbent_dumbms1_error_bat1_under_volt_encode(bat_undervolt_arr[1]);
    data_frame.bat2_under_volt = policanbent_dumbms1_error_bat2_under_volt_encode(bat_undervolt_arr[2]);
    data_frame.bat3_under_volt = policanbent_dumbms1_error_bat3_under_volt_encode(bat_undervolt_arr[3]);
    data_frame.bat4_under_volt = policanbent_dumbms1_error_bat4_under_volt_encode(bat_undervolt_arr[4]);

    policanbent_dumbms1_error_pack(msg_bat_data.data, &data_frame, POLICANBENT_DUMBMS1_ERROR_LENGTH);

    uint32_t mailbox;

    HAL_CAN_AddTxMessage(&hcan1, &msg_bat_data.tx_header, msg_bat_data.data, &mailbox);
}

/**
 * @brief Initializes a CAN TX Header for not extended frames
 * @param tx_header: header by reference
 * @param std_id: standard (not extended) ID
 * @param dlc: frame length
 */
static void can_tx_header_init(CAN_TxHeaderTypeDef *tx_header,
                               uint32_t std_id,
                               uint32_t dlc) {
    tx_header->ExtId = 0;
    tx_header->IDE = CAN_ID_STD;
    tx_header->RTR = CAN_RTR_DATA;
    tx_header->StdId = std_id;
    tx_header->DLC = dlc;
}