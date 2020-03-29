
def calculateTable( n ):
    title = [ 0 ]
    table = [ ]
    polynomialsI = [ 11 , 19 , 37 , 67 , 131 , 283 ]
    module = polynomialsI[ n - 3 ]
    valuesArchived = [ ]
    for t in range( 1 , 2**n):
        title.append(t)
    table.append(title)
    for i in range( 1, 2**n ): 
        valuesArchived.append( calculateValues( i , n , module ) )
    for j in range( 1 , ( 2**n ) ):
        table.append( calculateRow( j,  valuesArchived , n ) )
    return table

def calculateValues( i , n , module ):
    values = [ ]
    prev = i
    values.append( prev )
    for j in range( 2 , n+1 ):
        aux = prev << 1
        if ( prev & (2**(n-1)) ):
            aux = ( aux ^ module ) & (2**n-1)
        prev = aux
        values.append( aux )
    return values


def calculateRow( val , rowValues , n ):
    row = [ val ]
    for i in range(1,2**n):
        decompose = [ ]
        for j in range(n):
            aux = rowValues[ val-1 ]
            if( i & 2**j ):
                decompose.append( aux[j] )
        xor = 0
        for a in range( len(decompose) ):
            xor = xor ^ decompose[a]
        row.append(xor)
    return row
