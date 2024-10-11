#include <iostream>
#include <cstdlib>

using namespace std;

struct nvector
{
    int *a;
    size_t n;
};

void mult_num(nvector& vect, int num){
    int t [vect.n];
    for (int i = 0; i < vect.n; i++){
        t[i] = vect.a[i] * num;
    }
    for (size_t i = 0; i < vect.n; i++){
        cout << t[i] << " ";
    }
}

void sum(nvector& vect, nvector& vect2){
    for (size_t i = 0; i < vect.n; i++){
        cout << vect.a[i] + vect2.a[i] << " ";
    }
}

void mult_scalar(nvector& vect, nvector& vect2){
    int scal = 0;
    for (size_t i = 0; i < vect.n; i++){
        scal +=  vect.a[i] * vect2.a[i];
    }
    cout << scal << "\n";
}

int main(){
    cout << "Enter number of dimensions: ";
    int n;
    cin >> n;

    try {
        struct nvector vect;
        vect.a = new int[n]{};
        vect.n = n;

        cout << "Enter vector number by number:\n";
        for (size_t i = 0; i < n; i++){
            int x;
            cin >> x;
            vect.a[i] = x;
        }

        cout << "Choose action (enter number):" << endl;
        cout << "1. Multiply by number" << endl;
        cout << "2. Add with another vector" << endl;
        cout << "3. Multiply scalar with another vector" << endl;
        int act;
        cin >> act;

        switch (act) {
            case 1:
                cout << "Enter number: ";
                int num;
                cin >> num;
                cout << "Result: ";
                mult_num(vect, num);
                break;
            case 2:
                cout << "Enter second vector number by number:\n";
                struct nvector vect2;
                vect2.a = new int[n]{};
                for (size_t i = 0; i < n; i++){
                    int x;
                    cin >> x;
                    vect2.a[i] = x;
                }
                cout << "Result: ";
                sum(vect, vect2);
                break;
            case 3:
                cout << "Enter second vector number by number:\n";
                struct nvector vect2_2;
                vect2_2.a = new int[n]{};
                for (size_t i = 0; i < n; i++){
                    int x;
                    cin >> x;
                    vect2_2.a[i] = x;
                }
                cout << "Result: ";
                mult_scalar(vect, vect2_2);
                break;

            default:
                cerr << "Invalid action.\n";
                exit(EXIT_FAILURE);
        }

        delete[] vect.a;
    } 
    catch (const exception& e) 
    {
        cerr << "Error occured" << e.what();
        exit(EXIT_FAILURE);
    }

    return 0;
}