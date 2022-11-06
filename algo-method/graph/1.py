n, m = map(int, input().split())
g = [[] for i in range(n)]
for i in range(m):
    a, b = map(int, input().split())
    g[a].append(b)
    g[b].append(a)
dist = [-1] * n
nodes = [[] for i in range(n)]
dist[0] = 0
nodes[0] = [0]
for k in range(1, n):
    for v in nodes[k - 1]:
        for nv in g[v]:
            if dist[nv] != -1:
                continue
            dist[nv] = dist[v] + 1
            nodes[k].append(nv)
for k in range(n):
    nodes[k].sort()
    print(*nodes[k])
