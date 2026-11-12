#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int n,m,r,c,hang[20],lie[20],l[20][20],ans=0x7fffffff;

void go2(int i,int last){
	if(i==c+1){
		int a[r+1][c+1];
		for(int j=1; j<=r; j++){
			for(int k=1; k<=c; k++){
				a[j][k]=l[hang[j]][lie[k]];
			}
		}
		int sum=0;
		for(int j=1; j<=r; j++){
			for(int k=1; k<=c; k++){
				if(j!=r)  sum+=abs(a[j][k]-a[j+1][k]);
				if(k!=c)  sum+=abs(a[j][k]-a[j][k+1]);
			}
		}
		ans=min(ans,sum);
		return;
	}
	for(int j=last+1; j<=m; j++){
		lie[i]=j;
		go2(i+1,j);
	}
}

void go1(int i,int last){
	if(i==r+1){
		go2(1,0);
		return;
	}
	for(int j=last+1; j<=n; j++){
		hang[i]=j;
		go1(i+1,j);
	}
}

int main(){
	
	freopen("submatrix.in","r",stdin);
	freopen("submatrix.out","w",stdout);
	cin>>n>>m>>r>>c;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin>>l[i][j];
		}
	}
	go1(1,0);
	cout<<ans;
	
	return 0;
} 
