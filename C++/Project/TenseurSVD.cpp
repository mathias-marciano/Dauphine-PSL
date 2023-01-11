#include <iostream>
#include <cmath>
#include "TenseurSVD.h"
using namespace std;

int main()
{ 
    int ordre = 3;
    int dims[3] = {3,3,3};
    Tenseur T(dims, ordre);
    T[0] = 0.9073; 
    T[1] = 0.7158; 
    T[2] = -0.3698; 
    T[3] = 1.7842; 
    T[4] = 1.6970; 
    T[5] = 0.0151; 
    T[6] = 2.1236; 
    T[7] = -0.0740; 
    T[8] = 1.4429;
    T[9] = 0.8924; 
    T[10] = -0.4898;
    T[11] = 2.4288;
    T[12] = 1.7753;
    T[13] = -1.5077; 
    T[14] = 4.0337;
    T[15] = -0.6631; 
    T[16] = 1.9103; 
    T[17] = -1.7495;
    T[18] = 2.1488; 
    T[19] = 0.3054; 
    T[20] = 2.3753; 
    T[21] = 4.2495; 
    T[22] = 0.3207; 
    T[23] = 4.7146; 
    T[24] = 1.8260; 
    T[25] = 2.1335;
    T[26] = -0.2716;
    cout<<"---------------Creation et affichage du mode 1 tenseur T----------------"<<endl;
    Matrice T_1 = T.mode(1);
    T_1.affiche();
    
    cout<<"---------------Nouveau tenseur T avec l'appel de la fonction hosvd----------------"<<endl;
    TenseurSVD T_hosv = hosvd(T);
    Matrice T_1_bis = T_hosv.mode(1);
    T_1_bis.affiche();
    float erreur_relative = 0;
    float Norme_T = norm(T_1);
    for(int i=0;i<3;i++){
        for(int j=0;j<9;j++){
           float c = fabs(T_1[j][i] - T_1_bis[j][i])/Norme_T;
           if(c > erreur_relative){
               erreur_relative = c;
           }
        }
    }
    cout <<"Erreur relative : "<<erreur_relative<<endl;
    cout<<"Il semble y avoir une erreur dans la recuperation des facteurs U donc probleme au niveau de la fonction svd pour des matrices 3x9.";
}
