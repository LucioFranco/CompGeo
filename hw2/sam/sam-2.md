---
title: Homework 2
author: Sam Windham *with Lucio Franco*
date: 10/17/17
geometry: margin=1in
---

# 1.
```
PROCEDURE LeftTangent(Polygon p, Point q):
	// first point is left tangent
	if isLeft(q, p[n-1], p[0]) AND !isLeft(q, p[0], p[1]):
		return (q, p[0])
    
	let i = 0, offset = 1
	loop:
		// direction of current edge
		let edgeDir = isLeft(q, p[i], p[i+1])
		
		// current edge is the left tangent point
		if isLeft(q, p[i-1], p[i]) AND !edgeDir:
			return (q, p[i])
	    
		// check directions and continue search
		
		let prevEdgeDir = isLeft(q, p[i - offset], p[i - offset + 1])
		
		// current edge is left
		if edgeDir:
			// previous edge is left AND current point left of previous point
			if prevEdgeDir AND !isLeft(q, p[i-offset], p[i]):
				i -= offset
				offset = 1
			// prev edge is right OR current edge left of previous edge
			else:
				offset *= 2
		else: 
			// previous edge is left
			if prevEdgeDir: 
				i -= offset
				offset = 1
			else: 
				offset *= 2
			
		i = min(i + offset, n - 1)
```

The algorithm performs an exponential search on the points of $P$ and returns the line segment between q and the tangent point. The `isLeft(a, b, c)` function returns the polarity of `cross(<a,b>, <b,c>)`. Exponential search runs in $O(log n)$.


\newpage

# 3.
## a.

## b.

# 4.

# 5.


