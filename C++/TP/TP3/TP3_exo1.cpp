#include <iostream>

using namespace std;

struct complexe {
    float re_part, im_part;
};

complexe sum(complexe a, complexe b){ //Question 1
    complexe c;
    c.re_part = a.re_part + b.re_part;
    c.im_part = a.im_part + b.im_part;
    return c;
}

void multiply(float r, complexe *ptr){
    ptr->re_part= r * (ptr->re_part);
    ptr->im_part = r * (ptr->im_part);
}

int main()
{
    complexe a;
    complexe b;
    a.re_part = 2.5;
    a.im_part = 4.6;
    b.re_part = 3.1;
    b.im_part = 2.4;
    //Question 1
    complexe c = sum(a,b);
    cout << "Re(a+b) = "<<c.re_part<<"\n";
    cout << "Im(a+b) = "<<c.im_part<<"\n";
    //Question 2
    complexe *ptr = &a;
    float k = 2;
    multiply(k, ptr);
    cout << "Re("<<k<<" * a) = "<<a.re_part<<"\n"; 
    cout <<"Im("<<k<<" * a) = "<<a.im_part;
}