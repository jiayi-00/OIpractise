#include<iostream>
#include<string>
using namespace std;

struct ge{
	int i,j,bu;
} q[1000005];
int n,m,map[105][105],used[105][105],ans,h,t; 
int di[9]={0,2,2,1,-1,-2,-2,-1,1};//方向数组 
int dj[9]={0,1,-1,-2,-2,-1,1,2,2};

int main(){
	
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++) cin>>map[i][j];
	}
	h=t=0;
	used[1][1]=1;
	ge g;
	g.i=g.j=g.bu=1;
	q[++t]=g;
	while(h<t){
		ge topg=q[++h];
		for(int k=1; k<=8; k++){
			int newi=topg.i+di[k];
			int newj=topg.j+dj[k];
			if(newi>=1 && newi<=n && newj>=1 && newj<=m && used[newi][newj]==0 && map[newi][newj]==0){
				used[newi][newj]=1;
				ge newg;//建立新邻居 
				newg.bu=topg.bu+1; newg.i=newi; newg.j=newj;//更新数据 
				q[++t]=newg;//存进新邻居 
				if(newg.i==n && newg.j==m){
	 				cout<<newg.bu-1<<endl;
					return 0;
				}
			}
		}
	} 
	
	return 0;
}




