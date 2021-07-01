/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/06/06
 * Version: 0.0.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "alternateLed.h"


/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
/**
 * @brief El comportamiento esta basado en la siguiente tabla:
 * 
 * | Tecla  |           Resultado             |
 * |--------|---------------------------------|
 * |  TEC1  |       Cambio de sentido         | <-- deshabilitado si los led estan apagados o intermitentes
 * |  TEC2  |      Cambio de velocidad        | <-- deshabilitado si los led estan apagados
 * |  TEC3  | Secuencia/Intermitencia de LEDS | <-- deshabilitado si los led estan apagados
 * |  TEC4  |     Habilita/Apaga de LEDS      |
 * 
 * @return int 
 */
int main(void)
{
	/* Variables de manejo de Leds */
	bool_t (*ledFunction[FUNCIONES_QTY])(gpioMap_t) = {apagarLeds,encenderLedUnico};
	funcion_t funcion_actual = HABILITADO;
	gpioMap_t led_actual = LEDB;
	/* Variables de Retardo no bloqueante */
	delay_t delayLeds;
	demoras_t demora = D500MS;
	const uint16_t times[DEMORAS_QTY] = {PERIODO_150MS,PERIODO_500MS,PERIODO_1S};
	/* banderas (flags) de control */
	bool_t flag[FLAGS_QTY] = {true};
      
	boardInit();

	delayConfig(&delayLeds, times[demora]);

   // ----- Loop infinito -------------------------
   while(true) {
		/* definición de prioridaes */
		if (ledFunction[funcion_actual] == apagarLeds) {
			flag[CAMBIAR_SENTIDO] = false;
			flag[CAMBIAR_VELOCIDAD] = false;
			flag[FUNCION_LEDS] = false;
		}
		else if (ledFunction[funcion_actual] == conmutarLeds) {
			flag[CAMBIAR_SENTIDO] = false; // si no hay secuencia no se puede cambiar sentido
		}

	   /*-----------------Cambio de sentido de conmutación------------------*/
	   if (!gpioRead(TEC1)) {
		   if (flag[CAMBIAR_SENTIDO]) {
			   flag[CAMBIAR_SENTIDO] = false;
				flag[SENTIDO_CRECIENTE] = !flag[SENTIDO_CRECIENTE];
		   }
	   }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag[CAMBIAR_SENTIDO] = true;
	   }

	   /* --------------Cambio de velocidad de conmutación------------------*/
	   if (!gpioRead(TEC2)) {
		   if (flag[CAMBIAR_VELOCIDAD]) {
			   flag[CAMBIAR_VELOCIDAD] = false;
			   demora++;
			   /*reset contador (hay 3 velocidades)*/
			   if (demora == DEMORAS_QTY) {
				   demora = D150MS;
			   }
			   delayConfig(&delayLeds, times[demora]);
		   }
	   }
	   else {
			/*habilitar el cambio próximo cuando se suelta la tecla*/
		   flag[CAMBIAR_VELOCIDAD] = true;
	   }
		
		/*------------------------------ Cambiar función de Leds -----------------------*/
		if (!gpioRead(TEC3)) {
		   if (flag[FUNCION_LEDS]) {
			   flag[FUNCION_LEDS] = false;
				if (ledFunction[HABILITADO] == encenderLedUnico) {
					ledFunction[HABILITADO] = conmutarLeds;
				}
				else {
					ledFunction[HABILITADO] = encenderLedUnico;
				}
		   }
	   }
	   else {
			/*habilitar el encendido de leds próximo cuando se suelta la tecla*/
		   flag[FUNCION_LEDS] = true;
	   }

		/*------------------------------- Apagar/Habilitar Leds ------------------------*/
		if (!gpioRead(TEC4)) {
		   if (flag[CONMUTAR_LEDS]) {
			   flag[CONMUTAR_LEDS] = false;
				funcion_actual ^= HABILITADO;
		   }
	   }
	   else {
			/*habilitar el apagado de leds próximo cuando se suelta la tecla*/
		   flag[CONMUTAR_LEDS] = true;
	   }

	   /*  -----------------------Retardo no bloqueante----------------------------*/
	   if (delayRead(&delayLeds)) {
			
			led_actual += 2 * flag[SENTIDO_CRECIENTE] - 1; // 1 si flag es true y -1 si flag es false;

		   if (led_actual > LED3 && flag[SENTIDO_CRECIENTE]) {
			   led_actual = LEDB;
		   }
			else if (led_actual < LEDB && !flag[SENTIDO_CRECIENTE]) {
				led_actual = LED3;
			}
	   }
		
	   /* -------------------Conmutación o apagao de los leds------------------------*/
		ledFunction[funcion_actual](led_actual); // ledFunction apunta a "encenderLedUnico", "conmutarLeds" o "apagarLeds"  segun el seteo por tecla.
   }
	// Nunca se alcanza este punto debido al ciclo infinito del while(true)
   return 0;
}

bool_t encenderLedUnico(gpioMap_t led) {
	bool_t no_error;
	uint8_t i;
	for (i = LEDR ; i <= LED3 ; i++) {
		no_error = gpioWrite(i, i == led);
		if (!no_error) {
			break;
		}
	}
	return no_error;
}

bool_t apagarLeds(gpioMap_t led) {
	return encenderLedUnico(0); // 0 no corresponde a ningu led (valores válidos de 40 a 45)
}

bool_t conmutarLeds(gpioMap_t numero) {
	bool_t no_error = true;
	uint8_t i;
	for (i = LEDB ; i <= LED3 ; i++) {
		no_error = gpioWrite(i, (numero % 2) == 0);
		if (!no_error) {
			break;
		}
	}
	return no_error;
}
