n, m = map(int, input().split())
k = []
x = []
for i in range(m):
    kx = list(map(int, input().split()))
    k.append(kx[0])
    x.append(kx[1:])

t = [[False for _ in range(n)] for _ in range(n)]
for i in range(m):
    for j in range(k[i]):
        for l in range(k[i]):
            t[x[i][j] - 1][x[i][l] - 1] = True
f = True
for i in range(n):
    for j in range(n):
        if t[i][j] == False:
            f = False

if f:
    print("Yes")
else:
    print("No")
