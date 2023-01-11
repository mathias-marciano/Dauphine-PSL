#include <iostream>

using namespace std;

const int LMAX_NOM =30;

struct date {
	int jour;
	int mois;
	int annee;
};

struct personne {
	int L_NOM;
	char *nom = new char[LMAX_NOM];
	date date_inscr;
};

void inscr_personne(personne *p, int LMIN_NOM){
	cout << "Entrez chaque lettre du nom de la personne : ";
    for(int i=0; i<LMIN_NOM; i++){
        cin >> p->nom[i];
    }
	cout << "Entre le jour d'inscription : ";
	cin >> p->date_inscr.jour;
	cout << "Entre le mois d'inscription : ";
	cin >> p->date_inscr.mois;
	cout << "Entre l'annee d'inscription : ";
	cin >> p->date_inscr.annee;
}

int main(){
	int longueur;
	cout <<"Entrez une longueur de nom : ";
	cin >> longueur;
	personne p;
	inscr_personne(&p, longueur);
	cout << "Nom : "<<p.nom;
	cout << "Date d'inscription : "<<p.date_inscr.jour<<"/"<<p.date_inscr.mois<<"/"<<p.date_inscr.annee;
}