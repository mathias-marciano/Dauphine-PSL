#include <iostream>
#include <cmath>
#include "Vecteur.h"
using namespace std;

int main()
{
    //Question 1
    cout<<"Question 1"<<endl;
    float tab_u[] = {1,1,1};
    int dim_u = 3;
    Vecteur u(tab_u, dim_u);
    float tab_v[] = {3,4,0,0};
    int dim_v = 4;
    Vecteur v(tab_v, dim_v);
    cout << "-------------Tenseur u-------------\n";
    u.affiche();
    cout << "-------------Tenseur v-------------\n";
    v.affiche();


    //Question 2
    Vecteur t(u);
    
    //Question 3
    cout<<"Question 3"<<endl;
    u[2] = 0;
    cout << "-------------Tenseur u-------------\n";
    u.affiche();
    cout << "-------------Tenseur t-------------\n";
    t.affiche();
    
    //Question 4
    cout<<"Question 4"<<endl;
    float ps_v = dot(v,v);
    float norme_v = norm(v);
    cout << "Le produit scalaire v*v vaut "<<ps_v<<" et la norme de v vaut "<<norme_v<<".\n";
    
    //Question 5
    cout<<"Question 5"<<endl;
    float n = 1/norme_v;
    Vecteur v2 = n * v;
    cout << "-------------Tenseur v/norme(v)-------------\n";
    v2.affiche();
    
    //Question 6
    cout<<"Question 6"<<endl;
    Vecteur w = v.subvec(1, 3);    
    cout << "-------------Tenseur v-------------\n";
    v.affiche();
    cout << "-------------Tenseur w-------------\n";
    w.affiche();
    
    //Question 7
    cout<<"Question 7"<<endl;
    Vecteur u_w_add = u + w;
    Vecteur u_w_sou = u - w;
    cout << "-------------Tenseur u + w-------------\n";
    u_w_add.affiche();
    cout << "-------------Tenseur u - w-------------\n";
    u_w_sou.affiche();
}