#include<bits/stdc++.h>
#define ll long long
#define mid(l,r) ((l+r)>>1)
#define InRange(L,R,l,r) ((l<=L)&&(R<=r))
#define OutofRange(L,R,l,r) ((L>r)||(R<l))
using namespace std;
const int MAXN=100005;
ll a[MAXN],w[MAXN*4],lzy[MAXN*4];
int n,m;

void pushup(const int u){
    w[u]=w[u*2]+w[u*2+1];
}

void build(const int u,int l,int r){
    if(l==r){
        w[u]=a[l];
        return ;
    }
    int M=mid(l,r);
    build(u*2,l,M);
    build(u*2+1,M+1,r);
    pushup(u);
}

ll query1(int u,int l,int r, int p){
    if(l==r) return w[u];
    int M=mid(l,r);
    if(M>=p) return query1(u*2,l,M,p);
    else return query1(u*2+1,M+1,r,p);
}

void maketag(int u,int len,ll x){
    lzy[u]+=x;
    w[u]+=len*x;
}

void pushdown(int u,int L,int R){
    if(lzy[u]){
        int M=mid(L,R);
        maketag(u*2,M-L+1,lzy[u]);
        maketag(u*2+1,R-M,lzy[u]);
        lzy[u]=0;
    }
}

void update(int u,int L,int R,int l,int r,ll x){
    if(InRange(L,R,l,r)){
        maketag(u,R-L+1,x);
        return;
    }
    if(OutofRange(L,R,l,r)) return;
    
    pushdown(u,L,R);
    int M=mid(L,R);
    update(u*2,L,M,l,r,x);
    update(u*2+1,M+1,R,l,r,x);
    pushup(u);
}

ll query(int u,int L,int R,int l,int r){
    if(InRange(L,R,l,r)) return w[u];
    if(OutofRange(L,R,l,r)) return 0;
    
    pushdown(u,L,R);
    int M=mid(L,R);
    return query(u*2,L,M,l,r) + query(u*2+1,M+1,R,l,r);
}

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>a[i];
    build(1,1,n);
    
    for(int i=1; i<=m; i++){
        int op,x,y;
        ll k;
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;
            update(1,1,n,x,y,k);
        }
        else{
            cout<<query(1,1,n,x,y)<<'\n';
        }
    }
    return 0;
}