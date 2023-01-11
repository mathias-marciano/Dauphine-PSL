#include <iostream>

using namespace std;

const int NMOIS = 12;

struct enreg {
	int stock;
	float prix;
	int ventes[NMOIS];
};

void zeros(enreg *e){
	e->stock = 0;
	e->prix = 0;
}

int main(){
	enreg e;
	zeros(&e);
	cout << e.stock;
	cout << e.prix;
}

