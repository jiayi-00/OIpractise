#include<bits/stdc++.h>
#define ll long long
using namespace std;

int di[5]={0,0,0,1,-1};
int dj[5]={0,1,-1,0,0};
int ans=0x7fffffff;
string goal="123804765";
map<string ,int > mp;
int h(string now){
    int res=0;
    for(int i=0; i<9; i++){
        if(now[i]!=goal[i] && goal[i]!='0'){
            res++;
        }
    }
    return res;
}
void dfs(string now,int depth,int mxdepth){
    if(depth+h(now)>mxdepth)  return ;
    if(ans!=0x7fffffff)  return ;
    if(depth>mxdepth)  return;
    if(now==goal){
        ans=depth;
        return ;
    }
    int l0,h0,id0;
    for(int i=0; i<9; i++){
        if(now[i]=='0'){
            h0=i/3; l0=i%3; id0=i;
            break;
        }
    }
    for(int i=1; i<=4; i++){
        int nh=di[i]+h0;
        int nl=dj[i]+l0;
        int id=nh*3+nl;
        if(nh>=0 && nh<=2 && nl>=0 && nl<=2){
            swap(now[id],now[id0]);
            if(!mp[now]){
                mp[now]=1;
                dfs(now,depth+1,mxdepth);
                mp[now]=0;
            }
            swap(now[id],now[id0]);
        }
    }
}
void IDAstar(string s){
    mp[s]=1;
    for(int mxdepth=0; ;mxdepth++){
        dfs(s,0,mxdepth);
        if(ans!=0x7fffffff){
            cout<<ans;
            return ;
        }
    }
}
signed main(){
    string s;
    cin>>s;
    IDAstar(s);
    return 0;
}