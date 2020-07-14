#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"Vigenere.h"
using namespace std;

int* generateKey(string alphabet,string message){
    char option;
    short int position;
    int *auxKeyVigenere;
    cout << "You want to choose the key (Y/n): ";
    cin >> option;
    if ( option == 'n' || option == 'N'){
        srand(time(NULL));
        lenKey = (rand()+5) % 15;
        for (int i = 0; i < lenKey; i++){
            position = (rand()+1) % alphabet.length() ;
            keyVigenere += alphabet[position];
        }
    }
    else{
        cout << "Enter your key: " << endl;
        cin >> keyVigenere;
        lenKey = keyVigenere.length();
    }
    cout <<"Key: "<< keyVigenere << endl;
    setLength(message,alphabet,keyVigenere);
    auxKeyVigenere = matchCharToIndex(keyVigenere,alphabet);
    return auxKeyVigenere;
}

int * encryptVigenere(int *messageVig, int *key){
    int j=0;
    int *encryptMessage = memoryAllocation(lenMessage);
    
    for (int i=0; i< lenMessage ; i++){
        encryptMessage[i] = ( messageVig[i]+key[j] ) % lenAlphabet;
        j++;
        j = (j == lenKey) ? 0 : j;
    }
    return encryptMessage;
}

int * decryptVigenere(int * message, int * key){
    int j=0;
    int * originalMessage = memoryAllocation(lenMessage);
    for (int i=0; i< lenMessage ; i++){
        originalMessage[i] = (message[i]-key[j] < 0) ? lenAlphabet-(key[j]-message[i])%lenAlphabet : (message[i]-key[j]) % lenAlphabet;
        j++;
        j = (j == lenKey) ? 0 : j;
    }
    return originalMessage;
}

int * matchCharToIndex(string s,string alphabet){
    int *auxS = memoryAllocation( s.length() );
    for(int i = 0; i < s.length() ; i++)
        auxS[i]=  alphabet.find(s[i]);
    return auxS;
}

string matchIndexToChar(int *encryptMessage, string alphabet){
    string auxEncryptMessages;
    int position;
    for ( int i = 0; i < lenMessage ; i++ ){
        position = encryptMessage[i];
        auxEncryptMessages += alphabet[position];
    }
    return auxEncryptMessages;
}

void setLength(string message,string alphabet,string key){
    lenAlphabet = alphabet.length();
    lenKey = key.length();
    lenMessage = message.length();
}

int * memoryAllocation( int len ) {
	int *memory;
	memory = (int *)malloc(len*sizeof(int)  );
	if( memory == NULL )	{
		perror("Error, Can't reserve memory");
		exit(EXIT_FAILURE);
	}
	return memory;
}