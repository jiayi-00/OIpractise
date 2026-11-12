#include<iostream>
#include<string>

using namespace std;
const int MX=1e6+5;
int n, m;
int t[MX],level[100005],b[MX];
int lowbit(int i){
	return i&(-i);
}
void add(int i){
	while(i<=100000){
		++t[i];
		i+=lowbit(i);
	}
}
int query(int i){
	int s=0;
	while(i){
		s+=t[i];
		i-=lowbit(i);
	}
	return s;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; i++){
		int x, y;
			
		cin >> x >> y;
		x++;y++;
		++level[query(x)];
		add(x);    
	}
	for(int i=0; i<n; i++){
		cout << level[i] << '\n';
	}
	return 0;
}
