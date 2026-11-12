#include<bits/stdc++.h>
#define int long long
using namespace std;
int q;
int jump(int x){
	for (int i=2; i<=sqrt(x); i++)
		if (x%i==0)
			return x/i;
	return 1;
}
void solve(){
    int a, b, ans=0;
    cin >> a >> b;
    while(a!=b){
        while(a>b) {
            a=jump(a);
            ans++;
        }
        while(a<b){
            b=jump(b);
            ans++;
        }
    }
    cout << ans << endl;
}
signed main(){
    cin >> q;
    while (q--){
        solve();
    }
    
	return 0;
} 