#include <iostream>
#include <cmath>
using namespace std;

void sumTab(float tab[], int n, float *ptr);

int main(){
	float sum = 0;
	float *ptr;
	int n = 7;
	float tab[7] = {3,5,2,3,2,10.4,10};
	ptr = &sum;
	sumTab(tab, n, ptr);
	cout << "La somme des éléments du tableau est : "<<sum<<endl;
}

void sumTab(float tab[], int n, float *ptr){
	for(int i=0; i<n; i++){
		*ptr+=tab[i];
	}
}