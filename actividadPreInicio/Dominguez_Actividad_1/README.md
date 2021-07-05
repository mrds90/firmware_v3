# Actividad 1

Conmutar secuencialmente leds



## Descripción

Utiliza la lectura de las teclas para tomar desiciones.
El comportamiento del firmware está definido por la siguiente tabla de verdad

| Tecla  |           Resultado             |
|--------|---------------------------------|
|  TEC1  |       Sentido incremental       |
|  TEC2  |           Período 150           |
|  TEC3  |           Período 750           |
|  TEC4  |       Sentido decremental       |

## Getting Started

### Dependencias

* Utiliza la librería sapi.h de firmware v3

### Installing

* en la terminal del CIAA launcher ir a la ruta del firmware v3.
* seleccionar el programa con el comando
```
make select_program
```
* elegir el la carpeta actividadPreInicio/Dominguez_Actividad_1
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

## Author

Contributors names and contact info

Dominguez Marcos
[@mrds90](https://github.com/mrds90)

