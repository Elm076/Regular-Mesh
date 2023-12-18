# Análisis de tablas de dispersión

* *Adrián González Pérez*

## Tamaño de tabla: 109098
| función | máximo de colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:---------------:|:----------------------:|
| (key%maxElements+attempt * (unsigned int)sqrt(key + attempt*attempt))%maxElements;   |          44          |      0.699      |         0.7809         |
| (key+attempt*attempt)%maxElements   |         109          |      0.699      |         4.925          |
| ((key%maxElements)+(attempt*(prime2-(key%prime2)+1)))%maxElements   |         347          |      0.699      |         1.652          |
| ((key % maxElements) + (attempt*((key%prime1)+1)))%maxElements   |          43          |      0.699      |         0.841          |


## Justificación de la configuración elegida
Hemos optado por la configuración de la primera función de dispersión relatada en este documento (h3(x) en el código de la práctica)
debido a que es la que mejor resultado da el mejor promedio de colisiones para un mismo factor de carga