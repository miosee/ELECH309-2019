/* 
 * File:   adc.h
 * Author: M. Os�e
 *
 * Created on 11 janvier 2016, 14:10
 */

#ifndef ADC_H
#define	ADC_H


/**
 * En-t�te de la librairie de l'ADC pour les labos d'ELEC-H310 (et ELEC-H309)
 * 
 * Ces fonctions utilisent l'ADC1 du dsPIC de l'Explorer16 pour convertir la 
 * l'entr�e analogique AN0.
 * L'ADC1 est utilis� en polling, avec d�marrage en software de la conversion
 */


/**
 * Initialise l'ADC1 pour convertir AN0, sur 12 bits, avec auto-sampling et 
 * d�marrage en software
 */
void adcPollingInit(void);


/**
 * D�marre une conversion
 */
void adcPollingStart(void);

/**
 * renvoie 1 si la conversion est termin�e, 0 sinon
 */
int adcPollingConversionFinished(void);

/**
 * Renvoie le r�sultat de la derni�re conversion.
 * Si on essaie de lire pendant une conversion, la fonction le d�tecte et 
 * renvoie -32768, qui est une valeur impossible comme r�sultat de conversion.
 */
int adcPollingRead(void);


#endif	/* ADC_H */

