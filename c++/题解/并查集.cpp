#include<bits/stdc++.h>
using namespace std;
int n,m,f[10001];
int find(int i){
	if(f[i]==i)  return i;
	f[i]=find(f[i]); 
	return f[i];
}
int main(){
	cin>>n>>m;
	int z,x,y;
	for(int i=1; i<=n; i++)  f[i]=i;
	for(int i=1; i<=m; i++){
		cin>>z>>x>>y;
		int r1=find(x),r2=find(y);
		if(z==1) {
			if(r1!=r2)  f[r1]=r2;
		}
		else{	
			if(r1==r2)  cout<<"Y"<<endl;
			else  cout<<"N"<<endl;
		}
	}
	return 0;
} 
