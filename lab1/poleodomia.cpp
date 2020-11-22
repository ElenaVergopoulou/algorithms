#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 
using namespace std;

struct shit{
	long long int num;
	int count;
};

vector<long long int> L, R, F;
stack<shit> stoiva;



int main(){
	ios_base::sync_with_stdio(false);
	long long int N;
	cin >> N;
	int i, k;
	long long int previous, sum=0;

	for(i=0;i<N;i++){
		cin >> k;
		F.push_back(k);
	}

	shit s;

	previous=F[0];
	for (i=0;i<N;i++){
		if (F[i]<=previous) {
			sum+=F[i];
			L.push_back(sum);
			s.num=F[i];
			s.count=1;
			stoiva.push(s);
			previous=F[i];
		}
		
		else{
			int counter=1;
			
			while(!stoiva.empty() && F[i]>stoiva.top().num){
				//sum-=counter*stoiva.top();
				counter+=stoiva.top().count;
				sum-=stoiva.top().num * stoiva.top().count;
				//cout << "stoivatop " << stoiva.top() << endl;
				stoiva.pop();
			}
			//for (int j=0;j<counter;j++) 
			s.num=F[i];
			s.count=counter;
			stoiva.push(s);
			sum=sum+s.count*F[i];
			L.push_back(sum);
			previous=F[i];
		}
	}
	previous=F[N-1];
	sum=0;
	while(!stoiva.empty()){
		stoiva.pop();
	}
	for (i=N-1;i>=0;i--){
		if (F[i]<=previous) {
			sum+=F[i];
			R.push_back(sum);
			s.num=F[i];
			s.count=1;
			stoiva.push(s);
			previous=F[i];
		}
		
		else{
			int counter=1;
			
			while(!stoiva.empty() && F[i]>stoiva.top().num){
				//sum-=counter*stoiva.top();
				counter+=stoiva.top().count;
				sum-=stoiva.top().num * stoiva.top().count;
				//cout << "stoivatop " << stoiva.top() << endl;
				stoiva.pop();
			}
			//for (int j=0;j<counter;j++) 
			s.num=F[i];
			s.count=counter;
			stoiva.push(s);
			sum=sum+s.count*F[i];
			R.push_back(sum);
			previous=F[i];
		}
	}
	long long int min=L[0]+R[N-1]-F[0];
	for (i=1;i<N;i++){
		if(L[i]+R[N-1-i]-F[i]<min) min = L[i]+R[N-1-i]-F[i];
	}

	cout << min << endl;

}
