/*
ID:j8629j81
PROG:ride
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s1,s2;
signed main(){
    freopen("ride.in","r",stdin);
    freopen("ride.out","w",stdout);

    cin>>s1>>s2;
    int r1=1,r2=1;
    for(int i=0; i<s1.size(); i++){
        r1*=s1[i]-'A'+1;
    }
    for(int i=0; i<s2.size(); i++){
        r2*=s2[i]-'A'+1;
    }
    if(r1%47==r2%47)  cout<<"GO\n";
    else cout<<"STAY\n";
    return 0;
}