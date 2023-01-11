#define Tenseurr
#include <iostream>
#include <cmath>
#include "Matrice.h"

class Tenseur{
    protected:
        int d;
        int *tab_dim;
        int nbelts;
        Vecteur tenseur_vect;
    public:
        Tenseur(int *, int);
        Tenseur(int *, int, Vecteur);
        Tenseur(int *, int, int, Matrice);
        ~Tenseur();
        Tenseur(const Tenseur &T);
        Tenseur & operator=(const Tenseur &);   
        float & operator[](int);
        Tenseur operator+(Tenseur &);
        Tenseur operator-(Tenseur &);
        Matrice mode(int);
        void affiche_vec();
        int getD();
        int getTabDim(int);
};


//Fonction phi 
int phi(int ordre, int *dims, int *indices){
    int S = indices[ordre-1];
    if(ordre > 1){
        for(int i=1;i<ordre;i++){
            int product = indices[ordre-i - 1] - 1; 
            for(int j=ordre;j>ordre-i;j--){
                product = product * dims[j-1];
            }
            S = S + product;
        }
    }
    return S;
}

//Fonction reste division euclidienne dans cet exercice
float reste(int a, int b){
    int R = a%b;
    if(R==0){
        return b;
    }
    return R;
}


//Fonction inverse de phi
void invphi(int ordre, int *dims, int i, int *indices){
    int F[ordre];
    F[ordre-1] = i;
    indices[ordre-1] = reste(F[ordre-1], dims[ordre-1]);
    if(ordre > 1){
        for(int t=ordre-2;t>-1;t--){
            F[t] = ((F[t+1] - indices[t+1])/dims[t+1]) + 1;
            indices[t] = reste(F[t], dims[t]);
        }
    }
}

//Fonction qui renvoie jk
int phik(int ordre, int *dims, int * indices, int k){ //k correspond au mode
    int ordre_2 = ordre -1;
    int dims_2[ordre_2];
    int indices_2[ordre_2];
    
    //Remplissage de indices_2 sans l'indice ik et de dims_2 sans l'element nk
    if(k > 1){    
        for(int i=0;i<k-1;i++){
            indices_2[i] = indices[i];
            dims_2[i] = dims[i];
        }
        for(int i=k;i<ordre_2+1;i++){
            indices_2[i-1] = indices[i];
            dims_2[i-1] = dims[i];
        }
    } else {
        for(int i=0;i<ordre_2;i++){
            indices_2[i] = indices[i+1];
            dims_2[i] = dims[i+1];
        }
    }
    
    int j = phi(ordre_2, dims_2, indices_2);
    return j;
}

//Constructeur qui cree un tenseur nulle de taille donnee
Tenseur::Tenseur(int *tab, int taille){
    d = taille;
    nbelts = 1;
    tab_dim = new int[d]; 
    for(int i=0;i<taille;i++){
        tab_dim[i] = tab[i];
        nbelts = nbelts * tab[i];
    }
    Vecteur v(nbelts);
    tenseur_vect = v;
}

//Constructeur qui cree un tenseur avec sa version vectorisee fourni
Tenseur::Tenseur(int *tab, int taille, Vecteur V){
    d = taille;
    nbelts = 1;
    tab_dim = new int[d]; 
    for(int i=0;i<taille;i++){
        tab_dim[i] = tab[i];
        nbelts = nbelts * tab[i];
    }
    tenseur_vect = V;
}

//Constructeur prenant un objet de type Matrice
Tenseur::Tenseur(int *tab, int taille, int k, Matrice A){
    d = taille;
    nbelts = 1;
    tab_dim = new int[d]; 
    for(int i=0;i<taille;i++){
        tab_dim[i] = tab[i];
        nbelts = nbelts * tab[i];
    }
    Vecteur v(nbelts);
    
    int nbLigne = tab_dim[k-1];
    int nbCol = nbelts / tab_dim[k-1];
    int indices[d];
    for(int i=0;i<nbLigne;i++){
        indices[k-1] = i+1;
        for(int j=0;j<nbCol;j++){
            int dims_2[d-1];
            
            //Tableau des dimensions sans l'element nk
            if(k > 1){
                for(int l=0;l<k-1;l++){
                    dims_2[l] = tab_dim[l];
                }
                if(k < d){
                    for(int l=k;l<d;l++){
                        dims_2[l-1] = tab_dim[l];
                    }
                }
            } else {
                for(int l=0;l<d-1;l++){
                    dims_2[l] = tab_dim[l+1];
                }
            }
            
            int indices_2[d-1];
            invphi(d-1, dims_2, j+1, indices_2);
            if(k > 1){
                for(int l=0;l<k-1;l++){
                    indices[l] = indices_2[l];
                }
                for(int l=k;l<d;l++){
                    indices[l] = indices_2[l-1];
                }
            } else {
                for(int l=k;l<d;l++){
                    indices[l] = indices_2[l-1];
                }
            }
            
            //On dispose de tous les indices de l'elements : on peut donc le placer dans le vecteur v
            int place = phi(d, tab_dim, indices);
            v[place-1] = A[j][i];
            
        }
    }
    tenseur_vect = v;
}

//Destructeur qui supprime tab_dim 
Tenseur::~Tenseur(){
    delete [] tab_dim;
}

//Affiche le tenseur de façon vectorisee
void Tenseur::affiche_vec(){
    tenseur_vect.affiche();
}

//Constructeur de recopie
Tenseur::Tenseur(const Tenseur &T){
    d = T.d;
    tab_dim = new int[d];
    for(int i=0;i<d;i++){
        tab_dim[i] = T.tab_dim[i];
    }
    nbelts = T.nbelts;
    tenseur_vect = T.tenseur_vect;
}

//Surcharge de l'operateur affectation
Tenseur & Tenseur::operator=(const Tenseur &T){
    if(this != &T){
        d = T.d;
        tab_dim = new int[d];
        for(int i=0;i<d;i++){
            tab_dim[i] = T.tab_dim[i];
        }
        nbelts = T.nbelts;
        tenseur_vect = T.tenseur_vect;
    }
    return *this;
}

//Surcharge de l'operateur [] qui selectionne l'element i du tenseur vectorisee
float & Tenseur::operator[](int i){
    return tenseur_vect[i];
}

//Surcharge de l'operateur + : additionne deux tenseurs de memes dimensions et ordre
Tenseur Tenseur::operator+(Tenseur &T){
    if(d == T.d){
        
        //Verification des dimensions
        for(int i=0;i<d;i++){
            if(tab_dim[i] != T.tab_dim[i]){
                cout << "Les tenseurs n'ont pas les memes dimensions.\n";
                return *this;
            }
        }
        
        Vecteur add(nbelts);
        for(int i=0;i<nbelts;i++){
            add[i] = tenseur_vect[i] + T[i];
        }
        Tenseur A(tab_dim, d, add);
        return A;
    } else {
        cout <<"Les tenseurs n'ont pas le meme ordre.\n";
        return *this;
    }
}    

//Surcharge de l'operateur - : soustrait deux tenseurs de memes dimensions et ordre
Tenseur Tenseur::operator-(Tenseur &T){
    if(d == T.d){
        
        //Verification des dimensions
        for(int i=0;i<d;i++){
            if(tab_dim[i] != T.tab_dim[i]){
                cout << "Les tenseurs n'ont pas les memes dimensions.\n";
                return *this;
            }
        }
        
        Vecteur add(nbelts);
        for(int i=0;i<nbelts;i++){
            add[i] = tenseur_vect[i] - T[i];
        }
        Tenseur A(tab_dim, d, add);
        return A;
    } else {
        cout <<"Les tenseurs n'ont pas le meme ordre.\n";
        return *this;
    }
}    

Matrice Tenseur::mode(int k){
    int nbLigne = tab_dim[k-1]; //nk le nombre de lignes
    int nbCol = nbelts/tab_dim[k-1]; //N/nk le nombre de colonnes
    Matrice A(nbLigne, nbCol);
    
    //Remplissage de la matrice A à partir du vecteur tenseur_vect
    for(int i=0;i<nbelts;i++){
        int indices[d];
        invphi(d, tab_dim, i+1, indices); //Remplissage des indices
        int j = phik(d, tab_dim, indices, k); //Position de la colonne
        A[j-1][indices[k-1] - 1] = tenseur_vect[i];
    }
    return A;
}


//Retourne l'ordre du tenseur
int Tenseur::getD(){
    return d;
}

//Accede a la dimension d'indice i
int Tenseur::getTabDim(int i){
    return tab_dim[i];
}

//Produit modal
Tenseur pmod(Tenseur S, Matrice M, int k){
    int m_k = M.getLines();
    int ordre = S.getD();
    int tab_dim_2[ordre];
    int tab_dim_S[ordre];
    int N = 1;
    int n_k = S.getTabDim(k-1);
    //Remplissage tableau dimension pour le nouveau tenseur
    //Et recuperation du tableau de dimension de S
    for(int i=0;i<ordre;i++){
        if(i != k-1){
            tab_dim_2[i] = S.getTabDim(i);
        } else {
            tab_dim_2[i] = m_k;
        }
        N = N * tab_dim_2[i];
        tab_dim_S[i] = S.getTabDim(i);
    }
    
    Vecteur V(N);
    
    for(int i=0;i<N;i++){
        int indices_T[ordre];
        int indices_S[ordre];
        invphi(ordre, tab_dim_2, i+1, indices_T); //Recuperation des indices
        
        //Remplissage indices de S
        for(int l=0;l<ordre;l++){
            indices_S[l] = indices_T[l];
        }

        //Calcul de la somme
        float Sum = 0;
        for(int j=0;j<n_k;j++){
            indices_S[k-1] = j+1;
            //S = S + M[j][indices[k-1] - 1]
            int place = phi(ordre, tab_dim_S, indices_S); //Indice dans le vecteur de S(i1, i2,...id)
            Sum = Sum + M[j][indices_T[k-1] - 1] * S[place-1];
        }
        V[i] = Sum;
    }
    
    Tenseur T(tab_dim_2, ordre, V);
    return T;
}


