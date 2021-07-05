/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/07/02
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Dominguez_Actividad_1.h"

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
 * Las teclas 1 y 4 no responden si la otra esta presionada.
 * Las teclas 2 y 3 no responden si la otra esta presionada.
 * 
 * @return int 
 */
int main(void)
{
	/* Variables de Retardo no bloqueante */
	delay_t delayLeds;
	const uint16_t times[DEMORAS_QTY] = {PERIODO_150MS,PERIODO_750MS};

	boardInit();

	delayConfig(&delayLeds, times[D150MS]);

   // ----- Loop infinito -------------------------
   while(true) {
		
		/* Variables de manejo de Leds */
		static gpioMap_t secuencia1[] = {LEDB,LED1,LED2,LED3};
		static gpioMap_t secuencia2[] = {LED3,LED2,LED1,LEDB};
		static control_secuencia_t control_secuencia = {.ptrLed = &secuencia1[0], .ptrPrimerLed = &secuencia1[0], .ptrUltimoLed = &secuencia1[sizeof(secuencia1)/sizeof(secuencia1[0])]};

		/* banderas (flags) de control para las teclas */
		static bool_t flag_tecla[FLAGS_QTY] = {true};
	   
		/*-----------------Cambio de sentido de conmutación------------------*/
	   if (leerTecla(TEC1)) { // Sentido de secuencia 1 (INCREMENTAL)
		   if (flag_tecla[CAMBIAR_SENTIDO]) {
			   flag_tecla[CAMBIAR_SENTIDO] = false;
				control_secuencia.ptrLed = &secuencia1[0];
				control_secuencia.ptrPrimerLed = &secuencia1[0];
				control_secuencia.ptrUltimoLed = &secuencia1[sizeof(secuencia1)/sizeof(secuencia1[0])];
		   }
	   }
      else if (leerTecla(TEC4)) { // Sentido de secuencia 2 (DECREMENTAL)
         if (flag_tecla[CAMBIAR_SENTIDO]) {
			   flag_tecla[CAMBIAR_SENTIDO] = false;
				control_secuencia.ptrLed = &secuencia2[0];
				control_secuencia.ptrPrimerLed = &secuencia2[0];
				control_secuencia.ptrUltimoLed = &secuencia2[sizeof(secuencia2)/sizeof(secuencia2[0])];
         }
      }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag_tecla[CAMBIAR_SENTIDO] = true;
	   }
	   /* --------------Cambio de velocidad de conmutación------------------*/
	   if (leerTecla(TEC2)) { // elegir  150ms de período
		   if (flag_tecla[CAMBIAR_VELOCIDAD]) {
			   flag_tecla[CAMBIAR_VELOCIDAD] = false;
			   delayConfig(&delayLeds, times[D150MS]);
		   }
	   } 
      else if (leerTecla(TEC3)) { // elegir 750ms de período
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

bool_t apagarLeds(void) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		if (!apagarLed(i)) {
			no_error = false;
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