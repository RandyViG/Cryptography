from GF import *
from AES import *

def  menu():
    print('\t\t************* Finete Fields *************')
    print('\t\t1. GF(2^n) Multuplication Table')
    print('\t\t2. Key schedule AES 128')
    print('\t\t3. Key schedule AES 192')
    print('\t\t4. Exit')
    option = int( input("\t\tChoose a option: " ) )
    return option

if __name__ == "__main__":
    while(True):
        option = menu()
        if option == 1:
            n = int( input("\t\tEnter the n for GF in a range of 3 to 8: ") )
            r = input("\t\tEnter the representation that you like (h)exa or (p)olynomial: ")
            if ( r == 'h' or r == 'p' ):
                table = calculateTable( n , r )
                fileName = 'GF_2^'+str(n)+'.txt'
                saveTable( fileName , table )
            else:
                print('\t\tInvalid Representation')
                continue
        elif option == 2:
            fileName = input('\t\tEnter the name of the file where is the key of 128: ')
            key = readFile( fileName )
            keys = keySchedule128( key )
            fileName = 'KeysAES128.txt'
            saveKeys( fileName ,  keys[1:] )
        elif option == 3:
            pass
        else:
            break
    