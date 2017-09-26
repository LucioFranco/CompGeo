% Homework 1
% Sam Windham, *Worked with Lucio Franco*
% 9/26/2017


# 1.
## a.

```Python
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
```	
The algorithm takes the cross product of every edge.

## b.


# 2.
## a.
Proof by induction. 

A triangle or polygon of size $n=3$ has a unique triangulation. Adding a vertex to this polygon will create a quadrilateral. Placing the vertex outside of the polygon results in a convex quadrilateral. And since a convex quadrilateral can never have unique triangulation, it  must be placed within the polygon.

The ear lemma in class states that *Every polygon $P$ with $n>3$ vertices has at least two ears.*

Using this we can say that the added vertex must fall within an ear, and that there exists a point within the ear that has only one diagonal.

!!!
**Polygons do not contain collinear edges**`
!!!

# 3.
!!!
**Lucio**
!!!

# 4.
## a.
The cross product of two vectors $v_1$ and $v_2$ gives us the area of the parallelogram that they form. Half of this area gives us the area formed between the two vectors. 
The polarity of the cross product is determined by the orientation of the two vectors since 
$v_1 \times v_2 = -(v_2 \times v_1)$.

For each pair of points $p_i$ and $p_{i-1}$ that share an edge, the formula finds the cross product of the vectors from the origin to those points. e.g.
$$(x_i,y_i) \times (x_{i-1},y_{i-1}) = (x_i y_{i-1} - x_{i-1} y_i)$$
It then sums each of these cross-products and scales by $1/2$.
This leaves us with the area within the polygon. The orientation of the points correctly add and subtract the areas.

For a triangle ($p_1$, $p_2$, $p_3$), let $v_1$ be the vector from the origin to $p_1$, $v_2$ be the vector from the origin to $p_2$, and $v_3$ be the vector from the origin to $p_3$.

!!!
**Finish**
!!!

## b.
!!!
**Together**
!!!

# 5.
## a.
!!!
**Together**
!!!

## b.
!!!
**Together**
!!!

## c.
!!!
**Together**
!!!

## d.
!!!
**Together**
!!!

