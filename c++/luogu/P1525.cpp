// P1525 [NOIP2010] Prisoners -- greedy + bipartite DSU (two copies of each node)
// Sort edges by grudge value descending, add the constraint "a and b are in different prisons"
// i means prisoner i is in prison 1, i+n means prisoner i is in prison 2
// constraint ---> uni(a,b+n) and uni(b,a+n)
// If find(a)==find(b), this edge contradicts every bigger constraint already added
// ---> it is the biggest unavoidable conflict ---> ans=c
// No contradiction at all ---> no conflict happens ---> ans=0
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=100005;
int n, m, ans;
int fa[2*MX];
struct node{
	int a, b, c;
}edges[MX];
bool cmp(node x, node y){
	return x.c>y.c;
}
int find(int x){
	if(fa[x]==x)  return x;
	return fa[x]=find(fa[x]);
}
void uni(int x, int y){
	fa[find(x)]=find(y);
}
signed main(){
	cin >> n >> m;
	for(int i=1; i<=2*n; i++)  fa[i]=i;
	for(int i=1; i<=m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		edges[i].a=a;
		edges[i].b=b;
		edges[i].c=c;
	}
	sort(edges+1, edges+m+1, cmp);
	for(int i=1; i<=m; i++){
		int a=edges[i].a, b=edges[i].b, c=edges[i].c;
		if(find(a)==find(b)){
			ans=c;
			break;
		}
		uni(a,b+n);
		uni(b,a+n);
	}
	cout << ans;
	return 0;
}
