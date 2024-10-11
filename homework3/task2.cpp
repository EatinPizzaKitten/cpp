#include <iostream>

using namespace std;
int find(int array[], int l, int sample);
int find(float array[], int l, float sample);
int find(char array[], int l, char sample);

int main(){
    int arr [] = {0, 1, 2, 3, 5, 6, 7, 8};

    cout << "Enter target element: ";
    int sample;
    cin >> sample;

    int size = sizeof(arr) / sizeof(arr[0]);
    int index = find(arr, size, sample);

    if (index != -1){
        cout << sample << " is found at index " << index << endl;
    }
    else{
        cout << "Element " << sample << " is not found" << endl;
    }

    return 0;
}

int find(int array[], int l, int sample){
    for (int i = 0; i < l; i++){
        if (array[i] == sample){
            return i;
        }
    }
    return -1;
}

int find(float array[], int l, float sample){
    for (int i = 0; i < l; i++){
        if (array[i] == sample){
            return i;
        }
    }
    return -1;
}

int find(char array[], int l, char sample){
    for (int i = 0; i < l; i++){
        if (array[i] == sample){
            return i;
        }
    }
    return -1;
}