class Polygon:
    def __init__(self, n, x, y):
        self.n = n
        self.x = x
        self.y = y

def isClockwise(p):
    # do something here
    print p.n
    print p.x
    print p.y


def cross(v1,v2):
    return (v1[0] * v2[1]) - (v2[0] * v1[1])
def turn(p1,p2,p3):
    return cross(


A = (-2.96, 3.07)
B = (-0.66, 5.3)
C = (3.31, 3.05)
D = (1.62, -0.16)
E = (4.18, -3.22)
F = (-1.65, -3.34)
G = (-5.09, -1.22)
H = (-1.01, 1.27)

n = 8
x1 = [A[0],B[0],C[0],D[0],E[0],F[0],G[0],H[0]]
y1 = [A[1],B[1],C[1],D[1],E[1],F[1],G[1],H[1]]

p = Polygon(n, x1, y1)

#isClockwise(p)
print cross((1.17-3.07,3.84-1.24),(-1.34-3.07,0.32-1.24))
