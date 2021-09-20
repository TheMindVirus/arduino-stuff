//FPGA Manufacturer: Intel Altera Cyclone 10
//FPGA Model Number: 10CL016YU256C8G

#include "VidorCYC.h"

#define PEX_PIN1    CYC_R10        //WAKE#
#define PEX_PIN2    3V3            //VCC_3V3
#define PEX_PIN3    CYC_P11        //RESERVED
#define PEX_PIN4    GND            //GND
#define PEX_PIN5    CYC_R11        //RESERVED
#define PEX_PIN6    CYC_P8         //N/C
#define PEX_PIN7    CYC_M6         //RESERVED
#define PEX_PIN8    CYC_L7         //USIM_VDD
#define PEX_PIN9    GND            //GND
#define PEX_PIN10   CYC_N8         //USIM_DATA
#define PEX_PIN11   CYC_T8         //UART_RX
#define PEX_PIN12   CYC_M8         //USIM_CLK
#define PEX_PIN13   CYC_R8         //UART_TX
#define PEX_PIN14   CYC_L8         //USIM_RST
#define PEX_PIN15   GND            //GND
#define PEX_PIN16   CYC_M10        //RESERVED
#define PEX_PIN17   NINA_GPIO24    //RI
#define PEX_PIN18   GND            //GND
#define PEX_PIN19   NINA_GPIO25    //RESERVED
#define PEX_PIN20   CYC_N12        //W_DISABLE#
#define PEX_PIN21   GND            //GND
#define PEX_PIN22   CYC_T12        //PERST#
#define PEX_PIN23   CYC_T9         //UART_CTS
#define PEX_PIN24   3V3            //RESERVED
#define PEX_PIN25   CYC_R9         //UART_RTS
#define PEX_PIN26   GND            //GND
#define PEX_PIN27   GND            //GND
#define PEX_PIN28   CYC_T13        //N/C
#define PEX_PIN29   GND            //GND
#define PEX_PIN30   CYC_R12        //I2C_SCL
#define PEX_PIN31   CYC_A9         //DTR
#define PEX_PIN32   CYC_F13        //I2C_SDA
#define PEX_PIN33   CYC_B9         //RESERVED
#define PEX_PIN34   GND            //GND
#define PEX_PIN35   GND            //GND
#define PEX_PIN36   USB_DM         //USB_DM
#define PEX_PIN37   GND            //GND
#define PEX_PIN38   USB_DP         //USB_DP
#define PEX_PIN39   3V3            //VCC_3V3
#define PEX_PIN40   GND            //GND
#define PEX_PIN41   3V3            //VCC_3V3
#define PEX_PIN42   CYC_R13        //LED_WWAN#
#define PEX_PIN43   GND            //GND
#define PEX_PIN44   CYC_P14        //RESERVED
#define PEX_PIN45   CYC_T15        //PCM_CLK
#define PEX_PIN46   CYC_R14        //RESERVED
#define PEX_PIN47   CYC_T14        //PCM_DOUT
#define PEX_PIN48   CYC_F14        //N/C
#define PEX_PIN49   CYC_D16        //PCM_DIN
#define PEX_PIN50   GND            //GND
#define PEX_PIN51   CYC_D15        //PCM_SYNC
#define PEX_PIN52   3V3            //VCC_3V3

#define PEX_RST     PEX_PIN22      //PERST#

size_t PEX_IO_PINS[] =
{
    PEX_PIN1,   //CYC_R10
//  PEX_PIN2,   //3V3
    PEX_PIN3,   //CYC_P11
//  PEX_PIN4,   //GND
    PEX_PIN5,   //CYC_R11
    PEX_PIN6,   //CYC_P8
    PEX_PIN7,   //CYC_M6
    PEX_PIN8,   //CYC_L7
//  PEX_PIN9,   //GND
    PEX_PIN10,  //CYC_N8
    PEX_PIN11,  //CYC_T8
    PEX_PIN12,  //CYC_M8
    PEX_PIN13,  //CYC_R8
    PEX_PIN14,  //CYC_L8
//  PEX_PIN15,  //GND
    PEX_PIN16,  //CYC_M10
//  PEX_PIN17,  //NINA_GPIO24
//  PEX_PIN18,  //GND
//  PEX_PIN19,  //NINA_GPIO25
    PEX_PIN20,  //CYC_N12
//  PEX_PIN21,  //GND
    PEX_PIN22,  //CYC_T12
    PEX_PIN23,  //CYC_T9
//  PEX_PIN24,  //3V3
    PEX_PIN25,  //CYC_R9
//  PEX_PIN26,  //GND
//  PEX_PIN27,  //GND
    PEX_PIN28,  //CYC_T13
//  PEX_PIN29,  //GND
    PEX_PIN30,  //CYC_R12
    PEX_PIN31,  //CYC_A9
    PEX_PIN32,  //CYC_F13
    PEX_PIN33,  //CYC_B9
//  PEX_PIN34,  //GND
//  PEX_PIN35,  //GND
//  PEX_PIN36,  //USB_DM
//  PEX_PIN37,  //GND
//  PEX_PIN38,  //USB_DP
//  PEX_PIN39,  //3V3
//  PEX_PIN40,  //GND
//  PEX_PIN41,  //3V3
    PEX_PIN42,  //CYC_R13
//  PEX_PIN43,  //GND
    PEX_PIN44,  //CYC_P14
    PEX_PIN45,  //CYC_T15
    PEX_PIN46,  //CYC_R14
    PEX_PIN47,  //CYC_T14
    PEX_PIN48,  //CYC_F14
    PEX_PIN49,  //CYC_D16
//  PEX_PIN50,  //GND
    PEX_PIN51,  //CYC_D15
//  PEX_PIN52,  //3V3
};

size_t PEX_IO_COUNT = sizeof(PEX_IO_PINS) / sizeof(size_t);

const char* PEX_IO_LABELS[] =
{
    "PEX_PIN1",   //CYC_R10
//  "PEX_PIN2",   //3V3
    "PEX_PIN3",   //CYC_P11
//  "PEX_PIN4",   //GND
    "PEX_PIN5",   //CYC_R11
    "PEX_PIN6",   //CYC_P8
    "PEX_PIN7",   //CYC_M6
    "PEX_PIN8",   //CYC_L7
//  "PEX_PIN9",   //GND
    "PEX_PIN10",  //CYC_N8
    "PEX_PIN11",  //CYC_T8
    "PEX_PIN12",  //CYC_M8
    "PEX_PIN13",  //CYC_R8
    "PEX_PIN14",  //CYC_L8
//  "PEX_PIN15",  //GND
    "PEX_PIN16",  //CYC_M10
//  "PEX_PIN17",  //NINA_GPIO24
//  "PEX_PIN18",  //GND
//  "PEX_PIN19",  //NINA_GPIO25
    "PEX_PIN20",  //CYC_N12
//  "PEX_PIN21",  //GND
    "PEX_PIN22",  //CYC_T12
    "PEX_PIN23",  //CYC_T9
//  "PEX_PIN24",  //3V3
    "PEX_PIN25",  //CYC_R9
//  "PEX_PIN26",  //GND
//  "PEX_PIN27",  //GND
    "PEX_PIN28",  //CYC_T13
//  "PEX_PIN29",  //GND
    "PEX_PIN30",  //CYC_R12
    "PEX_PIN31",  //CYC_A9
    "PEX_PIN32",  //CYC_F13
    "PEX_PIN33",  //CYC_B9
//  "PEX_PIN34",  //GND
//  "PEX_PIN35",  //GND
//  "PEX_PIN36",  //USB_DM
//  "PEX_PIN37",  //GND
//  "PEX_PIN38",  //USB_DP
//  "PEX_PIN39",  //3V3
//  "PEX_PIN40",  //GND
//  "PEX_PIN41",  //3V3
    "PEX_PIN42",  //CYC_R13
//  "PEX_PIN43",  //GND
    "PEX_PIN44",  //CYC_P14
    "PEX_PIN45",  //CYC_T15
    "PEX_PIN46",  //CYC_R14
    "PEX_PIN47",  //CYC_T14
    "PEX_PIN48",  //CYC_F14
    "PEX_PIN49",  //CYC_D16
//  "PEX_PIN50",  //GND
    "PEX_PIN51",  //CYC_D15
//  "PEX_PIN52",  //3V3
};
