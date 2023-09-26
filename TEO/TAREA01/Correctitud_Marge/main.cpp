#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Copiar datos a los arreglos temporales leftArray[] y rightArray[]
    for (int i = 0; i < n1; i++)
    {
        leftArray[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        rightArray[j] = arr[middle + 1 + j];
    }

    // Se mezcla los arreglos temporales de nuevo en arr[left..right]
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        } else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)  // Se copia los elementos restantes de leftArray[], si los hay
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)  // Se copia los elementos restantes de rightArray[], si los hay
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        // Punto medio del arreglo
        int middle = left + (right - left) / 2;
        // Se ordena la primera y segunda mitad
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        // Se mezcla las mitades ordenadas
        merge(arr, left, middle, right);
    }
}

int main()
{
    std::vector<int> arr =
    {12, 11, 13, 5, 6, 7};
    int arr_size = arr.size();

    std::cout << "Arreglo sin ordenar: ";
    for (int i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr_size - 1);

    std::cout << "Arreglo ordenado: ";
    for (int i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
