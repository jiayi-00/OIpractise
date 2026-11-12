#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=15;
int N, x, y, v;
int a[MX][MX];
//  与传纸条完全同一套DP 只换输入: 第一行N 随后每行 x y v 一行0 0 0结束
//  走k步时路径可在第i行、第j行 列号 = k-i+2 / k-j+2 --->两条路径取得的最大和
int f[MX*2][MX][MX];

signed main(){
	cin >> N;
	while(cin >> x >> y >> v){
		if(x==0&&y==0&&v==0)  break;
		a[x][y]=v;
	}
	f[0][1][1]=a[1][1];
	for(int k=1; k<=2*N-2; k++)
		for(int i=1; i<=N; i++){
			int c1=k-i+2;
			if(c1<1||c1>N)  continue;
			for(int j=1; j<=N; j++){
				int c2=k-j+2;
				if(c2<1||c2>N)  continue;
				int tmp=0;
				for(int pi=i-1; pi<=i; pi++){
					if(pi<1)  continue;
					int pc1=(k-1)-pi+2;
					if(pc1<1||pc1>N)  continue;
					for(int pj=j-1; pj<=j; pj++){
						if(pj<1)  continue;
						int pc2=(k-1)-pj+2;
						if(pc2<1||pc2>N)  continue;
						tmp=max(tmp, f[k-1][pi][pj]);
					}
				}
				//  同一个格子只算一次
				f[k][i][j]=tmp+(i==j?a[i][c1]:a[i][c1]+a[j][c2]);
			}
		}
	cout << f[2*N-2][N][N];
	return 0;
}
