#include <iostream>
#include <cmath>
using namespace std ;
main (){
  int valeur;
  while(valeur!=0){
    cout <<"Entrez une valeur positive (0 pour terminer) : ";
    cin >> valeur;
    if(valeur >0){
        cout <<"La racine de " <<valeur<< " est : "<<sqrt(valeur)<<".\n";
    }
    if(valeur<0){
      cout <<"Erreur, la valeur ne peut pas etre negative.\n";
    }
  }
  cout <<"Fin du programme\n";
}
