#include<bits/stdc++.h>
#define int long long
using namespace std;
int a, b, c, flag=0;
int exgcd(int a, int b, int &x, int &y){
	if(b==0){
		x=1; y=0;
		return a;
	}
	int g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
int gcd(int x, int y){
	return y==0 ? x : gcd(y,x%y); 
}
signed main(){
	cin >> a >> b >> c;
	int x, y;
	int g=exgcd(a,b,x,y);
	if(c%g!=0){
		cout << "No solution";
		return 0;
	}
	int k=c/g;
	int x0=x*k, y0=y*k;
	int dx=b/g, dy=a/g;
	cout << x0 << " " << y0 << "\n";
	cout << dx << " " << -dy;
	return 0;
}