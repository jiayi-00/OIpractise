#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=55;
int m, n;
int a[MX][MX];
//  两条路径同时从(1,1)出发走向(m,n) 每步只能向右或向下 所以两条路径步数始终相同
//  走k步时两条路径分别在第i行、第j行 列号可由 k 与行号唯一确定: col = k-row+2
//  f[k][i][j] --->两个人的最大好感度之和 好感度非负 不可达记0不影响取max
int f[MX*2][MX][MX];

signed main(){
	cin >> m >> n;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			cin >> a[i][j];
	f[0][1][1]=a[1][1];
	for(int k=1; k<=m+n-2; k++)
		for(int i=1; i<=m; i++){
			int c1=k-i+2;                        //  第一条路径所在列
			if(c1<1||c1>n)  continue;
			for(int j=1; j<=m; j++){
				int c2=k-j+2;                    //  第二条路径所在列
				if(c2<1||c2>n)  continue;
				int tmp=0;
				//  上一步每条路径只能来自本行(向右)或上一行(向下)
				for(int pi=i-1; pi<=i; pi++){
					if(pi<1)  continue;
					int pc1=(k-1)-pi+2;          //  上一步第一条路径的列
					if(pc1<1||pc1>n)  continue;
					for(int pj=j-1; pj<=j; pj++){
						if(pj<1)  continue;
						int pc2=(k-1)-pj+2;      //  上一步第二条路径的列
						if(pc2<1||pc2>n)  continue;
						tmp=max(tmp, f[k-1][pi][pj]);
					}
				}
				//  两路径重合在同一格时 该同学只帮一次
				f[k][i][j]=tmp+(i==j?a[i][c1]:a[i][c1]+a[j][c2]);
			}
		}
	cout << f[m+n-2][m][m];
	return 0;
}
