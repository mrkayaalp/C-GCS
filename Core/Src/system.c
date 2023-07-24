#include "system.h"
#include "def.h"

uint8_t LoraArtamReceivePacket[41];
uint8_t LoraAkuReceivePacket[53];
uint8_t ArUART_Buffer[390];
uint8_t AkUART_Buffer[440];
int16_t crc;
enum avionics_error_enum avi_status;
enum flight_state_enum flight_status;
uint16_t packet_number;
uint8_t bat_level;

Altitude altitude;
Velocity velocity;
Accel accel;
float accelleration;
float maxAccelleration;

Gps gps;
Aku aku;

LoRa myLoRa;
LoRa myLoRaT;

u16_to_u8 converter16;
float_to_u8 converter32;

void ParseArtamLoRaData()
{

    crc = CRCCalculator(LoraArtamReceivePacket, 39);
    converter16.u8[0] = LoraArtamReceivePacket[39];
    converter16.u8[1] = LoraArtamReceivePacket[40];

    if (crc == converter16.u16)
    {
        avi_status = LoraArtamReceivePacket[0];
        flight_status = LoraArtamReceivePacket[1];

        converter16.u8[0] = LoraArtamReceivePacket[2];
        converter16.u8[1] = LoraArtamReceivePacket[3];
        packet_number = converter16.u16;

        bat_level = LoraArtamReceivePacket[4];

        converter32.u8[0] = LoraArtamReceivePacket[5];
        converter32.u8[1] = LoraArtamReceivePacket[6];
        converter32.u8[2] = LoraArtamReceivePacket[7];
        converter32.u8[3] = LoraArtamReceivePacket[8];
        gps.utc_time = (float)converter32.u32;

        converter16.i16 = LoraArtamReceivePacket[9];
        converter16.i16 = LoraArtamReceivePacket[10];
        altitude.altitude = (float)converter16.i16;

        converter16.i16 = LoraArtamReceivePacket[11];
        converter16.i16 = LoraArtamReceivePacket[12];
        altitude.maxAltitude = (float)converter16.i16;

        converter16.i16 = LoraArtamReceivePacket[13];
        converter16.i16 = LoraArtamReceivePacket[14];
        velocity.trueVelocity = (float)converter16.i16;

        converter16.i16 = LoraArtamReceivePacket[15];
        converter16.i16 = LoraArtamReceivePacket[16];
        velocity.maxTrueVelocity = (float)converter16.i16;

        converter32.u8[0] = LoraArtamReceivePacket[17];
        converter32.u8[1] = LoraArtamReceivePacket[18];
        converter32.u8[2] = LoraArtamReceivePacket[19];
        converter32.u8[3] = LoraArtamReceivePacket[20];
        accelleration = converter32.u32;

        converter32.u8[0] = LoraArtamReceivePacket[21];
        converter32.u8[1] = LoraArtamReceivePacket[22];
        converter32.u8[2] = LoraArtamReceivePacket[23];
        converter32.u8[3] = LoraArtamReceivePacket[24];
        maxAccelleration = converter32.u32;

        converter32.u8[0] = LoraArtamReceivePacket[25];
        converter32.u8[1] = LoraArtamReceivePacket[26];
        converter32.u8[2] = LoraArtamReceivePacket[27];
        converter32.u8[3] = LoraArtamReceivePacket[28];
        gps.latitude = converter32.u32;

        converter32.u8[0] = LoraArtamReceivePacket[29];
        converter32.u8[1] = LoraArtamReceivePacket[30];
        converter32.u8[2] = LoraArtamReceivePacket[31];
        converter32.u8[3] = LoraArtamReceivePacket[32];
        gps.longtitude = converter32.u32;

        converter16.i16 = LoraArtamReceivePacket[33];
        converter16.i16 = LoraArtamReceivePacket[34];
        accel.x = (float)converter16.i16;

        converter16.i16 = LoraArtamReceivePacket[35];
        converter16.i16 = LoraArtamReceivePacket[36];
        accel.y = (float)converter16.i16;

        converter16.i16 = LoraArtamReceivePacket[37];
        converter16.i16 = LoraArtamReceivePacket[38];
        accel.z = (float)converter16.i16;


        sprintf(ArUART_Buffer, "%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f \n", LoRa_getRSSI(&myLoRa),HAL_GetTick(), avi_status, flight_status, packet_number, bat_level, gps.utc_time, altitude.altitude, altitude.maxAltitude, velocity.trueVelocity, velocity.maxTrueVelocity, accelleration, maxAccelleration, gps.latitude, gps.longtitude, accel.x, accel.y, accel.z);
        HAL_UART_Transmit_IT(&huart7, ArUART_Buffer, strlen(ArUART_Buffer));
    }
//    else
//        //    {
//        //     artamErrorLed();
//        sprintf(ArUART_Buffer, "ARTAM crc error! \n");
//
////    HAL_UART_Transmit_IT(&huart7, ArUART_Buffer, strlen(ArUART_Buffer));
//    //    }
}

void ParseAkuLoRaData()
{
    crc = CRCCalculator(LoraAkuReceivePacket, 51);
    converter16.u8[0] = LoraAkuReceivePacket[51];
    converter16.u8[1] = LoraAkuReceivePacket[52];

    if (crc == converter16.u16 + 500)
    {
        converter32.u8[0] = LoraAkuReceivePacket[0];
        converter32.u8[1] = LoraAkuReceivePacket[1];
        converter32.u8[2] = LoraAkuReceivePacket[2];
        converter32.u8[3] = LoraAkuReceivePacket[3];
        aku.tick = converter32.u32;

        converter16.u8[0] = LoraAkuReceivePacket[4];
        converter16.u8[1] = LoraAkuReceivePacket[5];
        aku.pckt_nmbr = (int16_t)converter16.i16;

        aku.flight_state_flag = (int8_t)LoraAkuReceivePacket[6];
        aku.stabilization_flag = (int8_t)LoraAkuReceivePacket[7];

        converter16.u8[0] = LoraAkuReceivePacket[8];
        converter16.u8[1] = LoraAkuReceivePacket[9];
        aku.altitude = (int16_t)converter16.i16;

        converter32.u8[0] = LoraAkuReceivePacket[10];
        converter32.u8[1] = LoraAkuReceivePacket[11];
        converter32.u8[2] = LoraAkuReceivePacket[12];
        converter32.u8[3] = LoraAkuReceivePacket[13];
        aku.vertical_velocity = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[14];
        converter32.u8[1] = LoraAkuReceivePacket[15];
        converter32.u8[2] = LoraAkuReceivePacket[16];
        converter32.u8[3] = LoraAkuReceivePacket[17];
        aku.true_accel = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[18];
        converter32.u8[1] = LoraAkuReceivePacket[19];
        converter32.u8[2] = LoraAkuReceivePacket[20];
        converter32.u8[3] = LoraAkuReceivePacket[21];
        aku.yaw = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[22];
        converter32.u8[1] = LoraAkuReceivePacket[23];
        converter32.u8[2] = LoraAkuReceivePacket[24];
        converter32.u8[3] = LoraAkuReceivePacket[25];
        aku.pitch = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[26];
        converter32.u8[1] = LoraAkuReceivePacket[27];
        converter32.u8[2] = LoraAkuReceivePacket[28];
        converter32.u8[3] = LoraAkuReceivePacket[29];
        aku.roll = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[30];
        converter32.u8[1] = LoraAkuReceivePacket[31];
        converter32.u8[2] = LoraAkuReceivePacket[32];
        converter32.u8[3] = LoraAkuReceivePacket[33];
        aku.utc_time = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[34];
        converter32.u8[1] = LoraAkuReceivePacket[35];
        converter32.u8[2] = LoraAkuReceivePacket[36];
        converter32.u8[3] = LoraAkuReceivePacket[37];
        aku.latitude_TLC = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[38];
        converter32.u8[1] = LoraAkuReceivePacket[39];
        converter32.u8[2] = LoraAkuReceivePacket[40];
        converter32.u8[3] = LoraAkuReceivePacket[41];
        aku.longtitude_TLC = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[42];
        converter32.u8[1] = LoraAkuReceivePacket[43];
        converter32.u8[2] = LoraAkuReceivePacket[44];
        converter32.u8[3] = LoraAkuReceivePacket[45];
        aku.latitude_CTC = converter32.u32;

        converter32.u8[0] = LoraAkuReceivePacket[46];
        converter32.u8[1] = LoraAkuReceivePacket[47];
        converter32.u8[2] = LoraAkuReceivePacket[48];
        converter32.u8[3] = LoraAkuReceivePacket[49];
        aku.longtitude_CTC = converter32.u32;

        aku.wifi_connection_flag = (int8_t)LoraAkuReceivePacket[50];

        sprintf(AkUART_Buffer, "%f,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\n",aku.tick, aku.pckt_nmbr, aku.flight_state_flag, aku.stabilization_flag, aku.altitude, aku.vertical_velocity, aku.true_accel, aku.yaw, aku.pitch, aku.roll, aku.utc_time, aku.latitude_TLC, aku.longtitude_TLC, aku.latitude_CTC, aku.longtitude_CTC, aku.wifi_connection_flag);
        // HAL_UART_Transmit(&huart7, AkUART_Buffer, strlen(AkUART_Buffer), 250);
    }
    else
    {
        //        akuErrorLed();
        //        sprintf(AkUART_Buffer, "AKU crc error!");
        //        HAL_UART_Transmit(&huart7, AkUART_Buffer, strlen(AkUART_Buffer), 250);
    }
}

void initLoRa()
{
    HAL_Delay(25);

    myLoRa.CS_port = SPI6_NSS_GPIO_Port;
    myLoRa.CS_pin = SPI6_NSS_Pin;
    myLoRa.reset_port = PW2_RST_GPIO_Port;
    myLoRa.reset_pin = PW2_RST_Pin;
    myLoRa.DIO0_port = PW2_DIO0_GPIO_Port;
    myLoRa.DIO0_pin = PW2_DIO0_Pin;
    myLoRa.hSPIx = &hspi6;

    HAL_Delay(25);

    myLoRa.frequency = 440.000;         // default = 433 MHz
    myLoRa.spredingFactor = SF_7;       // default = SF_7
    myLoRa.bandWidth = BW_500KHz;       // default = BW_125KHz
    myLoRa.crcRate = CR_4_5;            // default = CR_4_5
    myLoRa.power = POWER_20db;          // default = 20db
    myLoRa.overCurrentProtection = 100; // default = 100 mA
    myLoRa.preamble = 8;                // default = 8;

    HAL_Delay(25);

    HAL_GPIO_WritePin(PW2_RST_GPIO_Port, PW2_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI6_NSS_GPIO_Port, SPI6_NSS_Pin, GPIO_PIN_SET);

    uint16_t LoRa_status = LoRa_init(&myLoRa);

    HAL_Delay(25);

    if (LoRa_status != LORA_OK)
        HAL_GPIO_WritePin(GPIO_7_GPIO_Port, GPIO_PIN_7, GPIO_PIN_SET);

    LoRa_startReceiving(&myLoRa);

    HAL_Delay(25);
}

void initLoRaT()
{
    HAL_Delay(25);

    myLoRaT.CS_port = SPI1_NSS_GPIO_Port;
    myLoRaT.CS_pin = SPI1_NSS_Pin;
    myLoRaT.reset_port = PW1_RST_GPIO_Port;
    myLoRaT.reset_pin = PW1_RST_Pin;
    myLoRaT.DIO0_port = PW1_DIO0_GPIO_Port;
    myLoRaT.DIO0_pin = PW1_DIO0_Pin;
    myLoRaT.hSPIx = &hspi1;

    HAL_Delay(25);

    myLoRaT.frequency = 440.000;         // default = 433 MHz
    myLoRaT.spredingFactor = SF_7;       // default = SF_7
    myLoRaT.bandWidth = BW_500KHz;       // default = BW_125KHz
    myLoRaT.crcRate = CR_4_5;            // default = CR_4_5
    myLoRaT.power = POWER_20db;          // default = 20db
    myLoRaT.overCurrentProtection = 250; // default = 100 mA
    myLoRaT.preamble = 8;                // default = 8;

    HAL_Delay(25);

    HAL_GPIO_WritePin(PW1_RST_GPIO_Port, PW1_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);

    uint16_t LoRa_status = LoRa_init(&myLoRaT);

    HAL_Delay(25);

    if (LoRa_status != LORA_OK)
        HAL_GPIO_WritePin(GPIO_7_GPIO_Port, GPIO_PIN_7, GPIO_PIN_SET);

    LoRa_startReceiving(&myLoRaT);

    HAL_Delay(25);
}

void loraArtamRecevice()
{
    LoRa_receive(&myLoRa, LoraArtamReceivePacket, sizeof(LoraArtamReceivePacket));
}

void loraAkuRecevice()
{
    LoRa_receive(&myLoRaT, LoraAkuReceivePacket, sizeof(LoraAkuReceivePacket));
}
void artamErrorLed(void)
{
    HAL_GPIO_WritePin(USER_LED8_GPIO_Port, USER_LED8_Pin, 1);
    HAL_Delay(100);
    HAL_GPIO_WritePin(USER_LED8_GPIO_Port, USER_LED8_Pin, 0);
}

void akuErrorLed(void)
{
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 1);
    HAL_Delay(100);
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 0);
}
