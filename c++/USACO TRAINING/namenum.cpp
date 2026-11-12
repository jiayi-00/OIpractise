/*
ID:j8629j81
PROG:namenum
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
unordered_map<int,vector<string>> ans;
unordered_map<char,int> mp;
void init(){
    mp['A']=2;mp['B']=2;mp['C']=2;
    mp['D']=3;mp['E']=3;mp['F']=3;
    mp['G']=4;mp['H']=4;mp['I']=4;
    mp['J']=5;mp['K']=5;mp['L']=5;
    mp['M']=6;mp['N']=6;mp['O']=6;
    mp['P']=7;mp['R']=7;mp['S']=7;
    mp['T']=8;mp['U']=8;mp['V']=8;
    mp['W']=9;mp['X']=9;mp['Y']=9;
}
signed main(){
    freopen("namenum.in","r",stdin);
    freopen("namenum.out","w",stdout);
    init();
    ifstream dict("dict.txt");
    
    string word;
    while(dict>>word){
        int a=0;
        bool ok=true;
        for(char ch:word){
            char c=toupper(ch);
            if(!mp.count(c)){
                ok=false;
                break;
            }
            a=a*10+mp[c];
        }
        if(ok)  ans[a].push_back(word);
    }
    dict.close();
    cin>>n;
    if(ans.find(n)==ans.end() ||ans[n].empty()) cout<<"NONE"<<endl;
    else{
        for(int i=0;i<ans[n].size();i++){
            cout<<ans[n][i]<<endl;
        }
    }
    return 0;
}