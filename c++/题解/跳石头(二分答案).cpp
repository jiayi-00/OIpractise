#include<bits/stdc++.h>
#define int long long
using namespace std;
int l, n, m;
int d[50005];
signed main(){
    cin >> l >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> d[i];
    }
    d[n+1]=l;
    int l=0, r=1e9;
    while(l<=r){
        int mid=(l+r)>>1;
		int cnt=0, last=0;
		for(int i=1; i<=n+1; i++){
			if(d[i]-last<mid){
				cnt++;
			}
            else  last=d[i];
		}
		if(cnt>m)  r=mid-1;
		else  l=mid+1;
	}
	cout << r ;
    return 0;
}