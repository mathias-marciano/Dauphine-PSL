#include <iostream>

using namespace std;

struct complexe {
    float re_part, im_part;
};

//On créer une fonction qui initialise un complexe pour eviter trop de lignes de code
complexe init(float re, float im){ 
    complexe c;
    c.re_part = re;
    c.im_part = im;
    return c;
}

complexe sum(complexe a, complexe b){ //Question 1
    complexe c;
    c.re_part = a.re_part + b.re_part;
    c.im_part = a.im_part + b.im_part;
    return c;
}

complexe sumTab(complexe tab[], int n){
    complexe S = init(0,0);
    for(int i=0;i<n;i++){
        S = sum(S, tab[i]);
    }
    return S;
}

int main()
{
    complexe a = init(3,6);
    complexe b = init(1,3);
    complexe c = init(8,2);
    int n = 3;
    complexe tab[n] = {a, b, c};
    complexe d = sumTab(tab, n);
    cout <<"La somme du tableau donne le complexe : " << d.re_part << " + " << d.im_part << "i";
}