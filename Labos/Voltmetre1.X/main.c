#include "init.h"
#include "audio.h"
#include "lcd.h"
#include "clav.h"
#include "adc.h"
#include <xc.h>


int main(void) {
    int voltage;
    int n, tmp;
    
    // Configuration de l'horloge pour avoir FCY = 40MHz
	oscillatorInit(OSC_FREQ_8MHZ);
    
    // Configuration des LEDs
    TRISA = 0xFF00;     // configure RA0->RA7 en sortie

    // Configuration de L'ADC pour utilisation en polling sur AN0
    adcPollingInit();
    
    // Configuration du Timer2 pour deborder à 1kHz
	PR2 = 39999;                 // T2=1ms=(PR2+1)*25ns => PR2=39999
	T2CONbits.TON = 1;
    
	while(1) {
        // Si le TIMER2 a deborde, on demarre une conversion de l'ADC
        if (IFS0bits.T2IF) {
            IFS0bits.T2IF = 0;
            adcPollingStart();
        }
        // Si l'ADC a fini une conversion, on lit le resultat et on l'affiche sur led LEDs
        if (adcPollingConversionFinished()) {
            voltage = adcPollingRead();
            // Affichage sur les LEDS, voir plus bas pour l'explication detaillee
            n = (8*voltage)/4095;   // calcul du nombre de LEDs a allumer
            tmp = 1 << n;           // Shift a gauche
            LATA = tmp - 1;         // affichage proprement dit
        }
	}
}


/* Calcul de la valeur a afficher sur les LEDs
 * 
 * On sait que 0 <= voltage <= 4095
 * On veut allumer de 0 a 8 LEDs, la 1ere etape est donc de transformer voltage
 * en une valeur comprise entre 0 et 8 :
 * 
 *     n = (8*voltage)/4095;
 * 
 * Les parenthèses assure que la multiplication soit faite avant la division.
 * Comme on travaille avec des entiers, c'est important pour eviter les erreurs d'arrondi
 * 
 * n nous donne donc le nombre de LEDs a allumer. Pour faire cela, on peut utiliser
 * une serie de if/else (ou un switch/case), mais on peut aussi faire 
 * un calcul en binaire :
 *   Le resultat qu'on veut obtenir est un nombre binaire dont les n bits de poids faible
 *   valent 1 et les autres 0. Prenons par exemple n = 5, on veut obtenir 0b0001 1111
 *   (Bien que le dsPIC travaille en 16 bits, les valeurs seront donnees sur 8 bits
 *   pour plus de simplicite, les 8 bits de poids forts seront toujours a 0).
 * 
 * Pour obtenir ce resulat, on va partir du nombre 1 : 0b0000 0001
 * On va ensuite faire n "shift a gauche" sur ce nombre : c'est a dire qu'on decale
 * tous les bits vers la gauche (le bit de poids fort disparait) et on ajoute un 0 
 * comme nouveau bit de poids faible.  Dans notre exemple, on shift notre 1 5 fois
 * pour obtenir 0b0010 0000
 * Le bit n est a 1, tous les autres sont a 0
 * 
 * Enfin, on soustrait 1 au resultat precedent, ce qui tranforme le bit n en 0 
 * et les bits a sa droite (0 -> n-1) en 1. Dans notre exemple, on obtient donc 
 * bien le resultat voulu : 0b0001 1111 
 */