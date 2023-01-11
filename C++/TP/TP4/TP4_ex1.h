#define TP4_ex1_h
#include <iostream>

using namespace std;

//Question 1
enum typecase {vide,joueur1,joueur2};
	//Question 2
class Morpion{
	private:
		typecase tab[3][3];
		typecase player;
	public:
		Morpion();
		void jouer(int i, int j);
		typecase gagnant();
};

Morpion::Morpion(){
	for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++){
        	tab[i][j] = vide;
    	}
	}	
	player = joueur1;	
}
void Morpion::jouer(int i, int j){
	if(i >= 0 & i<=2 & j >=0 & j <=2){
		if(tab[i][j]==0){ //si la case est vide
			tab[i][j] = player;
			if(player==joueur1){
			    player=joueur2;
			    cout<<"Au tour du joueur 2\n";
			} else {
			    player=joueur1;
			    cout<<"Au tour du joueur 1\n";
			}
		} else {
			cout<<"La case est déjà occupé par le joueur"<<tab[i][j]<<endl;
		}
		} else {
			cout <<"Erreur au niveau des indices.";
		}
	}

typecase Morpion::gagnant(){
	//S'il y a trois cases identiques  sur la même ligne
	for(int i=0;i<3;i++){
		if(tab[i][0]==tab[i][1] & tab[i][1]==tab[i][2] & tab[i][0] != vide){ 
			return tab[i][0];
		}
	}
	//S'il y a trois cases identiques  sur la même colonne
	for(int j=0;j<3;j++){
		if(tab[0][j]==tab[1][j] & tab[1][j]==tab[2][j] & tab[0][j] != vide){
			return tab[0][j];
		}
	}

	//S'il y a trois cases identiques sur l'une des diagonales
	if (tab[0][0] == tab[1][1] & tab[1][1]== tab[2][2] & tab[1][1] != vide){
		return tab[0][0];
	}

	if (tab[0][2] == tab[1][1] & tab[1][1] == tab[2][0] & tab[0][2] != vide){
		return tab[0][2];
	}
	return vide;
}