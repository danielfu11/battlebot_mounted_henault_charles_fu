/*
 * main.c
 *
 *
 *
 */

// INCLUDE ALL HEADER FILES
#include "msp.h"
#include "port_final.h"
#include "timer_final.h"
#include "uart_final.h"
#include "functions_final.h"
#include "circbuf_final.h"


CircBuf_t Ranged_Controls;
CircBuf_t* Ranged = &Ranged_Controls;
volatile uint32_t LeftEnc = 0;          // Counts left encoder pulses
volatile uint32_t RightEnc = 0;         // Counts right encoder pulses
volatile uint8_t flags = 0;             // BIT0: melee = 0, ranged = 1 BIT1: received commands = 1
volatile float distance = 0.0;

void main(void)
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // Stop watchdog timer
    port_config();
    timer_config();
    uart_config();
    CB_initialize_buffer(&Ranged, 100);
    __enable_irq();

    while(1){
        if (flags & BIT1){          // if a commmand has been received through terminal
            Receive_Function();     // Interpret the commands
            flags &= ~BIT1;         // clear command flag
        }
    }
}
