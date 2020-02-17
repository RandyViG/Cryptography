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
    string nameFile, message,alphabet, encryptVig,keyVigString,fileOut;
    short int option;
    int *key = NULL, *messageIndex = NULL, *encryptMessageVig = NULL, keyAffine[3],a,n,res;

    do{
        cout << "Clasical Cryptography" << endl;
        cout << "Choose one option: " << endl;
        cout << "1. Encrypt using Vigenere" << endl;
        cout << "2. Decrypt using Vigenere" << endl;
        cout << "3. Verify Key is valid for affine cipher " << endl;
        cout << "4. Calculate a^-1 mod N" << endl;
        cout << "5. Encrypt using Affine" << endl;
        cout << "6. Decrypt using Affine" << endl;
        cout << "8. Salir" << endl;
        cin >> option;

        switch ( option ) {
        case 1:

            fileOut = "encryptText.vig";
            cout << "Enter the name of the file where is the message:" << endl;
            cin >> nameFile;
            message = readFile(nameFile);
            cout << "Enter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            key = generateKey(alphabet,message);
            messageIndex = matchCharToIndex(message,alphabet);
            encryptMessageVig = encryptVigenere(messageIndex,key);
            encryptVig = matchIndexToChar(encryptMessageVig,alphabet);
            writeF(encryptVig,fileOut);
            break;

        case 2:

            fileOut = "decryptedText.txt";
            cout << "Enter the name of the file where is the message:" << endl;
            cin >> nameFile;
            encryptVig = readFile(nameFile);
            cout << "Enter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            cout << "Enter the key for decrypt the message:" << endl;
            cin >> keyVigString;
            setLength(encryptVig,alphabet,keyVigString);
            encryptMessageVig = matchCharToIndex(encryptVig,alphabet);
            key = matchCharToIndex(keyVigString,alphabet);
            messageIndex = decryptVigenere(encryptMessageVig,key);
            message = matchIndexToChar(messageIndex,alphabet);
            writeF(message,fileOut);
            break;
            
        case 3:

            cout << "key : (a + b)" << endl;
            cout << "Enter a: ";
            cin >> keyAffine[0];
            cout << "Enter b: ";
            cin >> keyAffine[1];
            cout << "Enter the Alphabet's lenght: ";
            cin >> keyAffine[3];
            if(validateKey(keyAffine))
                cout << "Valid key!" << endl;
            else
                cout << "Invalid key!" << endl;
            break;

        case 4: 
            cout << "a^-1 mod n " << endl;
            cout << "Enter a: ";
            cin >> a;
            cout << "a^-1 mod n " << endl;
            cout << "Enter n: ";
            cin >> n;
            res = modInverse(a,n);
            break;
        case 5:

            fileOut = "encryptText.aff";
            cout << "Enter the name of the file where is the message:" << endl;
            cin >> nameFile;
            message = readFile(nameFile);
            cout << message << endl;
            cout << "Enter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            key = generateKeyAffine(alphabet,message);
            messageIndex = matchCharToIndexAffine(message,alphabet);
            cout << "Indices ok" << endl;
            encryptMessageVig = encryptAffine(messageIndex,key);
            cout << "Encryptado " << endl;
            for (int i=0 ; i < message.length();i++)
                cout << encryptMessageVig[i] << " ";
            cout << endl;
            encryptVig = matchIndexToCharAffine(encryptMessageVig,alphabet);
            cout << "Recuperando" << endl;
            cout << encryptVig;
            writeF(encryptVig,fileOut);
            break;

        case 6:
            fileOut = "decryptedText.txt";
            cout << "Enter the name of the file where is the message:" << endl;
            cin >> nameFile;
            encryptVig = readFile(nameFile);
            cout << "Enter the name of the file where is the alphabet:" << endl ;
            cin >> nameFile;
            alphabet = readFile(nameFile);
            alphabet = cleanString(alphabet);
            cout << "Enter the key for decrypt the message: (a +b)" << endl;
            cout << "Enter a: ";
            cin >> keyAffine[0];
            cout << "Enter b: ";
            cin >> keyAffine[1];
            encryptMessageVig = matchCharToIndexAffine(encryptVig,alphabet);
            messageIndex = decryptAffine( encryptVig,encryptMessageVig,keyAffine,alphabet );
            for (int i=0 ; i < message.length();i++)
                cout << messageIndex[i] << " ";
            message = matchIndexToCharAffine(messageIndex,alphabet);
            cout << endl << "Todo ok: " << message << endl;
            writeF(message,fileOut);
            break;
        case 7:
            option = 7;
            break;
        default:
            cout << "Invalid option";
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
