#include <iostream>
#include <cmath>
using namespace std;

int occurences(char mot[], char lettre);

int main(){
	char mot[] = "testee";
	char lettre = 'e';
	cout << "Il y a " << occurences(mot, lettre) << " " << lettre << " dans le mot " << mot<< endl;
}

int occurences(char mot[], char lettre){
	int i = 0;
	int j = 0;
	int occur = 0;
	while(i!=1){
		if (mot[j] == lettre){
			occur++;
		} else if (mot[j] == '\0') {
			i = 1; //Si on atteint la fin de la chaîne, on sort de la boucle
		}
		j++;
	}
	return occur;
}