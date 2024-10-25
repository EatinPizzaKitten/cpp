#include <iostream>
#include <limits>

using namespace std;
struct author {string name; string surname;};
struct library
{
    string title;
    struct author creator;
    string year, pages;

    void displayBook() const {
        cout << "Title: " << title << "\n";
        cout << "Author: " << creator.name << " " << creator.surname << "\n";
        cout << "Publication year: " << year << "\n";
        cout << "Number of pages: " << pages << "\n \n";
    }

    void createBook() {
        cout << "Enter the title: ";
        getline(cin, title);

        cout << "Enter author's name: ";
        getline(cin, creator.name);

        cout << "Enter author's surname: ";
        getline(cin, creator.surname);

        cout << "Enter publication year: ";
        string tempYear;
        if (!(cin >> tempYear)) {
            tempYear = "0";
        }
        year = tempYear;

        cout << "Enter number of pages: ";
        string tempPages;
        if (!(cin >> tempPages)) {
            tempPages = "0";
        }
        pages = tempPages;
        cout << endl;

        this -> displayBook();
    }
};

int main() {    
    library myLibrary;
    bool flag = 1;
    while (flag) {
        myLibrary.createBook();

        cout << "Type 'stop' to stop \n";
        string act;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, act);
        if (act == "stop") {
            flag = 0;
        }
    }


    return 0;
}