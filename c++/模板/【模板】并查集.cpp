#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n, m;
int fa[10005];
int find(int x){
	if(fa[x]==x)  return x;
	else{
		fa[x]=find(fa[x]);
		return fa[x];
	}
}
signed main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++)  fa[i]=i;
	for(int i=1; i<=m; i++){
		int z, x, y;
		cin >> z >> x >>y;
		int rx=find(x), ry=find(y);
		if(z==1)  fa[rx]=ry;
		else  {
			if(rx==ry)  cout << "Y\n";
			else  cout << "N\n";
		}
	}
	return 0;
}
