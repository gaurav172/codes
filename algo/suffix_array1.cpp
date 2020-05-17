#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define TRACE
#ifdef TRACE
#define tr(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define tr(...)
#endif

#define ll long long 
#define ld long double 
#define endl "\n"
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (ll)(a.size())
#define all(a) a.begin(), a.end() 
#define fr(i,n) for(i=1;i<=n;i++)
#define rp(i,n) for(i=0;i<n;i++)
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());      // Use mt19937_64 for 64 bit random nos.

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth element.(0-based)
typedef pair<ll, ll> ii;
typedef vector<ll> vl;
typedef vector<ii> vii;
const ll N = 200010;
ll mod=1e9+7;

ll ffmod(ll x, ll y, ll mod)
{
    ll rt=1;
    while(y)
    {
        if(y&1ll) rt=(rt*x)%mod;
        x=(x*x)%mod, y/=2ll;
    }
    return rt;
}

struct SuffixArray
{
    // Note that string should not have '#' character, if you want to join two strings, use '$'. 0 is appended to lcp array. O(NlogN) implementation of suffix array and O(N) implementation of lcp array.
    ll n;
    const ll alphabet = 256;
    string s;
    vector<ll> p, c;

    SuffixArray(const string &s1) : n(s1.length()+1), s(s1+"#"), p(n), c(n)
    {
        vector<ll> cnt(max(alphabet, n), 0);
        for (ll i = 0; i < n; i++) cnt[s[i]]++;
        for (ll i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
        for (ll i = 0; i < n; i++) p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        ll classes = 1;
        for (ll i = 1; i < n; i++)
        {
            if (s[p[i]] != s[p[i-1]]) classes++;
            c[p[i]] = classes - 1;
        }

        vector<ll> pn(n), cn(n);
        for (ll h = 0; (1 << h) < n; ++h)
        {
            for (ll i = 0; i < n; i++)
            {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (ll i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for (ll i = 1; i < classes; i++) cnt[i] += cnt[i-1];
            for (ll i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; // 
            cn[p[0]] = 0, classes = 1;
            for (ll i = 1; i < n; i++)
            {
                pair<ll, ll> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<ll, ll> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        s.pop_back();
        n--;
        p.erase(p.begin());
    }

    vector<ll> GetSuffixArray() { return p; }

    vector<ll> GetLCP()
    {
        ll k = 0;
        vector<ll> lcp(n-1, 0);
        vector<ll> rank(n, 0);
        for(ll i=0;i<n;i++) rank[p[i]] = i;
        for(ll i=0;i<n;i++, k?k--:0)
        {
            if (rank[i] == n-1) { k=0; continue; }
            ll j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
        }
        lcp.PB(0);
        return lcp;
    }
};

vl p,lcp;
string s;

int main()
{
    FIO;
    ll n,i;
    cin>>s;
    n=SZ(s);
    SuffixArray obj(s);
    p = obj.GetSuffixArray();
    lcp = obj.GetLCP();
    tr(SZ(p),SZ(lcp));
    rp(i,n) tr(i,p[i],lcp[i]);
    return 0;
}
