import fileinput

tableau = [
    ['e','n','c','r','y'],
    ['p','t','a','b','d'], 
    ['f','g','h','i','k'],
    ['l','m','o','q','s'],
    ['u','v','w','x','z']
  ]

def get_a_b(M, tableau, decrypt=False): 
    A = B = ''
    should_stop = False
    for letter in M:
        a = b = -1 
        should_stop = False
        for row in range(len(tableau)):
            for col in range(len(tableau[0])):
                if tableau[row][col] == letter:
                    a = row
                    b = col
                    should_stop = True
                if should_stop:
                    break
            if should_stop:
                break
        if decrypt:
            A += str(a) + str(b)
        else:
            A += str(a)
            B += str(b)
    return A if decrypt else A + B 

def bifid_encryption(M, tableau):
    M = M.lower().replace(' ', '')
    AB = get_a_b(M, tableau)
    C = ''
    for i in range(1, len(AB), 2):
        a = int(AB[i-1])
        b = int(AB[i])
        C += tableau[a][b]
    return C.upper()

def bifid_decryption(C, tableau):
    M = ''
    AB = get_a_b(C.lower().replace(' ', ''), tableau, decrypt=True)
    A = AB[:len(AB)//2]
    B = AB[len(AB)//2:]
    for i in range(len(A)):
        a = int(A[i])
        b = int(B[i])
        M += tableau[a][b]
    return M.upper()

if __name__ == '__main__':
  lines = []
  for line in fileinput.input():
    lines.append(line[:-1])
  
  for i in range(1, len(lines), 2):
    op = lines[i-1]
    msg = lines[i]
    if op == 'DECRYPT':
      print(bifid_decryption(msg, tableau))
    else:
      print(bifid_encryption(msg, tableau))