#include<iostream>
#include<algorithm>
using namespace std;

long long int n,a[200001];

int main(){
	
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    int m=unique(a+1,a+n+1)-(a+1);
    if(m<=1)cout<<-1<<endl;
    else if(m==2)cout<<a[1]%a[2]<<endl;
    else cout<<max(a[m-2]%a[m],a[m]%a[m-1])<<endl;
    
    return 0;
}
