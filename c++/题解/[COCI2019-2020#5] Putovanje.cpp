#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=200005;
int n, ans;
int fa[MX][20], dep[MX], diff[MX], p1[MX], p2[MX];
int head[MX], cnt;
struct node{
	int to, nex, c1, c2;
}edges[2*MX];
void add(int u, int v, int c1, int c2) {
	edges[++cnt].to=v;
	edges[cnt].nex=head[u];
	edges[cnt].c1=c1;
	edges[cnt].c2=c2;
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
		p1[v]=edges[e].c1;
		p2[v]=edges[e].c2;
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
		diff[t]--;
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
	diff[L]-=2;
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
	cin >> n ;
	for(int i=1; i<n; i++) {
		int x, y, c1, c2;
		cin >> x >> y >> c1 >> c2;
		add(x,y,c1,c2);
		add(y,x,c1,c2);
	}
	dfs(1,0);
	for(int i=1; i<n; i++) {
		
		int L=lca(i,i+1);
	}
	re(1,0);
	for(int i=1; i<=n; i++) {
		ans+=min(diff[i]*p1[i],p2[i]);
	}
	cout << ans;
	return 0;
}
