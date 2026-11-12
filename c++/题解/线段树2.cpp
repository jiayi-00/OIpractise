#include<bits/stdc++.h>
#define ll long long
#define mid(l,r) ((l+r)>>1)
#define InRange(L,R,l,r) ((l<=L)&&(R<=r))
#define OutofRange(L,R,l,r) ((L>r)||(R<l))
using namespace std;
const int MAXN=100005;
ll a[MAXN],w[MAXN*4],add[MAXN*4],mul[MAXN*4];
int n,q;
ll MOD;

void pushup(int u){
    w[u] = (w[u*2] + w[u*2+1]) % MOD;
}

void build(int u, int l, int r){
    mul[u] = 1;
    add[u] = 0;
    if(l == r){
        w[u] = a[l] % MOD;
        return;
    }
    int M = mid(l, r);
    build(u*2, l, M);
    build(u*2+1, M+1, r);
    pushup(u);
}

void maketag(int u, int len, ll m, ll a){
    w[u] = (w[u] * m + len * a) % MOD;
    mul[u] = (mul[u] * m) % MOD;
    add[u] = (add[u] * m + a) % MOD;
}

void pushdown(int u, int L, int R){
    int M = mid(L, R);
    int left = u*2, right = u*2+1;
    maketag(left, M-L+1, mul[u], add[u]);
    maketag(right, R-M, mul[u], add[u]);
    mul[u] = 1;
    add[u] = 0;
}

void update(int u, int L, int R, int l, int r, ll m, ll a){
    if(OutofRange(L, R, l, r)) return;
    if(InRange(L, R, l, r)){
        maketag(u, R-L+1, m, a);
        return;
    }
    pushdown(u, L, R);
    int M = mid(L, R);
    update(u*2, L, M, l, r, m, a);
    update(u*2+1, M+1, R, l, r, m, a);
    pushup(u);
}

ll query(int u, int L, int R, int l, int r){
    if(InRange(L, R, l, r)) return w[u] % MOD;
    if(OutofRange(L, R, l, r)) return 0;
    pushdown(u, L, R);
    int M = mid(L, R);
    return (query(u*2, L, M, l, r) + query(u*2+1, M+1, R, l, r)) % MOD;
}

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cin >> n >> q >> MOD;
    
    for(int i=1; i<=n; i++) cin >> a[i];
    build(1, 1, n);
    
    for(int i=1; i<=q; i++){
        int op, x, y;
        ll k;
        cin >> op >> x >> y;
        if(op == 1){
            cin >> k;
            update(1, 1, n, x, y, k % MOD, 0);
        }
        else if(op == 2){
            cin >> k;
            update(1, 1, n, x, y, 1, k % MOD);
        }
        else{
            cout << query(1, 1, n, x, y) << '\n';
        }
    }
    return 0;
}