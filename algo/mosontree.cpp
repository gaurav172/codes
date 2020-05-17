let query be (u,v)
P = lca(u,v)
if P = u => ST[u],ST[v]
else [EN[u],ST[v]] + [ST[P],ST[P]]
only take points which appear exactly once.