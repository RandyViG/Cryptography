#include<iostream>
#include<stdlib.h>
#include<time.h>
#include"Affine.h"

using namespace std;

int validateKey(int *key){
    int greatestCommon;
    greatestCommon = gcd(key[0],key[2]);
    if ( greatestCommon == 1 && 0< key[1] < key[2] )
        return 1;
    else
        return 0;
}

int gcd(int a, int n){
    if ( n == 0)
        return a;
    else
        return gcd( n, a%n );   
}

int modInverse(int a, int m){
    int x, y;
    int g = euclideanAlgorithm(a, m, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist" << endl;
    else {
        int res = (x%m + m) % m;
        cout << "Modular multiplicative inverse is " << res << endl;
        return res;
    }
    return -1;
}

int euclideanAlgorithm(int a, int b, int *x, int *y){
    if (a == 0){
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = euclideanAlgorithm(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

int* generateKeyAffine(string alphabet,string message){
    char option;
    int *key,valid;

    key = memoryAllocationAffine(3);

    lenAlphabetAffine = alphabet.length();
    lenMessageAffine = message.length();

    key[2] = lenAlphabetAffine;

    cout << "You want to choose the key (Y/n): ";
    cin >> option;
    if ( option == 'n' || option == 'N'){
        srand(time(NULL));
        do{
            key[0] = (rand()+1) % alphabet.length();
            key[1] = (rand()+1) % lenAlphabetAffine;
            valid = validateKey(key);
        }while(valid != 1);   
    }
    else{
        do{
            cout << "Enter your key: (a+b): " << endl;
            cout << "a: ";
            cin >> key[0];
            cout << "b: ";
            cin >> key[1];
            valid = validateKey(key);
        }while(valid != 1);
    }
    return key;
}

int * encryptAffine(int *message, int *key){
    int *encryptMessage = memoryAllocationAffine(lenMessageAffine);
    for (int i=0; i< lenMessageAffine ; i++)
        encryptMessage[i] = ( (key[0]*message[i]) + key[1] ) % lenAlphabetAffine;
    return encryptMessage;
}

int * decryptAffine(string msm ,int * message, int * key,string alphabet){
    int * originalMessage = memoryAllocationAffine(msm.length());
    int inv = modInverse(key[0],alphabet.length());
    cout << "Inverso de a :  " << inv << endl;
    int modb = alphabet.size() - ( key[1] %alphabet.size() );
    for (int i=0; i< msm.size() ; i++){
        //modb = (inv * (message[i] - key[1])) % alphabet.length();
        //originalMessage[i] = ( modb < 0) ? modInverse(modb,alphabet.length()) : modb;
        originalMessage[i] = inv * (message[i]+modb)%alphabet.size();
        //originalMessage[i] = key[0]*(message[i]+key[1])%alphabet.size();
    }

    for (int i=0; i< msm.size();i++)
        cout << "Original: " << originalMessage[i] << " ";
    return originalMessage;
}

int * matchCharToIndexAffine(string s,string alphabet){
    int *auxS = memoryAllocationAffine( s.length() );
    for(int i = 0; i < s.length() ; i++)
        auxS[i]=  alphabet.find(s[i]);
    return auxS;
}

string matchIndexToCharAffine(int *encryptMessage, string alphabet,int len){
    string auxEncryptMessages;
    cout << "Entrando: ";
    int position;
    for (int i =0; i < len ; i++)
        cout << encryptMessage[i] << " ";

    for ( int i = 0; i < len ; i++ ){
        position = encryptMessage[i];
        auxEncryptMessages += alphabet[position];
    }
    return auxEncryptMessages;
}

int * memoryAllocationAffine( int len ) {
	int *memory;
	memory = (int *)malloc(len*sizeof(int)  );
	if( memory == NULL ){
		perror("Error, Can't reserve memory");
		exit(EXIT_FAILURE);
	}
	return memory;
}
