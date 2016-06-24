# Algoritmo Forward Checking + Conflict-directed Back Jumping para el OPHS
Proyecto de ILI295 - Inteligencia Artificial, UTFSM Campus San Joaquín 2016-1

Alex Arenas Fuentes

El algoritmo realiza dos busquedas completas con la técnica FC-CBJ. De acuerdo al modelo matemático, existen dos variables:

- La variable u[i] corresponde a la posición del POI i dentro de todo el Tour.
- La variable X[i][j][k] indica que el lugar j se visita despues del lugar i en el día k

Por lo tanto el primer FC-CBJ se encarga de generar todas las combinaciones posibles para u[i] y el segundo FC-CBJ de exporar todo el espacio de búsqueda para X[i][j][k]. 

Antes de ejecutar, deben existir las siguientes carpetas en el mismo directorio donde se encuentra el archivo main.cpp:
- instances
- candidates
- tmp
- out

El código se divide en dos clases:
- Helper
- ForwardChecking

La clase ForwardChecking contiene todos los métodos necesarios para realizar la búsqueda conmpleta con la técnica FC-CBJ. La clase Helper se encarga de leer y escribir archivos, calcular distancias euclidianas y otros métodos útiles.

Los archivos cpp distribuyen de forma más ordenda los métodos de las clases.
- La clase Helper está definida en el archivo helper.h y sus métodos están programados en helper.cpp
- La clase ForwardChecking está definida en el archivo forwardcheking.h y sus métodos se dividen en los siguientes archivos.
- El archivo forwardchecking.cpp contiene métodos generales de la técnica.
- El archivo u.cpp contiene métodos para manipular la variable u[i].
- El archivo x.cpp contiene métodos para manipular la variable X[i][j][k].
- El archivo dom_u.cpp contiene métodos para operar los dominios de las variables u[i].
- El archivo dom_x.cpp contiene métodos para operar los dominios de las variables X[i][j][k].
- El archivo conf_u.cpp contiene métodos para operar los conjuntos conflicto de las variables u[i].
- El archivo conf_x.cpp contiene métodos para operar los conjuntos conflicto de las variables X[i][j][k].
- El archivo main.cpp ordena la ejecución del algoritmo, recibe parámetros entrada y ejecuta las búsquedas FC-CBJ.

La sintáxis básica para ejecutar el algoritmo con el makefile es:
```
make INSTANCE={instancia}
```
El comando anterior ejecuta solo el segundo FC-CBJ y el primero en caso de que no exista un archivo de rutas. El parámetro INSTANCE es obligatorio y hace referencia a una instancia que exista en 
```
./instances/SET0/{instancia}.ophs
```
Para forzar la generación de rutas se puede agregar el parametro routes:
```
make routes INSTANCE={instancia}
```
Las combinaciones de u[i] se guardan en un archivo de rutas en
```
./tmp/instancia.routes.
```
La instancia más pequeña con la que se ha probado el algoritmo es ./instances/SET0/6-10-1-2.ophs. Para ejecutar esta instancia se debe escribir:
```
make INSTANCE=6-10-1-2
```

Durante la ejecución del algoritmo se generarán algunos archivos de salida para analizar algunas características del algoritmo

- Archivos Log de tiempo en la carpeta ./tmp/, llamados
```
{instancia}_u.time
{instancia}_u_FC.time
{instancia}_u_CBJ.time
{instancia}_X.time
{instancia}_X_FC.time
{instancia}_X_CBJ.time
```
Los archivos terminados en _FC guardan el instante (en segundos) en que se realizó un ForwardChecking de las variables aun no instanciadas. Los archivos terminados en _CBJ guardan el instante (en segundos) en que se realizó un retorno inteligente utilizando el conjunto conflicto de la variable actualmente instanciada. Finalmente los archivos sin sufijo, incluyen margas generales del algoritmo durante su ejecución.

- Archivos de Soluciones Candidatas en la carpeta ./candidates/, llamados:
```
{instancia}_{score}_{pois visitados}.out
```
- La mejor solución encontrada hasta el momento en la carpeta ./out/ llamado
```
{instancia}.out
```


El código fuente se encuentra disponible en linea en https://github.com/alexarenasf/IA-ForwardChecking
