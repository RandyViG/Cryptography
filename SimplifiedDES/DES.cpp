#include <iostream>
#include "DES.h"

using namespace std;

char encrypt( char text , unsigned short int key ){
    short int subkey1, subkey2;
    generateSubkeys( key , &subkey1, &subkey2 );
    
}

void generateSubkeys( short int key, short int* subkey1, short int* subkey2 ){
    char left, right;
    short int k;
    k = p10( key );
    //Split the key
    left = (k >> 5) & 31;
    right = k & 31;
    //Circular Shift Left
    left = ( left << 1 | left >> 4 ) & 31;
    right = ( left << 1 | left >> 4 ) & 31;
    *subkey1 = subKey1( left , right );
    *subkey2 = subKey2( left , right );
}

short int p10( short int key ){
    Permutation10 auxKey, aux;
    aux.word = key;
    auxKey.p1 = aux.p3;
    auxKey.p2 = aux.p5; 
    auxKey.p3 = aux.p2; 
    auxKey.p4 = aux.p7;
    auxKey.p5 = aux.p4;
    auxKey.p6 = aux.p10;
    auxKey.p7 = aux.p1;
    auxKey.p8 = aux.p9;
    auxKey.p9 = aux.p8;
    auxKey.p10 = aux.p6;
    auxKey.pF = 0;
    cout << "key: " << auxKey.word << endl;

    return auxKey.word;
}

short int subKey1( short int left, short int rigth ){
    short int aux;
    char subKey;
    aux = left << 5 | rigth;
    subKey = p8( aux );

    return subKey;
}

short int subKey2( short int left, short int rigth ){
    short int aux;
    char subKey;
    //Circular Shift Left
    left =  ( left << 2 | left >> 3 ) & 31;
    rigth = ( rigth << 2 | rigth >> 3 ) & 31;
    aux = left << 5 | rigth;
    subKey = p8( aux );

    return subKey;
}

short int p8( short int key ){
    Permutation8 aux;
    Permutation10 auxKey;
    auxKey.word = key;
    aux.p1 = auxKey.p6;
    aux.p2 = auxKey.p3;
    aux.p3 = auxKey.p7;
    aux.p4 = auxKey.p4;
    aux.p5 = auxKey.p8;
    aux.p6 = auxKey.p5;
    aux.p7 = auxKey.p10;
    aux.p8 = auxKey.p9;

    return aux.word;
}