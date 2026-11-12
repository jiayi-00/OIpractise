#include<bits/stdc++.h>
using namespace std;
int n,m,fa[10001],ans,c[10001],min_c=1e9;
int find(int i){
	if(fa[i]==i)  return i;
	fa[i]=find(fa[i]);
	return fa[i];
}
struct t{
	int a,b,z;
}edge[1000001];
bool cmp(t x,t y){
	return (x.z*2+c[x.a]+c[x.b])<(y.z*2+c[y.a]+c[y.b]);
}
int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		fa[i]=i;
		cin>>c[i];
	} 
	for(int i=1; i<=m; i++) {
		cin>>edge[i].a>>edge[i].b>>edge[i].z;
	}
	sort(edge+1,edge+m+1,cmp);
	for(int i=1; i<=m; i++){
		int r1=find(edge[i].a),r2=find(edge[i].b);
		if(r1!=r2){
			fa[r1]=r2;
			//cout<<i<<':'<<' '<<edge[i].a<<' '<<edge[i].b<<' '<<edge[i].z<<endl;
			int c1=c[edge[i].a],c2=c[edge[i].b];
			ans+=edge[i].z*2;
			ans+=c1+c2;
			min_c=min(min_c,min(c1,c2));
		}
	}
	cout<<ans+min_c<<endl;
	
	return 0;
} 
