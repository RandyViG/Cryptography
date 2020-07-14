#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string fileName,cadenaF,cadenaR,alfabeto,a,b;
    cout << "Enter the name of file \n\tName: ";
    cin >> fileName;
    a="abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ifstream fe(fileName);

    while (!fe.eof()) {
        getline(fe,cadenaR);
        cadenaF=cadenaF+cadenaR;
    }
    fe.close();
    
    for (int i=0;i<a.length();i++){
        if(cadenaR.find(a[i])==-1){
            cout << "La letra " << a[i] <<" no esta en el alfabeto"<<endl;
        }else{
            cout << "La letra " << a[i] <<" esta en el alfabeto"<<endl;
            alfabeto+=a[i];
        }

    }
    cout << alfabeto << endl;
    
}
