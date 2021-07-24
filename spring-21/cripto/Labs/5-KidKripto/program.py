import fileinput

def init_comp(a, b, A, B):
    M = a*b -1 
    e = A*M + a
    d = B*M + b
    n = (e*d-1)/M
    return (M, e, d, n)

def encrypt(x, e, n):
    return int((x*e) % n)

def decrypt(y, d, n):
    return int((y*d) % n)

if __name__ == '__main__':
    op = input()
    a = int(input())
    b = int(input())
    A = int(input())
    B = int(input())
    msg = int(input())
    #print(op, a, b, A, B, msg)
    (M, e, d, n) = init_comp(a, b, A, B)
    #print(M, e, d, n)
    if op == 'E':
        print(encrypt(msg, e, n))
    elif op == 'D':
        print(encrypt(msg, d, n))
