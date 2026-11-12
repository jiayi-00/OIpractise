#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
    string now;
    int bu;
};
int di[5]={0,0,0,1,-1};
int dj[5]={0,1,-1,0,0};
string goal="123804765";
queue<node > q;
map<string ,int > mp;
void bfs(string s){
    node N;
    N.now=s; N.bu=0;
    q.push(N); mp[s]=1;
    while(!q.empty()){
        node N=q.front(); q.pop();
        if(N.now==goal){
            cout<<N.bu;
            return ;
        }
        int h0,l0,id0;
        for(int i=0; i<9; i++){
            if(N.now[i]=='0'){
                h0=i/3 ,l0=i%3 ,id0=i;
                break;
            }
        }
        for(int i=1; i<=4; i++){
            int nh=h0+di[i];
            int nl=l0+dj[i];
            if(nh>=0 && nh<=2 && nl>=0 && nl<=2){
                int id=nh*3+nl;
                swap(N.now[id],N.now[id0]);
                if(!mp[N.now]){
                    node NN;
                    NN.now=N.now; NN.bu=N.bu+1;
                    q.push(NN); mp[N.now]=1;
                }
                swap(N.now[id],N.now[id0]);
            }
        }       
    }

}
signed main(){
    string s;
    cin>>s;
    bfs(s);
    return 0;
}
