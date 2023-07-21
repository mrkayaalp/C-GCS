#include "system.h"
#include "def.h"

uint8_t LoraReceivePacket[41];
uint8_t UART_Buffer[390];
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

LoRa myLoRa;
LoRa myLoRaT;

u16_to_u8 converter16;
float_to_u8 converter32;

void ParseLoRaData()
{
    // LoraReceivePacketi dizi olarak tanımlamammamışın
    // Değişkenler için defdeki structları kullanabilirsin

    crc = CRCCalculator(LoraReceivePacket, 39);
    converter16.u8[0] = LoraReceivePacket[39];
    converter16.u8[1] = LoraReceivePacket[40];

    if (crc == converter16.u16)
    {
        avi_status = LoraReceivePacket[0];
        flight_status = LoraReceivePacket[1];

        converter16.u8[0] = LoraReceivePacket[2];
        converter16.u8[1] = LoraReceivePacket[3];
        packet_number = converter16.u16;

        bat_level = LoraReceivePacket[4];

        converter32.u8[0] = LoraReceivePacket[5];
        converter32.u8[1] = LoraReceivePacket[6];
        converter32.u8[2] = LoraReceivePacket[7];
        converter32.u8[3] = LoraReceivePacket[8];
        gps.utc_time = (float) converter32.u32;



        converter16.i16 = LoraReceivePacket[9];
        converter16.i16 = LoraReceivePacket[10];
        altitude.altitude = (float) converter16.i16;

        converter16.i16 = LoraReceivePacket[11];
        converter16.i16 = LoraReceivePacket[12];
        altitude.maxAltitude = (float) converter16.i16;

        converter16.i16 = LoraReceivePacket[13];
        converter16.i16 = LoraReceivePacket[14];
        velocity.trueVelocity = (float) converter16.i16;

        converter16.i16 = LoraReceivePacket[15];
        converter16.i16 = LoraReceivePacket[16];
        velocity.maxTrueVelocity = (float) converter16.i16;

        converter32.u8[0] = LoraReceivePacket[17];
        converter32.u8[1] = LoraReceivePacket[18];
        converter32.u8[2] = LoraReceivePacket[19];
        converter32.u8[3] = LoraReceivePacket[20];
        accelleration = converter32.u32;

        converter32.u8[0] = LoraReceivePacket[21];
        converter32.u8[1] = LoraReceivePacket[22];
        converter32.u8[2] = LoraReceivePacket[23];
        converter32.u8[3] = LoraReceivePacket[24];
        maxAccelleration = converter32.u32;

        converter32.u8[0] = LoraReceivePacket[25];
        converter32.u8[1] = LoraReceivePacket[26];
        converter32.u8[2] = LoraReceivePacket[27];
        converter32.u8[3] = LoraReceivePacket[28];
        gps.latitude = converter32.u32;

        converter32.u8[0] = LoraReceivePacket[29];
        converter32.u8[1] = LoraReceivePacket[30];
        converter32.u8[2] = LoraReceivePacket[31];
        converter32.u8[3] = LoraReceivePacket[32];
        gps.longtitude = converter32.u32;

        converter16.i16 = LoraReceivePacket[33];
        converter16.i16 = LoraReceivePacket[34];
        accel.x = (float) converter16.i16;

        converter16.i16 = LoraReceivePacket[35];
        converter16.i16 = LoraReceivePacket[36];
        accel.y = (float) converter16.i16;

        converter16.i16 = LoraReceivePacket[37];
        converter16.i16 = LoraReceivePacket[38];
        accel.z = (float) converter16.i16;

        sprintf(UART_Buffer, "%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", avi_status, flight_status, packet_number, bat_level, gps.utc_time, altitude.altitude, altitude.maxAltitude, velocity.trueVelocity, velocity.maxTrueVelocity, accelleration, maxAccelleration, gps.latitude, gps.longtitude, accel.x, accel.y, accel.z);
        HAL_UART_Transmit(&huart7, UART_Buffer, strlen(UART_Buffer), 100);
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

    myLoRaT.frequency = 433.663;         // default = 433 MHz
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

void loraRecevice()
{
    LoRa_receive(&myLoRa, LoraReceivePacket, sizeof(LoraReceivePacket));
}
