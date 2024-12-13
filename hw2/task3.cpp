#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int size;
    cout << "Enter array size: ";
    cin >> size;
    int quad[size] {0};
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        quad[i] = i*i;
        sum += quad[i];
    }
    cout << "Array's elements' sum: " << sum << "\n";
    return 0;
}