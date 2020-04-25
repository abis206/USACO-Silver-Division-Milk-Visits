#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int, int>
#define S second
#define F first
using namespace std;
const int MAXN = 100005;
typedef long long ll;
vector<int> adj[100005];
int dis[20][100005];
int lev[100005];
int n;
string s;
int H[100005];
int G[100005];
void DFS(int ver, int par = -1){
    if(s[ver-1] == 'G')
        G[ver]++;
    else
        H[ver]++;
    for(auto node : adj[ver]){
        if(node == par)continue;
        lev[node] = lev[ver] + 1;
        dis[0][node] = ver;
        G[node] += G[ver];
        H[node] += H[ver];
        DFS(node, ver);
    }
}
int lca(int X, int Y){
    if(lev[X] < lev[Y])
        swap(X, Y);
    for(int i=19;i>=0;i--){
        int x = dis[i][X];
        if(x != -1 && lev[x] >= lev[Y]){
            X = x;
        }
    }
    if(X == Y)
        return X;
    for(int i=19;i>=0;i--){
        int x = dis[i][X];
        int y = dis[i][Y];
        if(x != -1 && y != -1 &&x != y){
            X = x;
            Y = y;
        }
    }
    return dis[0][X];
}
void build(){
    for(int i=1;i<20;i++){
        for(int j=1;j<=n;j++){
            int x = dis[i-1][j];
            if(x == -1)continue;
            dis[i][j] = dis[i-1][x];
        }
    }
}
int main(){
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    memset(dis, -1, sizeof(dis));
    int m;
    cin>>n>>m>>s;
    for(int i=1;i<n;i++){
        int x, y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    lev[1] = 1;
    DFS(1);
    build();
    while(m--){
        int x, y;
        char c;
        cin>>x>>y>>c;
        int node = lca(x, y);
        int h = 0, g = 0;
        if(node == 1){
            h = H[x] + H[y] - H[node];
            g = G[x] + G[y] - G[node];
        }
        else{
            h = H[x] + H[y] - H[node];
            h -= H[dis[0][node]];
            g = G[x] + G[y] - G[node];
            g -= G[dis[0][node]];
        }
        if(c == 'G'){
            cout<<(g>=1)?1:0;
        }
        else{
            cout<<(h>=1)?1:0;
        }
    }
    return 0;
}

