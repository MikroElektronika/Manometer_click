/*
Example for Manometer Click

    Date          : Sep 2018.
    Author        : Nenad Filipovic

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : v7.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization -  Initializes I2C structures.
- Application Initialization - Initialization driver enable's - I2C and start write log to Usart Terminal.
- Application Task - (code snippet) This is a example which demonstrates the use of Manometer Click board.
     Measured pressure ( mbar ) and temperature ( degrees Celsius ) from sensor,
     results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart for aproximetly every 2 sec.

Additional Functions :

- UART
- Conversions

*/

#include "Click_Manometer_types.h"
#include "Click_Manometer_config.h"

char textLog[10];
float readData;

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_MANOMETER_I2C_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );
    Delay_100ms();
}

void applicationInit()
{
    manometer_i2cDriverInit( (T_MANOMETER_P)&_MIKROBUS1_GPIO, (T_MANOMETER_P)&_MIKROBUS1_I2C, _MANOMETER_I2C_ADDRESS );
    mikrobus_logWrite( "      Initialization", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );
    Delay_100ms();
}

void applicationTask()
{
    readData = manometer_getPressure();
    Delay_10ms();

    mikrobus_logWrite( " Pressure:    ", _LOG_TEXT );
    IntToStr( readData, textLog );
    mikrobus_logWrite( textLog, _LOG_TEXT );
    mikrobus_logWrite( " mbar", _LOG_LINE );

    readData = manometer_getTemperature();
    Delay_10ms();

    mikrobus_logWrite( " Temperature: ", _LOG_TEXT );
    IntToStr( readData, textLog );
    mikrobus_logWrite( textLog, _LOG_TEXT );
    mikrobus_logWrite( " °C", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );

    Delay_1sec();
    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}