#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//Считывает таблицу слов из файла с расположением path
void readLibrary(vector<vector<string>>& library, string path) {
    string line;

    ifstream in(path);
    if (in.is_open())
    {
        //Пока вводят строки - считываем.
        while (getline(in, line))
        {
            //Каждый раз при входе в новую строку увеличиваем размер массива.
            library.resize(library.size() + 1);
            library[library.size() - 1].resize(1);
            for (int i = 0; i < line.size(); i++) {
                //Если не табуляция - считываем символ.
                if (line[i] != '\t') {
                    //Чтобы не тратить лишнюю память, не создавал счётчики, а обращался к размеру вектора.
                    library[library.size() - 1][library[library.size() - 1].size() - 1].push_back(line[i]);
                }
                //Иначе - увеличиваем кол-во полей.
                else { library[library.size() - 1].resize(library[library.size() - 1].size() + 1); }
            }
        }
    }
    in.close();     // закрываем файл
}

//Увеличивает регистр всех символов полей столбца column из таблицы library.
void makeUpper(vector<vector<string>>& library, int column) {
    for (int i = 0; i < library.size(); ++i) {
        //Проверяем, есть ли такой столбец в таблице строк.
        if (column < library[i].size()) {
            transform(library[i][column].begin(), library[i][column].end(), library[i][column].begin(), ::toupper);
        }
    }
}

//Уменьшает регистр всех символов полей столбца column из таблицы library.
void makeLower(vector<vector<string>>& library, int column) {
    for (int i = 0; i < library.size(); ++i) {
        //Проверяем, есть ли такой столбец в таблице строк.
        if (column < library[i].size()) {
            transform(library[i][column].begin(), library[i][column].end(), library[i][column].begin(), ::tolower);
        }
    }
}

//У всех полей столбца Column из таблицы library заменяет все символы changing на changeTo
void changeChar(vector<vector<string>>& library, int column, char changing, char changeTo) {
    for (int i = 0; i < library.size(); ++i) {
        //Проверяем, есть ли такой столбец в таблице строк.
        if (column < library[i].size()) {
            for (int j = 0; j < library[i][column].size(); ++j) {
                //Если символ совпадает с тем, который мы хотели менять - меняем на ChangeTo.
                if (library[i][column][j] == changing) { library[i][column][j] = changeTo; }
            }
        }
    }
}

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
}
