# MiniLidar-Escaner
Pequeño Escáner Lidar para propósitos 3D

MiniLidar-Escáner es un proyecto que ha sido desarrollado, contando su concepción imaginaria, desde el año 2016. Nace bajo la necesidad de potenciar la cantidad y precisión de los datos espaciales, en diferentes circunstancias. En especial, el fundamento central es su aplicabilidad en Arqueología, buscando mejorar las formas técnicas y metodológicas en que se representa la realidad espacial. 

El eje del trabajo es un sensor Lidar Lite v3, que gira tanto vertical como horizontalmente, asistido un por un motor paso a paso y un servo motor. Todo ello es controlado por un Arduino, usando el primero, además, un driver pololu A4988.
Mediante una secuencia de acción, el sensor lidar recorre el espacio verticalmente, grado a grado y, cuando finaliza, el motor paso a paso avanza, continuando así la iteración hasta completar los 360º. 
A través del teorema Euclidiano, se transforman las coordenadas Esféricas (ρ,θ,φ) a Cartesianas, resultando en una secuencia con puntos en el espacio, del tipo X, Y, Z.  
