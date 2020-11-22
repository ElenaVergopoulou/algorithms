#include <bits/stdc++.h>
using namespace std;
const int MAX = 200005;
int id[MAX], nodes, edges;
pair <long long, pair<int, int> > p[MAX];
#define ll long long
#define pb push_back
#define mp make_pair
#define N 100005 //size of graph

vector< pair<int,int> > g[N]; 
int subsize[N],n; 
ll res;
ll ans[400005];
void initialize()
{
    for(int i = 0;i < MAX;++i)
        id[i] = i;
    
    for(int i=0;i<400005;i++)
    ans[i] = 0;
}

int root(int x)
{
    while(id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void union1(int x, int y)
{
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

long long kruskal(pair<long long, pair<int, int> > p[])
{
    int x, y;
    long long cost, minimumCost = 0;
    for(int i = 0;i < edges;++i)
    {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        if(root(x) != root(y))
        {
            minimumCost += cost;
            g[x].pb(mp(y,cost));
            g[y].pb(mp(x,cost));
            union1(x, y);
        }    
    }
    return minimumCost;
}

void dfs(int node,int cost,int parent)
    {
        subsize[node]=1; 
        for(auto it:g[node])
        {
            int next=it.first;
            int c=it.second;
            if(next!=parent)
            {
                dfs(next,c,node);
                subsize[node]+=subsize[next]; 
            }
        }
        //cout<<(n-subsize[node])*subsize[node]<<" "<<cost<<"\n";
        //res += ((ll)(n-subsize[node])) * ((ll)subsize[node]) * pow(2,cost);
        
        ll fre = ((ll)(n-subsize[node])) * ((ll)subsize[node]) ;
        if(fre!=0)
        ans[cost] = ((ll)(n-subsize[node])) * ((ll)subsize[node]);
    }
int main()
{
    //freopen("input17.txt", "r", stdin);
    //freopen("ans.txt", "w", stdout);
    int x, y, i;
    long long weight, cost, minimumCost;
    initialize();
    cin >> nodes >> edges;
    n=nodes;
    for(i = 0;i < edges;++i)
    {
        cin >> x >> y >> weight;
        p[i] = mp(weight, mp(x, y));
    }
    sort(p, p + edges);
    minimumCost = kruskal(p);
    res=0;
    dfs(1,0,-1);
    for (i=0;i<400004;i++)
    {
        if(ans[i]!=0){
            //cout<<i<<" "<<ans[i]<<"\n";
            ans[i+1] += ans[i]/2 ;
            ans[i] = ans[i]%2 ;
        }
    }
    int pos = -1 ;
    for(i=400005;i>=0;i--){
        if(ans[i]==1){
            pos=i;
            break;
        }
    }
    if(pos==-1)
    cout<<0<<"\n";
    else
    {
        for(i=pos;i>=0;i--)
        cout<<ans[i];
    }
    cout<<"\n";
    //cout<<res<<"\n";
    return 0;
}
