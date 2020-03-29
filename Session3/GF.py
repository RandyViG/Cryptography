
def calculateTable( n ):
    #polynomialsI = [ [3,1,0],[4,1,0],[5,2,0],[6,1,0],[7,1,0],[8,4,3,1,0] ]
    polynomialsI = [ 10, 18 , 36 , 66 , 130 , 282 ]
    module = polynomialsI[ n - 3 ]
    for i in range( n ): 
        valuesArchived = calculateValues( 2**i , n , module )
        print(  valuesArchived )
        #for j in range( 1 , ( 2 ** n ) ):
    
    return


def calculateValues( i , n , module ):
    values = [ ]
    print("Madulo: {}".format(module) )
    prev = i
    values.append( prev )
    for j in range( 2 , n+1 ):
        aux = prev << 1
        if ( prev & (2**(n-1)) ):
            aux = ( aux ^ module ) & (2**n-1)
        prev = aux
        values.append( aux )
    return values
