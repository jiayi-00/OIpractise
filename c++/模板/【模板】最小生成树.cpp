#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt, head[5005];
int n, m;
int fa[10005];
struct node{
	int fro, to, w;
}edges[200005];
bool cmp(node x,node y){
	return x.w<y.w;
}
int find(int x){
	if(fa[x]==x)  return x;
	else{
		fa[x]=find(fa[x]);
		return fa[x];
	}
}
signed main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		fa[i]=i;
	}
	for(int i=1; i<=m; i++){
		int a,b,c;
		cin >> a >> b >> c;
		edges[i]={a,b,c};
	}
	sort(edges+1, edges+m+1, cmp);
	int ans=0,cnt=0;
	for(int i=1; i<=m; i++){
		int fx=find(edges[i].fro);
		int fy=find(edges[i].to);
		if(fx!=fy){
			fa[fx]=fy;
			ans+=edges[i].w;
			cnt++;
			if(cnt==n-1) break;
		}
	}
	
	if(cnt==n-1) cout << ans << endl;
	else cout << "orz" << endl;
	return 0;
} 
