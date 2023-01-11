#include <iostream>
#include <cmath>
using namespace std ;

float calculatrice(float a, float b, char c);

int main (){
    float a;
    float b;
    cout << "Entrez un nombre a : ";
    cin >> a;
    cout << "Entrez un nombre b : ";
    cin >> b;
    float addition = calculatrice(a, b, '+');
    float soustraction = calculatrice(a, b, '-');
    float multiplication = calculatrice(a, b, '*');
    float division = calculatrice(a, b, '/');
    cout << "a + b = "<<addition<<endl;
    cout << "a - b = "<<soustraction<<endl;
    cout << "a * b = "<<multiplication<<endl;
    cout << "a / b = "<<division<<endl;
}

float calculatrice(float a, float b, char c){
    switch (c){
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/': 
            if (b == 0){
                cout << "On ne peut pas diviser par 0.\n";
                return 0;
            }

            return a / b;

        default:
            cout << "Opération incorrecte.";
            return 0;
    }
}

