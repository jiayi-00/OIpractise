#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=300005;
int n;
int fa[MX][35], dep[MX], diff[MX], a[MX];
int head[MX], cnt;
struct node{
    int to, nex;
}edges[2*MX];

void add(int u, int v) {
    edges[++cnt].to=v;
    edges[cnt].nex=head[u];
    head[u]=cnt;
}

void dfs(int i, int f) {
    dep[i]=dep[f]+1;
    fa[i][0]=f;
    for(int j=1; (1<<j)<=dep[i]; j++) {
        fa[i][j]=fa[fa[i][j-1]][j-1];
    }
    for(int e=head[i]; e; e=edges[e].nex) {
        int v=edges[e].to;
        if(v==f)  continue;
        dfs(v,i);
    }
}

int lca(int a,int b) {
    if(dep[a]<dep[b]) swap(a,b);
    int diff_dep=dep[a]-dep[b];
    for(int i=0; diff_dep; i++, diff_dep>>=1) {
        if(diff_dep&1) a=fa[a][i];
    }
    if(a==b) return a;
    for(int i=log2(dep[a]); i>=0; i--) {
        if(fa[a][i]!=fa[b][i]) {
            a=fa[a][i];
            b=fa[b][i];
        }
    }
    return fa[a][0];
}

void re(int i, int f) {
    for(int e=head[i]; e; e=edges[e].nex) {
        int v=edges[e].to;
        if(v==f)  continue;
        re(v,i);
        diff[i]+=diff[v];
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
    }
    for(int i=1; i<n; i++) {
        int x, y;
        cin >> x >> y;
        add(x,y);
        add(y,x);
    }
    
    dfs(1,0);
    
    
    for(int i=1; i<n; i++) {
        int L = lca(a[i], a[i+1]);
        diff[a[i]]++;
        diff[a[i+1]]++;
        diff[L]--;
        if(fa[L][0]) diff[fa[L][0]]--;
    }
    
    re(1,0);
    
    for(int i=1; i<=n; i++) {
        if(i != a[1]) diff[i]--;
        cout << diff[i] << '\n';
    }
    
    return 0;
}
