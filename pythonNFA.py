import queue

f = open("date.txt","r")
n = int(f.readline())
l = []
mat = {}
for linie in f:
    aux = linie.split()
    if len(aux) :
        l.append(aux)
m = int(l[0][0])
muc = l[1]
muc.append('$')
q0 = int(l[2][0])
k = int(l[3][0])
qf = l[4]
lat = int(l[5][0])
for i in range(6, 6 + lat):
    x = int(l[i][0])
    c = l[i][1]
    y = int(l[i][2])
    j = 0
    while muc[j] != c:
        j += 1
    if (x,c) not in mat:
        mat[(x,c)] = [y]
    else:
        mat[(x,c)].append(y)
s = l[6+lat][0]
Q1 = queue.Queue()
Q2 = queue.Queue()
viz = [0]*(n+1)

def evaluate2(s):
    global n, m, q0, k, qf, mat, muc
    lg = len(s)
    Q1.put(q0)
    viz[q0] = 1
    for poz in range(lg):
        if Q1.empty() :
            return False
        while Q1.empty() != True :
            x = Q1.get()
            Q2.put(x)
            if (x, '$') in mat:
                for stare in mat[(x,'$')] :
                    if viz[stare] != poz+1 :
                        viz[stare] = poz+1
                        Q1.put(stare)
        while Q2.empty() != True :
            x = Q2.get()
            if (x, s[poz]) in mat :
                for stare in mat[(x,s[poz])] :
                    if viz[stare] != poz + 2:
                        viz[stare] = poz + 2
                        Q1.put(stare)
    while Q1.empty() != True :
        x = Q1.get()
        Q2.put(x)
        if (x,'$') in mat :
            for stare in mat[(x,'$')] :
                if viz[stare] != lg + 1 :
                    viz[stare] = lg + 1
                    Q1.put(stare)
    while Q2.empty() != True :
        x = Q2.get()
        for stare in qf :
            if stare == x :
                return True
    return False


print(mat)

"""if evaluate2(s):
    print("Cuvantul e acceptat")
else:
    print("Cuvantul nu e acceptat")"""



