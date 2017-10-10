class Polygon:
    def __init__(self, points):
        self.n = len(points)
        self.points = points
        self.x, self.y = zip(*points)

def cross(v1,v2):
    return (v1[0] * v2[1]) - (v2[0] * v1[1])
