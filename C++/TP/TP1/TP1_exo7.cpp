#include <iostream>
#include <cmath>
using namespace std ;

int pgcd(int a, int b);

int main(){
	int a;
	int b;
	cout << "Entrez a : ";
	cin >> a;
	cout << "Entrez b : ";
	cin >> b;
	cout << pgcd(a, b);
}

int pgcd(int a, int b){
	if (b == 0){
		return a;
	} else {
		/* On applique l'algorithme d'Euclide */
		int r = a % b;
		while (r != 0){
			a = b;
			b = r;
			r = a%b;
		}
		return b;
	}
}