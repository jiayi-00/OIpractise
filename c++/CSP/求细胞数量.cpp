#include<iostream>
#include<string>
using namespace std;

int n,m,s,vis[101][101];
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
string a[101];

void dfs(int x,int y){
	vis[x][y]=1;
	for(int i=0; i<=3; i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>0&&nx<=n&&ny>=0&&ny<m&&!vis[nx][ny]&&a[nx][ny]!='0'){
			dfs(nx,ny);
		}
	}
}

int main(){
	
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=n; i++){
		for(int j=0; j<m; j++){
			if(!vis[i][j]&&a[i][j]!='0'){
				s++;
				dfs(i,j);
			}
		}
	}
	cout<<s;
	
	return 0;
}
