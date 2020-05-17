void update(ll i,ll s,ll e,ll l,ll r,ll x)
{
    ll lc=(i<<1);
    ll rc=((i<<1)|1);
    if(lazy[i])
    {
        seg[i]=seg[i]+lazy[i];
        if(s!=e)
        {
            lazy[lc]+=lazy[i];
            lazy[rc]+=lazy[i];
        }
        lazy[i]=0;
    }
    if(s>r || l>e)
        return;
    if(s>=l && e<=r)
    {
        seg[i]=seg[i]+x;
        if(s!=e)
        {
            lazy[lc]+=x;
            lazy[rc]+=x;
        }
        return;
    }
    ll m=(s+e)/2;
    update(lc,s,m,l,r,x);
    update(rc,m+1,e,l,r,x);
    seg[i]=min(seg[lc],seg[rc]);
}
ll query(ll i,ll s,ll e,ll l,ll r)
{
    ll lc=(i<<1);
    ll rc=((i<<1)|1);
    if(lazy[i])
    {
        seg[i]=seg[i]+lazy[i];
        if(s!=e)
        {
            lazy[lc]+=lazy[i];
            lazy[rc]+=lazy[i];
        }
        lazy[i]=0;
    }
    if(s>r || l>e)
        return 1e16;
    if(s>=l && e<=r)
        return seg[i];
    ll m=(s+e)/2;
    return min(query(lc,s,m,l,r),query(rc,m+1,e,l,r));
}
