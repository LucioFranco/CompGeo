# Sam Windham and Lucio Franco
# Homework 2
# 10/17/17


# Help classes/functions ----------------------
class Polygon:
    def __init__(self, points):
        self.n = len(points)
        self.points = points
        self.x, self.y = zip(*points)

# helper function for cross product
def cross(v1,v2):
    return (v1[0] * v2[1]) - (v2[0] * v1[1])

# End helpers --------------------------------


# 1.
def left_tan(p, q):
    for point in p.points:
        a = 1 + 1
    return q




# polygon in CCW order, n = 6
# tangents at L(1,3) and R(3,1)
p = Polygon([(2,1),(3,1),(3,2),(2,3),(1,3),(1,2)])

result = left_tan(p, (0,0))
print result


