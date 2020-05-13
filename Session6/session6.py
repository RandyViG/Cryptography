from Crypto.Util.number import isPrime, getRandomInteger, GCD,inverse

#Product N
numbers = [ 5963 , 899 , 2701 , 23264323 , 6283 ]
#Public keys
e = [ 1987 , 57697 , 3401 , 34567 , 59 ]

print('\t*********** BREAKING RSA ***********')

for k,n in enumerate(numbers):
    p = 0
    q = 0
    i = 2
    while i ** 2 < n:
        if isPrime( i ):
            p = n / i
            if p % 2 == 1:
                if isPrime( int(p) ):
                    q = i
                    break
        i += 1
    if q == 0:
        print('Public key: {} timeout expired, primes not found!\n' .format(k) )
        continue

    phi = ( p -1 ) * ( q-1 )
    d = inverse( e[k] , phi )

    print('\tKey: {}' .format(k) )
    print('\tPrimes  p:{}  q:{}'.format(p,q) )
    print('\tPublic key: {}  n:{}' .format(e[k],n) )
    print('\tPrivate key:{}\n' .format(d) )
