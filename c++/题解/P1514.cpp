#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=505;
int n, m, ans;
int a[MX][MX], vis[MX][MX], cov[MX];
int l[MX], r[MX];
int sx[MX*MX], sy[MX*MX];
int dx[5]={0, 0, 0, 1, -1};
int dy[5]={0, 1, -1, 0, 0};

//  从第一行第 id 座城市出发, 水只能流向海拔更低的相邻城市
//  它灌得到的干旱区城市恰好是连续一段 ---> [l[id], r[id]]
void dfs(int id) {
	int top=1;
	sx[top]=1;  sy[top]=id;
	vis[1][id]=id;
	while(top>0) {
		int x=sx[top], y=sy[top];
		top--;
		if(x==n) {
			l[id]=min(l[id], y);
			r[id]=max(r[id], y);
			cov[y]=1;
		}
		for(int i=1; i<=4; i++) {
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<1 || nx>n || ny<1 || ny>m)  continue;
			if(a[nx][ny]>=a[x][y])  continue;
			if(vis[nx][ny]==id)  continue;
			vis[nx][ny]=id;
			top++;
			sx[top]=nx;  sy[top]=ny;
		}
	}
}

signed main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++)  cin >> a[i][j];
	}
	for(int j=1; j<=m; j++)  l[j]=m+1, r[j]=0;
	//  第一行里有更高的相邻城市时, 水一定能从那个城市流过来,
	//  所以它的蓄水厂永远不用建
	for(int j=1; j<=m; j++) {
		if(j>1 && a[1][j-1]>a[1][j])  continue;
		if(j<m && a[1][j+1]>a[1][j])  continue;
		dfs(j);
	}
	int bad=0;
	for(int j=1; j<=m; j++) {
		if(cov[j]==0)  bad++;
	}
	if(bad>0) {
		cout << 0 << '\n' << bad;
		return 0;
	}
	//  最少区间覆盖: 每次在左端点已被覆盖的区间里挑右端点最远的那个
	int now=0;
	while(now<m) {
		int best=0;
		for(int j=1; j<=m; j++) {
			if(l[j]<=now+1 && r[j]>best)  best=r[j];
		}
		ans++;
		now=best;
	}
	cout << 1 << '\n' << ans;
	return 0;
}
