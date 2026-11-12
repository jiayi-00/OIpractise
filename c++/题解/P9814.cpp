#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=3005;
const int NEG=-4e18;
int n, m, ans;
int a[MX], b[105];
//  b 升序后，前缀 b[1..j] 当垫子（不取），后缀 b[k..m] 才可能取
//  f 滚动两轮，s = 序列末尾那个元素取(1)还是不取(0)
int f0[105][105][2], f1[105][105][2];

signed main(){
	cin >> n;
	for(int i=1; i<=n; i++)  cin >> a[i];
	cin >> m;
	for(int i=1; i<=m; i++)  cin >> b[i];
	sort(b+1,b+m+1);
	for(int j=0; j<=m+1; j++)
		for(int k=0; k<=m+1; k++)
			f0[j][k][0]=f0[j][k][1]=NEG;
	f0[0][m+1][0]=0;        //  空序列
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m+1; j++)
			for(int k=0; k<=m+1; k++)
				f1[j][k][0]=f1[j][k][1]=NEG;
		//  j 升序、k 降序，保证同轮依赖先算好
		for(int j=0; j<=m; j++)
			for(int k=m+1; k>=j+1; k--){
				//  s=0: 末尾放垫子 b[j] 或放 a[i]（不取）
				int best=f0[j][k][0];
				if(f0[j][k][1]>best)  best=f0[j][k][1];
				if(j>0){
					if(f1[j-1][k][0]>best)  best=f1[j-1][k][0];
					if(f1[j-1][k][1]>best)  best=f1[j-1][k][1];
				}
				f1[j][k][0]=best;
				//  s=1: 取 a[i] 或取 b[k]
				best=NEG;
				if(i>=1&&f0[j][k][0]!=NEG)  best=f0[j][k][0]+a[i];
				if(k<=m&&f1[j][k+1][0]!=NEG){
					int t=f1[j][k+1][0]+b[k];
					if(t>best)  best=t;
				}
				f1[j][k][1]=best;
			}
		memcpy(f0,f1,sizeof(f0));
	}
	ans=0;
	for(int j=0; j<=m; j++)
		for(int s=0; s<2; s++)
			if(f0[j][j+1][s]>ans)  ans=f0[j][j+1][s];
	cout << ans;
	return 0;
}
