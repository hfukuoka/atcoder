x, y, z = map(int, input().split())
if x > 0:
    if x < y or y < 0:
        ans = x
    elif z < y:
        if z > 0:
            ans = x
        else:
            ans = abs(z) * 2 + x
    else:
        ans = -1
else:
    if y < x or y > 0:
        ans = abs(x)
    elif y < z:
        if z < 0:
            ans = abs(x)
        else:
            ans = z * 2 + abs(x)
    else:
        ans = -1
print(ans)
