#include <bits/stdc++.h>

using namespace std;

const int MAXn = 200005;

int k , n, s[4005],dp[4005][4005][2],dp1[4005][2];
int cov[MAXn][2];

bool mark[MAXn];
vector< int > G[MAXn];

void dfs1(int x) {

	cov[x][0] = 0; 
	cov[x][1] = 1; 

	mark[x] = true;
	for(int i=0; i<G[x].size(); i++) {

		int y = G[x][i];

		if (!mark[y]) {

			dfs1(y);
			cov[x][0] += cov[y][1];
			cov[x][1] += min( cov[y][0], cov[y][1] );
		}
	}
}

void dfs2(int u,int par)
{
	s[u]=1;
	int c=0;
	for(auto v:G[u])
	{
		if(v!=par)
		{
			dfs2(v,u);
			s[u]+=s[v];
		}
	}
	s[u]=1;
	for(auto v:G[u])
	{
		if(v!=par)
		{
			s[u]+=s[v];
			if(c)
			{
				for(int j=s[u]-1;j;j--)
				{
					for(int l=1;l<=min(s[v],j);l++)
					{
						dp1[j][0]=min(dp1[j][0],dp1[j-l][0]+dp[v][l][0]);
						dp1[j][1]=min(dp1[j][1],dp1[j-l][1]+dp[v][l][1]);
					}
				}
			}
			else
			{
				for(int j=0;j<s[u];j++)
				{
					dp1[j][0]=dp[v][j][0];
					dp1[j][1]=dp[v][j][1];
				}
			}
			c++;
		}
	}
	for(int j=0;j<=s[u];j++)
	{
		dp[u][j][0]=min((j?1+dp1[j-1][1]:1000000),dp1[j][0]);
		dp[u][j][1]=min((j?1+dp1[j-1][1]:1000000),(j?dp1[j-1][0]:1000000));
	}
	for(int j=0;j<s[u];j++)
		dp1[j][0]=dp1[j][1]=1000000;
	dp1[0][0]=0;
}

int main() {

	//freopen("inp.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	cin >> n >> k ;

	for(int i = 1; i<=n; i++) {
		G[i].clear();
		mark[i] = false;
	}

	for(int i = 0; i<n-1; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	if (k == n-1)
	{
		dfs1(1);
		cout << min(cov[1][0],cov[1][1]) << "\n";
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=n;j++)
			{
				dp[i][j][0]=dp[i][j][1]=1000000;
				dp1[j][0]=dp1[j][1]=1000000;
			}
		}
		dp1[0][0]=0;
		dfs2(1,0);
		int ans=1000000;
		for(int j=k+1;j<=n;j++)
			ans = min(ans,dp[1][j][1]);
		cout << ans << "\n";
	}

	return 0;
}