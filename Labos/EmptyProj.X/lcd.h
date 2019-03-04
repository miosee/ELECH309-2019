/******	LCD FUNCTION PROTOTYPES ******/

/*********************************************************************************/
/*       Procédure d'initialisation : doit être exécutée au début du programme,	 */
/*           avant toute utilisation de l'écran LCD								 */
/*********************************************************************************/
void Init_LCD( void );		        // initialize display	

/*********************************************************************************/
/*       Procédure d'affichage d'une chaîne de caractère		                 */
/*           utilisation : LCD_Print("Hello World");                             */
/*						ou char str[10];										 */
/*						   LCD_Print(str);										 */	
/*				str doit être terminé par le caractère nul						 */
/*           remarque : le curseur doit d'abord être positionné à l'endroit      */
/*                  où doit être affichée la chaîne							     */
/*********************************************************************************/
void LCD_Print(char *str);

/*********************************************************************************/
/*        Procédure d'affichage d'un caractère                                   */
/*           utilisation : LCD_Car('a');                                         */
/*					  ou   lcd_data('b');										 */
/*           remarque	: la position du curseur est incrémentée de 1   		 */
/*********************************************************************************/	
void LCD_Car(char c);

/*********************************************************************************/
/*        Procédure permettant le positionnement du curseur						 */
/*           utilisation : LCD_Pos(0x80);                                        */
/*           remarque : 1e caractère, 1e ligne=0x80                              */
/*                      1e caractère, 2e ligne=0xC0								 */
/*                             "0x" signifie que c'est de l'hexadécimal			 */
/*********************************************************************************/
void LCD_Pos(unsigned char c);

/*********************************************************************************/
/*        Procédure décrémentant la position du curseur de 1                     */
/*********************************************************************************/
void LCD_Back(void);

/*********************************************************************************/
/*        				Effacement de l'écran				                     */
/*     		   Position du curseur en début de la première ligne				 */
/*********************************************************************************/
void LCD_Clr(void);

/*********************************************************************************/
/*     		   Position du curseur en début de la première ligne				 */
/*********************************************************************************/
void LCD_Line1(void);

/*********************************************************************************/
/*     		   Position du curseur en début de la deuxième ligne				 */
/*********************************************************************************/
void LCD_Line2(void);

/*********************************************************************************/
/*     		   				Affichage du curseur					 			 */
/*						avec curseur : _ => b=0x02;								 */	
/*						sans curseur : b=0x00;									 */
/*					avec curseur clignotant  : _ => b=0x03;						 */
/*********************************************************************************/
void LCD_Curs(unsigned char b);

/*********************************************************************************/
/*     		   				Décalage de l'affichage					 			 */
/*							à droite : b=O;									     */	
/*							à gauche : b=1;										 */
/*********************************************************************************/
void LCD_Shift(unsigned char b);

