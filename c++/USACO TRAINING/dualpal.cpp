/*
ID:j8629j81
PROG:dualpal
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s;
string tran(int x, int b){
    string ss="";
    while(x){
        int t=x%b;
        if(t<10) ss+=t+'0';
        else ss+=t-10+'A';
        x/=b;
    }
    reverse(ss.begin(),ss.end());
    return ss;
}
signed main(){
    freopen("dualpal.in","r",stdin);
    freopen("dualpal.out","w",stdout);
    cin>>n>>s;
    for(int i=s+1; n; i++){
        int cnt=0;
        for(int j=2; j<=10; j++){
            string t=tran(i,j);
            string t2=t;
            reverse(t2.begin(),t2.end());
            if(t==t2) cnt++;
        }
        if(cnt>=2){
            cout<<i<<endl;
            n--;
            if(n==0) break;
        }
    }
    return 0;
}