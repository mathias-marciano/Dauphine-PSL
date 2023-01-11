#include <iostream>
#include "TP4_exo1.h"
using namespace std;

int main(){
	Morpion unepartie;
	int i, j;
	typecase winner = vide;
	while(unepartie.gagnant() ==vide){
		cout<<"Ligne ?";
		cin >>i;
		cout<<"Colonne ?";
		cin>>j;
		unepartie.jouer(i,j);
		winner = unepartie.gagnant();
	}
	cout<<"Le gagnant est : "<<winner;
}