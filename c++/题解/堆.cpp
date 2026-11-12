#include<bits/stdc++.h>
using namespace std;
long long n,m,a,b,c;
priority_queue<long long > q;
int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		cin>>a>>b>>c;
		for(int x=1; x<=(m+3)/3; x++){
			int zhi=a*x*x+b*x+c;
			if(q.size()<m)  q.push(zhi);
			else{
				if(zhi<q.top()){
					q.pop();
					q.push(zhi);
				}
			}
		}
	}
	cout<<q.size()<<endl;
	long long l[10005];
	for(int i=1; i<=m; i++) {
		l[m-i+1]=q.top();
		q.pop();
	}
	
	for(int i=1; i<=m; i++)  cout<<l[i]<<' ';
	return 0;
} 
