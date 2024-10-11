#include <iostream>

using namespace std;

struct author {char* name = "Неизвестен"; char* second_name};
struct library
{
    char title = "Неизвестен";
    struct author creator;
    int year = 0, pages = 0;
    void displayBook(library& book) {
        cout << "Название: " << book.title << "\n";
        cout << "Автор: " << book.author.name << "\n";
        cout << "Год издания: " << book.year << "\n";
        cout << "Количество страниц: " << book.pages << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    
    return 0;
}