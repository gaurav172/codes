Can be used to solve difference constraints
xi - xj <= Wij
construct a graph with edges xi->xj with weight wij. Introudce a source vertex, add edge with weight 0 to each vertex.
check if negative cycle exists using bellmann ford. Assignment is xi= shortestdist(v,xi). also minimizes max(xi)-min(xj).
