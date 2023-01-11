#define Matricee
#include <iostream>
#include <cmath>
#include "Vecteur.h"
using namespace std;

class Matrice{
    private:
        Vecteur *mat;
        int dims[2];

    public:
        void affiche();
        Matrice();
        Matrice(int, int);
        Matrice(Vecteur);
        Matrice(Vecteur *, int);
        ~Matrice();
        Matrice(const Matrice &M);
        Matrice & operator=(const Matrice &);
        Vecteur & operator[](int);
        Matrice operator+(const Matrice &);
        Matrice operator-(const Matrice &);
        Matrice operator*(const Matrice &);
        Vecteur mvprod(Vecteur);
        Matrice transpose();
        Matrice submat(int, int, int, int);
        int getLines(); //Utile pour norm()
        int getCols(); //Utile pour norm()
        friend Matrice operator*(float, Matrice);
};

//Affiche les informations d'une matrice
void Matrice::affiche(){
    cout << "La matrice est de dimension "<<dims[0]<<" x "<<dims[1]<<endl;
    cout << "Les coefficients de la matrice sont : \n";
    for(int i=0;i<dims[0];i++){
        for(int j=0;j<dims[1];j++){
            cout <<mat[j][i]<<" ";
            if(j==dims[1]-1){
                cout <<"\n";
            }
        }
    }
}

//Constructeur qui cree une matrice de taille i x j qui est nulle
Matrice::Matrice(int nbLignes, int nbColonnes){
    dims[0] = nbLignes;
    dims[1] = nbColonnes;
    mat = new Vecteur[nbColonnes];
    for(int i=0;i<nbColonnes;i++){
        mat[i] = Vecteur(nbLignes);
    }
}

//Constructeur qui cree une matrice ayant pour termes diagonaux ceux du vecteur en argument
Matrice::Matrice(Vecteur a){
    int taille = a.getDimension();
    dims[0] = taille;
    dims[1] = taille;
    
    //On cree dans un premier temps une matrice nulle
    mat = new Vecteur[taille];
    for(int i=0;i<taille;i++){
        mat[i] = Vecteur(taille);
    }
    
    //Puis on modifie les termes diagonaux
    for(int i=0;i<taille;i++){
        mat[i][i] = a[i];
    }
}

//Constructeur qui cree une matrice dont les coefficients sont fournis
Matrice::Matrice(Vecteur *M, int taille){
    dims[0] = M[0].getDimension();
    dims[1] = taille;
    mat = new Vecteur[taille];
    for(int i=0;i<dims[1];i++){
        mat[i] = M[i];
    }
}

//Destructeur qui supprime mat
Matrice::~Matrice(){
    delete [] mat;
}

//Constructeur de recopie
Matrice::Matrice(const Matrice &M){
    dims[0] = M.dims[0];
    dims[1] = M.dims[1];
    mat = new Vecteur[dims[1]];
    for(int i=0;i<dims[1];i++){
        mat[i] = M.mat[i];
    }
}

//Surdefinition de l'operateur d'affectation
Matrice & Matrice::operator=(const Matrice &M){
   if(this != &M)
   {
        dims[0] = M.dims[0];
        dims[1] = M.dims[1];
        mat = new Vecteur[dims[1]];
        for(int i=0;i<dims[1];i++){
            mat[i] = M.mat[i];
        }
    }
    return *this;
}

//Surcharge de l'operateur [] qui selectionne la colonne i de la matrice
Vecteur & Matrice::operator[](int i){
    return mat[i];
}

//Surcharge de l'operateur + : additionne deux matrice de meme taille
Matrice Matrice::operator+(const Matrice &B){
    if(dims[0] == B.dims[0] and dims[1] == B.dims[1]){
        Matrice C(dims[0], dims[1]); //On cree une matrice nulle
        for(int i=0;i<dims[0];i++){
            for(int j=0;j<dims[1];j++){
                C.mat[j][i] = mat[j][i] + B.mat[j][i];
            }
        }
        return C;
    } else {
        cout << "Les matrices n'ont pas la meme taille.\n";
        float tab_c[] = {0};
        Vecteur c(tab_c, 1);
        Matrice C(c);
        return C;
    }
}

//Surcharge de l'operateur - : soustrait deux matrice de meme taille
Matrice Matrice::operator-(const Matrice &B){
    if(dims[0] == B.dims[0] and dims[1] == B.dims[1]){
        Matrice C(dims[0], dims[1]); //On cree une matrice nulle
        for(int i=0;i<dims[0];i++){
            for(int j=0;j<dims[1];j++){
                C.mat[j][i] = mat[j][i] - B.mat[j][i];
            }
        }
        return C;
    } else {
        cout << "Les matrices n'ont pas la meme taille.\n";
        float tab_c[] = {0};
        Vecteur c(tab_c, 1);
        Matrice C(c);
        return C;
    }
}

//Surcharge de l'operateur * : produit de deux matrices de taille compatible
Matrice Matrice::operator*(const Matrice &B){
    if(dims[1] == B.dims[0]){
        Matrice C(dims[0], B.dims[1]);
        for(int i=0;i<dims[0];i++){
            for(int j=0;j<B.dims[1];j++){
                float sum = 0;
                for(int k=0;k<dims[1];k++){
                    sum = sum + mat[k][i] * B.mat[j][k];
                }
                C.mat[j][i] = sum;
            }
        }
        return C;
    } else {
        cout << "Les matrices n'ont pas des tailles compatibles.\n";
        float tab_c[] = {0};
        Vecteur c(tab_c, 1);
        Matrice C(c);
        return C;
    }
}

//Produit matrice-vecteur
Vecteur Matrice::mvprod(Vecteur a){
    if(dims[1] == a.dim){
        Vecteur b(dims[0]);
        for(int i=0;i<dims[0];i++){
            float sum = 0;
            for(int k=0;k<dims[1];k++){
                sum = sum + mat[k][i] * a[k];
            }
            b[i] = sum;
        }
        return b;
    } else {
        cout << "Le vecteur et la matrice n'ont pas des dimensions compatibles.\n";
        float tab_b[] = {0};
        Vecteur b(tab_b, 1);
        return b;
    }
}

//Renvoie la transpose d'une matrice
Matrice Matrice::transpose(){
    Matrice B(dims[1], dims[0]); //On cree une matrice nulle
    for(int i=0;i<dims[1];i++){
        for(int j=0;j<dims[0];j++){
            B.mat[j][i] = mat[i][j];
        }
    }
    return B;
}

//Renvoie la sous-matrice selectionne
Matrice Matrice::submat(int i_l, int j_l, int i_c, int j_c){
    Matrice B(j_l - i_l + 1, j_c - i_c + 1);
    for(int i=0;i<B.dims[0];i++){
        for(int j=0;j<B.dims[1];j++){
            B[j][i] = mat[i_c + j][i_l + i];
        }
    }
    return B;
}

//Renvoie le nombre de lignes d'une matrice
int Matrice::getLines(){
    return dims[0];
}

//Renvoie le nombre de colonnes d'une matrice
int Matrice::getCols(){
    return dims[1];
}

//Renvoie la norme de Frobenius d'une matrice
float norm(Matrice A){
    float sum = 0;
    for(int i=0;i<A.getLines();i++){
        for(int j=0;j<A.getCols();j++){
            sum = sum + pow(A[j][i],2);
        }
    }
    return sqrt(sum);
}

//Surcharge de l'operateur scalaire
Matrice operator*(float k, Matrice A){
    Matrice B(A.dims[0], A.dims[1]); //On cree une matrice nulle
    for(int i=0;i<A.dims[0];i++){
        for(int j=0;j<A.dims[1];j++){
            B[j][i] = k * A[j][i];
        }
    }
    return B;
}

//Produit vecteur-transpose(vecteur)
Matrice outer(Vecteur a, Vecteur b){
    if(a.getDimension() == b.getDimension()){
        Matrice A(a.getDimension(), a.getDimension());
        for(int i=0;i<a.getDimension();i++){
            for(int j=0;j<a.getDimension();j++){
                A[j][i] = a[i] * b[j];
            }
        }
        return A;
    } else {
        cout << "Les vecteurs doivent etre de meme dimension.\n";
        float tab_c[] = {0};
        Vecteur c(tab_c, 1);
        Matrice A(c);
        return A;
    }
}

Matrice::Matrice(){
    mat = nullptr;
}
