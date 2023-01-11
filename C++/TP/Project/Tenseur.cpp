#include <iostream>
#include <cmath>
#include "Tenseur.h"
using namespace std;

int main()
{ 
    //Question 1
    cout<<"Question 1"<<endl;
    cout<<"---------------Creation et affichage tenseur T----------------"<<endl;
    int tab[3] = {2,2,2};
    int d = 3;
    Tenseur T(tab, d);
    T.affiche_vec();
 
    //Question 2
    cout<<"Question 2"<<endl;
    cout<<"---------------Creation et affichage tenseur U----------------"<<endl;
    Vecteur v_U(8);
    for(int i=0;i<8;i++){
        v_U[i] = 1;
    }
    Tenseur U(tab, d, v_U);
    U.affiche_vec();
    
    //Question 3
    cout<<"Question 3"<<endl;
    cout<<"---------------Creation et affichage tenseur V = U + T----------------"<<endl;
    Tenseur V = U + T;
    V.affiche_vec();
    
    cout<<"---------------Creation et affichage tenseur W = U - T----------------"<<endl;
    Tenseur W = U - T;
    W.affiche_vec();
    
    //Question 4
    cout<<"Question 4"<<endl;
    int indices[3] = {2,2,2};
    int position = phi(d, tab, indices); //Position de (2,2,2) dans le vecteur
    cout <<"--------------Affichage et modification de U(2,2,2)-----------------"<<endl;
    cout<<"U(2,2,2) = "<<U[position-1]<<endl;
    cout<<"Modification....."<<endl;
    U[position-1] = -1;
    cout<<"---------------Affichage tenseur U----------------"<<endl;
    U.affiche_vec();
    cout<<"---------------Affichage tenseur V----------------"<<endl;
    V.affiche_vec();
    
    //Question 5
    cout<<"Question 5"<<endl;
    cout<<"---------------Calcul et affichage tenseur T mode 1---------------"<<endl;
    Matrice T_1 = T.mode(1);
    T_1.affiche();
    
    //Question 6
    cout<<"Question 6"<<endl;
    cout<<"---------------Modifications coefficients tenseur T---------------"<<endl;
    T[0] = 1;
    T[1] = 3;
    T[2] = 4;
    T[3] = 0.33;
    T[4] = 0;
    T[5] = -1;
    T[6] = 1.5;
    T[7] = 2;
    T.affiche_vec();
    Matrice T_2 = T.mode(2);
    T_2.affiche();
    
    //Question 7
    cout<<"Question 7"<<endl;
    cout<<"---------------Calcul et affichage du produit modal S---------------"<<endl;
    Matrice A(3,2);
    A[0][0] = 3;
    A[0][1] = 0;
    A[0][2] = 0;
    A[1][0] = -1;
    A[1][1] = 6;
    A[1][2] = -3;
    Tenseur S = pmod(T, A, 3);
    S.affiche_vec();
    cout<<"Affichage du mode 3 de S :"<<endl;
    Matrice S_3 = S.mode(3);
    S_3.affiche();
    
    //Question 8
    cout<<"Question 8"<<endl;
    cout<<"---------------Calcul et affichage du tenseur R = S + S---------------"<<endl;
    Tenseur R = S + S;
    R.affiche_vec();
}
