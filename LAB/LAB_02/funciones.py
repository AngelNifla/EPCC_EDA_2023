import random

################################Bubble Sort################################
def BubbleSort(vector):
    vec =vector[:]
    size = len(vec)
    for i in range(size):
        for j in range(0, size-i-1):
            if vec[j] > vec[j+1]:
                aux = vec[j]
                vec[j] = vec[j+1]
                vec[j+1] = aux
    return vec

#################################Heap sort#################################

def Juntar(vec, n, i):
    largo = i
    izquierda = (2*i)+1
    derecha = (2*i)+2

    if izquierda < n and vec[i] < vec[izquierda]:
        largo = izquierda
    if derecha < n and vec[largo] < vec[derecha]:
        largo = derecha
    if largo != i:
        aux = vec[i]
        vec[i] = vec[largo]
        vec[largo] = aux
        Juntar(vec, n, largo)

def HeapSort(vector):
    vec = vector[:]
    n = len(vec)

    for i in range(n // 2 - 1, -1, -1):
        Juntar(vec, n, i)
    for i in range(n - 1, 0, -1):
        aux = vec[i]
        vec[i] = vec[0]
        vec[0] = aux
        Juntar(vec, i, 0)
    return vec

#################################Insertion sort#################################

def InsertionSort(vector):
    vec = vector[:]
    for i in range(1, len(vec)):
        llave = vec[i]
        j = i - 1
        while j >= 0 and llave < vec[j]:
            vec[j + 1] = vec[j]
            j -= 1
        vec[j + 1] = llave
    return vec

#################################Selection sort#################################

def SelectionSort(vector):
    vec = vector[:]
    n = len(vec)
    for i in range(n):
        minimo = i
        for j in range(i + 1, n):
            if vec[j] < vec[minimo]:
                minimo = j
        aux = vec[i]
        vec[i] = vec[minimo]
        vec[minimo] = aux
    return vec

#################################Shell sort#################################

def ShellSort(vector):
    vec = vector[:]
    n = len(vec)
    g = n // 2

    while g > 0:
        for i in range(g, n):
            t = vec[i]
            j = i
            while j >= g and vec[j-g]>t:
                vec[j] = vec[j-g]
                j -= g
            vec[j] = t
        g //= 2
    return vec

################################Merge Sort################################

def Merge(vec_izquierdo, vec_derecho):
    resultado = []
    izquierdo = 0
    derecho = 0

    while izquierdo < len(vec_izquierdo) and derecho < len(vec_derecho):
        if vec_izquierdo[izquierdo] < vec_derecho[derecho]:
            resultado.append(vec_izquierdo[izquierdo])
            izquierdo += 1
        else:
            resultado.append(vec_derecho[derecho])
            derecho += 1
    resultado.extend(vec_derecho[derecho:])
    resultado.extend(vec_izquierdo[izquierdo:])
    
    return resultado

def MergeSort(vector):
    if len(vector) <= 1:
        return vector

    media = len(vector) // 2
    vec_derecho = vector[media:]
    vec_izquierdo = vector[:media]

    vec_derecho = MergeSort(vec_derecho)
    vec_izquierdo = MergeSort(vec_izquierdo)

    return Merge(vec_izquierdo, vec_derecho)

#################################Quick sort#################################

def QuickSort(vector):
    vec = vector[:]
    if len(vec) <= 1:
        return vec
    
    pivot = vec[random.randint(0, len(vec) - 1)]
    menos = []
    igual = []
    mas = []
    
    for element in vec:
        if element < pivot:
            menos.append(element)
        elif element == pivot:
            igual.append(element)
        else:
            mas.append(element)
    
    return QuickSort(menos) + igual + QuickSort(mas)

