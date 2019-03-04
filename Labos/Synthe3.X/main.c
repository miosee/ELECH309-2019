#include "init.h"
#include "audio.h"
#include "lcd.h"
#include "clav.h"
#include "adc.h"
#include <xc.h>
#include <math.h>


#define SAMPLE_NB  50

/* Ces variables sont maintenant utilisees dans une ISR
 * Elles doivent donc etre 
 *   -  globales, pour etre accessibles au main et a l'ISR
 *   -  volatiles, car elles peuvent changer a tout moment
 * */
volatile int wave[SAMPLE_NB];
volatile int active;

// ISR associee au TIMER2
// On y place l'envoi d'echantillons au DAC audio
void _ISR _T2Interrupt(void) {
    static int i = 0;
    
    LATGbits.LATG12 = 1;
    IFS0bits.T2IF = 0;
    if (active) {
        audioWrite((long) wave[i++]);
        if (i >= SAMPLE_NB) {
            i = 0;
        }
    }
    LATGbits.LATG12 = 0;
}



int main(void) {
    int i;                  // index de boucles
    char c, oldC = 'z';     // variables pour la lecture du clavier
    
    // I. Initialisation des périphériques
    // On initialise l'oscillateur pour fonctionner à 40MHz
	oscillatorInit(OSC_FREQ_8MHZ);
    // On configure la communication vers le DAC audio de la carte d'extension
    audioInit();
    // On configure les GPIOS du clavier
    clavInit();
    // Configuration de 2 pattes en sortie pour visualiser les timings
    TRISGbits.TRISG12 = 0;  // Visualise les envois au DAC
    TRISGbits.TRISG13 = 0;  // Visualise la boucle principale

    // II. Initialisation des variables
    // On initialise le vecteur contenant le sinus à envoyer sur le DAC
    for (i=0; i<SAMPLE_NB; i++) {
        wave[i] = 1000*(1+sin(2*3.1416*i/SAMPLE_NB));
    }
    active = 0;
    
    // III. On configure le TIMER2 pour déborder à 20kHz. Il servira de base de
    // temps pour l'écriture dans le DAC audio
	PR2 = 1999;                 // T2=50us=(PR2+1)*25ns => PR2=1999
    T2CONbits.TON = 1;
    IEC0bits.T2IE = 1;      // on active l'interruption du TIMER2

	PR3 = 39999;                 // T2=1ms=(PR3+1)*25ns => PR2=39999
    T3CONbits.TON = 1;

	while(1) {
        if (IFS0bits.T3IF) {
            LATGbits.LATG13 = 1;
            IFS0bits.T3IF = 0;
            // Lecture du clavier
            // si on appuie sur 'A', on doit activer/desactiver le son
            c = readClav();
            /* Quand quelqu'un appuie sur une touche du clavier, cela dure au moins
             * 100ms, on passera donc plusieurs fois ici, pour éviter de detecter 
             * plusieurs fois le meme appui, on detecte les changements en comparant
             * avec l'ancienne valeur. */
            if (c != oldC) {
                oldC = c;
                if (c == 'A') {
                    active = !active;
                }
            }
            LATGbits.LATG13 = 0;
        }
    }
}
