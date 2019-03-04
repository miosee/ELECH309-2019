#include <xc.h>


void audioInit(void)
{
    TRISBbits.TRISB2 = 0;
    LATBbits.LATB2 = 1;
    SPI1CON1bits.MODE16 = 1;        // mots de 16 bits
    SPI1CON1bits.PPRE = 1;          // primary prescaler = 16:1
    SPI1CON1bits.SPRE = 7;          // secondary prescaler = 1:1
    SPI1CON1bits.MSTEN = 1;         // mode master
    SPI1CON1bits.CKP = 1;           // on veut le mode (1,1), ...
    SPI1CON1bits.CKE = 0;           //  mais (CKE est l'inverse de CPHA)
    SPI1STATbits.SPIEN = 1;         // active le périphérique
}


void audioWrite(int sig)
{
    IFS0bits.SPI1IF = 0;
    
    LATBbits.LATB2 = 0;
    SPI1BUF = (0x3000|sig)&0x3FFF;
    while(!IFS0bits.SPI1IF);
    LATBbits.LATB2 = 1;
    SPI1BUF;
}
