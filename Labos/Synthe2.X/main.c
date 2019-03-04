#include "init.h"
#include "audio.h"
#include "lcd.h"
#include "clav.h"
#include "adc.h"
#include <xc.h>
#include <math.h>


#define SAMPLE_NB  50


int main(void) {
    int wave[SAMPLE_NB];    // Vecteur contenant l'onde � produire
    int i;                  // index de boucles
    int active = 0;         // variable d'etat indiquant si on doit produire le son ou non
    char c, oldC = 'z';     // variables pour la lecture du clavier
    
    // I. Initialisation des p�riph�riques
    // On initialise l'oscillateur pour fonctionner � 40MHz
	oscillatorInit(OSC_FREQ_8MHZ);
    // On configure la communication vers le DAC audio de la carte d'extension
    audioInit();
    // On configure les GPIOS du clavier
    clavInit();
    // Configuration de 2 pattes en sortie pour visualiser les timings
    TRISGbits.TRISG12 = 0;  // Visualise les envois au DAC
    TRISGbits.TRISG13 = 0;  // Visualise la boucle principale
    // On configure le TIMER2 pour d�border � 20kHz. Il servira de base de
    // temps pour l'�criture dans le DAC audio
	PR2 = 1999;                 // T2=50us=(PR2+1)*25ns => PR2=1999
    T2CONbits.TON = 1;
    

    // II. Initialisation des variables
    // On initialise le vecteur contenant le sinus � envoyer sur le DAC
    for (i=0; i<SAMPLE_NB; i++) {
        wave[i] = 2000*(1+sin(2*3.1416*i/SAMPLE_NB));
    }
    i = 0;
	while(1) {
        LATGbits.LATG13 = 1;
        // Lecture du clavier
        // si on appuie sur 'A', on doit activer/desactiver le son
        // readClav() prend de 25us � 100us � s'ex�cuter.
        // Elle perturbe donc le timing qu'on voulait imposer avec le TIMER2
        c = readClav();
        /* Quand quelqu'un appuie sur une touche du clavier, cela dure au moins
         * 100ms, on passera donc plusieurs fois ici, pour �viter de detecter 
         * plusieurs fois le meme appui, on detecte les changements en comparant
         * avec l'ancienne valeur. */
        if (c != oldC) {
            oldC = c;
            if (c == 'A') {
                active = !active;
            }
        }
        LATGbits.LATG13 = 0;
        // Envoi des echantillons au DAC (si actif)
        if (active) {
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
}
