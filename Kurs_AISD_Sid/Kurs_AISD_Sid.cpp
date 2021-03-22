#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int ost = 3;

int binsrch(int val, vector <int> v) { //ищет в векторе ближайшее значение снизу, если такого нет возвр -1
    int low = 0;
    int high = v.size() - 1;
    int f;
    //val++; //добавялем 1 на притирочный запас
    if (v[high] > val) return -1;
    while (high - low > 1) {
        f = (low + high) / 2;
        if (val == v[f]) { return f; }
        if (val > v[f]) { high = f; }
        else { low = f; }
    }
    if (val == v[low]) { return low; }
    if (val == v[high]) { return high; }
    if (v[low]>val && v[high]<val) return high;
    if (v[low] < val && v[high] < val) return low;
    if (v[high] > val) return -1;
}

int main()
{
    setlocale(LC_ALL, "rus");

    vector <int> lng;
    vector <int> shrt;
    string tmp;
    fstream frd("data.txt");
    do frd >> tmp; while (tmp != "long");
    frd >> tmp;
    while (tmp != "shrt") {
        lng.push_back(stoi(tmp));
        frd >> tmp;
    }
    frd >> tmp;
    while (!frd.eof()) {
        shrt.push_back(stoi(tmp));
        frd >> tmp;
    }

    //vector <int> lng = {15,20,25}; //отстортир по возр
    //vector <int> shrt = {12,7,7,6,6,5,5,5};//отсортир по убыв

    int sum_shrt = 0;
    int sum_lng = 0;
    for (int k : shrt) sum_shrt += k;   //получили сумму всех микроотрезков
    for (int k : lng) sum_lng += k;   //получили сумму всех макроотрезков
    sum_shrt -= shrt.size() - lng.size();
    if (sum_shrt > sum_lng)
        cout << "Warning! Lentgh of segments to be cut is too long!" << '\n' << "Final quantity will be less ..." << '\n';

    int j,x,sec,min,n_mint,n_minj,t = -1;

    int n_shrt = shrt.size(); //для выхода, когда кончатся бруски для изготовки
    for (int i = 0; i < lng.size() && n_shrt; i++) {
        j = 0;
        
        while (lng[i] >= ost && j < shrt.size()) {
            x = 0;
            min = INT32_MAX;
            //первичная проверка - можем ли отрезать j и j+1 элементы - если да , то отрезаем j,
            //обновляем lng[i]-=shrt[j] и затем обнуляем(или удаляем) shtr[j]=0 лучше, наверное, удалить
            if (n_shrt == 1) { //значит остался один элемент в массиве отрезков
                if (shrt[j] < lng[i]) {
                    cout << "произведена операция отреза от " << i << "-ой заготовки (с остаточной длиной = " << lng[i] << " ) отрезка длинной = " << shrt[j] << '\n';
                    lng[i] -= shrt[j];
                    cout << "все отрезки изготовлены ... WINNER! WINNER! CHICKEN DINNER!\n";
                    --n_shrt;
                    break;
                }
                else ++j;break;
            }
            if (n_shrt > 1) { //больше одного элем в массиве отрезков
                if (shrt[j] + shrt[j + 1] + 1 < lng[i]) { //если оставшаяся длина заготовки больше суммы двух длиннейших отрезков
                    cout << "произведена операция отреза от " << i << "-ой заготовки (с остаточной длиной = " << lng[i] << " ) отрезка длинной = " << shrt[j] << '\n';
                    lng[i] -= shrt[j] + 1;            //вычитаем
                    shrt.erase(shrt.begin() + j); //удаляем
                    --n_shrt;                   //уменьшаем
                    cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                    continue;
                }
                else {  //сначала пробуем найти второй элемент методом бинарного поиска
                    sec = lng[i] - shrt[j] - 1;
                    if (sec == 0) {
                        cout << "произведена операция отреза от " << i << "-ой заготовки (с остаточной длиной = " << lng[i] << " ) отрезка длинной = " << shrt[j] << '\n';
                        lng[i] -= shrt[j] + 1;            //вычитаем
                        shrt.erase(shrt.begin() + j); //удаляем
                        --n_shrt;                   //уменьшаем
                        cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                    }
                }
                t = binsrch(sec, shrt);
                if (t == -1) {  //в массиве нет элем для повторного отреза для пары с j элементом , нужно переходить к следующему
                       //if (!x) x = j;
                       if (j < shrt.size() - 1) {
                           ++j;
                           continue;
                       }
                       else {
                           if (lng[i] >= shrt[j]) {
                               cout << "произведена операция отреза от " << i << "-ой заготовки (с остаточной длиной = " << lng[i] << " ) отрезка длинной = " << shrt[j] << '\n';
                               lng[i] -= shrt[j] + 1;            //вычитаем
                               shrt.erase(shrt.begin() + j); //удаляем
                               --n_shrt;                   //уменьшаем
                               cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                               ++j; break;
                           }
                           else { 
                                cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                                ++j;
                                break; 
                           }
                       }
                }
                if (sec - shrt[t]==0) { // если разность равна 0 , значит это идеальная пара отрезков для отпила
                        cout << "произведена операция отреза от " << i << "-ой заготоввки (с остаточной длиной = " << lng[i] << " ) двух отрезков длинами = " << shrt[j] << " и " << shrt[t] << '\n';
                        lng[i] -= shrt[j] + shrt[t] + 1;            //вычитаем
                        shrt.erase(shrt.begin() + t); //удаляем
                        shrt.erase(shrt.begin() + j); //удаляем
                        --n_shrt;                   //уменьшаем
                        --n_shrt;                   //уменьшаем
                        cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                        break;  //выходим из цикла while , переходим к след заготовке в for
                }
                if (sec - shrt[t] < min && sec - shrt[t] > 0) {    //запоминаем номер миним остатка, для связки j и t элемента
                        min = sec-shrt[t];
                        n_minj = j;
                        n_mint = t;
                }
                if (j == shrt.size() - 1) {// последний из отрезков
                        cout << "произведена операция отреза от " << i << "-ой заготовки (с остаточной длиной = " << lng[i] << " ) двух отрезков длинами = " << shrt[n_minj] << " и " << shrt[n_mint] << '\n';
                        lng[i] -= shrt[n_minj] + shrt[n_mint] + 1;            //вычитаем
                        shrt.erase(shrt.begin() + n_mint); //удаляем
                        shrt.erase(shrt.begin() + n_minj); //удаляем
                        --n_shrt;                   //уменьшаем
                        --n_shrt;                   //уменьшаем
                        cout << "остаток после операции отреза " << i << "-ой заготовки : " << lng[i] << "\n\n";
                        break;  //выходим из цикла while , переходим к след заготовке в for
                }
                
            }
        } 
    }
    cout << "\n\n";
    for (int i = 0; i < lng.size();i++) {
        cout << "Итоговый остаток от " << i << "-й заготовки : " << lng[i] << '\n';
    }

    return 0;
}
