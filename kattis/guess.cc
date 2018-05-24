#include<iostream>
#include<string>
using namespace std;

int main(){
	int lower=0,upper=1001;
	while(true){
		int mid = (upper+lower)/2;
		cout<<mid<<endl;
		string s;cin>>s;
		if(s=="higher"){
			lower = mid;
		}else if(s=="lower"){
			upper = mid;
		}else if(s=="correct"){
			break;
		}
	}
	return 0;
}