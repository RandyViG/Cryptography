#ifndef __DES_H__
#define __DED_H__

typedef union{
    struct{
        char p1: 1;
        char p2: 1;
        char p3: 1;
        char p4: 1;
        char p5: 1;
        char p6: 1;
        char p7: 1;
        char p8: 1;
    };
    char word;
} Permutation8;

typedef union{
    struct{
        short int p1: 1;
        short int p2: 1;
        short int p3: 1;
        short int p4: 1;
        short int p5: 1;
        short int p6: 1;
        short int p7: 1;
        short int p8: 1;
        short int p9: 1;
        short int p10: 1;
        short int pF: 6;
    };
    short int word;
} Permutation10;

char encrypt( char text , unsigned short int key );
char decrypt();
void generateSubkeys( short int key, short int* subkey1, short int* subkey2 );
short int p10( short int key ); 
short int subKey1( short int left, short int rigth );
short int subKey2( short int left, short int rigth );
short int p8( short int key );

#endif