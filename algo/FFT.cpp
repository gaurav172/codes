using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
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
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
ll add(ll x,ll y)
{
    ll ret=x+y;
    return ret<0 ? ret+mod:ret>=mod ?ret-mod:ret;
}
vector<ll> multmod(vll a,vll b)
{
    vector<ll> C(sz(a),0),D(sz(b),0);
    for(int i=0;i<sz(a);i++)
    {
        C[i]=a[i]&0xFFFF;
        a[i]=a[i]>>16;
    }
    for(int i=0;i<sz(b);i++)
    {
        D[i]=b[i]&0xFFFF;
        b[i]=b[i]>>16;
    }
    vector<ll> z1=multiply(C,D),z2=multiply(a,b);
    for(int i=0;i<sz(a);i++)a[i]=add(a[i],C[i]);
    for(int i=0;i<sz(b);i++)b[i]=add(b[i],D[i]);
    vll z3=multiply(a,b);
    for(int i=0;i<sz(z3);i++)
    {
        ll x=z1[i]+z2[i];
        x%=mod;
        z3[i]=(z3[i]-x+mod)%mod;
        z2[i]%=mod;
        z3[i]=((ll)z3[i]<<16)%mod;
        z2[i]=((ll)z2[i]<<32)%mod;
    }
    for(int i=0;i<sz(z3);i++)
    {
        z3[i]+=z1[i];
        z3[i]+=z2[i];
        z3[i]%=mod;
    }
    return z3;
}