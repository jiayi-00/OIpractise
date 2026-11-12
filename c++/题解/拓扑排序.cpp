#include<bits/stdc++.h>
using namespace std;
const int mod=80112002;
int n,m,top,ans;
int indu[5005],st[5005],s[5005],outdu[5005],f[5005][5005];
int main(){
	cin>>n>>m;
	int a,b;
	for(int i=1; i<=m; i++){
		cin>>a>>b;
		if(!f[a][b]){
			indu[b]++;
			outdu[a]++;
		}
		f[a][b]=1;
	}
	for(int i=1; i<=n; i++) {
		if(indu[i]==0) {
			st[++top]=i;
			s[i]=1;
		} 
	} 
	while(top!=0){
		int u=st[top--];
		if(outdu[u]==0){
			ans+=s[u];
			ans&=mod;
		}
		for(int i=1; i<=n; i++){
			if(f[u][i]){
				s[i]+=s[u];
				s[i]&=mod;
				indu[i]--;
				if(indu[i]==0)  st[++top]=i;
			}
		}
	}
	for(int i=1; i<=n; i++)  cout<<s[i]<<' ';
	cout<<endl<<ans<<endl;
	return 0;
}
