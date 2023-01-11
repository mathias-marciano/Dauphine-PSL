#define TenseurSVDD
#include <iostream>
#include <cmath>
#include "Tenseur.h"
#include "SVD2.h"

class TenseurSVD : public Tenseur //Mode public pour pouvoir utiliser la fonction mode ainsi que les membres de tenseur
{
    private:
        Matrice *F;
    public:
        TenseurSVD(int *, int);
        TenseurSVD(int *, int, Vecteur);
        TenseurSVD(int *, int, int, Matrice);
        ~TenseurSVD();
        TenseurSVD(const TenseurSVD &);
        TenseurSVD & operator=(const TenseurSVD &);  
        Tenseur tenseurtotal();
};

TenseurSVD::TenseurSVD(int *tab, int taille): Tenseur(tab, taille) {
    F = new Matrice[d];
}

TenseurSVD::TenseurSVD(int *tab, int taille, Vecteur V): Tenseur(tab, taille, V) {
    F = new Matrice[d];
}

TenseurSVD::TenseurSVD(int *tab, int taille, int k, Matrice A): Tenseur(tab, taille, k, A) {
    F = new Matrice[d];
}

//Destructeur qui supprime F
TenseurSVD::~TenseurSVD(){
    delete [] F;
}

//Constructeur de recopie
TenseurSVD::TenseurSVD(const TenseurSVD &T): Tenseur(T)
{
    F = new Matrice[d];
    for(int i=0;i<d;i++){
        F[i] = T.F[i];
    }
}

//Surcharge de l'operateur affectation
TenseurSVD & TenseurSVD::operator=(const TenseurSVD &T){
    if(this != &T){
        d = T.d;
        tab_dim = new int[d];
        F = new Matrice[d];
        for(int i=0;i<d;i++){
            tab_dim[i] = T.tab_dim[i];
            F[i] = T.F[i];
        }
        nbelts = T.nbelts;
        tenseur_vect = T.tenseur_vect;
    }
    return *this;
}

Tenseur TenseurSVD::tenseurtotal()
{
    Matrice*SS = new Matrice[d];
    Matrice*VV = new Matrice[d];
    
    //Calcul des facteurs de decompositions dans la Matrice F
    for(int k=1;k<d+1;k++){
        Matrice T_k = mode(k);
        Matrice*USV = new Matrice[3];
        USV = svd(T_k, USV);
        F[k-1] = *USV; //Ajout de la matrice U
        SS[k-1] = *(USV+1);
        VV[k-1] = *(USV+2);
    }
    Tenseur S(tab_dim, d, tenseur_vect); //On initialise S=T
    //Calcul du coeur du tenseur
    for(int k=1;k<d+1;k++){
        S = pmod(S, F[k-1].transpose(), k);
    }
    
    Tenseur T_bis = S;
    //Calcul tenseur finale
    for(int k=1;k<d+1;k++){
        T_bis = pmod(T_bis, F[k-1], k);
    }
    
    return T_bis;
}

TenseurSVD hosvd(Tenseur T){
    //Conversion de Tenseur T en TenseurSVD
    int ordre = T.getD();
    int tab_dim_2[ordre];
    int N = 1;
    for(int i=0;i<ordre;i++){
        tab_dim_2[i] = T.getTabDim(i);
        N = N * tab_dim_2[i];
    }
    
    Vecteur V(N);
    for(int i=0;i<N;i++){
        V[i] = T[i];
    }
    
    TenseurSVD T_bis(tab_dim_2, ordre, V);
    
    Tenseur T_finale = T_bis.tenseurtotal();
    //Conversion de T_finale en TenseurSVD
    
    int ordre_T = T_finale.getD();
    int tab_dim_T[ordre_T];
    for(int i=0;i<ordre_T;i++){
        tab_dim_T[i] = T_finale.getTabDim(i);
    }

    int N_T = 1;
    for(int i=0;i<ordre_T;i++){
        N_T = N_T * tab_dim_T[i];
    }
    
    Vecteur V_T(N_T);
    
    for(int i=0;i<N_T;i++){
        V_T[i] = T_finale[i];
    }
    
    TenseurSVD T_finale_2(tab_dim_T, ordre_T, V_T);
    return T_finale_2;
}
