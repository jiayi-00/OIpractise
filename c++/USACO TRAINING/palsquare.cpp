/*
ID:j8629j81
PROG:palsquare
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b;
signed main(){
    freopen("palsquare.in","r",stdin);
    freopen("palsquare.out","w",stdout);
    cin>>b;
    for(int i=1; i<=300; i++){
        int x=i*i;
        int j=i;
        string s="";
        while(j){
            int t=j%b;
            if(t<10) s+=t+'0';
            else s+=t-10+'A';
            j/=b;
        }
        reverse(s.begin(),s.end());
        string s2="";
        while(x){
            int t=x%b;
            if(t<10) s2+=t+'0';
            else s2+=t-10+'A';
            x/=b;
        }
        string t=s2;
        reverse(t.begin(),t.end());
        if(s2==t){
            cout<<s<<" ";
            reverse(s.begin(),s.end());
            cout<<s2<<endl;
        }
    }

    return 0;
}