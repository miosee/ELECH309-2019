#include <xc.h>

//  CONFIGURATION BITS
///////////////////////////////////////////////////////////////////////////////
// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

// The dsPIC will be clocked by the primary oscillator with a 10MHz crystal.
// We want to use the PLL to obtain Fosc = 80MHz ( <=> 40MIPS ).
// Problem : with a 10MHz crystal, PLL constraints are not met with the
// default parameter.
// Solution :
//	- boot using the internal FRC oscillator as clock source,
//	- set the right PLL parameters to obtain Fosc = 80MHz, without violating
//	  the PLL constraints,
//	- switch the clock source to the PLL
//	- wait for the end of the clock switch
//
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config POSCMD = XT              // Primary Oscillator Source (XT Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

void oscillatorInit(int oscFreqInMHz) {
	// Configures PLL prescaler, PLL postscaler, PLL divisor
	// to obtain Fosc = 80MHz with the xt oscillator
	// Fosc = Fin*M/(N1+N2), where :
	// 		N1 = PLLPRE + 2
	// 		N2 = 2 x (PLLPOST + 1)
	//		M = PLLFBD + 2
    if (oscFreqInMHz == 8) {
        PLLFBD = 38;            // M=40
        CLKDIVbits.PLLPRE = 0;	// N1 = 2
        CLKDIVbits.PLLPOST = 0;	// N2 = 2
    } else if (oscFreqInMHz == 10) {
        PLLFBD = 30;			// M = 32
        CLKDIVbits.PLLPRE = 0;	// N1 = 2
        CLKDIVbits.PLLPOST = 0;	// N2 = 2
    }
	// Initiate Clock Switch to Primary Oscillator with PLL
	__builtin_write_OSCCONH( 3 );
	__builtin_write_OSCCONL( 1 );
	// Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b011);
}
