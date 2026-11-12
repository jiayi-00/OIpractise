#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=4e7+5;
int n,type,ans;
int a[MX],f[MX],l[MX],pre[MX];
signed main(){
	cin>>n>>type;
	if(type==0)  {
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			pre[i]=pre[i-1]+a[i];
		}
	}
	for (int i = 1; i <= n; i++){
		for(int j=i; j >= 1; j--){
			int s=pre[i]-pre[j-1];
			if(s >= l[j-1]){
				f[i]=f[j-1]+s*s;
				l[i]=s;
				break;
			}
		}
	}
	cout<<f[n];
	return 0;
} 
