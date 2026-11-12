#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n,a[100001],pp,k;
double w;

int main(){
	
	cin>>n>>w;
	for(int i=1; i<=n; i++){
		cin>>k;
		int l=1,h=i-1,pos=i;
		while(l<=h){
			int mid=(l+h)/2;
			if(a[mid]<=k)   l=mid+1;
			if(a[mid]>k){
				h=mid-1;
				pos=mid;
			}   
		}
		for(int j=i; j>pos; j--){
			a[j]=a[j-1];
		}
		a[pos]=k;
		int pp=max(1,(int)(i*w/100));
		cout<<a[i-pp+1]<<' ';
	}
	
	return 0;
} 
