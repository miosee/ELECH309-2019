#include "init.h"
#include "audio.h"
#include "lcd.h"
#include "clav.h"
#include "adc.h"
#include <xc.h>
#include <math.h>


#define SAMPLE_NB  50

int main(void) {
    int wave[SAMPLE_NB];
    int i;
    
    // I. Initialisation des périphériques
    // On initialise l'oscillateur pour fonctionner à 40MHz
	oscillatorInit(OSC_FREQ_8MHZ);
    // On configure la communication vers le DAC audio de la carte d'extension
    audioInit();
    // On configure le TIMER2 pour déborder à 20kHz. Il servira de base de
    // temps pour l'écriture dans le DAC audio
	PR2 = 1999;                 // T2=50us=(PR2+1)*25ns => PR2=1999
    T2CONbits.TON = 1;
    // Configuration d'une patte pour visualiser le timing des envois au DAC
    TRISGbits.TRISG12 = 0;


    // II. Initialisation des variables
    // On initialise le vecteur contenant le sinus à envoyer sur le DAC
    for (i=0; i<SAMPLE_NB; i++) {
        wave[i] = 1000*(1+sin(2*3.1416*i/SAMPLE_NB));
    }
    i = 0;
	while(1) {
        // I. Envoi d'un échantillon au DAC
        if (IFS0bits.T2IF) {
            LATGbits.LATG12 = 1;
            IFS0bits.T2IF = 0;
            audioWrite((long)wave[i++]);
            if (i >= SAMPLE_NB) {
                i = 0;
            }
            LATGbits.LATG12 = 0;
        }
    }
}
