#include <iostream>
#include <windows.h>
using namespace std;

int main(){
    int a;
    cin >> a;
    int flag = 0;
    int max = 0;
    for (int i = 2; i<a; i++)
    {
        if (a % i == 0)
        {
            max = i;
            flag++;
        }
    }
    if (flag != 0)
    {
        cout << "Max divider: " << max;
    }
    else
    {
        cout << "The number is prime";
    }
    return 0;
}