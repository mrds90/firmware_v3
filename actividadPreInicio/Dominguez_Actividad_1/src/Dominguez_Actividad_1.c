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
	gpioMap_t secuencia1[] = {LEDB,LED1,LED2,LED3};
	gpioMap_t secuencia2[] = {LED3,LED2,LED1,LEDB};
	
	control_secuencia_t control_secuencia = {.ptrLed = &secuencia1[0], .ptrPrimerLed = &secuencia1[0], .ptrUltimoLed = &secuencia1[4]};

   /* Variables de Retardo no bloqueante */
	delay_t delayLeds;
	const uint16_t times[DEMORAS_QTY] = {PERIODO_150MS,PERIODO_750MS};

	/* banderas (flags) de control */
	bool_t flag_tecla[FLAGS_QTY] = {true};
      
	boardInit();

	delayConfig(&delayLeds, times[D150MS]);

   // ----- Loop infinito -------------------------
   while(true) {
	   /*-----------------Cambio de sentido de conmutación------------------*/
	   if (leerTecla(TEC1)) {
		   if (flag_tecla[CAMBIAR_SENTIDO]) {
			   flag_tecla[CAMBIAR_SENTIDO] = false;
				control_secuencia.ptrLed = &secuencia1[0];
				control_secuencia.ptrPrimerLed = &secuencia1[0];
				control_secuencia.ptrUltimoLed = &secuencia1[4];
		   }
	   }
      else if (leerTecla(TEC4)) { // 150ms de período
         if (flag_tecla[CAMBIAR_SENTIDO]) {
			   flag_tecla[CAMBIAR_SENTIDO] = false;
				control_secuencia.ptrLed = &secuencia2[0];
				control_secuencia.ptrPrimerLed = &secuencia2[0];
				control_secuencia.ptrUltimoLed = &secuencia2[4];
         }
      }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag_tecla[CAMBIAR_SENTIDO] = true;
	   }
	   /* --------------Cambio de velocidad de conmutación------------------*/
	   if (leerTecla(TEC2)) { // 150ms de período
		   if (flag_tecla[CAMBIAR_VELOCIDAD]) {
			   flag_tecla[CAMBIAR_VELOCIDAD] = false;
			   delayConfig(&delayLeds, times[D150MS]);
		   }
	   } 
      else if (leerTecla(TEC3)) { // 750ms de período
		   if (flag_tecla[CAMBIAR_VELOCIDAD]) {
			   flag_tecla[CAMBIAR_VELOCIDAD] = false;
			   delayConfig(&delayLeds, times[D750MS]);
		   }
	   }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag_tecla[CAMBIAR_VELOCIDAD] = true;
	   }
		
	   /*  -----------------------Retardo no bloqueante----------------------------*/
	   if (demoraCumplida(&delayLeds)) {
			activarSecuencia(&control_secuencia);
	   }
		
	   /* -------------------Eleccíon del led a encender------------------------*/
		encenderLedUnico(*control_secuencia.ptrLed); // 
   }
	// Nunca se alcanza este punto debido al ciclo infinito del while(true)
   return 0;
}

bool_t encenderLedUnico(gpioMap_t led) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		if (i == led) {
			no_error = encenderLed(i);
		}
		else {
			no_error = apagarLed(i);
		} 
		if (!no_error) {
			break;
		}
	}
	return no_error;
}


void activarSecuencia(control_secuencia_t *ptr_secuencia) {
	ptr_secuencia->ptrLed++;
	if (ptr_secuencia->ptrLed == ptr_secuencia->ptrUltimoLed) {
		ptr_secuencia->ptrLed = ptr_secuencia->ptrPrimerLed;
	}
}