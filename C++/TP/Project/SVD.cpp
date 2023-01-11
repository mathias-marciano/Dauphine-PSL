#include <iostream>
#include <cmath>
#include "SVD.h"
using namespace std;

int main()
{
    cout<<"---------Affichage fonction givens----------"<<endl;
    float x = 1;
    float z = 2;
    float c;
    float s;
    givens(x,z,c,s);
    cout<<"Valeur de c : "<<c<<endl;
    cout<<"Valeur de s : "<<s<<endl;
    
    cout<<"---------Affichage fonction householder----------"<<endl;
    float tab_x[] = {-1,0};
    Vecteur x_2(tab_x, 2);
    float B_x;
    Vecteur v_x = householder(x_2, B_x);
    cout<<"---------Pour x=(-1,0)------------"<<endl;
    cout<<"---------Vecteur v--------------"<<endl;
    v_x.affiche();
    cout<<"Valeur de Beta : "<<B_x<<endl;
    
    float tab_y[] = {1/sqrt(2),1/sqrt(2)};
    Vecteur y(tab_y, 2);
    float B_y;
    Vecteur v_y = householder(y, B_y);
    cout<<"---------Pour y=(1/racine(2),1/racine(2))------------"<<endl;
    cout<<"---------Vecteur v--------------"<<endl;
    v_y.affiche();
    cout<<"Valeur de Beta : "<<B_y<<endl;
    
    float tab_z[] = {-4};
    Vecteur z_2(tab_z, 1);
    float B_z;
    Vecteur v_z = householder(z_2, B_z);
    cout<<"---------Pour z=(-4)------------"<<endl;
    cout<<"---------Vecteur v--------------"<<endl;
    v_z.affiche();
    cout<<"Valeur de Beta : "<<B_z<<endl;    
    
    cout<<"---------Affichage fonction qrsym------------"<<endl;
    float tab_M_c1[] = {10,-6};
    Vecteur M_c1(tab_M_c1, 2);
    float tab_M_c2[] = {-6, 10};
    Vecteur M_c2(tab_M_c2, 2);
    Vecteur tab_M_all[] = {M_c1, M_c2};
    Matrice M(tab_M_all, 2);
    
    Matrice Q_M = qrsym(M);
    cout<<"----------------Matrice Q de M-------------"<<endl;
    Q_M.affiche();
    
    cout<<"----------------Affichage fonction qrpivot------------"<<endl;
    float tab_M2_c1[] = {1,0.5, 0.33};
    Vecteur M2_c1(tab_M2_c1, 3);
    float tab_M2_c2[] = {0.5, 0.33, 0.25};
    Vecteur M2_c2(tab_M2_c2, 3);
    float tab_M2_c3[] = {0.33,0.25,0.2};
    Vecteur M2_c3(tab_M2_c3, 3);
    Vecteur tab_M2_all[] = {M2_c1, M2_c2, M2_c3};
    Matrice M2(tab_M2_all, 3);
    Matrice Q_M2(3,3);
    Matrice Pi = qrpivot(M2, Q_M2);
    Matrice R = Q_M2.transpose() * M2 * Pi;
    
    cout<<"----------------Matrice Q de M-------------"<<endl;
    Q_M2.affiche();
    cout<<"----------------Matrice Pi de M-------------"<<endl;
    Pi.affiche();
    cout<<"----------------Matrice R=transpose(Q) * M * Pi-------------"<<endl;
    R.affiche();
    
    cout <<"-------------Affichage de la decomposition en valeurs singulieres---------------"<<endl;
    
    float tab_A_c1[] = {1,0};
    Vecteur A_c1(tab_A_c1, 2);
    float tab_A_c2[] = {0, -1};
    Vecteur A_c2(tab_A_c2, 2);
    Vecteur tab_A_all[] = {A_c1, A_c2};
    Matrice A(tab_A_all, 2);
    cout << "-------------Matrice A-------------\n";
    A.affiche(); 

    Matrice*tab_A = new Matrice[3];
    tab_A = svd(A, tab_A);
    Matrice U_A = *tab_A;
    Matrice S_A = *(tab_A+1);
    Matrice V_A = *(tab_A+2);
    cout << "-------------Matrice U de A-------------\n";
    U_A.affiche();
    cout << "-------------Matrice Sigma de A-------------\n";
    S_A.affiche();
    cout << "-------------Matrice V de A-------------\n";
    V_A.affiche();


    float tab_B_c1[] = {2*sqrt(2),-sqrt(2)};
    Vecteur B_c1(tab_B_c1, 2);
    float tab_B_c2[] = {-2*sqrt(2), -sqrt(2)};
    Vecteur B_c2(tab_B_c2, 2);
    Vecteur tab_B_all[] = {B_c1, B_c2};
    Matrice B(tab_B_all, 2);
    cout << "-------------Matrice B-------------\n";
    B.affiche();
    
    Matrice*tab_B = new Matrice[3];
    tab_B = svd(B, tab_B);
    Matrice U_B = *tab_B;
    Matrice S_B = *(tab_B+1);
    Matrice V_B = *(tab_B+2);
    cout << "-------------Matrice U de B-------------\n";
    U_B.affiche();
    cout << "-------------Matrice Sigma de B-------------\n";
    S_B.affiche();
    cout << "-------------Matrice V de B-------------\n";
    V_B.affiche();

    float tab_C_c1[] = {0.5,sqrt(3)/2};
    Vecteur C_c1(tab_C_c1, 2);
    float tab_C_c2[] = {3*sqrt(3)/2, -1.5};
    Vecteur C_c2(tab_C_c2, 2);
    float tab_C_c3[] = {0,0};
    Vecteur C_c3(tab_C_c3, 2); 
    Vecteur tab_C_all[] = {C_c1, C_c2, C_c3};
    Matrice C(tab_C_all, 3);
    cout << "-------------Matrice C-------------\n";
    C.affiche();
    
    Matrice*tab_C = new Matrice[3];
    tab_C = svd(C, tab_C);
    Matrice U_C = *tab_C;
    Matrice S_C = *(tab_C+1);
    Matrice V_C = *(tab_C+2);
    cout << "-------------Matrice U de C-------------\n";
    U_C.affiche();
    cout << "-------------Matrice Sigma de C-------------\n";
    S_C.affiche();
    cout << "-------------Matrice V de C-------------\n";
    V_C.affiche();
}
