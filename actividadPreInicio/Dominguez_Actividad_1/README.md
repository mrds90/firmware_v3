# Actividad 1

Conmutar secuencialmente leds


## Descripción

Utiliza la lectura de las teclas para tomar decisiones.
El comportamiento del firmware está definido por la siguiente tabla de verdad

| Tecla  |           Resultado             |
|--------|---------------------------------|
|  TEC1  |       Sentido incremental       |
|  TEC2  |           Período 150           |
|  TEC3  |           Período 750           |
|  TEC4  |       Sentido decremental       |

### Dependencias

* Utiliza la librería sapi.h de firmware v3

### Compilacion

* abrir la terminal del CIAA launcher y ir a la ruta del firmware v3.
* seleccionar el programa con el comando
```
make select_program
```
* elegir la carpeta actividadPreInicio/Dominguez_Actividad_1
* compilar el programa el programa en la misma terminal con:
```
make all
```
### Descargar programa

* En la misma terminal y con la edu_ciaa_nxp conectada escribir

```
make download
```

## Help

Puede no tener seleccionado la placa correcta. Para corregir esto escriba
```
make select_board
```
Siempre debe estar en la ruta raiz de la carpeta clonada "firmware_v3" con la terminal de CIAA Launcher si desea usar los comandos.
## Autor

Dominguez Marcos
[@mrds90](https://github.com/mrds90)

