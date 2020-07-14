#include <iostream>

using namespace std;

int gcdR(int a,int b){
    if (b == 0)   
        return a;
    else    
        return gcdR(b,a%b); 
}

int main(){
    int gcd;
    for(int i=0;i<45;i++){
        gcd=gcdR(i,45);
        if(gcd==1){
            cout << i << " es posible llave a" << endl;
            
        }
    }
}