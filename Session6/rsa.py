from Crypto.Util.number import inverse, GCD,getPrime,getRandomRange

p =  getPrime( 32 )
q =  getPrime( 32 )

n = p * q
phi = ( p -1 ) * ( q-1 )

while( True ):
    e = getRandomRange( 0 , phi )
    if GCD( e , phi ) == 1:
        break
d = inverse( e , phi )
print('\t********************* R S A ********************')
print('\tp:{:20}  q:{:20}\n\tn:{:20}  phi:{:20}\n\te:{:20}  d:{:20}'.format(p,q,n,phi,e,d) )
