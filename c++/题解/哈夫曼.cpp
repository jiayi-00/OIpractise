#include<bits/stdc++.h>
using namespace std;
int n,ans[30]; 
struct node{
	int id,l=-1,r=-1;
}tree[10005];
struct p{
	int id,cishu;
}; 
priority_queue<p> q;
bool operator < (p a,p b){
	return a.cishu>b.cishu;
}
void go(int i,int step){
	ans[i]=step;
	if(tree[i].l!=-1)  go(tree[i].l,step+1);
	if(tree[i].r!=-1)  go(tree[i].r,step+1);
}
int main(){
	cin>>n;
	int cnt=0;
	for(int i=1; i<=n; i++) {
		cnt++;
		int a;
		cin>>a;
		q.push({cnt,a});
	} 
	for(int i=1; i<=n-1; i++){
		cnt++;
		p p1=q.top();q.pop();
		p p2=q.top();q.pop();
		q.push({cnt,p1.cishu+p2.cishu});
		tree[cnt].l=p1.id;
		tree[cnt].r=p2.id;
	}
	go(q.top().id,0);
	for(int i=1; i<=n; i++)  cout<<ans[i]<<' ';
	
	return 0;
} 
