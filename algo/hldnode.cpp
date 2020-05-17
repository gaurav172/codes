#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
typedef long long int ll;
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=2e5+5;
ll n;
vector<ll> vtr[M];
ll U[M],V[M],wt[M],sub[M],base[M],seg[4*M],anc[M][20],lvl[M],val[M];
ll chain=0,chainNo[M],pos[M],chainHead[M],ptr=1;
inline ll adj(ll x,ll e)
{
	if(U[e]==x)
		return V[e];
	return U[e];
}
inline void dfs(ll x,ll p=0,ll l=1)
{
	sub[x]=1;
	anc[x][0]=p;
	lvl[x]=l;
	for(ll i=0;i<sz(vtr[x]);i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p)
		{
			dfs(u,x,l+1);
			sub[x]+=sub[u];
		}
	}
}
inline void hld(ll x,ll p)
{
	if(chainHead[chain]==0)
	{
		chainHead[chain]=x;
	}
	pos[x]=ptr;
	chainNo[x]=chain;
	base[ptr]=0;
	ptr++;
	ll sc=0;
	for(ll i=0;i<vtr[x].size();i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p)
		{
			if(sub[u]>sub[sc])
				sc=u;
		}
	}
	if(sc)
	{
		hld(sc,x);
	}
	for(ll i=0;i<vtr[x].size();i++)
	{
		ll e=vtr[x][i];
		ll u=adj(x,e);
		if(u!=p && u!=sc)
		{
			chain++;
			hld(u,x);
		}
	}
}
inline void build(ll i,ll s,ll e)
{
	if(s==e)
	{
		seg[i]=base[s];
		return;
	}
	ll m=(s+e)/2;
	build(2*i,s,m);
	build(2*i+1,m+1,e);
	if(lvl[seg[2*i]]<lvl[seg[2*i+1]])
		seg[i]=seg[2*i];
	else
		seg[i]=seg[2*i+1];
}
inline ll query(ll i,ll s,ll e,ll l,ll r)
{
	if(s>r || l>e)
		return 0;
	if(s>=l && e<=r)
		return seg[i];
	ll m=(s+e)/2;
	ll a=query(2*i,s,m,l,r),b=query(2*i+1,m+1,e,l,r);
	if(lvl[a]<lvl[b])
		return a;
	return b;
}
inline void pre()
{
	for(ll j=1;j<20;j++)
	{
		for(ll i=1;i<=n;i++)
			anc[i][j]=anc[anc[i][j-1]][j-1];
	}
}
inline void update(ll i,ll s,ll e,ll x,ll w)
{
	if(s==e)
	{
		seg[i]=w;
		return;
	}
	ll m=(s+e)/2;
	if(x<=m)
		update(2*i,s,m,x,w);
	else
		update(2*i+1,m+1,e,x,w);
	if(lvl[seg[2*i]]<lvl[seg[2*i+1]])
		seg[i]=seg[2*i];
	else
		seg[i]=seg[2*i+1];
}
inline ll lca(ll u,ll v)
{
	if(lvl[u]<lvl[v])
		swap(u,v);
	for(ll i=19;i>=0;i--)
	{
		if(lvl[u]-(1<<i)>=lvl[v])
		{
			u=anc[u][i];
		}
	}
	if(u==v)
		return u;
	for(ll i=19;i>=0;i--)
	{
		ll p=anc[u][i];
		ll q=anc[v][i];
		if(p!=q && p && q)
		{
			u=p;
			v=q;
		}
	}
	return anc[u][0];
}
inline ll queryup(ll u,ll x)
{
	if(u==x)
		return 0;
	ll val=0;
	while(1)
	{
		if(chainNo[u]==chainNo[x])
		{
			ll t=query(1,1,ptr,pos[x],pos[u]);
			if(lvl[t]<lvl[val])
				val=t;
			break;
		}
		ll t=query(1,1,ptr,pos[chainHead[chainNo[u]]],pos[u]);
		if(lvl[t]<lvl[val])
			val=t;
		u=anc[chainHead[chainNo[u]]][0];
	}
	return val;
}
inline ll ans(ll u,ll v)
{
	ll x=lca(u,v);
	ll a=queryup(u,x),b=queryup(v,x);
	if(lvl[a]>lvl[b])
		return b;
	return a;
}
inline void init()
{
	ptr=1;
	chain=0;
	for(ll i=0;i<=n;i++)
	{
		chainHead[i]=0;
		vtr[i].clear();
		val[i]=0;
		for(ll j=0;j<20;j++)
			anc[i][j]=0;
	}
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll i,j,test,p,q,l,r,w,type;
	test=1;
	lvl[0]=M;
	while(test--)
	{
		init();
		cin>>n>>q;
		for(ll i=1;i<n;i++)
		{
			cin>>U[i]>>V[i];
			vtr[U[i]].pb(i);vtr[V[i]].pb(i);
		}
		dfs(1);
		hld(1,0);
		ptr--;
		build(1,1,ptr);
		pre();
		while(q--)
		{
			cin>>type;
			if(type==0)
			{
				cin>>p;
				if(val[p]==0)
					val[p]=p;
				else
					val[p]=0;
				update(1,1,ptr,pos[p],val[p]);
			}
			else
			{
				cin>>p;
				ll t=ans(1,p);
				if(t==0)
					t=-1;
				cout<<t<<"\n";
			}
		}
	}
	return 0;
}