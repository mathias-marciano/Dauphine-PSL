#include <iostream>

using namespace std;

const int LMAX_NOM =30;

struct date {
	int jour;
	int mois;
	int annee;
};

struct personne {
	char nom[LMAX_NOM];
	date date_inscr;
};

void inscr.personne(personne *p){
	cout << "Entrez le nom de la personne : ";
	cin >> p->nom;
	cout << "Entre le jour d'inscription : ";
	cin >> p->date-inscr.jour;
	cout << "Entre le mois d'inscription : ";
	cin >> p->date-inscr.mois;
	cout << "Entre l'annee d'inscription : ";
	cin >> p->date-inscr.annee;
}

int main(){
	personne p;
	inscr.personne(&p);
	cout << "Nom : "<<p.nom;
	cout << "Date d'inscription : "<<p.date_inscr.jour<<"/"<<p.date_inscr.mois<<"/"<<p.date_inscr.annee;
}