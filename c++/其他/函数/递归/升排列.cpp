#include<iostream>
using namespace std;
int n,ans,lu[25],e,s,ci[25];
void go(int i){
	if(i==e){
		ans++;
		return;
	}
	if(i-lu[i]>=1 && ci[i-lu[i]]<2){
		ci[i-lu[i]]++;
		go(i-lu[i]);
		ci[i-lu[i]]--;
	}
	if(i+lu[i]<=n && ci[i+lu[i]]<2){
		ci[i+lu[i]]++;
		go(i+lu[i]);
		ci[i+lu[i]]--;
	}
} 
int main(){
	cin>>n;
	for(int j=1; j<=n; j++){
		cin>>lu[j];
	}
	cin>>s>>e;
	go(s);
	cout<<ans;
	return 0;
}
