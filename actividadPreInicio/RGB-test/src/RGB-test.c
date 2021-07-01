/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/06/13
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "RGB-test.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/
   /* Variable de Retardo no bloqueante */
   delay_t delayLedR;
   delay_t delayLedG;
   delay_t delayLedB;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void ) {

boardInit();

uint16_t period_r = 0;
uint16_t period_g = 0;
uint16_t period_b = 0;

delay_t delayLedR;
delay_t delayLedG;
delay_t delayLedB;

bool listo_para_cambiar_R= true;
bool listo_para_cambiar_G = true;
bool listo_para_cambiar_B = true;


// ----- Repeat for ever -------------------------
while( true ) {
	   /*Cambio de sentido de conmutación*/

	   /*Cambio de velocidad de conmutación*/
	   if ( gpioRead( TEC1 )){
		   listo_para_cambiar_R = true;
	   }
	   if (!gpioRead( TEC1 ) ){
		   if (listo_para_cambiar_R){
			   listo_para_cambiar_R = false;
			   period_r += 2;
			   if (period_r > 20) {
				   period_r = 0;
			   }
			   delayConfig( &delayLedR, period_r );


		   }

	   }

	   if ( gpioRead( TEC2 )){
		   listo_para_cambiar_G = true;
	   }
	   if (!gpioRead( TEC2 ) ){
		   if (listo_para_cambiar_G){
			   listo_para_cambiar_G = false;
			   period_g += 2;
			   if (period_g > 20) {
				   period_g = 0;
			   }
			   delayConfig( &delayLedG, period_g );


		   }

	   }

	   if ( gpioRead( TEC3 )){
		   listo_para_cambiar_B = true;
	   }
	   if (!gpioRead( TEC3 ) ){
		   if (listo_para_cambiar_B){
			   listo_para_cambiar_B = false;
			   period_b += 2;
			   if (period_b > 20) {
				   period_b = 0;
			   }
			   delayConfig( &delayLedB, period_b );

		   }

	   }

	   /*Retardo no bloqueante*/
	   if (delayRead(&delayLedR)){
		   gpioToggle(LEDR);
	   }
	   if (delayRead(&delayLedG)){
		   gpioToggle(LEDG);
	   }
	   if (delayRead(&delayLedB)){
		   gpioToggle(LEDB);

	   }


}

// YOU NEVER REACH HERE, because this program runs directly or on a
// microcontroller and is not called by any Operating System, as in the
// case of a PC program.
return 0;
}



