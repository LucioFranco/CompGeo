% Homework #1
% Lucio Franco, worked with Sam Windham.
% 10/17/2017

## 1)

## 3)

We know that there are $n \choose{2}$ lines inducded from a set of n points in general position. If we transform every point to the dual, the lines produced will intersect forming the point that represents the line between those two points that are now lines in the dual. We know that if the point formed from the intersection of the two lines is on the positive side of the dual, aka it has a x value greater than zero, it's line segment in the primal has a positive slope. 

From this we can run a plane sweep starting at the origin and sweeping along the x axis of the dual. Each time we encounter an intersection of two lines we can count this as a positive slope. There are also four possible combinations of the lines, when at the origin one can tell if both lines have positive slope, the line above has positive slope and the line below has negative slope, the line above has negtative slope and the line below has positive slope, or they both have negative slopes. 

From this we can eliminate possible events because for a fact we know that those two lines can not intersect as we move to the right when the line above has a positive slope and the line below has a negative slope. For part (a) we would continue the line sweep until weve gone through all of the intersections but for part (b) instead of starting at the origin, we would start at $m$ and continue until we have hit $m$. 

Since as we move to the right the slope of the line produced from the intersection in the dual will have a larger slope. Every intersection found within this bound will be counted as a positive slope. A brute force algorithinm would take $\theta{n\choose{2}}$ but with the plane sweep and the eleimination of events we can reduce this to $O{n\choose{2}}$ because in most cases we will be able to eliminate some events. In the worst case, all lines would have a positive slope and therefore no matter what we need to check each so this would produce a runtime of $O {{n}\choose{2}}$.

## 4)


## 5)


