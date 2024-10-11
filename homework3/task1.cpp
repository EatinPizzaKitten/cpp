#include <iostream>

using namespace std;

#define TYPE_ARRAY DYNAMIC_MEMORY
#define ARRAY_SIZE 10


void fill(int* array)
{
    for (int i = 0; i < ARRAY_SIZE; i++){
        array[i] = rand() % 100 + 0;  //"Случайным" образом заполняем массив
    }
}

int main(){
    int *array = nullptr;

    #ifdef TYPE_ARRAY
        array = new int[ARRAY_SIZE];
    #else
        static int stat_array[ARRAY_SIZE];
        array = &stat_array[0];
    #endif

    fill(array);

    for (int i = 0; i < ARRAY_SIZE; i++){
        cout << array[i] << ' ';
    }
    cout << endl;

    #ifdef TYPE_ARRAY
        delete[] array;
    #endif
    return 0;
}