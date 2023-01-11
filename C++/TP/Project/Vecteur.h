#define Vecteure
#include <iostream>
#include <cmath>

using namespace std;

class Vecteur{
    private:
        float *tab;
        int dim;

    public:
        void affiche();
        Vecteur(int);
        Vecteur(float*, int);
        ~Vecteur();
        Vecteur(const Vecteur &);
        Vecteur operator=(const Vecteur &);
        Vecteur operator+(const Vecteur &);
        Vecteur operator-(const Vecteur &);
        float & operator[](int);
        Vecteur subvec(int, int);
        int getDimension(); //utile pour la fonction dot
        friend Vecteur operator*(float, const Vecteur &);
        Vecteur(); //Constructeur vide pour la class Matrice
        friend class Matrice;
};

//Affiche les informations du tenseur
void Vecteur::affiche(){
    cout << "Le tenseur est de dimension :"<<dim<<endl;
    cout << "Voici le contenu du tenseur :\n";
    for(int i=0;i<dim;i++){
        cout <<tab[i]<<"\n";
    }
}

//Constructeur creant un tenseur nulle de taille fourni
Vecteur::Vecteur(int taille){
    dim = taille;
    tab = new float[taille];
    for(int i=0;i<dim;i++){
        tab[i] = 0;
    }
}

//Constructeur creant un tenseur fourni
Vecteur::Vecteur(float *tableau, int taille){
    dim = taille;
    tab = new float[dim];
    for(int i=0;i<dim;i++){
        tab[i] = tableau[i];
    }
}

//Destructeur qui supprime tab 
Vecteur::~Vecteur(){
    delete [] tab;
}

//Constructeur de recopie
Vecteur::Vecteur(const Vecteur &a){
    dim = a.dim;
    tab = new float[dim];
    for(int i=0;i<dim;i++){
        tab[i] = a.tab[i];
    }
}

//Surcharge de l'operateur =
Vecteur Vecteur::operator=(const Vecteur &a){
    if(this != &a){
        dim = a.dim;
        tab = new float[dim];
        for(int i=0;i<dim;i++){
            tab[i] = a.tab[i];
        }
    }
    return *this;
}

//Surcharge de l'operateur + : additionne deux vecteurs de meme taille
Vecteur Vecteur::operator+(const Vecteur &a){
    if(dim == a.dim){
        float tab_b[dim];
        for(int i=0;i<dim;i++){
            tab_b[i] = tab[i] + a.tab[i];
        }
        Vecteur b(tab_b, dim);
        return b;
    } else {
        cout <<"Les vecteurs ne sont pas de meme taille.\n";
        float tab_b[1] = {0};
        Vecteur b(tab_b, 1);
        return b;
    }
}    

//Surcharge de l'operateur - : soustrait deux vecteurs de meme taille
Vecteur Vecteur::operator-(const Vecteur &a){
    if(dim == a.dim){
        float tab_b[dim];
        for(int i=0;i<dim;i++){
            tab_b[i] = tab[i] - a.tab[i];
        }
        Vecteur b(tab_b, dim);
        return b;
    } else {
        cout <<"Les vecteurs ne sont pas de meme taille.\n";
        float tab_b[1] = {0};
        Vecteur b(tab_b, 1);
        return b;
    }
}    

//Surcharge de l'operateur [] qui selectionne l'indice i de tab sans avoir a selectionner tab
float & Vecteur::operator[](int i){
    return tab[i];
}

//Selectionne une partie du vecteur
Vecteur Vecteur::subvec(int i, int j){
    float sous_tab[j-i+1];
    for(int k=i;k<j+1;k++){
        sous_tab[k-i]=tab[k];
    }
    Vecteur c(sous_tab, j-i+1);
    return c;
}

//Renvoie la taille du Vecteur
int Vecteur::getDimension(){
    return dim;
}

float dot(Vecteur a, Vecteur b){
    if(a.getDimension() == b.getDimension()){
        float sum = 0;
        for(int i=0;i<a.getDimension();i++){
            sum = sum + a[i] * b[i];
        }
        return sum;
    } else {
        cout << "Les vecteurs ne sont pas de meme taille.";
        float sum = 0;
        return sum;
    }
}

float norm(Vecteur a){
    return sqrt(dot(a,a));
}

//Surcharge de l'operateur scalaire
Vecteur operator*(float k, const Vecteur &d){
    int dimension = d.dim;
    float tab_b[dimension];
    for(int i=0;i<dimension;i++){
        tab_b[i] = k * d.tab[i];
    }
    Vecteur b(tab_b, dimension);
    return b;
}

//Constructeur vide pour la class Matrice
Vecteur::Vecteur(){ }