#include <iostream>

//#define n 10



int hsh(int k, int s) {
    return k % s;
}

int num_k(int k, int* vx, int* s) { //return number of key, if find it in table
    int ke = hsh(k, *s);
    int i = ke;
    int sz = *s;
    while (sz > 0) {
        if (vx[i] == k) return i;
        else {
            i = (i + 1) % *s;
            sz--;
        }
    }
    return -1;
}

void del_k(int k, int* vx, bool* ux, int* s) { //delete by key
    int del_no = num_k(k, vx, s);
    if (del_no > 0) {
        vx[del_no] = 0;
        ux[del_no] = false;
    }
    else std::cout << "Didn't find key = " << k;
}

void add(int k, int* vx, bool* ux, int* s) {
    int ke = hsh(k, *s);
    int overfl = *s;
    int db_s = *s + *s;
    int* vv;
    bool* uu;

    while (overfl and ux[ke] and vx[ke] != k)
    {
        ke = (ke + 1) % *s;
        overfl--;
    }
    if (overfl == 0)                //udvoenie din massiva
    {                               //vnutri function add rabotaet,
                                    //posle vihoda iz nee v main v massive kakayto hren'
        vv = new int[db_s];
        uu = new bool[db_s];
        for (int i = 0;i < db_s;i++) { uu[i] = false; vv[i] = 0; }
        for (int i = 0;i < *s;i++) add(vx[i], vv, uu, &db_s);
        add(k, vv, uu, &db_s);
        for (int i = 0;i < db_s;i++) std::cout << vv[i] << " ";
        std::cout << std::endl;
        *s = db_s;
        delete[] vx;
        delete[] ux;
        //vx = new int[db_s]; //stavil ; posle lab v assemblere ne otoshel
        //ux = new bool[db_s];
        vx = vv;
        ux = uu;
        for (int i = 0;i < db_s;i++) std::cout << vx[i] << " ";
        std::cout << std::endl;
        //delete vv;
        //delete uu;

    }
    if (!ux[ke])
    {
        ux[ke] = true;
        vx[ke] = k;
    }

}



using namespace std;

int main()
{
    int sizeArr = 10;
    int x, kol;

    int* v;
    bool* u;

    v = new int[sizeArr];
    u = new bool[sizeArr];


    /*add(15,v,u,&sizeArr);
    add(7,v,u,&sizeArr);
    add(42,v,u,&sizeArr);
    add(31,v,u,&sizeArr);
    add(12,v,u,&sizeArr);
    add(18,v,u,&sizeArr);
    add(34,v,u,&sizeArr);
    add(12,v,u,&sizeArr);
    add(36,v,u,&sizeArr);
    */
    for (int i = 0;i < sizeArr;i++) { u[i] = false; v[i] = 0; };
    cout << "Enter num of elements to add >>>  ";
    cin >> kol;
    cout << "Enter list of " << kol << " values to add below" << endl;
    for (int i = 0;i < kol;i++) {
        cin >> x;
        add(x, v, u, &sizeArr);
    }


    for (int i = 0;i < sizeArr;i++) cout << v[i] << " ";

    cout << endl << "Enter value to delete >>   ";
    cin >> x;
    del_k(x, v, u, &sizeArr);

    for (int i = 0;i < sizeArr;i++) cout << v[i] << " ";

    delete [] u;
    delete [] v;
    return 0;
}
