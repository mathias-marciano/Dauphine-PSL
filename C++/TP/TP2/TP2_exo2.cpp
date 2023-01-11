#include <iostream>
#include <cmath>
using namespace std;

void minMaxTab(float t1[10]){
	float min = t1[0];
	float max = t1[0];
	for(int i=1; i<10; i++){
		if(min > t1[i]){
			min = t1[i];
		}
		if(max < t1[i]){
			max = t1[i];
		}
	}
    cout << "Le minimum du tableau 1 est : "<<min<<endl;
    cout << "Le maximum du tableau 2 est : "<<max<<endl;
}

void replaceTab(float t1[10], float t2[10]){
	//int j = 0;
	float *ptr1, *ptr2;
	ptr1 = t1;
	ptr2 = t2;
	for(int i=0; i < 10; i++){
	    if(t2[i] > 0){
	        *ptr1 = t2[i];
	    } else {
	        *ptr1 = 0;
	    }
	    ptr1++; //le pointeur pointe maintenant l'indice suivant de t1
	}
}

int main(){
	float t1[10] = {1.2, 2.3, 2.6, 7.5, 9.2, -0.9, -2.3, 10.3, 6.5, 9.2};
	float t2[10] = {5.8, -4.7, 1.2, 7.3, 4.7, 9.2, 3.6, -8.4, 2.3, 11.2};
	minMaxTab(t1);
	replaceTab(t1, t2);
	cout << "Voici le nouveau tableau t1 : ";
	for(int i = 0; i < 10; i++){
	    cout << t1[i] << "; ";
	}
}