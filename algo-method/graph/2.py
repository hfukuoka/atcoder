from queue import Queue

n, m = map(int, input().split())
g = [[] for _ in range(n)]
for i in range(m):
    a, b = map(int, input().split())
    g[a].append(b)
    g[b].append(a)

dist = [-1] * n

q = Queue()

dist[0] = 0
q.put(0)

while not q.empty():
    v = q.get()
    for nv in g[v]:
        if dist[nv] != -1:
            continue
        dist[nv] = dist[v] + 1
        q.put(nv)

print(max(dist))
