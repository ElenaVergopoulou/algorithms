#include <bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<ll, ll> iPair;

class Graph
{
	ll N; 

public:
	list< pair<ll, ll> > *adj;

	Graph(ll N); 

	void addEdge(ll u, ll v, ll w);

	vector<ll> shortestPath(ll s);
};

Graph::Graph(ll N)
{
	this->N = N;
	adj = new list<iPair> [N];
}

void Graph::addEdge(ll u, ll v, ll w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

vector<ll> Graph::shortestPath(ll src)
{
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	vector<ll> dist(N, INF);

	pq.push(make_pair(0, src));
	dist[src] = 0;
	
	vector<bool> f(N, false);

	while (!pq.empty())
	{
		ll u = pq.top().second;
		pq.pop();
		f[u] = true;

		list< pair<ll, ll> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			ll v = (*i).first;
			ll weight = (*i).second;

			if (f[v] == false && dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n,m,k,l,b;
    cin>>n>>m>>k>>l>>b;

    Graph roads(n+1);
    for(ll i=0;i<m;i++){
        ll u,v,x;
        cin>>u>>v>>x;
        roads.addEdge(u,v,x);
    }
    map<ll,vector<ll>>paths;
    ll min_time=0;
    vector<ll>routes(k),gas(b);
    for(ll i=0;i<k;i++){
        cin>>routes[i];
        if(i>0){
            for(auto mn=roads.adj[routes[i-1]].begin();mn!=roads.adj[routes[i-1]].end();mn++){
                if(mn->first==routes[i]){
                    min_time+=mn->second;
                    break;
                }
            }
        }
    }

    for(ll i=0;i<b;i++){
        cin>>gas[i];
        roads.addEdge(0,gas[i],0);
    }

    vector<ll>nearest_gas_station=roads.shortestPath(0);
    vector<ll>stops(k-2);
    for(ll i=1;i<k-1;i++){
        stops[i-1]=nearest_gas_station[routes[i]];
    }
    sort(stops.begin(),stops.end());

    for(ll i=0;i<l;i++) min_time+=stops[i];
    cout<<min_time<<'\n';
    return 0;
}