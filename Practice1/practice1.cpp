#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include"Vigenere.h"
#include"Affine.h"

using namespace std;

string readFile(string);
string cleanString(string);
void writeF(string,string);

int main(){
    string nameFile, message,alphabet, encryptString,keyVigString,fileOut;
    short int option;
    char next;
    int *key = NULL, *messageIndex = NULL, *encryptMessage = NULL, keyAffine[3],a,n,res;

    do{
        nameFile="";
        message="";
        alphabet="";
        encryptString="";
        keyVigenere="";
        messageIndex=NULL;
        encryptMessage=NULL;
        system("clear");
        cout << "\t************************ Clasical Cryptography ************************" << endl;
        cout << "\t\t 1. Encrypt using Vigenere" << endl;
        cout << "\t\t 2. Decrypt using Vigenere" << endl;
        cout << "\t\t 3. Verify Key is valid for affine cipher " << endl;
        cout << "\t\t 4. Calculate a^-1 mod N" << endl;
        cout << "\t\t 5. Encrypt using Affine" << endl;
        cout << "\t\t 6. Decrypt using Affine" << endl;
        cout << "\t\t 7. Exit" << endl; 
        cout << "\t\t Choose one option: ";
        cin >> option;
        system("clear");
        switch ( option ) {
        case 1:

            fileOut = "encryptText.vig";
            cout << "\tEnter the name of the file where is the message:" << endl;
            cin >> nameFile;
            message = readFile(nameFile);
            cout << "\tEnter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            key = generateKey(alphabet,message);
            messageIndex = matchCharToIndex(message,alphabet);
            encryptMessage = encryptVigenere(messageIndex,key);
            encryptString = matchIndexToChar(encryptMessage,alphabet);
            writeF(encryptString,fileOut);
            cout << "\tPress a key to continue... " << endl;
            cin >> next;
            break;

        case 2:

            fileOut = "decryptedText.txt";
            cout << "\tEnter the name of the file where is the message:" << endl;
            cin >> nameFile;
            encryptString = readFile(nameFile);
            cout << "\tEnter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            cout << "\tEnter the key for decrypt the message:" << endl;
            cin >> keyVigString;
            setLength(encryptString,alphabet,keyVigString);
            encryptMessage = matchCharToIndex(encryptString,alphabet);
            key = matchCharToIndex(keyVigString,alphabet);
            messageIndex = decryptVigenere(encryptMessage,key);
            message = matchIndexToChar(messageIndex,alphabet);
            writeF(message,fileOut);
            cout << "\tPress a key to continue... " << endl;
            cin >> next;
            break;
            
        case 3:

            cout << "\tkey : (a + b)" << endl;
            cout << "\tEnter a: ";
            cin >> keyAffine[0];
            cout << "\tEnter b: ";
            cin >> keyAffine[1];
            cout << "\tEnter the Alphabet's lenght: ";
            cin >> keyAffine[2];
            if(validateKey(keyAffine)==1)
                cout << "\tValid key!" << endl;
            else
                cout << "\tInvalid key!" << endl;
            cout << "Press a key to continue... " << endl;
            cin >> next;
            break;

        case 4: 

            cout << "\ta^-1 mod n " << endl;
            cout << "\tEnter a: ";
            cin >> a;
            cout << "\ta^-1 mod n " << endl;
            cout << "\tEnter n: ";
            cin >> n;
            res = modInverse(a,n);
            cout << "\tPress a key to continue... " << endl;
            cin >> next;
            break;
        case 5:

            fileOut = "encryptText.aff";
            cout << "\tEnter the name of the file where is the message:" << endl;
            cin >> nameFile;
            message = readFile(nameFile);
            cout << message << endl;
            cout << "\tEnter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            key = generateKeyAffine(alphabet,message);
            messageIndex = matchCharToIndexAffine(message,alphabet);
            encryptMessage = encryptAffine(messageIndex,key);
            encryptString = matchIndexToCharAffine(encryptMessage,alphabet,message.size());
            writeF(encryptString,fileOut);
            cout << "\tPress a key to continue... " << endl;
            cin >> next;
            break;

        case 6:
            fileOut = "decryptedText.txt";
            cout << "\tEnter the name of the file where is the message:" << endl;
            cin >> nameFile;
            encryptString = readFile(nameFile);
            cout << "\tEnter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            cout << "\tEnter the key for decrypt the message: (a+b)" << endl;
            cout << "\tEnter a: ";
            cin >> keyAffine[0];
            cout << "\tEnter b: ";
            cin >> keyAffine[1];
            encryptMessage = matchCharToIndexAffine(encryptString,alphabet);
            messageIndex = decryptAffine( encryptString,encryptMessage,keyAffine,alphabet );
            message = matchIndexToCharAffine(messageIndex,alphabet,encryptString.size());
            writeF(message,fileOut);
            cout << "Press a key to continue... " << endl;
            cin >> next;
            break;

        case 7:
            option = 7;
            break;
        default:
            cout << "\tInvalid option";
            break;
        }
    }while (option != 7);
    return 0;
}

string readFile( string nameFile ){
    ifstream file( nameFile.c_str() );
    string line;
    string message;
    if(file.fail())
        cerr << "Error, Can't open the file" << nameFile << endl;
    else
        while( !file.eof() ){
            getline(file, line);
            message += line;
        }
    file.close();

    return message;
}

string cleanString( string alphabet ){
    string auxAlphabet;
    for (int i =0; i < alphabet.size() ; i++)
        if ( alphabet[i] != 32)
            auxAlphabet += alphabet[i];

    return auxAlphabet;
}

void writeF( string encryptVig , string fileName){
    ofstream file;
    file.open( fileName );
    file << encryptVig;
    file.close();
}
