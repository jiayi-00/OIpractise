#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[25],b[25],side,s,f;
void pin(int i){
	if(s>side) return;
	if(i>n){
		if(f==4 && s==0){
			cout<<"yes"<<endl;
			f=5;
		}
		return;
	}
	if(b[i]==0){
		if(s+a[i]<=side){
			s+=a[i];
			b[i]=1;
			if(s==side){
				f++;
				int temp_s=s,temp_f=f;
				s=0;
				pin(1);
				s=temp_s;
				f=temp_f;
				s=side;
			}else pin(i+1);
			s-=a[i];
			b[i]=0;
		}
	}
	pin(i+1);
}
int main(){
	cin>>t;
	for(int i=1; i<=t; i++){
		cin>>n;
		int maxa=0,sum=0;
		f=0,s=0;
		for(int i=1; i<=n; i++){
			cin>>a[i];
			maxa=max(maxa,a[i]);
			sum+=a[i];
			b[i]=0;
		}
		if(sum%4!=0 || maxa>sum/4){
			cout<<"no"<<endl;
			continue;
		} 
		side=sum/4;
		sort(a+1,a+n+1,greater<int>());
		pin(1);
		if(f!=5){
			cout<<"no"<<endl;
		}
		f=0;
	}
	return 0;
}
