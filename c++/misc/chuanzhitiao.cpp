#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=55;
int m, n;
int a[MX][MX];
//  Both paths start at (1,1) and walk to (m,n), each step going right or down,
//  so the two paths always have taken the same number of steps after k moves.
//  With k steps taken, the row i of a path determines its column: col = k-i+2.
//  f[k][i][j] ---> best total kindness when path1 is on row i and path2 on row j.
//  Kindness is non-negative, so unreachable states may stay 0.
int f[MX*2][MX][MX];

signed main(){
	cin >> m >> n;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			cin >> a[i][j];
	f[0][1][1]=a[1][1];
	for(int k=1; k<=m+n-2; k++)
		for(int i=1; i<=m; i++){
			int c1=k-i+2;                        //  column of path1
			if(c1<1||c1>n)  continue;
			for(int j=1; j<=m; j++){
				int c2=k-j+2;                    //  column of path2
				if(c2<1||c2>n)  continue;
				int tmp=0;
				//  each path's previous row is i or i-1 (same row = moved right)
				for(int pi=i-1; pi<=i; pi++){
					if(pi<1)  continue;
					int pc1=(k-1)-pi+2;          //  previous column of path1
					if(pc1<1||pc1>n)  continue;
					for(int pj=j-1; pj<=j; pj++){
						if(pj<1)  continue;
						int pc2=(k-1)-pj+2;      //  previous column of path2
						if(pc2<1||pc2>n)  continue;
						tmp=max(tmp, f[k-1][pi][pj]);
					}
				}
				//  when both paths share a cell, that student helps only once
				f[k][i][j]=tmp+(i==j?a[i][c1]:a[i][c1]+a[j][c2]);
			}
		}
	cout << f[m+n-2][m][m];
	return 0;
}
