#include <iostream>
#include <cmath>
using namespace std;

int main(){
	/*------------Question 1----------------*/
	int n;
	cout << "Entrez une taille pour le tableau : ";
	cin >> n;
	int *tab = new int[n]; 
	/*------------Question 2----------------*/
	for (int i=0;i<n;i++){
		cout << "Entrez la valeur "<< i+1<<endl;
		cin >> tab[i];
	}
	/*------------Question 3----------------*/
	int tab2[n];
	for (int i=0;i<n;i++){
		tab2[i] = tab[i]*tab[i];	
	}
	/*------------Question 4----------------*/
	delete[] tab;
	cout << "Voici les valeurs du tableau 2 : ";
	for (int i=0;i<n;i++){
		cout << tab2[i] << "; ";	
	}
}