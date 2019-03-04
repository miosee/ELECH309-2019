#include "init.h"
#include <xc.h>


int main(void)
{
    // Configuration de l'horloge pour avoir FCY = 40MHz
	oscillatorInit(OSC_FREQ_8MHZ);

    // I. Configuration des sorties pour les LEDs
    TRISAbits.TRISA0 = 0;   // RA0, connectee a une LED est configuree en sortie
    TRISCbits.TRISC4 = 0;   // RC4, GPIO de la carte d'extension est configuree en sortie (pour la led UB)
    
    // II. Configuration de RC1 en sortie
   	TRISCbits.TRISC1 = 0;
    // II. Configuration du timer2 a 10kHz
	PR2 = 3999;                 // T2=100us=(PR2+1)*25ns => PR2=3999
	T2CONbits.TON = 1;
    
    // III. Configuration de RA1 en sortie
   	TRISAbits.TRISA1 = 0;
    // III. Configuration du timer1 a 2Hz
    T1CONbits.TCKPS = 0b11;     // prescaler 256:1
	PR1 = 39062;                 // T1=250ms=(PR1+1)*25ns*256 => PR1=39062
	T1CONbits.TON = 1;

	while(1) {
        // I. Connexion entre RD7 et RA0 (LED de l'Explorer16)
        LATAbits.LATA0 = !PORTDbits.RD7;
        // I. Connexion entre RD7 et RC4 (LED UB)
        LATCbits.LATC4 = !PORTDbits.RD7;
        
        // II. Si le timer2 deborde, on change l'etat de RC1
        if (IFS0bits.T2IF) {
            IFS0bits.T2IF = 0;
            LATCbits.LATC1 = !LATCbits.LATC1;
        }

        // III. Si le timer1 deborde, on change l'etat de RA1
        if (IFS0bits.T1IF) {
            IFS0bits.T1IF = 0;
            LATAbits.LATA1 = !LATAbits.LATA1;
        }
	}
}
