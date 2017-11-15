---
title: Homework 4
author: Sam Windham *with Lucio Franco*
date: 11/16/2017
geometry: margin=1in
---

# 1.
## a.

A flip graph with a single node must be formed from a set of points with a unique triangulation.
Such a triangulation requires that no two neighboring triangles form a convex quadrilateral.

A set of points that have only one triangulation can formed from the following:

The general form of the set has $n-2$ collinear points (let the last points in either direction be $p_1$ or $p_{n-2}$). The set then has  two more points that form a triangle with $p_1$ or $p_{n-2}$, exterior to the $n-2$ points. 

More formally, start  with a triangle formed by $p_1$, $p_2$, and $p_3$. Then, add each remaining point exterior to the triangle. These points must fall on the line through $p_3$, perpendicular to the segment $p_1$, $p_2$.
At point $p_i$, the set of $i$ points will contain a unique triangulation. Adding $p_i$ will create two more triangles in its triangulation that together form a convex quadrilateral. 

Therefore, this construction will produce a point set with a single-node flip graph for all $n>3$.

![Two examples - unique triangulation for each](img/1.a.png){width=300px}

## b.



## c.



# 2.



# 3. (or) 4.



# 5.
## a.

```
NN(q: query point, n: node, p: ref point, d: ref distance)
[recursively]
if n = leaf: [base case]
	d' = dist(q, n.point)
	if d' < d:
		d = d'
		p = n.point
if n = node:
	if dist(q, n) < d, then:
		NN(q, n.left, p, d)
		NN(q, n.right, p, d)
return p
```

Initial call: $NN(q, root, null, \infty)$

## b.



## c.


