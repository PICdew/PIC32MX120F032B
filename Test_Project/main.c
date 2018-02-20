/* DEVCFG3 */
/* USERID = No Setting */
#pragma config PMDL1WAY = OFF           /* Peripheral Module Disable Configuration (Allow multiple reconfigurations) */
#pragma config IOL1WAY = OFF            /* Peripheral Pin Select Configuration (Allow multiple reconfigurations) */

/* DEVCFG2 */
#pragma config FPLLIDIV = DIV_1         /* PLL Input Divider (1x Divider) */
#pragma config FPLLMUL = MUL_24         /* PLL Multiplier (24x Multiplier) */
#pragma config FPLLODIV = DIV_1         /* System PLL Output Clock Divider (PLL Divide by 1) */

/* DEVCFG1 */
#pragma config FNOSC = FRC              /* Oscillator Selection Bits (Fast RC Osc (FRC)) */
#pragma config FSOSCEN = OFF            /* Secondary Oscillator Enable (Disabled) */
#pragma config IESO = OFF               /* Internal/External Switch Over (Disabled) */
#pragma config POSCMOD = HS             /* Primary Oscillator Configuration (HS osc mode) */
#pragma config OSCIOFNC = OFF           /* CLKO Output Signal Active on the OSCO Pin (Disabled) */
#pragma config FPBDIV = DIV_8           /* Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8) */
#pragma config FCKSM = CSDCMD           /* Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled) */
#pragma config WDTPS = PS1048576        /* Watchdog Timer Postscaler (1:1048576) */
#pragma config WINDIS = OFF             /* Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode) */
#pragma config FWDTEN = OFF             /* Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls)) */
#pragma config FWDTWINSZ = WINSZ_25     /* Watchdog Timer Window Size (Window Size is 25%) */

/* DEVCFG0 */
#pragma config JTAGEN = ON              /* JTAG Enable (JTAG Port Enabled) */
#pragma config ICESEL = ICS_PGx1        /* ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1) */
#pragma config PWP = OFF                /* Program Flash Write Protect (Disable) */
#pragma config BWP = OFF                /* Boot Flash Write Protect bit (Protection Disabled) */
#pragma config CP = OFF                 /* Code Protect (Protection Disabled) */

#include <xc.h>
#include "digital_io.h"

int main(void){
    pin_set_direction(&RB1, INPUT);
    pin_set_direction(&RA4, OUTPUT);
    pin_open_drain_selection(&RB1, ON); /* Does nothing, RB1 not 5V Tolerant */
    pin_open_drain_selection(&RB5, ON);
    pin_select_working_mode(&RA3, ANALOGIC); /* Does not work, RA3 not AN port */
    pin_select_working_mode(&RA0, ANALOGIC);
    pin_assign_pull_up(&RB0, ON);
    pin_assign_pull_down(&RB2, ON);
    pin_assign_interrupt_on_change(&RB1, ON);
    pin_assign_peripheral(&RA1, &INT4); /* Should do nothing because assignment is illegal */
    pin_assign_peripheral(&RB3, &INT4);   
    while(1){
        if(pin_read(&RB1) == HIGH) pin_set_output_high(&RA4);
        else pin_set_output_low(&RA4);
    }
}