#include <iostream>
#include <cmath>
#include "SimplifiedDes.h"

using namespace std;

char encrypt( unsigned short int key , char message ){
    unsigned short int subKey1, subKey2,aux,aux1,subKey[2],r1,r2;
    char auxMessage;
    Permutation *ip;
    ip = memoryAllocation(8);
    generateSubKeys( key , &subKey1 , &subKey2 );
    subKey[0] = subKey1;
    subKey[1] = subKey2;
    generateIP(ip);
    aux = makePermutation(message,ip,8);
    r1 = round(aux,subKey[0]);
    r1= ((r1 << 4)&240) | ((r1>>4)&15);
    r2 = round(r1,subKey[1]);
    generateIPInverse(ip);
    r2 =makePermutation(r2,ip,8);
    printf("\nCaracter: %d",r2 );

    return r2;
}

char decrypt( unsigned short int key , char message ){
    unsigned short int subKey1, subKey2,aux,aux1,subKey[2],r1,r2;
    char auxMessage;
    Permutation *ip;
    ip = memoryAllocation(8);
    generateSubKeys( key , &subKey1 , &subKey2 );
    subKey[0] = subKey1;
    subKey[1] = subKey2;
    generateIP(ip);
    aux = makePermutation(message,ip,8);
    r1 = round(aux,subKey[1]);
    r1= ((r1 << 4)&240) | ((r1>>4)&15);
    r2 = round(r1,subKey[0]);
    generateIPInverse(ip);
    r2 =makePermutation(r2,ip,8);
    printf("\nCaracter: %d",r2 );

    return r2;
}

void generateSubKeys( unsigned short int key, unsigned short int * subKey1 , unsigned short int * subKey2){
    Permutation * p10;
    p10 = memoryAllocation(10);
    generateP10( p10 );
    displayTable(p10,10);
    *subKey1 = generateKey1( key , p10 );
    *subKey2 = generateKey2( key , p10 );
}

unsigned short int round( unsigned short int message , unsigned short int subkey ){
    unsigned short int left, right,ep,s,ep2,final;
    Permutation *EP;
    EP = memoryAllocation(4);
    left = ( message >> 4 ) & 15;
    right = message  & 15;
    generateEP(EP);
    ep = makePermutation(right,EP,4);
    generateEP2(EP);
    ep2 = makePermutation(right,EP,4);
    ep = ep << 4 | ep2 ;
    ep = ep ^ subkey;
    s = generateS( ep );
    generateP4( EP );
    s = makePermutation(s,EP,4);
    left = left ^ s;
    final=(( left << 4 ) | right);

    return final;
}

void generateP10( Permutation *p10 ){
    int setValues[]={6,8,9,1,10,4,7,2,5,3};
    for (int i = 0; i < 10 ; i++){
        p10[i].origin = i;
        p10[i].target = setValues[i];
    }
}

void generateP8( Permutation *p8 ){
    int setValues[]={9,10,5,8,4,7,3,6,2,1};
    for (int i = 0; i < 10 ; i++){
        p8[i].origin = i;
        p8[i].target = setValues[i];
    }
}

void generateP4( Permutation *p4 ){
    int setValues[]={1,3,4,2};
    for (int i = 0; i < 4 ; i++){
        p4[i].origin = i;
        p4[i].target = setValues[i];
    }
}

void generateIP( Permutation *ip ){
    int setValues[]={7,5,8,4,1,3,6,2};
    for (int i = 0; i < 8 ; i++){
        ip[i].origin = i;
        ip[i].target = setValues[i];
    }
}

void generateIPInverse( Permutation *ip ){
    int setValues[]={6,8,2,7,5,3,1,4};
    for (int i = 0; i < 8 ; i++){
        ip[i].origin = i;
        ip[i].target = setValues[i];
    }
}

void generateEP( Permutation *ep ){
    int setValues[]={3,2,1,4};
    for (int i = 0; i < 4 ; i++){
        ep[i].origin = i;
        ep[i].target = setValues[i];
    }
}

void generateEP2( Permutation *ep ){
    int setValues[]={1,4,3,2};
    for (int i = 0; i < 4 ; i++){
        ep[i].origin = i;
        ep[i].target = setValues[i];
    }
}

unsigned short int generateS( unsigned short int ep ){
    unsigned short int left,right,auxS0,auxS1,auxS,r,c;
    unsigned short int s0[4][4] = { {1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2} };
    unsigned short int s1[4][4] = { {0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3} };
    left = ( ep >> 4);

    if(left&8){
        r=2;
        if(left&1){
            r=r|1;
        }
    }else if(left&1){
        r=1;
    }else{
        r=0;
    }
    //Columna
    if(left&4){
        c=2;
        if(left&2){
            c=c^1;
        }
    }else if(left&2){
        c=1;
    }else{
        c=0;
    }
    auxS0 = s0[r][c];
    r=0;
    c=0;
    right = (ep &15);

    if(right&8){
        r=2;
        if(right&1){
            r=r^1;
        }
    }else if(right&1){
        r=1;
    }else{
        r=0;
    }
    //Columna
    if(right&4){
        c=2;
        if(right&2){
            c=c^1;
        }
    }else if(right&2){
        c=1;
    }else{
        c=0;
    }

    auxS1 = s1[r][c];
    auxS = (auxS0 << 2) | auxS1 ;

    return auxS;
}

unsigned short int generateKey1( unsigned short int key , Permutation * p10 ){
    unsigned short int subkey;
    unsigned short int  left,right;
    Permutation * p8;
    p8 = memoryAllocation(10);
    generateP8(p8);
    subkey = makePermutation( key, p10 , 10 );
    left =   subkey >> 5 ;
    right = ( (subkey << 11 ) >> 11 ) & 0x1F;
    left = (left << 1 | left >> 4) & 31;
    right = (right << 1 | right >> 4)&31;
    subkey = left << 5 | right ;
    subkey = makePermutation( subkey ,p8,10);
    free(p8);

    return subkey & 0xFF;
}

unsigned short int generateKey2( unsigned short int key , Permutation * p10 ){
    unsigned short int subkey;
    unsigned short int  left,right;
    Permutation * p8;
    p8 = memoryAllocation(10);
    generateP8(p8);
    subkey = makePermutation( key, p10 , 10 );
    left =   subkey >> 5 ; 
    right = ( (subkey << 11 ) >> 11 ) & 0x1F;
    left = (left << 3 | left >> 2) & 31;
    right = (right << 3 | right >> 2) & 31; 
    subkey = left << 5 | right ;
    subkey = makePermutation( subkey , p8 , 10);
    free(p8);

    return subkey & 0xFF;
}

unsigned short int makePermutation( unsigned short int key , Permutation * p , short int len){
    unsigned short int auxMessage[len],aux[len];
    short int index;
    unsigned short int permutation = 0;

    for (int i = 0; i< len; i++)
        auxMessage[i] = ( key & (int)pow(2,i) );

    for (int i=0; i < len; i++){
        index = p[i].target;
        aux[i] = auxMessage[(len-1)-(index-1)];
    }

    for (int i = 0; i<len; i++)
        if(aux[i] != 0)
            permutation += (int)pow(2,i);

    return permutation;
}

unsigned char makeExpantion( unsigned short int right , Permutation *ep , short int len ){
    unsigned int auxMessage[len/4],aux[len];
    short int index;
    unsigned short int message=0;

    for (int i = 0; i < len/2; i++)
        auxMessage[i] = right & (int)pow(2,i);   
    for (int i = 0; i < len; i++){
        index = ep[i].target;
        aux[i] = auxMessage[(len-1)-(index-1)];
    }
    for (int i = 0; i < len; i++){
        if(aux[i] != 0)
            message += pow(2,i);
    }

    return message;
} 

Permutation * memoryAllocation( int len ) {
	Permutation *memory;
	memory = (Permutation *)malloc(len*sizeof(Permutation)  );
	if( memory == NULL )	{
		perror("Error, Can't reserve memory");
		exit(EXIT_FAILURE);
	}

	return memory;
}

void displayTable( Permutation * t, int len){
    for(int i = 0; i < len ; i++)
        cout << "\t " << t[i].origin << " | ";
    cout << endl;
    for(int i = 0; i < len ; i++)
        cout << "\t " << t[i].target << " | ";
    cout << endl;
}