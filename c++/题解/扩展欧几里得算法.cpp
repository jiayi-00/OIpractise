#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c=1,x,y;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	int g=exgcd(b,a%b,x,y);
	int x1=x,y1=y;
	x=y1;
	y=x1-a/b*y1;
	
	return g;
}
signed main(){
	cin>>a>>b;
	int g=exgcd(a,b,x,y);
	int x1=x*(c/g),y1=y*(c/g);
	x1=(x1%(b/g)+b/g)%(b/g);	
	cout<<x1;
	return 0;
} 
