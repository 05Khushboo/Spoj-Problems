n = raw_input()
n = int(n)
a,b,c,d = 1,1,0,0
a,b,c,d = long(a),long(b),long(c),long(d)
for i in xrange(2,n+1):
    c = a + b;
    c = long(c)
    d = b
    d = long(d)
    a = d
    b = c
    a,b,c,d = long(a),long(b),long(c),long(d)
print a+b
