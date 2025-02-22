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

#define PERIODO_150MS              150 
#define PERIODO_750MS              750 

/*=====[Public function-like macros]=========================================*/

/**
 * @brief leo el estado de la tecla
 * 
 * @param tecla gpioMap_t
 * @return bool_t (true si tecla apretada)
 */
#define leerTecla(tecla) !gpioRead(tecla)

/**
 * @brief Enciende el led que le defino
 * 
 * @param led gpioMap_t
 * @return bool_t (true si logro encender)
 */
#define encenderLed(led) gpioWrite(led, 1)

/**
 * @brief apago el led que le defino
 * 
 * @param led gpioMap_t
 * @return bool_t (true si logro apagar)
 */
#define apagarLed(led) gpioWrite(led, 0)

/**
 * @brief Controla si el tiempo de demora elegido ya se cumplió
 * 
 * @param demora *delay_t
 * @return bool_t (true si la demora se cumplió)
 */
#define demoraCumplida(demora) delayRead(demora)

/*=====[Definitions of public data types]====================================*/

/**
 * @brief Indice de flags que habilitan las teclas
 * 
 */
typedef enum {
   CAMBIAR_SENTIDO,
   CAMBIAR_VELOCIDAD,

   FLAGS_QTY
} flag_tecla_t;

/**
 * @brief Indice del vector que tiene los tiempos de demora.
 * 
 */
typedef enum {
   D150MS,
   D750MS,

   DEMORAS_QTY
} demoras_t;

/**
 * @brief Estructura para controlar de forma escalable y genérica cualquier secuencia.
 * 
 */
typedef struct {
   gpioMap_t *ptrLed;
   gpioMap_t *ptrPrimerLed;
   gpioMap_t *ptrUltimoLed;
} control_secuencia_t;

/*=====[Prototypes (declarations) of public functions]=======================*/



/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __DOMINGUEZ_ACTIVIDAD_1_H__ */
