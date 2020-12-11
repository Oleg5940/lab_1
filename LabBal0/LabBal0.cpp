#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

struct Cont {
    double num;
    double drobsum;
    bool isset = false;
    bool is_end = false;
};

#include "cont.cpp"

bool isCont(vector<Cont> cont, int vsize, int i);
void pushCont(vector<Cont>& cont, int num);
void endCont(vector<Cont>& cont);

void showMenu()
{
    cout << "1.\n";
    cout << "2.\n";
    cout << "3.\n";
    cout << "4.\n";
    cout << "5. Вывести меню повторно.\n";
    cout << "6. Выход.\n";
}

void split(string str, vector<Cont>& cont, char delim = ' ')
{
    stringstream ss(str);
    string token;

    int i = 0;
    while (getline(ss, token, delim)) {
        int new_n = strtod(token.c_str(), NULL);

        if (new_n == 0 && token[0] != '0') {
            continue;
        }

        pushCont(cont, new_n);
        i++;
    }

    endCont(cont);
}

bool isEmpty(string pos, vector<Cont>& cont)
{
    if (pos == "" || pos == "\n") {
        return true;
    }

    split(pos, cont);

    bool isEmpty = true;
    for (int i = 0; isCont(cont, cont.size(), i); i++) {
        if (!cont[i].isset) {
            break;
        }
        isEmpty = false;
        break;
    }

    return isEmpty;
}

void inFile(vector<Cont>& cont)
{
    string path; //строка для пути к файлу
    ifstream file; //обьект класса для считывания из файла

    cout << "Введите путь к файлу:\n";
    cin >> path; //вводим путь к файлу
    file.open(path); //связываем обьект с файлом

    if (!file.is_open()) {  //если пользователь ввел неверный путь
        cout << "Ошибка: файл не найден!\n";
        return;
    }
    else { //если нашли файл
        cout << "Идёт считывание данных...\n";
        char element[10]; //массив для числа из файла

        int i = 0;
        for (; !file.eof(); i++) {
            file >> element; //считываем все символы до пробела
            pushCont(cont, atof(element));
        }

        file.close(); //прекращаем работу с файлом
        endCont(cont);

        cout << "Данные успешно считаны!\n";
    }
}

void task2(vector<Cont>& cont)
{
    int vsize = cont.size();

    for (int i = 0; ; i++) {
        int numint = cont[i].num - (int)cont[i].num;
        int sum = 0;
        while (numint > 0) {
            sum += numint % 10;
            numint /= 10;
        }

        cont[i].drobsum = sum;
    }

    for (int i = 0; isCont(cont, vsize, i); i++) {
        for (int j = i + 1; isCont(cont, vsize, j); j++) {
            if (cont[i].num > cont[j].num) {
                Cont t = cont[i];
                cont[i] = cont[j];
                cont[j] = t;
            }
        }
    }

    endCont(cont);
}

void task3(vector<Cont> cont)
{
    int vsize = cont.size();

    int kolg = 0;
    int kolb = 0;
    int koln = 0;

    for (int i = 0; isCont(cont, vsize, i); i++) {
        int num = cont[i].num;
        if (num > 0) {
            kolg++;
        }
        else if (num == 0) {
            koln++;
        }
        else {
            kolb++;
        }
    }

    cout << kolg << " " << kolb << " " << koln << "\n";
}

int main()
{
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");
    ios::sync_with_stdio(false);

    int k, vsize = 1000;
    vector<Cont> cont(vsize);

    showMenu();
    do {
        cout << "\n";
        cin >> k;

        switch (k) {
        case 1: {
            cout << "Введите последовательность чисел:\n";

            string pos = "";
            cin >> pos;

            if (isEmpty(pos, cont)) {
                inFile(cont);
            }

            break;
        }

        case 2: {
            task2(cont);
        }

        case 3: {
            task3(cont);
        }

        case 5:
            showMenu();
            break;
        }
    } while (k != 6);
}