#include<iostream>
using namespace std;

int a[105],r[105],n;

void merge(int s,int mid,int t){//合并 
	int i=s,k=s,j=mid+1;
	while(i<=mid && j<=t){
		if(a[i]>a[j]) r[k++]=a[j++];
		else r[k++]=a[i++];
	}
	while(i<=mid) r[k++]=a[i++];
	while(j<=t) r[k++]=a[j++];
	for(int w=s; w<=t; w++) a[w]=r[w];
}

void mergesort(int s,int t){//拆分 
	if(s==t) return;
	int mid=(s+t)/2;
	mergesort(s,mid);
	mergesort(mid+1,t);
	merge(s,mid,t);
}

int main(){
	
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	mergesort(1,n);
	for(int i=1; i<=n; i++) cout<<a[i]<<' ';
	
	return 0;
}
