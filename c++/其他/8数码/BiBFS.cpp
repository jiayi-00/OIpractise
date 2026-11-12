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
queue<node > q1,q2;
map<string ,int > mp1,mp2;
void BiBFS(string start){
    node N;
    N.now=start; N.bu=0;
    mp1[N.now]=0;
    q1.push(N);
    N.now=goal;
    mp2[N.now]=0;
    q2.push(N);
    int op=0;
    while(!q1.empty() || !q2.empty()){
        node N;
        if(op==0){
            if(!q1.empty()){
                N=q1.front();
                q1.pop();
            }
        }
        if(op==1){
            if(!q2.empty()){
                N=q2.front();
                q2.pop();
            }
        }
        if(op==0 && mp2.count(N.now)){
            cout<<N.bu+mp2[N.now];
            return ;
        }
        if(op==1 && mp1.count(N.now)){
            cout<<N.bu+mp1[N.now];
            return ;
        }
        int l0,h0,id0;
        for(int i=0; i<9; i++){
            if(N.now[i]=='0'){
                h0=i/3;l0=i%3;id0=i;
                break;
            }
        }
        for(int i=1; i<=4; i++){
            int nh=h0+di[i];
            int nl=l0+dj[i];
            int id=nh*3+nl;
            if(nh>=0 && nh<=2 && nl>=0 && nl<=2){
                swap(N.now[id],N.now[id0]);
                node NN;
                NN.now=N.now; NN.bu=N.bu+1;
                if(op==0 && !mp1.count(N.now)){
                    q1.push(NN);
                    mp1[N.now]=NN.bu;
                }
                if(op==1 && !mp2.count(N.now)){
                    q2.push(NN);
                    mp2[N.now]=NN.bu;
                }
                swap(N.now[id],N.now[id0]);
            }
        }
        op^=1;
    }
}
signed main(){
    string s;
    cin>>s;
    BiBFS(s);
    return 0;
}