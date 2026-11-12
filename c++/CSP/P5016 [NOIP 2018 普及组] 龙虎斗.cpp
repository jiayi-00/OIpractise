#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

long long int n,m,a[100001],p,s1,s2,l_s,h_s,min_i;
void go1(bool f){
	long long min_s=1e18;
	min_i=m; 
	for(int i=1; i<=n; i++){
		long long t_l=l_s;
		long long t_h=h_s;
		
		if(i<m){
			t_l+=s2*(m-i); 
		}else if(i>m){
			t_h+=s2*(i-m);
		}
		long long diff=abs(t_l-t_h);
		if(diff<min_s){
			min_s=diff;
			min_i=i;
		}else if(diff==min_s&&i<min_i){
			min_i=i; 
		}
	}
} 

int main(){
	
	cin>>n;
	for(int i=1; i<=n; i++)  cin>>a[i];
	cin>>m>>p>>s1>>s2;
	a[p]+=s1;
	for(int i=1; i<m; i++)  l_s+=a[i]*(m-i);
	for(int i=m+1; i<=n; i++)  h_s+=a[i]*(i-m);
	if(l_s==h_s){
		cout<<m;
		return 0;
	}
	go1(l_s>h_s);
	cout<<min_i;
	
	return 0;
} 
