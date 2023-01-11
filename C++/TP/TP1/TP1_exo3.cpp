#include <iostream>
#include <cmath>
using namespace std ;
main (){
  int hauteur;
  cout << "Entrer la hauteur de l'arbre : ";
  cin >> hauteur;
  for(int i=1; i<=hauteur; i++){
    for(int j=1; j<=8-i; j++){
      cout <<"=";
    }
    for(int j=1; j<=(2*i)-1; j++){
      cout <<"*";
    }
    for(int j=1; j<=8-i; j++){
      cout <<"=";
    }
    cout <<"\n";
  }
}
