#include<iostream>
#include<vector>
using namespace std;

class Enumerator{
private:
	int nn=0,total=0;
	vector<int> digits;
	int valid(){
		int base = digits.size(),res=0;
		for(int i=0;i<base;i++){
			res = (res*10+digits[i])%base;
		}
		if(res==0)return 1;
		return 0;
	}
	void recTrace(int d){
		if(!valid())return;
		if(d==nn){
			total++;
			return;
		}
		for(int i=0;i<10;i++){
			if(i==0 && d==0)continue;
			digits.push_back(i);
			recTrace(d+1);
			digits.pop_back();
		}
	}
public:
	int numValids(int n){
		nn = n;total = 0;
		recTrace(0);
		return total;
	}
};

int main(){
	Enumerator _enum;
	int n;
	cin>>n;
	cout<<_enum.numValids(n)<<endl;
	return 0;
}