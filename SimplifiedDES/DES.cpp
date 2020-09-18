#include <iostream>
#include "DES.h"

using namespace std;

char encrypt( char text , unsigned short int key ){
    unsigned char subkey1, subkey2;
    generateSubkeys( key , &subkey1, &subkey2 );
    
}

void generateSubkeys( unsigned short int key, unsigned char* subkey1, unsigned char* subkey2 ){
    unsigned short int left, right;
    unsigned short int k;
    k = p10( key );
    //Split the key
    left = (k >> 5) & 31;
    right = k & 31;
    //Circular Shift Left
    left = ( left << 1 | left >> 4 ) & 31;
    right = ( right << 1 | right >> 4 ) & 31;
    *subkey1 = subKey1( left , right );
    *subkey2 = subKey2( left , right );
}

short int p10( unsigned short int key ){
    /**
     *  _________________________________________
     * | 10 | 9 | 8 | 7 | 6 | 5 | 4  | 3 | 2 | 1 | Original
     * | 8  | 6 | 9 | 4 | 7 | 1 | 10 | 2 | 3 | 5 | Permutación
     * 
    */
    Permutation10 auxKey, aux;
    aux.word = key;
    auxKey.word = 0;
    auxKey.p1 = aux.p5;
    auxKey.p2 = aux.p3; 
    auxKey.p3 = aux.p2; 
    auxKey.p4 = aux.p10;
    auxKey.p5 = aux.p1;
    auxKey.p6 = aux.p7;
    auxKey.p7 = aux.p4;
    auxKey.p8 = aux.p9;
    auxKey.p9 = aux.p6;
    auxKey.p10 = aux.p8;

    return auxKey.word;
}

unsigned char subKey1( unsigned short int left, unsigned short int rigth ){
    unsigned short int aux;
    unsigned char subKey;
    aux = left << 5 | rigth;
    subKey = p8( aux );

    return subKey;
}

unsigned char subKey2( unsigned short int left, unsigned short int rigth ){
    short int aux;
    char subKey;
    //Circular Shift Left
    left =  ( left << 2 | left >> 3 ) & 31;
    rigth = ( rigth << 2 | rigth >> 3 ) & 31;
    aux = left << 5 | rigth;
    subKey = p8( aux );

    return subKey;
}

short int p8( unsigned short int key ){
    /**
     *  ________________________________________
     * | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | Original
     * | -  | - | 5 | 8 | 4 | 7 | 3 | 6 | 1 | 2 | Permutación de compresión
     * 
    */
    Permutation8 aux;
    Permutation10 auxKey;
    auxKey.word = key;
    aux.word = 0;
    aux.p1 = auxKey.p2;
    aux.p2 = auxKey.p1;
    aux.p3 = auxKey.p6;
    aux.p4 = auxKey.p3;
    aux.p5 = auxKey.p7;
    aux.p6 = auxKey.p4;
    aux.p7 = auxKey.p8;
    aux.p8 = auxKey.p5;

    return aux.word;
}