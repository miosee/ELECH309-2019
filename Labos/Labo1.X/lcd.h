/******	LCD FUNCTION PROTOTYPES ******/

/*********************************************************************************/
/*       Proc�dure d'initialisation : doit �tre ex�cut�e au d�but du programme,	 */
/*           avant toute utilisation de l'�cran LCD								 */
/*********************************************************************************/
void Init_LCD( void );		        // initialize display	

/*********************************************************************************/
/*       Proc�dure d'affichage d'une cha�ne de caract�re		                 */
/*           utilisation : LCD_Print("Hello World");                             */
/*						ou char str[10];										 */
/*						   LCD_Print(str);										 */	
/*				str doit �tre termin� par le caract�re nul						 */
/*           remarque : le curseur doit d'abord �tre positionn� � l'endroit      */
/*                  o� doit �tre affich�e la cha�ne							     */
/*********************************************************************************/
void LCD_Print(char *str);

/*********************************************************************************/
/*        Proc�dure d'affichage d'un caract�re                                   */
/*           utilisation : LCD_Car('a');                                         */
/*					  ou   lcd_data('b');										 */
/*           remarque	: la position du curseur est incr�ment�e de 1   		 */
/*********************************************************************************/	
void LCD_Car(char c);

/*********************************************************************************/
/*        Proc�dure permettant le positionnement du curseur						 */
/*           utilisation : LCD_Pos(0x80);                                        */
/*           remarque : 1e caract�re, 1e ligne=0x80                              */
/*                      1e caract�re, 2e ligne=0xC0								 */
/*                             "0x" signifie que c'est de l'hexad�cimal			 */
/*********************************************************************************/
void LCD_Pos(unsigned char c);

/*********************************************************************************/
/*        Proc�dure d�cr�mentant la position du curseur de 1                     */
/*********************************************************************************/
void LCD_Back(void);

/*********************************************************************************/
/*        				Effacement de l'�cran				                     */
/*     		   Position du curseur en d�but de la premi�re ligne				 */
/*********************************************************************************/
void LCD_Clr(void);

/*********************************************************************************/
/*     		   Position du curseur en d�but de la premi�re ligne				 */
/*********************************************************************************/
void LCD_Line1(void);

/*********************************************************************************/
/*     		   Position du curseur en d�but de la deuxi�me ligne				 */
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
/*     		   				D�calage de l'affichage					 			 */
/*							� droite : b=O;									     */	
/*							� gauche : b=1;										 */
/*********************************************************************************/
void LCD_Shift(unsigned char b);

