#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "DES.h"

using namespace std;

void menu(void);
string readFile( string nameFile );
void writeFile( string encryptMessage , string fileName );

int main( void ){
    short int k;
    char a;
    //cin >> k;
    //cout << "K: " << k << endl;
    a = encrypt( 'a' , 642 );
    //cout << "key: " << a << endl;
    return 0;
}

void menu( void ){
    cout << "\t********************** Simplified DES *********************" << endl;
    cout << "\t\t1. Encrypt using DES" << endl;
    cout << "\t\t2. Decrypt using DES" << endl;
    cout << "\t\t3. Exit" << endl;
    cout << "\t\tChoose the option: ";
}

string readFile( string nameFile ){
    ifstream file( nameFile.c_str() );
    string line;
    string message;
    if( file.fail() )
        cerr << "\tError, Can't open the file" << nameFile << endl;
    else
        while( !file.eof() ){
            getline(file, line);
            message += line;
        }
    file.close();

    return message;
}

void writeFile( string message , string fileName){
    ofstream file;
    file.open( fileName );
    file << message;
    file.close();
}