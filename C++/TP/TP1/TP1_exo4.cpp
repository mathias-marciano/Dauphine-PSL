#include <iostream>
#include <cmath>
using namespace std ;
int main (){
    int un_3 = 0; /*u0*/
    int un_2 = 0; /*u1*/
    int un_1 = 1; /*u2*/
    int un = 0; 
    int n;
    cout <<"Entrer l'indice n du terme de la suite de Tribonacci voulu : ";
    cin >> n;
    if (n==0 | n==1){
        cout << "La valeur du terme u"<<n<<" est : "<<un_3<<endl;
    } 
    else if (n==2){
        cout << "La valeur du terme u"<<n<<" est : "<<un_1<<endl;
    }
    else {
        for(int i=3; i<=n; i++){
            un = un_1 + un_2 + un_3;
            un_3 = un_2; /*u(n-3) = u(n-2) pour la prochaine iteration et ainsi de suite */
            un_2 = un_1;
            un_1 = un;
        }
        cout << "La valeur du terme u"<<n<<" est : "<<un<<endl;
    }
}