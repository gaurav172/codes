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
const ll mod=1e6+3;
ll mat[20][20],cf[20];
ll power(ll a,ll b)
{
	ll val=1;
	while(b)
	{
		if(b%2)
			val=(val*a)%mod;
		b/=2;
		a=(a*a)%mod;
	}
	return val;
}
int main()
{
	// ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(ll i=0;i<11;i++)
	{
		mat[i][0]=1;
		for(ll j=1;j<11;j++)
		{
			mat[i][j]=i*mat[i][j-1];
			mat[i][j]%=mod;
		}
		cout<<"? "<<i<<endl;
		cin>>mat[i][11];
		if(!mat[i][11])
		{
			cout<<"! "<<i<<endl;
			return 0;
		}
	}
	for(ll i=0;i<11;i++)
	{
		ll ind=i;
		for(ll j=i;j<11;j++)
			if(mat[j][i]>mat[ind][i])
				ind=j;
		swap(mat[i],mat[ind]);
		for(ll j=0;j<11;j++)
		{
			if(i==j)
				continue;
			ll nm=(mod-mat[j][i])%mod;
			ll dn=mat[i][i];
			ll ft=(nm*power(dn,mod-2))%mod;
			for(ll k=0;k<12;k++)
			{
				mat[j][k]+=ft*mat[i][k];
				mat[j][k]%=mod;
				mat[j][k]=(mat[j][k]+mod)%mod;
			}
		}
	}
	for(ll i=0;i<11;i++)
	{
		cf[i]=(mat[i][11]*power(mat[i][i],mod-2))%mod;
	}
	for(ll i=11;i<1e6+3;i++)
	{
		ll z=0;
		ll cr=1;
		for(ll j=0;j<11;j++)
		{
			z=(z+cf[j]*cr)%mod;
			cr=(cr*i)%mod;
		}
		if(z==0)
		{
			cout<<"! "<<i<<endl;
			return 0;
		}
	}
	cout<<"! -1"<<endl;
	return 0;
}