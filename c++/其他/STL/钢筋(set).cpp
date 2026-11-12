#include<iostream>
#include<string>
#include<set> 
using namespace std;
set<int> a;
int n;
int main(){
	cin>>n;
	int x,w;
	while(n--){
		cin>>x>>w;
		if(x==1){
			if(!a.count(w)) a.insert(w);
			else  cout<<"Already Exist"<<endl;
		}else  {
			if(a.empty())  cout<<"Empty"<<endl;
			else{
				set<int>::iterator itb=a.lower_bound(w);
				set<int>::iterator its=itb;
				if(its!=a.begin())  its--;
				int ans;
				if(itb==a.end()){
					itb--;
					ans=*itb;
				}else{
					if(w-*its<=*itb-w)  ans=*its;
					else  ans=*itb;
				}
				cout<<ans<<endl;
				a.erase(ans);
			}
		}
	}
	return 0;
}
