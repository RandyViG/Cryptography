#ifndef __DES_H__
#define __DED_H__

typedef union{
    struct{
        unsigned char p1: 1;
        unsigned char p2: 1;
        unsigned char p3: 1;
        unsigned char p4: 1;
        unsigned char p5: 1;
        unsigned char p6: 1;
        unsigned char p7: 1;
        unsigned char p8: 1;
    };
    unsigned char word;
} Permutation8;

typedef union{
    struct{
        unsigned short int p1: 1;
        unsigned short int p2: 1;
        unsigned short int p3: 1;
        unsigned short int p4: 1;
        unsigned short int p5: 1;
        unsigned short int p6: 1;
        unsigned short int p7: 1;
        unsigned short int p8: 1;
        unsigned short int p9: 1;
        unsigned short int p10: 1;
        unsigned short int pF: 6;
    };
    unsigned short int word;
} Permutation10;

char encrypt( char text , unsigned short int key );
char decrypt();
void generateSubkeys( unsigned short int key, unsigned char* subkey1, unsigned char* subkey2 );
short int p10( unsigned short int key ); 
unsigned char subKey1( unsigned short int left, unsigned short int rigth );
unsigned char subKey2( unsigned short int left, unsigned short int rigth );
short int p8( unsigned short int key );

#endif