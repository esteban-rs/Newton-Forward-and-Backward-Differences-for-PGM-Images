Newton Forward and Backward Differences for PGM Images

Compilar como 
	g++ main.cpp Tools.cpp -o main

Correr como	
	./main Insumos/cat.pgm
	./main Insumos/shark.pgm

1. Al ejecutar el programa se hace el gradiente para 3,5 y 7 puntos de interpolación por defecto

2. Los archivos escritos se quedan en  "Out"

3. La librería "tools" contiene
   3.1) Clase PGM para leer y escribir archivos PGM
   3.2) Función Diferencias Hacia Adelante
   3.3) Función Diferencias Hacia Atrás
   3.4) Calcular gradiente por filas 
   3.5) Calcular gradiente por columnas

5. En el archivo "main.cpp" se declara el número de puntos a interpolar 

