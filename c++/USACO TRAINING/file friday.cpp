/*
ID:j8629j81
PROG:friday
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[8]={0},m[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
signed main(){
    freopen("friday.in","r",stdin);
    freopen("friday.out","w",stdout);
    cin>>n;
    int y=1900,cnt=1;
    for(int i=1; i<=n; i++,y++){
        if(y%4==0 && y%100!=0 || y%400==0){
            m[2]=29;
        }
        else  m[2]=28;
        for(int j=1; j<=12; j++){
            int day=(cnt+12)%7;
            if(day==0)  day=7;
            a[day]++;
            cnt=(cnt+m[j])%7;
            if(cnt==0)  cnt=7;
        }
    }
    cout<<a[6]<<' '<<a[7]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<' '<<a[4]<<' '<<a[5]<<'\n';
    return 0;
}