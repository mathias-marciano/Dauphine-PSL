#include <iostream>
#include <cmath>
using namespace std;

void ajouter(int p, int &n){
	n += p;
}

int main(){
	int n=0;
	int p;
	cout << "Entrez la valeur de p : ";
	cin >> p;
	ajouter(2*p, n);
	cout << "n = "<<n<<endl;
}