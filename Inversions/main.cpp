/*
нахождение количества инверсий, суть следущая:
заводим массив пар, хранящий пары элементов ЗНАЧЕНИЕ-НОМЕР
заводим массив элементов, на i-м месте 1 или 0 будет показывать, вычеркнуто ли число в исходном массиве
сортируем пары по возрастанию, берем минимальный элемент, по его индексу апдейтим в единичном
и считаем сумму от 0 до того индекса
прибавляем в количество инверсий
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n=200;
int *tree = new int[n*4];

void build(int v, int tl, int tr, int a[]) {
    if (tl==tr)
        tree[v]=a[tl];
    else {
        int tm=(tl+tr)/2;
        build(2*v, tl, tm, a);
        build(2*v+1, tm+1, tr, a);
        tree[v]=tree[2*v]+tree[2*v+1];
    }
}

void update(int v, int tl, int tr, int ind, int k) { //ind-индекс в а, k - значение в а, которое изменяем
    if (tl==tr)
        tree[v]=k;
    else {
        int tm=(tl+tr)/2;
        if (ind<=tm)
            update(2*v, tl, tm, ind, k);
        else
            update(2*v+1, tm+1, tr, ind, k);
        tree[v]=tree[2*v]+tree[2*v+1];
    }
}

int sum (int v, int tl, int tr, int l, int r) {
    if (l>r)
        return 0;
    if (tl==l && tr==r) {
        return tree[v];
    } else {
        int tm=(tl+tr)/2; //tl+(tr-tl)/2
        int tmp1=sum(2*v,tl, tm, l, min(tm,r));
        int tmp2=sum(2*v+1, tm+1, tr, max(l,tm+1),r);
        int tmp3=tmp2+tmp1;
        return tmp3;
    }
}

int main() {

    //ввод описанного глобального n

    cin >> n;
    int *inver = new int[n]; //массив из единиц
    vector <int> a(n);
//    pair<int, int> p;

    //массив пар значение/индекс
    vector<pair <int, int> > pairs(n);

    int i,j=0;
    int con=0; //счетчик

    //перестановка
    for (i=0; i<n; i++, j++) {
        cin >> a[i];
        pairs[j].first = a[i]-1; //ставим -1 чтоб везде было до n-1
        pairs[j].second = i;
    }

    for (i=0; i<n; i++)
        inver[i]=1;

    build(1,0,n-1,inver);
    //сортируем пары по первому значению
    sort(pairs.begin(), pairs.end());

    //for (i=0; i<4*n; i++)
      //  cout << tree[i] << " ";

    //предварительный вывод
    for (i=0; i<n; i++){
        cout << pairs[i].first << " " << pairs[i].second << endl;
    }

    //обновляем следующий и считаем количество перестановок для него
    for (i=0; i<n; i++) {
        update(1,0,n-1,pairs[i].second,0);
        con += sum(1,0,n-1,0,pairs[i].second);
      //  cout << con << " ";
    }

  //  for (i=0; i<4*n; i++)
    //    cout << tree[i] << " ";

    cout << endl << con;






    return 0;
}
