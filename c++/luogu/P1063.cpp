#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=205;
int n, ans;
int a[MX], f[MX][MX];
//  bead i = (a[i], a[i+1]), so a[i]*a[k+1]*a[j+1] is the energy of the last merge
//  f[i][j] = max energy to merge beads i..j into one bead, intervals from short to long
//  circle: duplicate a, then answer = max f[i][i+n-1] over all starts i

signed main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		a[i+n]=a[i];
	}
	for(int len=2; len<=n; len++){
		for(int i=1; i+len-1<=2*n-1; i++){
			int j=i+len-1;
			for(int k=i; k<j; k++){
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+a[i]*a[k+1]*a[j+1]);
			}
		}
	}
	for(int i=1; i<=n; i++)  ans=max(ans,f[i][i+n-1]);
	cout << ans;
	return 0;
}
