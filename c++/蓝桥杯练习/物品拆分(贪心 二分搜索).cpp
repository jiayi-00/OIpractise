#include<iostream>
#include<algorithm>
using namespace std;
struct task{
	int x,y;
}l[110];
int n,min,a;
bool compare(task a,task b){
	return a.x-a.y>b.x-b.y;
}
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>l[i].x>>l[i].y;
	}
	sort(l+1,l+n+1,compare);
	for(int i=1; i<=n; i++){
		if(a<l[i].x){
			min+=l[i].x-a;
			a=l[i].x;
		}
		a-=l[i].y;
	}
	cout<<min;
	return 0;
}
