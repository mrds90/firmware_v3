/*=============================================================================
 * Author: Marcos Dominguez <mrds0690@gmail.com>
 * Date: 2021/06/06
 * Version: 0.0.1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __ALTERNATELED_H__
#define __ALTERNATELED_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

#define PERIODO_150MS              150 
#define PERIODO_500MS              500 
#define PERIODO_1S                 1000 
#define LED_QTY                    4 //Cantidad de leds

/*=====[Public function-like macros]=========================================*/

#define leerTecla(tecla) gpioRead(tecla) 

/*=====[Definitions of public data types]====================================*/
typedef enum {
   CAMBIAR_SENTIDO,
   CAMBIAR_VELOCIDAD,
   SENTIDO_CRECIENTE,
   CONMUTAR_LEDS,
   FUNCION_LEDS,

   FLAGS_QTY
} flag_t;

typedef enum {
   D150MS,
   D500MS,
   D1S,

   DEMORAS_QTY
} demoras_t;

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
 * @param led 
 * @return bool_t 
 */
bool_t encenderLedUnico(gpioMap_t led);
/**
 * @brief Apaga todos los leds
 * 
 * @param led No tiene uso. Existe el argumento para poder apuntar la función al mismo puntero que encenderLedUnico.
 * @return bool_t 
 */
bool_t apagarLeds(gpioMap_t led);
/**
 * @brief Conmuta todos los leds segun paridad del numero que llega como parametro. Enciende en pares y apaga en impares.
 * 
 * @param numero 
 * @return bool_t 
 */
bool_t conmutarLeds(gpioMap_t numero);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __ALTERNATELED_H__ */
