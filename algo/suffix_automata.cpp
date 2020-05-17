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
// A substring of string s is path from start state 0.(try to think after reading this)
// No. of states = 2*sz(s), No. of Transitions <= 3*n -4 , n>=3
struct state
{
	ll len;
	ll link;
	map<char,ll> next;
};
state st[M];
ll D[M];
ll last=0,tot=0;
void sa_init()
{
	st[0].len=0;
	st[0].link=-1;
	tot++;
	last=0;
}
void sa_extend(char c)
{
	ll curr=tot++;
	st[curr].len=st[last].len+1;
	ll p=last;
	while(p!=-1 && st[p].next.find(c)==st[p].next.end())
	{
		st[p].next[c]=curr;
		p=st[p].link;
	}
	if(p==-1)
		st[curr].link=0;
	else
	{
		ll q=st[p].next[c];
		if(st[q].len==st[p].len+1)
			st[curr].link=q;
		else
		{
			ll clone=tot++;
			st[clone].len=st[p].len+1;
			st[clone].link=st[q].link;
			st[clone].next=st[q].next;
			while(p!=-1 && st[p].next[c]==q)
			{
				st[p].next[c]=clone;
				p=st[p].link;
			}
			st[q].link=st[curr].link=clone;
		}
	}
	last=curr;
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s;
	cin>>s;
	sa_init();
	ll n=sz(s);
	for(ll i=0;i<n;i++)
		sa_extend(s[i]);
	return 0;
}