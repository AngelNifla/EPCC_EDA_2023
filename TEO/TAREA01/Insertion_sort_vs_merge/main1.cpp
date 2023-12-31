#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr)       //Funcion de ordenamiento Sort
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main()      //Funcion Principal
{
    std::vector<int> arr =
    {12, 11, 13, 5, 6};
    
    insertionSort(arr);

    std::cout << "Arreglo ordenado: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
