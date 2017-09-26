# HW 1 Probelm 1
# Sam Windham
#
#   Find if polygon is cloackwise.
#   Uses primitive turn algorithm on every
#     three points and sums each result.
#   A negative result means a clockwise polygon,
#     else, counter-clockwise.
#   Iterates through all n vertices.
#     => T(n) = O(n)

# Object to hold x/y data for polygons
class Polygon:
    def __init__(self, n, x, y):
        self.n = n
        self.x = x
        self.y = y

# helper functions for cross product
#   and primitive turn algorithm
def cross(v1,v2):
    return (v1[0] * v2[1]) - (v2[0] * v1[1])

def turn(p, q, r):
    v1 = (q[0] - p[0], q[1] - p[1])
    v2 = (r[0] - p[0], r[1] - p[1])
    c = cross(v1, v2)

    if(c > 0): return 1
    elif(c < 0): return -1
    else: return 0

# Primary algorithm for problem 1a.
#   Checks is each angle is a left
#   or right turn and sums the results.
def isClockwise(poly):
    sum = 0
    for i in range(0, poly.n - 2):
        p = (poly.x[i], poly.y[i])
        q = (poly.x[i+1], poly.y[i+1])
        sum += cross(p, q)

    if(sum > 0): return True
    else: return False

# Primary algorithm for problem 1b.
def hasIntersectingSegments(poly):
    return True


# Sample data
A = (-2,4)
B = (-2,0)
C = (0,-2)
D = (2,0)
E = (0,2)
F = (2,4)
G = (0,6)

# New example polygon
n = 7
x1 = [A[0],B[0],C[0],D[0],E[0],F[0],G[0]]
y1 = [A[1],B[1],C[1],D[1],E[1],F[1],G[1]]
p = Polygon(n, x1, y1)

# Test example
print isClockwise(p)
