#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
int a[85];
//  max score of taking the whole interval [j,j+step-1] of one row --->longer interval
//  answer can reach 80*80*1000*2^80, far beyond long long, so use __int128
__int128 f[85][85], ans;

void print(__int128 x) {         //  __int128 has no cout, print decimal by hand
	if(x>9)  print(x/10);
	cout << (char)(x%10+'0');
}

signed main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++) {        //  rows are independent, handle them one by one
		for(int j=1; j<=m; j++) {
			cin >> a[j];
			f[j][1]=a[j]*2;          //  interval of length 1 is taken first, weight 2^1
		}
		for(int step=2; step<=m; step++)
			for(int j=1; j<=m-step+1; j++)   //  take a[j] or a[j+step-1] first, the rest is scaled by 2
				f[j][step]=max(2*(a[j]+f[j+1][step-1]),2*(a[j+step-1]+f[j][step-1]));
		ans+=f[1][m];
	}
	print(ans);
	return 0;
}
