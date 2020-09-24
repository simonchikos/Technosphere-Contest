#include <iostream>
#include <vector>
#include "library.h"
#include <fstream>

using namespace std;

int main(){
    string tmp, path;
    vector<vector<string>> library;
    int amount_of_actions;

    cout << "Введите путь к вашему текстовому файлу: " << endl;
    cin >> path;
    readLibrary(library, path);

    cout << "Введите кол-во действий: " << endl;
    cin >>  amount_of_actions;

    //Обрабатываем поочерёдно каждую команду.
    for (int i = 0; i < amount_of_actions; ++i) {
        //Объявляем счётчики.
        int column = 0, counter = 0;

        cout << "Введите " << i + 1 << " команду: " << endl;
        cin >> tmp;

        //Т.к номер столбца может остоять из нескольких цифр - нужно считать число до двоеточия.
        for(int i = 0; tmp[i] != ':'; ++i) {
            column = column * 10 + (tmp[i] - '0');
            counter++;
        }

        //Проверяем список команд:
        if (tmp[counter + 1] == 'U') { makeUpper(library, column); }
        else if (tmp[counter + 1] == 'u') { makeLower(library, column); }
        else if (tmp[counter + 1] == 'R') { changeChar(library, column, tmp[counter + 2], tmp[counter + 3]); }
        else { cout << "Wrong Command! Can't execute! Try Again! " << endl; }
    }
    //Выводим результат работы в наш файл.
    ofstream out;
    out.open(path);
    for (int i = 0; i < library.size(); ++i) {
        for (int j = 0; j < library[i].size(); ++j) {
            out << library[i][j] << '\t';
        }
        out << endl;
    }
    out.close();
}
