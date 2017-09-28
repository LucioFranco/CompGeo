# HW 1 Probelm 1
# Sam Windham, Lucio Franco
# 9/26/17

# Object to hold x/y data for polygons
class Polygon:
    def __init__(self, points):
        self.n = len(points)
        self.x = [p[0] for p in points]
        self.y = [p[1] for p in points]

# helper function for cross product
def cross(v1,v2):
    return (v1[0] * v2[1]) - (v2[0] * v1[1])

# Primary algorithm for problem 1a.
#   Takes a Polygon object as input.
#   Sums cross products of each two neighboring
#     edges and checks polarity.
def isClockwise(poly):
    sum = 0
    for i in range(0, poly.n):
        p = (poly.x[i], poly.y[i])
        # Account for wrap-around
        next = (i + 1) % poly.n
        q = (poly.x[next], poly.y[next])
        if cross(p, q) > 0: sum += 1
        elif cross(p, q) < 0: sum -=1

    # Clockwise is negative
    return sum <= 0

def isSimple(poly):
    # Inital cross product
    prev_x_prod = cross((poly.x[0], poly.y[0]), (poly.x[1], poly.y[1]))
    # Simple convex polygons change polarity at most once
    max_change = 1
    for i in range(1, poly.n):
        p = (poly.x[i], poly.y[i])
        q = (poly.x[(i + 1) % poly.n], poly.y[(i + 1) % poly.n])
        # Compute cross product of i and i+1
        current_cross = cross(p,q)
        # Opposite signs produce a negative value.
        if (prev_x_prod * current_cross) < 0:
            max_change -= 1
        prev_x_prod = current_cross
    return max_change >= 0


### Tests ###

# Clockwise (True)
poly1 = Polygon([(0,0), (0,1), (1,0)])
assert isClockwise(poly1) == True
assert isSimple(poly1) == True

poly2 = Polygon([(0,2), (2,3), (3,2), (2,1), (0,1)])
assert isClockwise(poly2) == True
assert isSimple(poly2) == True

poly3 = Polygon([(-2.0, 1.0), (-3.0, 4.0), (0.0, 2.0), (0.0, 4.0), (1.0, 2.0), (3.0, 1.0), (-1.0, -1.0), (2.0, -2.0), (-2.0, -3.0), (-1.0, -2.0), (-4.0, -1.0), (1.0, 1.0), (-4.0, 0.0)])
assert isClockwise(poly3) == True
# isSimple() does not work for this polygon, not same parity

# Counter-clockwise (False)
poly4 = Polygon([(0,0), (1,0), (0,1)])
assert isClockwise(poly4) == False
assert isSimple(poly4) == True

poly5 = Polygon([(3,1), (2,3), (1,4), (0,1), (1,2)])
assert isClockwise(poly5) == False

poly6 = Polygon([(3.0, 2.0), (-1.0, 0.0), (1.0, 4.0), (-4.0, -2.0), (0.0, 0.0), (-4.0, -4.0), (3.0, 1.0), (-1.0, -5.0), (5.0, -1.0)])
assert isClockwise(poly6) == False

# No direction defaults to clockwise (True)
poly7 = Polygon([(0,0), (0,3), (0,2)])
assert isClockwise(poly7) == True

# Complex convex
poly8 = Polygon([(0,0), (1,3), (2,0), (0,2), (2,2)])
assert isSimple(poly8) == False

# Success!
print "All Tests Passed!"
