#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,d;
int f[105][105],g[105][105];
//  2只熊在(i,j)位置时 此前从未相遇过的概率 --->今天
//  g  --->明天
int suc(int p,int k){
	if(p==1)  return k==0?1:2;      // 留在 1, 或者向右走到 2
	if(p==n)  return k==0?n-1:n;    // 向左走到 n-1, 或者留在 n
	return k==0?p-1:p+1;            // 普通地点: 向左或向右
}

int gcd(int a,int b){
	while(b){
		int t=b;
		b=a%b;
		a=t;
	}
	return a;
}

signed main(){
	cin >> n >> x >> y >> d;
	f[x][y]=1;
	for(int day=1; day<=d; day++){
		memset(g,0,sizeof(g));        
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(f[i][j]==0)  continue;   
				for(int a=0; a<2; a++){
					for(int b=0; b<2; b++){
						int ni=suc(i,a),nj=suc(j,b);
						if(ni!=nj)  g[ni][nj]+=f[i][j];
					}
				}
			}
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				f[i][j]=g[i][j];
			}
		}
	}
	int all=1;
	for(int i=1; i<=d; i++)  all*=4;
	int no=0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i!=j)  no+=f[i][j];
		}
	}
	int p=all-no,q=all;
	int gg=gcd(p,q);
	cout << p/gg << '/' << q/gg << '\n';
	return 0;
}
