/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/07/02
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Dominguez_Actividad_1.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

/*=====[Main function, program entry point after power on or reset]==========*/
/**
 * @brief El comportamiento esta basado en la siguiente tabla:
 * 
 * | Tecla  |           Resultado             |
 * |--------|---------------------------------|
 * |  TEC1  |       Sentido a la derecha      |
 * |  TEC2  |           Período 150           |
 * |  TEC3  |           Período 750           |
 * |  TEC4  |     Sentido a la izquierda      |
 * 
 * @return int 
 */
int main(void)
{
	/* Variables de manejo de Leds */
	gpioMap_t led_actual = LEDB;
	
   /* Variables de Retardo no bloqueante */
	delay_t delayLeds;
	const uint16_t times[DEMORAS_QTY] = {PERIODO_150MS,PERIODO_750MS};

	/* banderas (flags) de control */
	bool_t flag[FLAGS_QTY] = {true};
      
	boardInit();

	delayConfig(&delayLeds, times[D150MS]);

   // ----- Loop infinito -------------------------
   while(true) {
	   /*-----------------Cambio de sentido de conmutación------------------*/
	   if (leerTecla(TEC1)) {
		   if (flag[CAMBIAR_SENTIDO]) {
			   flag[CAMBIAR_SENTIDO] = false;
				flag[SENTIDO] = DERECHA;
		   }
	   }
      else if (leerTecla(TEC4)) { // 150ms de período
         if (flag[CAMBIAR_SENTIDO]) {
			   flag[CAMBIAR_SENTIDO] = false;
				flag[SENTIDO] = IZQUIERDA;            
         }
      }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag[CAMBIAR_SENTIDO] = true;
	   }

	   /* --------------Cambio de velocidad de conmutación------------------*/
	   if (leerTecla(TEC2)) { // 150ms de período
		   if (flag[CAMBIAR_VELOCIDAD]) {
			   flag[CAMBIAR_VELOCIDAD] = false;
			   delayConfig(&delayLeds, times[D150MS]);
		   }
	   } 
      else if (leerTecla(TEC3)) { // 750ms de período
		   if (flag[CAMBIAR_VELOCIDAD]) {
			   flag[CAMBIAR_VELOCIDAD] = false;
			   delayConfig(&delayLeds, times[D750MS]);
		   }
	   }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag[CAMBIAR_VELOCIDAD] = true;
	   }
		
	   /*  -----------------------Retardo no bloqueante----------------------------*/
	   if (demoraCumplida(&delayLeds)) {
			
			led_actual += (flag[SENTIDO] << 1) - 1; // +1 si flag es DERECHA (led_actual + 2 * 1 - 1). -1 si flag es IZQUIERDA (led_actual + 2 * 0 - 1)

		   if (led_actual > LED3 && flag[SENTIDO]) { //ultimo led a la derecha?
			   led_actual = LEDB;
		   }
			else if (led_actual < LEDB && !flag[SENTIDO]) { //ultimo led a la izquierda?
				led_actual = LED3;
			}
	   }
		
	   /* -------------------Eleccíon del led a encender------------------------*/
		encenderLedUnico(led_actual); // 
   }
	// Nunca se alcanza este punto debido al ciclo infinito del while(true)
   return 0;
}

bool_t encenderLedUnico(gpioMap_t led) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		no_error = gpioWrite(i, i == led); // si i == led enciende, sino apaga.
		if (!no_error) {
			break;
		}
	}
	return no_error;
}
