#include <iostream>
#include <cmath>
using namespace std ;
main (){
  float sum;
  int n;
  sum = 0;
  cout <<"Entrer une valeur pour n : ";
  cin >> n;
  for(float i=1; i<=n; i++){
    sum = sum + (1/i);
  }
  cout <<"La valeur de la serie harmonique est : "<<sum<<endl;
}
