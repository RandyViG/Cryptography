#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "SimplifiedDes.h"

using namespace std;

void menu(void);
string readFile( string nameFile );
void writeF( string encryptMessage , string fileName );

int main( void ){
    unsigned short int key,des;
    short int option;
    char next,choose;
    string base = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"}; 
    vector< unsigned short int > messageCipher;
    vector< unsigned short int > cipher;
    string fileName,message,finalMessage;
    
    do{
        system("clear");
        key = 0;
        des = 0;
        message = "";
        finalMessage = "";
        messageCipher.clear();
        cipher.clear();
        srand(time(NULL));
        menu();
        cin >> option;

        switch( option ){
            case 1:

                cout << "\n\tEnter the name of the file where is the message: ";
                cin >> fileName;
                message = readFile( fileName );
                cout << "\n\t Do you want to choose the key (S/n)?: ";
                cin >> choose;
                if( choose == 'S' || choose == 's' ){
                    cout << "\n\t Enter the key to length 10 bits: ";
                    cin >> key; 
                }else{
                    key = 100 + rand() % 1024;
                    cout << "\t\n The key generate is: " << key << endl;
                }

                for (int i = 0; i < message.length() ; i++){
                    des = encrypt( key , i % 255 );
                    messageCipher.push_back( message[i] ^ des );
                }
                for (int i = 0; i < message.length() ; i++){
                    cipher.push_back( (messageCipher[i] >> 6) & 3 );
                    cipher.push_back( messageCipher[i] & 63 );
                }

                for (int i = 0; i < cipher.size() ; i++)
                    finalMessage += base[cipher[i]];

                writeF(finalMessage,"encrypt.des");
                cout << "\t\nEncrypted message successfully" << endl;
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;

                break;

            case 2:

                unsigned short int c1,c2;
                cout << "\n\t Enter the key to length 10 bits: ";
                cin >> key;
                cout << "\n\tEnter the name of the file where is the message: ";
                cin >> fileName;
                message = readFile( fileName );

                for (int i = 0; i < message.length() ; i+=2){
                    c1 = base.find( message[i] );
                    c2 = base.find( message[i+1] );
                    cipher.push_back( ( c1 << 6 ) | ( c2 & 63)  );
                }

                for (int i = 0; i < cipher.size() ; i++){
                    des = decrypt( key , i % 255 );
                    messageCipher.push_back( cipher[i] ^ des );
                }
                
                for (int i = 0; i < messageCipher.size() ; i++)
                    finalMessage += char( messageCipher[i] );
                
                writeF(finalMessage,"decrypt.txt");
                cout << "\t\nDecrypted message successfully" << endl;
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;

                break;
            case 3:
                option = 3;
                break;
            default:
                break;
        }

    }while( option != 3 );
    


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
    if(file.fail())
        cerr << "\tError, Can't open the file" << nameFile << endl;
    else
        while( !file.eof() ){
            getline(file, line);
            message += line;
        }
    file.close();

    return message;
}

void writeF( string encryptMessage , string fileName){
    ofstream file;
    file.open( fileName );
    file << encryptMessage;
    file.close();
}