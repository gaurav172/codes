#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;   
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ll long long int
#define ld double
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define all(a) a.begin(),a.end()
#define sz(a) (ll)(a.size())
const ll M=2e5+5;
struct Line
{
	ll m;
	ll C;
};
ll h[M],dp[M];
Line seg[4*M];
void init(ll n)
{
	for(ll i=0;i<=4*n;i++)
	{
		seg[i].m=0;
		seg[i].C=1e18;
	}
}
ll getval(ll x,Line L)
{
	return L.m*x+L.C;
}
void update(ll i,ll s,ll e,Line L)
{
	ll mi=(s+e)/2;
	bool lef=getval(h[s],L) < getval(h[s],seg[i]);
	bool mid=getval(h[mi],L) < getval(h[mi],seg[i]);
	if(mid)
		swap(seg[i],L);
	if(s==e)
		return;
	if(lef!=mid)
		update(2*i,s,mi,L);
	else
		update(2*i+1,mi+1,e,L);
}
ll getmin(ll i,ll s,ll e,ll x)
{
	ll mid=(s+e)/2;
	if(s==e)
		return getval(x,seg[i]);
	if(h[mid]>=x)
		return min(getval(x,seg[i]),getmin(2*i,s,mid,x));
	return min(getval(x,seg[i]),getmin(2*i+1,mid+1,e,x));
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n,c;
	cin>>n>>c;
	init(n);
	for(ll i=1;i<=n;i++)
		cin>>h[i];
	dp[1]=0;
	for(ll i=2;i<=n;i++)
	{
		Line L;
		L.m=-2*h[i-1];
		L.C=(h[i-1]*h[i-1])+dp[i-1]+c;
		update(1,1,n,L);
		dp[i]=h[i]*h[i]+getmin(1,1,n,h[i]);
	}
	cout<<dp[n]<<"\n";
	return 0;
}