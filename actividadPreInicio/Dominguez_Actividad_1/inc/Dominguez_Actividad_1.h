/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/07/02
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __DOMINGUEZ_ACTIVIDAD_1_H__
#define __DOMINGUEZ_ACTIVIDAD_1_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Definition macros of public constants]===============================*/

#define PERIODO_150MS              150 
#define PERIODO_750MS              750 
#define LED_QTY                    4 //Cantidad de leds

/*=====[Public function-like macros]=========================================*/
/**
 * @brief leo el estado de la tecla
 * 
 * @param tecla gpioMap_t
 * @return bool_t (true si tecla apretada)
 */
#define leerTecla(tecla) !gpioRead(tecla)
/**
 * @brief Controla si el tiempo de demora elegido ya se cumplió
 * 
 * @param demora *delay_t
 * @return bool_t (true si la demora se cumplió)
 */
#define demoraCumplida(demora) delayRead(demora)

/*=====[Definitions of public data types]====================================*/
typedef enum {
   SENTIDO,
   CAMBIAR_SENTIDO,
   CAMBIAR_VELOCIDAD,

   FLAGS_QTY
} flag_t;

typedef enum {
   D150MS,
   D750MS,

   DEMORAS_QTY
} demoras_t;

typedef enum {
   IZQUIERDA,
   DERECHA
   
} sentido_t;
/**
 * @brief Define si es una función de habilitación o deshabilitación (son dos estados posibles)
 * 
 */
typedef enum {
   DESHABILITADO,
   HABILITADO,

   FUNCIONES_QTY
} funcion_t;



/*=====[Prototypes (declarations) of public functions]=======================*/
/**
 * @brief Enciende el led que se le pasa por argumento y apaga los otros, si entra un valor que no corresponde a ningun led apaga todos *
 * 
 * @param led gpioMap_t
 * @return bool_t (true si pudo escribir todos los pines)
 */
bool_t encenderLedUnico(gpioMap_t led);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __DOMINGUEZ_ACTIVIDAD_1_H__ */
