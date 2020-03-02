#include <iostream>
#include "SimplifiedDes.h"

using namespace std;

void menu(void);

int main( void ){
    unsigned short int key;
    char message, messageCipher,next;
    short int option;
    
    do{
        system("clear");
        key = 0;
        message = 0;
        messageCipher = 0;
        menu();
        cin >> option;

        switch( option ){
            case 1:

                cout << "\n\t Enter the key to length 10 bits: ";
                cin >> key;
                cout << "\n\t Enter the letter: ";
                cin >> message;
                messageCipher = encrypt(key,message);
                cout << "\n\t The cipher letter is: " << messageCipher << endl;
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;
                break;
            case 2:
            
                cout << "\n\t Enter the key to length 10 bits: ";
                cin >> key;
                cout << "\n\t Enter the letter: ";
                cin >> message;
                messageCipher = decrypt(key,message);
                cout << "\n\t The decrypt letter is: " << messageCipher << endl;
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
    cout << "\t\t1. Encript using DES" << endl;
    cout << "\t\t2. Decript using DES" << endl;
    cout << "\t\t3. Exit" << endl;
    cout << "\t\tChoose the option: ";
}