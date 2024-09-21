#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    int sum = 0;
    int input;
    cin >> input;
    while (input != 0)
    {
        if (input > 0)
        {
            sum += input;
        }
        cout << "Your number: " << sum << "\n";
        cin >> input;
    }
    cout << "Program terminated";
    return 0;
}