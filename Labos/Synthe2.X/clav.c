#include <xc.h>
#define FCY 40000000
#include <libpic30.h>

void clavInit(void)
{
    TRISB |= 0x0F00;
    TRISD &= 0xF0FF;    // colonnes du clavier en output
    AD1PCFGL |= 0x0F00; // colonnes du clavier en numerique
    AD2PCFGL |= 0x0F00; // colonnes du clavier en numerique
}

char readClav( void )
{
    LATDbits.LATD8 = 1;
    LATDbits.LATD9 = 0;
    LATDbits.LATD10 = 0;
    LATDbits.LATD11 = 0;

    __delay_us(25);

    if(PORTBbits.RB8) return '1';
    if(PORTBbits.RB9) return '4';
    if(PORTBbits.RB10) return '7';
    if(PORTBbits.RB11) return 'A';

    LATDbits.LATD8 = 0;
    LATDbits.LATD9 = 1;
    LATDbits.LATD10 = 0;
    LATDbits.LATD11 = 0;

    __delay_us(25);

    if(PORTBbits.RB8) return '2';
    if(PORTBbits.RB9) return '5';
    if(PORTBbits.RB10) return '8';
    if(PORTBbits.RB11) return 'B';

    LATDbits.LATD8 = 0;
    LATDbits.LATD9 = 0;
    LATDbits.LATD10 = 1;
    LATDbits.LATD11 = 0;

    __delay_us(25);

    if(PORTBbits.RB8) return '3';
    if(PORTBbits.RB9) return '6';
    if(PORTBbits.RB10) return '9';
    if(PORTBbits.RB11) return 'C';

    LATDbits.LATD8 = 0;
    LATDbits.LATD9 = 0;
    LATDbits.LATD10 = 0;
    LATDbits.LATD11 = 1;

    __delay_us(25);

    if(PORTBbits.RB8) return 'F';
    if(PORTBbits.RB9) return 'E';
    if(PORTBbits.RB10) return 'D';
    if(PORTBbits.RB11) return 'C';

    return 'z';
}
