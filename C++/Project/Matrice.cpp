#include <iostream>
#include <cmath>
#include "Matrice.h"
using namespace std;

int main()
{
    //Question 1
    cout<<"Question 1"<<endl;
    float tab_A_c1[] = {1,1,0};
    Vecteur A_c1(tab_A_c1, 3);
    float tab_A_c2[] = {-0.5, 2, -1};
    Vecteur A_c2(tab_A_c2, 3);
    float tab_A_c3[] = {0,-1,1};
    Vecteur A_c3(tab_A_c3, 3);
    Vecteur tab_A[] = {A_c1, A_c2, A_c3};
    Matrice A(tab_A, 3);
    cout << "-------------Matrice A-------------\n";
    A.affiche();
    
    float tab_B_c1[] = {-2,0};
    Vecteur B_c1(tab_B_c1, 2);
    float tab_B_c2[] = {3,1};
    Vecteur B_c2(tab_B_c2, 2);
    Vecteur tab_B[] = {B_c1, B_c2};
    Matrice B(tab_B, 2);
    cout << "-------------Matrice B-------------\n";
    B.affiche();
    
    //Question 2
    cout<<"Question 2"<<endl;
    Matrice C = B;
    B[1][0] = 0;
    cout << "-------------Matrice B-------------\n";
    B.affiche();
    cout << "-------------Matrice C-------------\n";
    C.affiche();
    
    //Question 3
    cout<<"Question 3"<<endl;
    Matrice D = A.submat(0,2,0,1);
    cout << "-------------Matrice D-------------\n";
    D.affiche();
    
    //Question 4
    cout<<"Question 4"<<endl;
    float tab_v[] = {3,2,1};
    Vecteur v(tab_v, 3);
    Matrice E(v);
    cout << "-------------Matrice E-------------\n";
    E.affiche();
    
    //Question 5
    cout<<"Question 5"<<endl;
    Matrice Sum_B_C = B + C;
    Matrice Sou_C_B = C - B;
    Matrice Pdt_D_C = D*C;
    cout << "-------------Matrice B+C-------------\n";
    Sum_B_C.affiche();
    cout << "-------------Matrice C-B-------------\n";
    Sou_C_B.affiche();
    cout << "-------------Matrice D*C-------------\n";
    Pdt_D_C.affiche();
    
    //Question 6
    cout<<"Question 6"<<endl;
    float norme_C = norm(C);
    cout <<"La norme de la matrice C est de "<<norme_C<<endl;
    
    //Question 7
    cout<<"Question 7"<<endl;
    Matrice modif_B = 0.5*(B + B.transpose());
    cout << "-------------Matrice 0.5*(B + transpose(B))-------------\n";
    modif_B.affiche();
}