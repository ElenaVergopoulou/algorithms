#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define tree vector<pair<ll,vector<ll>>>
#define pb push_back
#define mp make_pair

ll getHeight(tree m,ll index){
	ll height=0;
	queue<ll>q;
	q.push((m[1].second)[index]);
	while(!q.empty()){
		if(height<m[q.front()].first) height=m[q.front()].first;
		if(m[q.front()].second.size()>=1) q.push((m[q.front()].second)[0]);
		if(m[q.front()].second.size()==2) q.push((m[q.front()].second)[1]);
		q.pop();
	}
	return height;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll k,b1=-1,b2=-1,length2=0,length4=0,length1=0;
	cin>>k;
	vector<ll>maxHeights(k);
	for(ll planet=0;planet<k;planet++){
		ll countries,x,lh=0,rh=0;
		cin>>countries;
		if(countries==1){
			cin>>x;
		}
		else{
			tree m(countries+1,mp(0,vector<ll>()));
			m[1].first=0;
			for(ll i=2;i<=countries;i++){
				cin>>x;
				(m[x].second).pb(i);
				m[i].first=m[x].first+1;
			}

			if(m[1].second.size()>=1) lh=getHeight(m,0);
			if(m[1].second.size()==2) rh=getHeight(m,1);
		}

		ll maxheight=max(lh,rh);
		maxHeights[planet]=max(lh,rh);

		if(planet>0){
			ll length=maxheight + maxHeights[planet-1] + k-1;
			length1=max(length1,length);
			if(planet==k-1){
				length=maxheight + maxHeights[0] + k-1;
				length1=max(length1,length);
			}
		}
		if(length2<lh+rh){
			length2=lh+rh;
		}


		if(b1==-1){
			b1=planet;
		}
		else{
			if(maxHeights[b1]<maxHeights[planet]){
				b2=b1;
				b1=planet;
			}
			else if(b2==-1){
				b2=planet;
			}
			else if(maxHeights[b2]<=maxHeights[planet]){
				b2=planet;
			}
			if(maxHeights[b1]==maxHeights[b2] && b1<b2){
				ll temp=b1;
				b1=b2;
				b2=temp;
			}
		}

		if(b1!=-1 && b2!=-1){
			ll length=maxHeights[b1]+maxHeights[b2];
			if(abs(b1-b2)<=k-abs(b1-b2)){
				length+=k-abs(b1-b2);
			}
			else length+=abs(b1-b2);
			length4=max(length4,length);
		}
	}
	
	ll longestRoute=max(length4,length2);
	longestRoute=max(longestRoute,length1);
	cout<<longestRoute<<"\n";

	return 0;
} 