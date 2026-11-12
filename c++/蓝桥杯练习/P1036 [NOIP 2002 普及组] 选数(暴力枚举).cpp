#include<iostream>
using namespace std;
int n,k,a[25],sum;
bool su(int b){
	if(b<2) return false;
	for(int i=2; i*i<=b-1; i++){
		if(b%i==0) return false;
	}
	return true;
}
void dfs(int cnt, int start, int s){
	if(cnt==k){
		if(su(s)) sum++;
		return ;
	}
	for(int i=start; i<=n; i++){
		dfs(cnt+1,i+1,s+a[i]);
	}
}
int main(){
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>a[i];
	dfs(0,1,0);
	cout<<sum;
	return 0;
} 
