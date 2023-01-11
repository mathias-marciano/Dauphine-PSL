#include <iostream>
#include <cmath>
using namespace std ;

int i = 0;
void call();

int main(){
	call();
	call();
	call();
}

void call(){
	i++;
	cout << "Appel de fonction numero "<<i<<"\n"<<endl;
}
