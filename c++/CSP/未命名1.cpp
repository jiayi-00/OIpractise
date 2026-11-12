#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long int n,k,ax[200001],sum;

int main(){

    freopen("pair.in","r",stdin);
    freopen("pair.out","w",stdout);
    
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>ax[i];
    sort(ax+1,ax+1+n);
    
    for(int i=1; i<=n; i++){
    	long long int low=1,high=n,wei1=-1,wei2=-1;
    	while(low<=high){
    		int mid=(low+high)/2;
    		if(ax[mid]<ax[i]+1) low=mid+1;
    		if(ax[mid]>=ax[i]+1) high=mid-1;
		}
		if(low<=n) wei1=low;
		
		low=1,high=n;
		while(low<=high){
    		int mid=(low+high)/2;
    		if(ax[mid]<=ax[i]+k) low=mid+1;
    		if(ax[mid]>ax[i]+k) high=mid-1;
		}
		if(high>=1) wei2=high;
		if(wei1!=-1 && wei1<=wei2) sum+=wei2-wei1+1;
	}
    
	cout<<sum;
    
    return 0;
}
