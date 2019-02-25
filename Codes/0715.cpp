#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 110;
const int INF = 1 << 20;

struct Point {
    double x, y;
};

struct Edge {
    int sta, end;
    double weight;
};

double dist(Point one, Point two) {
    return sqrt(pow((one.x - two.x),2) + pow((one.y - two.y),2));
}

Point vertices[MAXN];
Edge edges[MAXN*MAXN];


double Directed_MST(int root, int V, int E) {
    int Pre[V], ID[V];
    double In[V];
    double ret = 0;
    while(true) {
        //find the minimal edge
        for(int i = 0; i < V; ++i) {
            In[i] = INF;
        }
        for(int i = 0; i < E; ++i) {
            int end = edges[i].end;
            int sta = edges[i].sta;
            if(edges[i].weight < In[end]) {
                In[end] = edges[i].weight;
                Pre[end] = sta;
            }
        }
        //detect if there is a spanning tree
        for(int i = 0; i < V; ++i) {
            if(i == root) continue;
            if(In[i] == INF) return -1;
        }
        //find the cycles
        int cntVex = 0;
        memset(ID, -1, sizeof(ID));
        //root has no income edge
        In[root] = 0;
        //mark the new id for each vertex
        for(int i = 0; i < V; ++i) {
            ret += In[i];
            int beg = i;
            //find a cycle contians i
            while(Pre[beg] != i && ID[beg] == -1 && beg != root) {
                beg = Pre[beg];
            }
            //if there is a cycle, mark new ID of the vertex in the cycle
            if(beg != root && ID[beg] == -1) {
                for(int j = Pre[beg]; j != beg; ++j) {
                    ID[j] = cntVex;
                }
                ID[beg] = cntVex++;
            }
        }
        //no cycles
        if(cntVex == 0) break;
        //mark new ID for the vertices outside the cycles
        for(int i = 0; i < V; ++i) {
            if(ID[i] == -1) {
                ID[i] = cntVex++;
            }
        }
        //contract the cycles and remark the graph
        for(int i = 0; i < E; ++i) {
            int end = edges[i].end;
            edges[i].sta = ID[edges[i].sta];
            edges[i].end = ID[edges[i].end];
            if(edges[i].sta != edges[i].end) {
                edges[i].weight -= In[end];
            }
        }
        V = cntVex;
        root = ID[root];
    }
    return ret;
}

int main() {
    freopen("0715.in","r",stdin);
    int n, m, x, y, one, two;
    while(cin.peek() != EOF && cin >> n >> m) {
        for(int i = 0; i < n; ++i) {
            cin >> x >> y;
            vertices[i].x = x;
            vertices[i].y = y;
        }
        for(int i = 0; i < m; ++i) {
            cin >> one >> two;
            edges[i].sta = one-1;
            edges[i].end = two-1;
            if(one != two){
                edges[i].weight = dist(vertices[one-1], vertices[two-1]);
            } else {
                edges[i].weight = INF;
            }
        }
        double ans = Directed_MST(0, n, m);
        if(ans == -1) {
            cout << "NO\n";
        } else {
            cout << fixed << setprecision(2) << ans << endl;
        }
    }
    return 0;
}
