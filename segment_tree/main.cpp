#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n=4;
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

int main()
{
    int i;
    int *a = new int[n];

    //array:
    cout << n << " elements of array:" << endl;
    for (i=0; i<n; i++)
        cin >> a[i];
    //построение дерева
    build(1,0,n-1,a);

    //отрезок
    int l,r;
    cout << "l, r: ";
    cin >> l >> r;
    //сумма на отрезке
    cout << sum(1,0,n-1,l-1,r-1) << endl;

    //замена j-го элемента на значение k
    int j,p;
    cout << "a[j]=p; j >> p: ";
    cin >> j >> p;

    //обновление дерева
    update(1,0,n-1,j-1,p);
    cout << "new sum: " << sum(1,0,n-1,l-1,r-1) << endl;


    return 0;
}
