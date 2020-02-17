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
    int option,len, *row1,*row2;
    char next,key;
    string nameFile,message,encryptMessage,decryptMessage;
    table *permutation;
    do{
        len=0;
        message="";
        encryptMessage="";
        decryptMessage="";
        nameFile = "";
        row1 = NULL;
        row2 = NULL;
        tam=0;
        system("clear");
        menu();
        cin >> option;
        switch (option)
        {
        case 1:
                cout << "\tEnter the the permutation table " << endl;
                cout << "\tEnter the length of the permutation: ";
                cin >> len;
                row1 = (int *)malloc(len*sizeof(int) );
                row2 = (int *)malloc(len*sizeof(int) );
                permutation = memoryAllocation(len);
                inputData(permutation,row1,row2,len);
                inversePermutation(permutation,len,row2);
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;
            break;
        case 2:
                cout << "\tEnter the length of the permutation: ";
                cin >> len;
                permutation = memoryAllocation(len);
                permutation = generatePermutation(len);
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;
            break;
        case 3:
                cout << "\tEnter the name of the file where is the message:" << endl;
                cin >> nameFile;
                message = readFile(nameFile);
                message = cleanString(message);
                cout << "\tDo you want to choose the permutation (S/n)?: " << endl;
                cin >> key;
                if (key == 'S' || key=='s'){
                    cout << "\tEnter the name of the file where is the table:" << endl;
                    cin >> nameFile;
                    row2 = readNumbers(nameFile);
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
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;
            break;
        case 4:
                cout << "\tEnter the name of the file where is the message:" << endl;
                cin >> nameFile;
                message = readFile(nameFile);
                message = cleanString(message);
                cout << "\tEnter the name of the file where is the table:" << endl;
                cin >> nameFile;
                row2 = readNumbers(nameFile);
                permutation = memoryAllocation(tam);
                for (int i=0; i < tam; i++){
                    permutation[i].origin = i+1;
                    permutation[i].target = row2[i];
                }
                displayTable(permutation,tam);
                decryptMessage =  decrypt(permutation,message,tam);
                writeF(decryptMessage,"decrypt.txt");
                cout << "\tEnter a key for continue ..." << endl;
                cin >> next;
            break;
        case 5:  
                option = 5;
            break;
        default:
            break;
        }
    system("clear");
    }while(option!=5);
    return 0;
}

void menu( void ){
        cout << "\t********************** Permutation *********************" << endl;
        cout << "\t\t1. Enter a permutation table" << endl;
        cout << "\t\t2. Generate a permutation table" << endl;
        cout << "\t\t3. Encript using permutation" << endl;
        cout << "\t\t4. Decript using permutation" << endl;
        cout << "\t\t5. Exit" << endl;
        cout << "\t\tChoose the option: ";
}

void saveTable(table *t, int * row1, int * row2, int len){
    for (int i = 0; i < len ; i++)
        t[i].origin = row1[i]; 

    for (int i = 0; i < len ; i++)
        t[i].target = row2[i];
}

void inputData(table *t, int * row1, int * row2, int len){
    system("clear");
    for (int i=0; i< len; i++){
        cout << "\tEnter the element " << i+1 << " of the first row " << endl;
        cin >> row1[i];
    }
    system("clear");
    for (int i=0; i< len; i++){
    cout << "\tEnter the element " << i+1 << " of the second row " << endl;
    cin >> row2[i];
    }
    saveTable(t,row1,row2,len);
}

string readFile( string nameFile ){
    ifstream file( nameFile.c_str() );
    string line;
    string message;
    if(file.fail())
        cerr << "\tError, Can't open the file" << nameFile << endl;
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

int * readNumbers(string nameFile){
    ifstream file;
    vector<string> numbers;
    string line;

    int * row;

    file.open(nameFile);    
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