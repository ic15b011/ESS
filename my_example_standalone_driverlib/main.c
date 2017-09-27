/*
 *
 * Toggles led on pin 1 on port N
 *
 * Already set build options (no need to change anything):
 * Stack size set to 1024 byte
 * Heap size disabled - No malloc()
 * No code optimization
 * Strict floating point interrupt behaviour
 * Hardware floating point unit activated
 *
 */

#define TARGET_IS_TM4C129_RA2
#include <stdbool.h> /*driverlib header requires stdbool.h to be included a first header file before any driverlib header*/
#include <stdint.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>/*supplies GPIO_PIN_x*/
#include <driverlib/sysctl.h>
#include <driverlib/rom.h>
#include <inc/hw_memmap.h>/*supplies GPIO_PORTx_BASE*/

/*Controller is initially clocked with 16MHz*/
/* !! Changing this define does not change clock speed !! */
#define F_CPU 16000000

void main (void) {

    uint32_t ui32Strength;
    uint32_t ui32PinType;
    uint8_t ui8val = 0x1;
    //uint8_t ui8val2 = 0x55;
    uint32_t ui32Loop = 0;

	/*activate gpio port n*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    /*activate gpio port f*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /*configure GPIO_PIN_1 on port N as std pin*/
    GPIOPadConfigGet(GPIO_PORTN_BASE, GPIO_PIN_1, &ui32Strength, &ui32PinType);
    GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_1,ui32Strength,GPIO_PIN_TYPE_STD);

    /*configure GPIO_PIN_0 on port N as std pin*/
    GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0,ui32Strength,GPIO_PIN_TYPE_STD);

    /*configure GPIO_PIN_0 on port F as std pin*/
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0,ui32Strength,GPIO_PIN_TYPE_STD);
    /*configure GPIO_PIN_4 on port F as std pin*/
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,ui32Strength,GPIO_PIN_TYPE_STD);

    /*set pin 0 of gpio port n to output*/
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE,GPIO_PIN_1 | GPIO_PIN_0);

    /*set pin 4 of gpio port f to output*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_4);

    /*set pin 0 of gpio port f to output*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);


    GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_4, ui8val);
    for(;;) {
        ui8val = ui8val ^ 0xFF;/*toggle bit 1 in variable val*/
        /*write value of val to pin 1 of port n*/
        GPIOPinWrite (GPIO_PORTN_BASE, GPIO_PIN_1 | GPIO_PIN_0, ui8val);
        //GPIOPinWrite (GPIO_PORTN_BASE, GPIO_PIN_0, ui8val);
        /*write value of val to pin 1 of port f*/
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, ui8val);
        //ui8val2 = (ui8val) << 4;
        //GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_4, ui8val);
        // for(ui32Loop = 0; ui32Loop < 400000; ui32Loop++){}
        ROM_SysCtlDelay(F_CPU/2/3);  //approx 0,5 s
    }
}
