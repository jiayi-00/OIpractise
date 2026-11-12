#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=505;
int n, m, ans;
int a[MX][MX], vis[MX][MX], cov[MX];
int l[MX], r[MX];
//  hand-written stack: each cell is pushed at most once, so n*m entries are enough
int sx[MX*MX], sy[MX*MX];
int dx[5]={0, 0, 0, 1, -1};
int dy[5]={0, 1, -1, 0, 0};

//  start from city (1,id); water only flows to a lower 4-neighbour
//  the bottom cities it reaches form one segment ---> [l[id], r[id]]
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
	//  a first-row city with a higher neighbour is fed by that neighbour,
	//  so building a reservoir there is never necessary
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
	//  minimum interval cover: always take the interval with the farthest
	//  right end among those whose left end is already covered
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
