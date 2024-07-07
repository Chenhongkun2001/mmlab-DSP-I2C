

//###########################################################################
// FILE:    Example_2837xDI2c_eeprom.c
// TITLE:   I2C EEPROM Example
//
//! \addtogroup cpu01_example_list
//! <h1>I2C EEPROM Example (i2c_eeprom)</h1>
//!
//! This program will write 1-14 words to EEPROM and read them back.
//! The data written and the EEPROM address written to are contained
//! in the message structure, I2cMsgOut1. The data read back will be
//! contained in the message structure I2cMsgIn1.
//!
//! \b External \b Connections \n
//! - This program requires an external I2C EEPROM connected to
//!   the I2C bus at address 0x50.
//
//###########################################################################
// $TI Release: F2837xD Support Library v130 $
// $Release Date: Mon Oct 20 10:15:06 CDT 2014 $



// $ Modified by Chen HongKun, Chen Yiming, and Chen Jiahao, July 2024 in mmlab $
//###########################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
// Note: I2C Macros used in this example can be found in the
// F2837xD_I2C_defines.h file

// Prototype statements for functions found within this file.
void   I2CA_Init(void);
Uint32 I2CA_ReadData_Channel(Uint16 channel);
int I2cRead16bitData(Uint16 SlaveRegAddr);
int I2cWrite16bitData(Uint16 ConfigRegAddr, Uint16 value);
int Single_channel_config(Uint16 channel);
void Set_Rp(Uint16 channel, float n_kom);
void Set_L(Uint16 channel, float n_uh);
void Set_C(Uint16 channel, float n_pf);
void Set_Q_factor(Uint16 channel, float q);
Uint32 Set_FIN_FREF_DIV(Uint16 channel);
Uint32 Set_LC_stabilize_time(Uint16 channel);
Uint32 Set_conversion_time(Uint16 channel, Uint16 value);
Uint32 Set_driver_current(Uint16 channel, Uint16 value);
Uint32 Set_mux_config(Uint16 value);
Uint32 Set_sensor_config(Uint16 value);
void Select_channel_to_convert(Uint16 channel, Uint16* value);
Uint32 Reset_sensor();
Uint32 Parse_result_data(Uint16 channel, Uint32 raw_result, Uint32* result);
Uint32 Set_ERROR_CONFIG(Uint16 value);
void Read_sensor_infomation();
Uint32 reset_sensor();


__interrupt void i2c_int1a_isr(void);
void pass(void);
void fail(void);

#define I2C_SLAVE_ADDR        0x2B // I2C Address selection pin: when ADDR=L, I2C address = 0X2A,
                                                              // when ADDR=H, I2C address = 0x2B. (current disp. sensor design uses this address)
#define I2C_NUMBYTES         2     // 16 bits

// After transmitting the address of LDC1612(0X2B), it is needed to be transmitting the address of channel registers
// the channel registers is composed by 2 parts, that is, high address and low address.
#define I2C_EEPROM_HIGH_ADDR_CHANNEL0  0x00
#define I2C_EEPROM_LOW_ADDR_CHANNEL0   0x01
#define I2C_EEPROM_HIGH_ADDR_CHANNEL1  0x02
#define I2C_EEPROM_LOW_ADDR_CHANNEL1   0x03
// define the registers which are needed in LDC1612
#define SET_CONVERSION_TIME_REG_START           0X08
#define SET_CONVERSION_OFFSET_REG_START         0X0C
#define SET_LC_STABILIZE_REG_START              0X10
#define SET_FREQ_REG_START                      0X14
#define SENSOR_STATUS_REG                       0X18
#define ERROR_CONFIG_REG                        0X19
#define SENSOR_CONFIG_REG                       0X1A
#define MUL_CONFIG_REG                          0X1B
#define SENSOR_RESET_REG                        0X1C
#define SET_DRIVER_CURRENT_REG                  0X1E
#define READ_MANUFACTURER_ID                    0X7E
#define READ_DEVICE_ID                          0X7F

#define CHANNEL_NUM 2 // we use two channel
#define CHANNEL_0 0
// Global variables
// Two bytes will be used for the outgoing address,
// thus only setup 14 bytes maximum
Uint16 ERROR;

Uint16 dataHigh;
Uint16 dataLow;
Uint16 dataHigh_one;
Uint16 dataLow_one;
Uint32 result_zero;
Uint32 result_one;
Uint32 raw_result;
Uint32 channel0DataResult;
Uint32 channel1DataResult;
Uint32 raw_value;
Uint32 result;
int choose_channel;

float resistance[CHANNEL_NUM];
float inductance[CHANNEL_NUM];
float capacitance[CHANNEL_NUM];
float Q_factor[CHANNEL_NUM];
float Fsensor[CHANNEL_NUM];
float Fref[CHANNEL_NUM];
float inductance[CHANNEL_NUM];
float capacitance[CHANNEL_NUM];
Uint16 value;
Uint16 FIN_DIV, FREF_DIV;
Uint16 config = 0x1601;



struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          0x00,                   // Msg Byte 1, initialize
                          0x00};                  // Msg Byte 2, initialize

struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          0x00,
                          0x00};
// To make I2C_EEPROM_HIGH_ADDR, I2C_EEPROM_LOW_ADDR both equals to 0x00, the reason I choose to
// do that is the low-address and high-address of different channel is diverse.

struct I2CMSG *CurrentMsgPtr;              // Used in __interrupts
Uint16 PassCount;
Uint16 FailCount;


void main(void)
{
 //  Uint16 Error;
   Uint16 i;

//   CurrentMsgPtr = &I2cMsgOut1;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();

// For this example, only init the pins for the xxx port.
// These functions are found in the F2837xD_Gpio.c file.
   // use GPIO0, GPIO1 and reuse mode is 6 (I2C)
   GPIO_SetupPinMux(0, GPIO_MUX_CPU1, 6);
   GPIO_SetupPinMux(1, GPIO_MUX_CPU1, 6);

// First parameter is GPIO pin.
// The third parameter is GPIO pins that need to be reused.
// In a microcontroller or DSP (digital signal processor), each GPIO pin can often be configured for a number of different functions.
// For example, a GPIO pin can be configured as a normal digital input/output pin or as a communication pin for a peripheral such as I2C, UART, SPI, etc.
// This configuration is called pin multiplexing.
// According to manual script of 28377, page 914, chapter 7.7 GPIO and Peripheral Muxing, Table 7.8, the third parameter is 6.


// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU __interrupts and clear all CPU __interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.I2CA_INT = &i2c_int1a_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripherals:
   I2CA_Init();
   Single_channel_config(CHANNEL_0); // This part is corresponding to the Seeed's Github, of which address is attached below:

//  https://github.com/Seeed-Studio/Seeed_LDC1612/blob/master/Seeed_LDC1612.cpp
// This part is corresponding to sensor.single_channel_config from Seeed-LDC1612

// Step 5. User specific code

   // Clear Counters
   PassCount = 0;
   FailCount = 0;

   // Clear incoming message buffer
   for (i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
   {
       I2cMsgIn1.MsgBuffer[i] = 0x0000;
   }

// Enable __interrupts required for this example

// Enable I2C __interrupt 1 in the PIE: Group 8 __interrupt 1
//   PieCtrlRegs.PIEIER8.bit.INTx1 = 0; // 1

// Enable CPU INT8 which is connected to PIE group 8
   IER |= M_INT8;
   EINT;

//   Single_channel_config(CHANNEL_0);
   // Application loop
   for(;;)
   {
//  Just show the results rather than using many interrupt

//       I2cRead16bitData(0x00);
       I2CA_ReadData_Channel(0);



   }   // end of for(;;)
}   // end of main


void I2CA_Init(void)
{


   // Initialize I2C
   I2caRegs.I2CSAR.all = I2C_SLAVE_ADDR;      // Slave address - EEPROM control code
   // Configured secondary device address. This address must be the same as the address of the slave device connected to the I2C bus.
   // When the ADDR pin is set low, the device I2C address is 0x2B; when the ADDR pin is set high, the I2C address  is 0x2B

   I2caRegs.I2CPSC.all = 8;            // Prescaler - need 7-12 MHz on module clk

   I2caRegs.I2CCLKL = 40;           // NOTE: must be non zero, sets the duration of the I2C clock low
   I2caRegs.I2CCLKH = 40;           // NOTE: must be non zero, sets the duration of the I2C clock high
   // Frequency = SYSCLKOUT / (I2CCLKL+I2CCLKH)
   // In this place, the target I2C frequency is 400kHz, the Prescaler is disposed to 12MHz, 12MHz / 400KHz = 30
   // To make the high and low levels 50/50, the I2caRegs.I2CCLKL = 15; I2caRegs.I2CCLKH = 15

   I2caRegs.I2CIER.all = 0x24;      // Enable SCD & ARDY __interrupts
   //  Bit 0: ARBL (Arbitration Lost)
   //  Bit 1: NACK (No Acknowledge)
   //  Bit 2: ARDY (Register Access Ready)
   //  Bit 3: RRDY (Receive Data Ready)
   //  Bit 4: XRDY (Transmit Data Ready)
   //  Bit 5: SCD (Stop Condition Detected)
   //  Bit 6: AAS (Addressed As Slave)

   I2caRegs.I2CMDR.bit.MST = 1; // Master mode bit. The I2C module is a master and generates the serial clock on the SCL pin.
   I2caRegs.I2CMDR.bit.TRX = 0; // Transmitter mode bit.The I2C module is a transmitter and transmits data on the SDA pin.
//   I2caRegs.I2CMDR.bit.DLB = 1;   // Digital Loopback Mode, if not using Loopback Mode, don't using this.
   I2caRegs.I2CMDR.bit.IRS = 1;  // Take I2C out of reset. In usual mode, just let it be 1.

   I2caRegs.I2CFFTX.all = 0x6000;   // Enable FIFO mode and TXFIFO
   // Reset Clears all data in the transmitted FIFO buffer and resets the FIFO pointer.
   // This operation is usually performed during initialization or when the FIFO needs to be reconfigured to ensure that there is no residual data in the FIFO buffer to avoid affecting subsequent transfer operations.

   I2caRegs.I2CFFRX.all = 0x2040;   // Enable RXFIFO, clear RXFFINT,
   // TX FIFO interrupt Enable Used to enable FIFO interrupt.
   // When the data in the TX FIFO reaches a predetermined threshold (such as when the FIFO becomes empty or the amount of data reaches a certain level), an interrupt is triggered,
   // notifying the CPU of the appropriate processing operation.
   // This facilitates efficient I2C communication, as the CPU can be notified of interruptions when needed, rather than constantly polling the FIFO state.
   return;
}
Uint16 DataBuffer;
Uint16 data[2];


int I2cRead16bitData(Uint16 SlaveRegAddr){

    if (I2caRegs.I2CMDR.bit.STP == 1)
    {
       return I2C_STP_NOT_READY_ERROR;
    }

    // FRAME 1
    I2caRegs.I2CSAR.all = 0x2B; //  I2cMsgIn1.SlaveAddress;


     // Check if bus busy
     if (I2caRegs.I2CSTR.bit.BB == 1)
     {
         return I2C_BUS_BUSY_ERROR;
     }

     // FRAME 2
     I2caRegs.I2CCNT = 0 + 1; // datLen = 0
     I2caRegs.I2CDXR.all = SlaveRegAddr; // Address of Channel 0 MSB Conversion Result of LDC1614

     I2caRegs.I2CMDR.all = 0x2620; // TRX=1, no stop
     /* I2C_MSGSTAT_SEND_NOSTOP */
     /* I2C_MSGSTAT_SEND_NOSTOP */
     /* I2C_MSGSTAT_SEND_NOSTOP */


     // SLAVE ACK
     // Wait Register-access-ready
     while(I2caRegs.I2CSTR.bit.ARDY == 0);

     // FRAME 3 is SLAVE ADDR
     I2caRegs.I2CSAR.all = 0x2B; //  I2cMsgIn1.SlaveAddress;
     I2caRegs.I2CCNT = 2; // MSB + LSB of the MSB of the DATA
     I2caRegs.I2CMDR.all = 0x2C20; // TRX=0, with stop
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */


     // Check the status of the receive FIFO
     while(I2caRegs.I2CFFRX.bit.RXFFST == 0);
     DataBuffer = I2caRegs.I2CDRR.all; // MSB of the sensor data MSB/LSB
     DataBuffer = DataBuffer << 8;
     while(I2caRegs.I2CFFRX.bit.RXFFST == 0);
     DataBuffer |= I2caRegs.I2CDRR.all; // LSB of the sensor data MSB/LSB
     DELAY_US(50);
     return 1;
}


int I2cWrite16bitData(Uint16 ConfigRegAddr, Uint16 value){
    data[1] = value & 0x00ff;
    data[0] = value >> 8;
    while(I2caRegs.I2CMDR.bit.STP == 1);


    // FRAME 1
    I2caRegs.I2CSAR.all = 0x2B; //  I2cMsgIn1.SlaveAddress;


     // Check if bus busy
     if (I2caRegs.I2CSTR.bit.BB == 1)
     {
         return I2C_BUS_BUSY_ERROR;
     }

     // FRAME 2
     I2caRegs.I2CCNT = 3; // Slave Register Address + Data MSB from Master + Data LSB from Master
     I2caRegs.I2CDXR.all = ConfigRegAddr; // The address of the registers which are needed in LDC1612.


     I2caRegs.I2CMDR.all = 0x6E20; // TRX=1, with stop
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */
     /* I2C_MSGSTAT_RECEIVE_WITHSTOP */
     // BIT13, BIT11, BIT10, BIT9

     // SLAVE ACK
     // Wait Register-access-ready
     while(I2caRegs.I2CSTR.bit.XRDY == 0);
     I2caRegs.I2CDXR.all = data[0];
     while(I2caRegs.I2CSTR.bit.XRDY == 0);
     I2caRegs.I2CDXR.all = data[1];

     // FRAME 3 is SLAVE ADDR
//     I2caRegs.I2CSAR.all = 0x2B; //  I2cMsgIn1.SlaveAddress;

//     I2caRegs.I2CCNT = 2; // MSB + LSB of the MSB of the DATA

     // Check the status of the receive FIFO
     // According to Seeed, write MSB first.
//     while(I2caRegs.I2CFFTX.bit.TXFFST == 0);
//     data[0] = I2caRegs.I2CDXR.all; // MSB of the sensor data MSB/LSB
//     while(I2caRegs.I2CFFTX.bit.TXFFST == 0);
//     data[1] = I2caRegs.I2CDXR.all; // LSB of the sensor data MSB/LSB
//
     while(I2caRegs.I2CSTR.bit.XRDY == 0);
     DELAY_US(50);
     return 0;
}


Uint32 I2CA_ReadData_Channel(Uint16 channel){

    if(channel == 0){
        // CHANNEL 0
//        I2cGet16bitData(0x00, DataMSB);
        I2cRead16bitData(0x00);
        raw_value = (Uint32)DataBuffer << 16; //
        I2cRead16bitData(0x01);
        raw_value |= (Uint32)DataBuffer;
//        Parse_result_data(channel, raw_value, result);
    }else{
        // CHANNEL 1
        I2cRead16bitData(0x02);
        raw_value = (Uint32)DataBuffer << 16;
        I2cRead16bitData(0x03);
        raw_value |= (Uint32)DataBuffer; //
//       Parse_result_data(channel, raw_value, result);
    }

   return 1;
}


// Configuration of single channel

int Single_channel_config(Uint16 channel){
    // The value of Rp, L, C, Q_factor can be set from TI calculator.
    Set_Rp(CHANNEL_0, 15.727);
    Set_L(CHANNEL_0, 18.147);
    Set_C(CHANNEL_0, 100);
    Set_Q_factor(CHANNEL_0, 35.97);
    //
    if (Set_FIN_FREF_DIV(CHANNEL_0)) {
            return -1;
        }

    Set_LC_stabilize_time(CHANNEL_0);

        /*Set conversion interval time*/
    Set_conversion_time(CHANNEL_0, 0x0546);

        /*Set driver current!*/
    Set_driver_current(CHANNEL_0, 0xA000);

        /*single conversion*/
    Set_mux_config(0x20C);
        /*start channel 0*/
    //Uint16 config = 0x1601; this line is on 98.
    Select_channel_to_convert(CHANNEL_0, &config);
    Set_sensor_config(config);
    return 0;
}


void Set_Rp(Uint16 channel, float n_kom) {
    resistance[channel] = n_kom;
}



void Set_L(Uint16 channel, float n_uh) {
    inductance[channel] = n_uh;
}


void Set_C(Uint16 channel, float n_pf) {
    capacitance[channel] = n_pf;
}


void Set_Q_factor(Uint16 channel, float q) {
    Q_factor[channel] = q;
}


Uint32 Set_FIN_FREF_DIV(Uint16 channel) {
    Fsensor[channel] = 1 / (2 * 3.14 * sqrt(inductance[channel] * capacitance[channel] * pow(10, -18))) * pow(10, -6);

    FIN_DIV = (Uint16)(Fsensor[channel] / 8.75 + 1);


    if (Fsensor[channel] * 4 < 40) {
        FREF_DIV = 2;
        Fref[channel] = 40 / 2;
    } else {
        FREF_DIV = 4;
        Fref[channel] = 40 / 4;
    }

    value = FIN_DIV << 12;
    value |= FREF_DIV;
    return I2cWrite16bitData(SET_FREQ_REG_START + channel, value);
}


Uint32 Set_LC_stabilize_time(Uint16 channel){
    value = 30;
    return I2cWrite16bitData(SET_LC_STABILIZE_REG_START + channel, value);
}


Uint32 Set_conversion_time(Uint16 channel, Uint16 value) {
    return I2cWrite16bitData(SET_CONVERSION_TIME_REG_START + channel, value);
}


Uint32 Set_conversion_offset(Uint16 channel, Uint16 value) {
    return I2cWrite16bitData(SET_CONVERSION_OFFSET_REG_START + channel, value);
}


Uint32 Set_driver_current(Uint16 channel, Uint16 value) {
    return I2cWrite16bitData(SET_DRIVER_CURRENT_REG + channel, value);
}


Uint32 Set_ERROR_CONFIG(Uint16 value) {
    return I2cWrite16bitData(ERROR_CONFIG_REG, value);
}


Uint32 Set_mux_config(Uint16 value) {
    return I2cWrite16bitData(MUL_CONFIG_REG, value);
}


Uint32 Set_sensor_config(Uint16 value) {
    return I2cWrite16bitData(SENSOR_CONFIG_REG, value);
}


Uint32 Reset_sensor() {
    return I2cWrite16bitData(SENSOR_RESET_REG, 0x8000);
}



void Select_channel_to_convert(Uint16 channel, Uint16* value) {
    switch (channel) {
        case 0: *value &= 0x3fff;
            break;
        case 1: *value &= 0x7fff;
            *value |= 0x4000;
            break;
        case 2: *value &= 0xbfff;
            *value |= 0x8000;
            break;
        case 3: *value |= 0xc000;
            break;
    }
}

void Read_sensor_infomation() {
    I2cWrite16bitData(READ_MANUFACTURER_ID, &value);
    return ;
}


Uint32 Parse_result_data(Uint16 channel, Uint32 raw_result, Uint32* result) {
    *result = raw_result & 0x0fffffff;
    if (0xfffffff == *result) {
        *result = 0;
        return -1;
    }
    // else if(0==*result)
    // {
    //     Serial.println("result is none!!!");
    // }
    value = raw_result >> 24;
    if (value & 0x80) {
        ERROR = 1;
    }
    if (value & 0x40) {
        ERROR = 2;
    }
    if (value & 0x20) {
        ERROR = 3;
    }
    if (value & 0x10) {
        ERROR = 4;
    }
    return 0;
}


__interrupt void i2c_int1a_isr(void)     // I2C-A
{
   Uint16 IntSource, i;

   // Read __interrupt source
   IntSource = I2caRegs.I2CISRC.all;

   // Interrupt source = stop condition detected
   if(IntSource == I2C_SCD_ISRC)
   {
      // If completed message was writing data, reset msg to inactive state
      if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_WRITE_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
      }
      else
      {
         // If a message receives a NACK during the address setup portion of the
         // EEPROM read, the code further below included in the register access ready
         // __interrupt source code will generate a stop condition. After the stop
         // condition is received (here), set the message status to try again.
         // User may want to limit the number of retries before generating an error.
         if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_SEND_NOSTOP;
         }
         // If completed message was reading EEPROM data, reset msg to inactive state
         // and read data from FIFO.
         else if (CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_READ_BUSY)
         {
            CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_INACTIVE;
            for(i=0; i < I2C_NUMBYTES; i++)
            {
              CurrentMsgPtr->MsgBuffer[i] = I2caRegs.I2CDRR.all;
            }
         {
         // Check received data
         for(i=0; i < I2C_NUMBYTES; i++)
         {
            if(I2cMsgIn1.MsgBuffer[i] == I2cMsgOut1.MsgBuffer[i])
            {
                PassCount++;
            }
            else
            {
                FailCount++;
            }
         }
         if(PassCount == I2C_NUMBYTES)
         {
            pass();
         }
         else
         {
            fail();
         }

      }

    }
      }
   }  // end of stop condition detected

   // Interrupt source = Register Access Ready
   // This __interrupt is used to determine when the EEPROM address setup portion of the
   // read data communication is complete. Since no stop bit is commanded, this flag
   // tells us when the message has been sent instead of the SCD flag. If a NACK is
   // received, clear the NACK bit and command a stop. Otherwise, move on to the read
   // data portion of the communication.
   else if(IntSource == I2C_ARDY_ISRC)
   {
      if(I2caRegs.I2CSTR.bit.NACK == 1)
      {
         I2caRegs.I2CMDR.bit.STP = 1;
         I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
      }
      else if(CurrentMsgPtr->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP_BUSY)
      {
         CurrentMsgPtr->MsgStatus = I2C_MSGSTAT_RESTART;
      }
   }  // end of register access ready

   else
   {
      // Generate some error due to invalid __interrupt source
     asm("   ESTOP0");
   }

   // Enable future I2C (PIE Group 8) __interrupts
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

void pass()
{
   asm("   ESTOP0");
    for(;;);
}

void fail()
{
   asm("   ESTOP0");
    for(;;);
}
