#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    string text;
    string sample;
    cout << "Enter first string: ";
    cin >> text;
    cout << "Enter second string: ";
    cin >> sample;
    string::size_type i = 0, count = 0;
    for (;;){
        i = text.find(sample, i);
        if (i == string::npos) /// Смотрим, есть ли еще подстроки
        {
            break;
        }
        i += sample.size();
        count++;
    }
    cout << "Number of occurences: " << count;
    return 0;
}