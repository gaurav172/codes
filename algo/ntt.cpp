using LL = long long;
using PII = pair<int, int>;
 
const int mod = 998244353;
const int root = 973800541;
const int root_1 = 595374802;
const int root_pw = 1 << 20;
 
int inverse(int a) {
	int res = 1;
	for (int n = mod - 2; n > 0; n >>= 1) {
		if (n & 1) res = (res * 1ll * a) % mod;
		a = (a * 1ll * a) % mod;
	}
	return res;
}
 
void ntt(vector<int> & a, bool invert=false) {
    int n = a.size();
 
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if (i < j)
            swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);
 
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
 
    if (invert) {
        int n_1 = inverse(n);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}
vector<int> multiply(vector<int> &a,vector<int> &b)
{
    ll p=0;
    int x=sz(a),y=sz(b);
    while((1<<p)<max(sz(a),sz(b)))
        p=p+1;
    p++;
    ll S = (1<<p);
    a.resize(S,0);
    b.resize(S,0);
    ntt(a);ntt(b);
    std::vector<int> c(S,0);
    for(int i=0;i<S;i++)
        c[i] = (a[i]*1LL*b[i])%mod;
    a.resize(x,0);
    b.resize(y,0);
    c.resize(x+y,0);
    return c;
}