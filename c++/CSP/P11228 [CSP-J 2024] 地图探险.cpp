#include<iostream>
using namespace std;

int t,n,m,k,x,y,d,p[1001][1001];
int nx[4]={0,1,0,-1},ny[4]={1,0,-1,0};

int main(){
	
	cin>>t;
	while(t--){
		int ans=0;
		char a[1001][1001]={'x'};
		cin>>n>>m>>k>>x>>y>>d;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				cin>>a[i][j];
			}
		}
		for(int i=1; i<=k+1; i++){
			p[x][y]=1;
			int xl=x+nx[d],yl=y+ny[d];
			if(xl>=1&&xl<=n&&yl>=1&&yl<=m&&a[xl][yl]=='.'){
				x=xl,y=yl;
			}
			else d=(d+1)%4;
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				if(p[i][j]==1){
					p[i][j]=0;
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
} 
