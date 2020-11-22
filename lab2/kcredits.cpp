#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define node pair<ll, pair<int, int>>

using namespace std;

const int inf = 2 * (int)1e9;
vector<node> st;
int height = 1;


void init(int n)
{
    st.clear();
    height=1;
    while(height < n) height *= 2;
    st.resize(2*height, {-inf, {inf, -inf}});
}

node const merge(node le, node ri) {
    if (le.first < ri.first) swap(le, ri);
    if (ri.first == le.first) {
        le.second.first = min(le.second.first, ri.second.first);
        le.second.second = max(le.second.second, ri.second.second);
    }
    return le;
}

void  set_node(int i, node offset) {
    st[i+height] = merge(st[i+height], offset);
    for (i += height; i > 1; i /= 2) st[i/2] = merge(st[i], st[i^1]);
}

node const get_node(int a, int b, int i, int le, int ri) {
    if (ri <= a || b <= le) return {-inf, {inf, -inf}};
    else if (a <= le && ri <= b) return st[i];
    else return merge(get_node(a, b, 2*i, le, (le+ri)/2), get_node(a, b, 2*i+1, (le+ri)/2, ri));
}

node const get(int a, int b) {
    return get_node(a, b+1, 1, 0, height);
}

int binarySearch(const vector<int>& seq, int ele) {
    int low = 0;
    int high = (int)seq.size() - 1;
    while(low != high) {
        int mid = (low + high) / 2;
        if (seq[mid] < ele) low = mid + 1;
        else high = mid;
    }
    return low;
}

vector<node> constructDP(vector<int> seq, int n, int m, int l)
{
    vector<node> dp(n);
    for (int i = 0; i < n; ++i) {
        auto l_seq = get(0, seq[i]-1);
        l_seq.first += 1;

        auto r_seq = get(seq[i], m-1);
        r_seq.first += 1 - l;
        r_seq.second.first += 1;
        r_seq.second.second += 1;

        dp[i] = merge(l_seq, r_seq);
        set_node(seq[i], dp[i]);
    }
    return dp;
}

int __LISK(vector<int> seq, int k) {
    vector<int> seq_zip = seq;
    sort(seq_zip.begin(), seq_zip.end());
    seq_zip.erase(unique(seq_zip.begin(), seq_zip.end()), seq_zip.end());

    for (auto& v : seq) v = binarySearch(seq_zip, v) + 1;

    int n = seq.size();
    int m = seq_zip.size() + 1;
    int l0 = 0;
    int l1 = n;
    while(1) {
        int l = (l0 + l1) / 2;
        init(m);
        if (l > 0) set_node(0, {0, {0, 0}});
        else set_node(0, {0, {0, inf}});

        vector<node> dp= constructDP(seq,n,m,l);

        auto offset = get(0, m-1);
        if (offset.second.second < k) {
            l1 = l - 1;
        } else if (offset.second.first > k) {
            l0 = l + 1;
        } else {
            ll r = offset.first + 1;
            int v = m;
            int b = k;
            int res=0;
            for (int i = n-1; i >= 0; --i) {
                if (seq[i] < v) {
                    if (r == dp[i].first + 1 && dp[i].second.first <= b && b <= dp[i].second.second) {
                        res++;
                        r -= 1;
                        v = seq[i];
                    }
                } else {
                    if (r == dp[i].first + 1 - l && dp[i].second.first <= b-1 && b-1 <= dp[i].second.second) {
                        res++;
                        r -= 1 - l;
                        v = seq[i];
                        --b;
                    }
                }
            }
            return res;
        }
    }
}

int main() {
/*
    ifstream  file;
    file.open("input40.txt");

    int n, k;
    file >> n >> k;

    vector<int> seq(n);
    for (int i = 0; i < n; ++i) file >> seq[i];
*/

    int n, k;
    cin >> n >> k;

    vector<int> seq(n);
    for (int i = 0; i < n; ++i) cin >> seq[i];

    cout<<__LISK(seq, k)<<endl;
    return 0;
}