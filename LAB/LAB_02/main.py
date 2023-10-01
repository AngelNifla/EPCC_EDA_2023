import matplotlib.pyplot as plt
import numpy as np
from funciones import *
import time


Funciones = ['Bubble sort','Heap sort','Insertion sort','Selection sort',
             'Shell sort','Merge sort','Quick sort']
Sizes = [1000,5000,10000,50000,100000,50000,1000000]
Tiempos = [[],[],[],[],[],[],[]]

############ Se ingresa los datos del txt a un array################
data = []
for s in range(len(Sizes)):
  txt = open(str(Sizes[s])+'_Datos_Aleatorios.txt')
  for line in txt:
      line = line.rstrip()
      numero = ""
      for x in line:
          if x.find(','):
              numero += str(x)
          else:
              data.append(float(numero))
              numero = ""

  l = len(data)
  print('-> Datos en el vector: '+str(l))

  ##################Ejemplo para el funcionamiento de los algoritmos##################
  #data = [0.294866,0.652471,0.823452,0.278408,0.638479,0.00165671,0.441823,0.498432,0.633753,0.813833,0.765667]

#####################Ejecucion y calculo de la complejidad de los Algoritmos de Ordenamiento#####################
  inicio = time.time()
  Resultado = BubbleSort(data)
  final = time.time()
  Tiempos[0].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = HeapSort(data)
  final = time.time()
  Tiempos[1].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = InsertionSort(data)
  final = time.time()
  Tiempos[2].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = SelectionSort(data)
  final = time.time()
  Tiempos[3].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = ShellSort(data)
  final = time.time()
  Tiempos[4].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = MergeSort(data)
  final = time.time()
  Tiempos[5].append(round(final-inicio,4))
  Resultado.clear()

  inicio = time.time()
  Resultado = QuickSort(data)
  final = time.time()
  Tiempos[6].append(round(final-inicio,4))
  Resultado.clear()

  data.clear()
###################Impresion de los tiempos de cada algoritmo###################
  #s=len(Tiempos)
  #for i in range(s):
  #    print(str(i+1)+Funciones[i]+" -> "+str(Tiempos[i])+"\n")

#print(Tiempos)

################Graficando las comparaciones de las complejidades################
plt.figure(figsize=(6,6))
for i in range(len(Funciones)):
  if i%2 == 0:
    plt.plot(Sizes, Tiempos[i], marker='o', linestyle='-.', label=Funciones[i])
  elif i%3 == 0:
    plt.plot(Sizes, Tiempos[i], marker='v', linestyle=':', label=Funciones[i])
  else:
    plt.plot(Sizes, Tiempos[i], marker='D', linestyle='-', label=Funciones[i])
     
plt.legend()
plt.xlabel('Size', fontsize=10, color="blue")
plt.ylabel('Tiempo', fontsize=10, color="blue")
plt.title('Comparación de las Complejidades\nComputacionales de Algoritmos de Ordenamiento',
          fontsize=14, color="black")
plt.grid(True)
#plt.yticks(np.arange(0, 0.03, step=0.015))
plt.show()
