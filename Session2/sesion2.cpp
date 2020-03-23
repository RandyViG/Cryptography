#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<ctime>
#include<sstream>
#include<vector>
#include<algorithm>
#include<iterator>
#include"Permutation.h"
#include"SimplifiedDes.h"

using namespace std;

void menu(void);
void saveTable(table *,int *,int *,int);
void inputData(table *,int *,int *,int);
string readFile(string);
string cleanString( string);
int * readNumbers(string);
void writeF(string,string);

int tam=0;

int main( void ){
    unsigned short int key,des;
    int option,len, *row1,*row2;
    char next,choose;
    string fileName,message,encryptMessage,decryptMessage,finalMessage;
    table *permutation;
    string base = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"}; 
    vector< unsigned short int > messageCipher;
    vector< unsigned short int > cipher;
    do{
        len=0;
        message="";
        encryptMessage="";
        decryptMessage="";
        fileName = "";
        row1 = NULL;
        row2 = NULL;
        tam=0;
        key = 0;
        des = 0;
        finalMessage = "";
        messageCipher.clear();
        cipher.clear();
        srand(time(NULL));
        system("clear");
        
        menu();
        cin >> option;
        switch (option)
        {
        case 1:
                cout << "\tEnter the the permutation table " << endl;
                cout << "\tEnter the length of the permutation: ";
                cin >> len;
                cout << endl;
                row1 = (int *)malloc(len*sizeof(int) );
                row2 = (int *)malloc(len*sizeof(int) );
                permutation = memoryAllocation(len);
                inputData(permutation,row1,row2,len);
                permutation = inversePermutation(permutation,len,row2);
                displayTable(permutation,len);
                cout << "\tEnter a key for continue ";
                cin >> next;
                cout << endl;
            break;
        case 2:
                cout << "\tEnter the length of the permutation: ";
                cin >> len;
                permutation = memoryAllocation(len);
                permutation = generatePermutation(len);
                cout << "\tEnter a key for continue ";
                cin >> next;
                cout << endl;
            break;
        case 3:
                cout << "\tEnter the name of the file where is the message: " ;
                cin >> fileName;
                cout << endl;
                message = readFile(fileName);
                message = cleanString(message);
                cout << "\tDo you want to choose the permutation (S/n)?: ";
                cin >> choose;
                cout << endl;
                if (choose == 'S' || choose =='s'){
                    cout << "\tEnter the name of the file where is the table: ";
                    cin >> fileName;
                    cout << endl;
                    row2 = readNumbers(fileName);
                    permutation = memoryAllocation(tam);
                    for (int i=0; i < tam; i++){
                        permutation[i].origin = i+1;
                        permutation[i].target = row2[i];
                    }
                    encryptMessage = encrypt(permutation,message,tam);
                }
                else{
                    len = message.size();
                    permutation = memoryAllocation(len);
                    permutation = generatePermutation(len);
                    encryptMessage = encrypt(permutation,message,len);
                }
                writeF(encryptMessage,"encrypt.txt");
                cout << "\t\nEncrypted message successfully in the file encrypt.txt";
                cout << "\t\nEnter a key for continue ";
                cin >> next;
                cout << endl;
            break;
        case 4:
                cout << "\tEnter the name of the file where is the message: ";
                cin >> fileName;
                cout << endl;
                message = readFile(fileName);
                message = cleanString(message);
                cout << "\tEnter the name of the file where is the table: ";
                cin >> fileName;
                cout << endl;
                row2 = readNumbers(fileName);
                permutation = memoryAllocation(tam);
                row1 = (int *)malloc( tam*sizeof(int) );
                saveTable(permutation,row1,row2,tam);
                permutation = inversePermutation(permutation,tam,row2);
                displayTable(permutation,tam);
                decryptMessage =  decrypt(permutation,message,tam);
                writeF(decryptMessage,"decrypt.txt");
                cout << "\t\nDecrypted message successfully in the file: decrypt.txt";
                cout << "\t\nEnter a key for continue ";
                cin >> next;
                cout << endl;
            break;
        case 5:
                cout << "\n\tEnter the name of the file where is the message: ";
                cin >> fileName;
                message = readFile( fileName );
                cout << "\n\tDo you want to choose the key (S/n)?: ";
                cin >> choose;
                if( choose == 'S' || choose == 's' ){
                    cout << "\n\tEnter the key to length 10 bits: ";
                    cin >> key; 
                }else{
                    key = 100 + rand() % 1024;
                    cout << "\t\nThe key generate is: " << key << endl;
                }

                for (int i = 0; i < message.length() ; i++){
                    des = encryptDes( key , i % 255 );
                    messageCipher.push_back( message[i] ^ des );
                }
                for (int i = 0; i < message.length() ; i++){
                    cipher.push_back( (messageCipher[i] >> 6) & 3 );
                    cipher.push_back( messageCipher[i] & 63 );
                }

                for (int i = 0; i < cipher.size() ; i++)
                    finalMessage += base[cipher[i]];

                writeF(finalMessage,"encrypt.des");
                cout << "\t\nEncrypted message successfully in the file: encrypt.des";
                cout << "\t\nEnter a key for continue ...";
                cin >> next;
            break;
        case 6:
                unsigned short int c1,c2;
                cout << "\n\t Enter the key to length 10 bits: ";
                cin >> key;
                cout << "\n\tEnter the name of the file where is the message: ";
                cin >> fileName;
                message = readFile( fileName );

                for (int i = 0; i < message.length() ; i+=2){
                    c1 = base.find( message[i] );
                    c2 = base.find( message[i+1] );
                    cipher.push_back( ( c1 << 6 ) | ( c2 & 63)  );
                }

                for (int i = 0; i < cipher.size() ; i++){
                    des = decryptDes( key , i % 255 );
                    messageCipher.push_back( cipher[i] ^ des );
                }
                
                for (int i = 0; i < messageCipher.size() ; i++)
                    finalMessage += char( messageCipher[i] );
                
                writeF(finalMessage,"decrypt.txt");
                cout << "\t\nDecrypted message successfully in the file: decrypt.txt";
                cout << "\t\nEnter a key for continue ...";
                cin >> next;
            break;
        case 7:  
                option = 7;
            break;
        default:
            break;
        }
    system("clear");
    }while(option!=7);
    return 0;
}

void menu( void ){
        cout << "\t*************************** Sesson 2 **************************" << endl;
        cout << "\t\t1. Inverse Permutation table" << endl;
        cout << "\t\t2. Generate a Permutation table" << endl;
        cout << "\t\t3. Encrypt using permutation" << endl;
        cout << "\t\t4. Decrypt using permutation" << endl;
        cout << "\t\t5. Encrypt using DES" << endl;
        cout << "\t\t6. Decrypt using DES" << endl;
        cout << "\t\t7. Exit" << endl;
        cout << "\t\tChoose the option: ";
}

void saveTable(table *t, int * row1, int * row2, int len){
        
    for(int i = 0; i < len ; i++)
        row1[i] = i+1;

    for (int i = 0; i < len ; i++)
        t[i].origin = row1[i]; 

    for (int i = 0; i < len ; i++)
        t[i].target = row2[i];
}

void inputData(table *t, int * row1, int * row2, int len){
    system("clear");
    for (int i=0; i < len; i++)
        row1[i] = i + 1; 
    for (int i=0; i< len; i++){
        cout << "\tEnter the element " << i+1 << " of the permutation: ";
        cin >> row2[i];
        cout << endl;
    }
    saveTable(t,row1,row2,len);
}

string readFile( string fileName ){
    ifstream file( fileName.c_str() );
    string line;
    string message;
    if(file.fail()){
        cerr << "\tError, Can't open the file: " << fileName << endl;
        exit(-1);
    }
    else
        while( !file.eof() ){
            getline(file, line);
            message += line;
        }
    file.close();

    return message;
}

string cleanString( string message ){
    string auxMessage;
    for (int i =0; i < message.size() ; i++)
        if ( message[i] != 32)
            auxMessage += message[i];

    return auxMessage;
}

int * readNumbers(string fileName){
    ifstream file;
    vector<string> numbers;
    string line;

    int * row;

    file.open(fileName);    
    while (!file.eof()){
        getline(file,line);
        istringstream iss(line);
        copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(numbers));
    }
    row = (int *)malloc(numbers.size()*sizeof(int) );
    for (int i=0; i<numbers.size(); i++ )
        row[i] = atoi( numbers[i].c_str() );
    tam = numbers.size();
    return row;
}

void writeF( string encryptMessage , string fileName){
    ofstream file;
    file.open( fileName );
    file << encryptMessage;
    file.close();
}