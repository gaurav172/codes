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
// returns max-val between st-en
ll query(ll st,ll en)
{
	ll len=(en-st+1);
	len=ind[len];
	ll b=1<<len;
	ll val=max(sp[st][len],sp[en-b+1][len]);
	return val;
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll curr=0;
	for(ll i=1;i<M;i++)
	{
		ll b=1<<(1+curr);
		if(b>=i)
			ind[i]=curr;
		if(b==i)
			curr++;
	}
	//assing values to sp[i][0] here
	for(ll p=1;p<20;p++)
	{
		for(ll i=1;i<=n;i++)
		{
			ll b=1<<(p-1);
			if(i+b<=n)
			{
				sp[i][p]=max(sp[i][p-1],sp[i+b][p-1]);
			}
		}
	}

	return 0;
}