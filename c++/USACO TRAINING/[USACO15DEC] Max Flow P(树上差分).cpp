#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=50005;
int n, k, ans;
int fa[MX][20], dep[MX], diff[MX];
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
	int mac=log2(dep[i]);
	for(int j=1; j<=mac; j++) {
		fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	for(int e=head[i]; e; e=edges[e].nex) {
		int v=edges[e].to;
		if(v==f)  continue;
		dfs(v,i);
	}
}
int lca(int a,int b) {
	int s=a, t=b;
	if(dep[a]<dep[b]) {
		s=b; t=a;
		a=s; b=t;
	}
	for(int i=log2(dep[a]-dep[b]); i>=0; i--) {
		if(dep[b]<=dep[fa[a][i]])  a=fa[a][i];
	}
	if(a==b) {
		diff[s]++;
		diff[fa[t][0]]--;
		return a;
	} 
	int mac=log2(dep[a]);
	for(int i=mac; i>=0; i--) {
		if(fa[a][i]!=fa[b][i]) {
			a=fa[a][i];
			b=fa[b][i];
		}
	}
	int L=fa[a][0];
	diff[s]++;
	diff[t]++;
	diff[L]--;
	diff[fa[L][0]]--;
	return L;
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
	cin >> n >> k;
	for(int i=1; i<n; i++) {
		int x, y;
		cin >> x >> y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	for(int i=1; i<=k; i++) {
		int s, t;
		cin >> s >> t;
		int L=lca(s,t);
	}
	re(1,0);
	for(int i=1; i<=n; i++) {
		ans=max(ans,diff[i]);
	}
	cout << ans;
	return 0;
}
