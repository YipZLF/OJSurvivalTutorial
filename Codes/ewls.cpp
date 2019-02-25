#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cassert>
#define DEBUG
#define MAXN 760
#define MAXM 250010
#define DELTA 1
#define MAXSTEPS 100

using namespace std;

struct Edge
{
    // s: the other endpoint
    int s;
    // idx: index of this edge
    int idx;
    bool operator<(const Edge &right) const // override by s
    {
        return this->s < right.s;
    }
};

typedef set<Edge> EdgeSet;
typedef EdgeSet::iterator EdgeIter;
typedef set<int> EdgeSet_cG;
typedef EdgeSet_cG::iterator EdgeIter_cG;

// G: graph G, stored with adjacency list
// cG: complementary graph of G
// to find maximum clique on cG is equivalent to find minimum vertex cover in G
vector<EdgeSet> G;
vector<EdgeSet_cG> cG;
// ub: upper bound for MVC
int ub;
// C: candidate set (inC[u] is true iff vertex u is in C)
set<int> C;
bool inC[MAXN];
// Cstar: optimal set
set<int> Cstar;
// weights of edges (retrieved by the idx of edge)
int weights[MAXM];
// dscores of vertices (retrieved by the idx of edge)
int dscores[MAXN];
// the vertex last added to and removed from C
int tabuAdd, tabuRemove;
// n: number of vertices
// m: number of edges
int n, m;

/*
struct Endpoints
{
    int idx;
    int unctime; // the last time of an edge becoming uncovered
    int edp1, edp2;
    bool operator<(const Endpoints &right) const // override by uncovered time
    {
        if (this->edp1 == right.edp1 &&
            this->edp2 == right.edp2 &&
            this->unctime == right.unctime)
            return false;
        else
            return this->unctime < right.unctime;
    }
};*/

struct Endpoints
{
    int idx;
    int unctime; // the last time of an edge becoming uncovered
    int edp1, edp2;
    bool operator<(const Endpoints &op) const // override by uncovered time
    {
        if(this->idx == op.idx)
            return false;
        else{
            if(this->unctime==op.unctime){
                return this->idx < op.idx;
            }else{
                return this->unctime < op.unctime;
            }
        }
    }
};
/*
bool myCmp_edps(const Endpoints&eps1,const Endpoints &edp2){
    return eps1.idx<eps2.idx;
}*/

// mapping from idx of edge to its endpoints
map<int, Endpoints> idx2edps;
// L: uncovered edges
// UL: edges that are unchecked by ChooseExchangePair in current local search stage
set<Endpoints> L, UL;

void add_to_C(int u)
{
    assert(C.count(u) == 0);
    // things to be updated:
    // C, inC, UL, L, dscores
    C.insert(u);
    inC[u] = true;
    dscores[u] = -dscores[u];
    int v, e_idx;
    Endpoints pair;
    for (EdgeIter it = G[u].begin(); it != G[u].end(); ++it)
    {
        v = it->s;
        e_idx = it->idx;
        if (inC[v])
            dscores[v] += weights[e_idx];
        else
        {
            dscores[v] -= weights[e_idx];
            pair = idx2edps[e_idx];
            L.erase(pair);
            if (UL.count(pair))
                UL.erase(pair);
        }

    }
}

// suspicious
void rm_from_C(int u, int unctime)
{
    assert(C.count(u));
    // things to be updated:
    // C, inC, UL,L, dscores
    C.erase(u);
    inC[u] = false;
    dscores[u] = -dscores[u];
    int v, e_idx;
    Endpoints pair;
    for (EdgeIter it = G[u].begin(); it != G[u].end(); ++it)
    {
        v = it->s;
        e_idx = it->idx;
        if (inC[v])
            dscores[v] -= weights[e_idx];
        else
        {
            dscores[v] += weights[e_idx];
            idx2edps[e_idx].unctime = unctime;
            pair = idx2edps[e_idx];
            printf("%d,%d \n", pair.edp1, pair.edp2);
            L.insert(pair);
            UL.erase(pair);
        }
    }
}

// useful array used in add_vertices
// ncover[u] is the number of uncovered edges covered by u
int ncover[MAXN];

void add_vertices()
{
    // greedy strategy:
    // choose a vertex that covers most uncovered edges each time
    memset(ncover, 0, sizeof(ncover));
    for (set<Endpoints>::iterator it = L.begin(); it != L.end(); ++it)
    {
        ncover[it->edp1]++;
        ncover[it->edp2]++;
    }
    int u, v;
    while (!L.empty())
    {
        u = max_element(ncover, ncover + n) - ncover;
        // TODO: break ties randomly
        add_to_C(u);
        // update ncover
        ncover[u] = 0;
        for (EdgeIter it = G[u].begin(); it != G[u].end(); ++it)
        {
            v = it->s;
            if (!inC[v])
                ncover[v]--;
        }
    }
}

bool myCmp(int a, int b)
{
    // using this version of compare, the negative integer
    // with the smallest absolute value is reckoned the "largest"
    if ((a >= 0 && b >= 0) ||
        (a < 0 && b < 0))
        return a < b;
    else if (a < 0)
        return false;
    else
        return true;
}

void rm_vertices(int delta, int unctime)
{
    // remove some vertices from C
    int u;
    for(set<int>::iterator it = C.begin();it!=C.end();++it){
        if(dscores[*it]==0)
            C.erase(*it);
    }
    while (ub - C.size() < delta)
    {
        u = max_element(dscores, dscores + n, myCmp) - dscores;
        #ifdef DEBUG
        printf("current u is %d,%d\n",u,dscores[u]);
        
        #endif
        rm_from_C(u, unctime);
    }
}

int score(int u, int v)
{

    assert(C.count(u) != 0 && C.count(v) == 0);
    // calculate score(u,v)
    Edge edge;
    edge.s = v;
    EdgeIter it = G[u].find(edge);
    if (it != G[u].end())
    {
        int e_idx = it->idx;
        return dscores[u] + dscores[v] + weights[e_idx];
    }
    return dscores[u] + dscores[v];
}

// save results in *u and *v
// if not found, set *u=*v=-1
void ChooseExchangePair(int *u, int *v)
{
    int tempu, tempv;

    // get the oldest edge (v1*,v2*) in L
    set<Endpoints>::iterator edps = L.begin();
    printf("%d", edps->idx);
    int vstar1 = edps->edp1;
    int vstar2 = edps->edp2;
    // get S set
    Endpoints pair;
    int k = 0;
    map<int, Endpoints> S;
    for (set<int>::iterator it = C.begin(); it != C.end(); ++it)
    {
        int uinC = *it;
        if (uinC == tabuRemove)
            continue;
        pair.edp1 = uinC;
    #ifdef DEBUG
    printf("uinC:%d  vstar1: %d \n ",uinC,vstar1);
    #endif 
        if (vstar1 != tabuAdd && score(uinC, vstar1) > 0)
        {
            pair.edp2 = vstar1;
            S[k++] = pair;
        }
        if (vstar2 != tabuAdd && score(uinC, vstar2) > 0)
        {
            pair.edp2 = vstar2;
            S[k++] = pair;
        }
    }

    if (!S.empty())
    {
        // set (u*, v*) = random(S)
        int sidx = rand() % S.size();
        *u = S[sidx].edp1;
        *v = S[sidx].edp2;
        return;
    }

    // foreach e(v1, v2) ∈ UL, from old to young
    for (set<Endpoints>::iterator edps = UL.begin(); edps != UL.end(); ++edps)
    {
        int v1 = edps->edp1;
        int v2 = edps->edp2;
        S.clear();
        k = 0;
        for (set<int>::iterator it = C.begin(); it != C.end(); ++it)
        {
            int uinC = *it;
            if (uinC == tabuRemove)
                continue;
            pair.edp1 = uinC;
            if (v1 != tabuAdd && score(uinC, v1) > 0)
            {
                pair.edp2 = v1;
                S[k++] = pair;
            }
            if (v2 != tabuAdd && score(uinC, v2) > 0)
            {
                pair.edp2 = v2;
                S[k++] = pair;
            }
        }
        if (!S.empty())
        {
            // set (u*, v*) = random(S)
            int sidx = rand() % S.size();
            *u = S[sidx].edp1;
            *v = S[sidx].edp2;
            return;
        }
    }

    *u = *v = -1;
    return;
}

void ewls(int delta, int maxSteps)
{
    // graph G is stored as global variable
    // delta: adjust size of C
    // maxSteps: maximum number of steps
    int i, j, k;
    int u, v;
    int size = 0;
    int step = 0;
    L.clear();
    for (j = 0; j < m; ++j)
        L.insert(idx2edps[j]);
    UL = L;
    // initialize weights and dscores
    for (j = 0; j < m; ++j)
        weights[j] = 1;
    for (i = 0; i < n; ++i)
        dscores[i] = G[i].size();
    // initialize C and inC
    #ifdef DEBUG
    for(int i = 0 ; i < n ; ++i){
              printf("dscores[%d] is %d\n",i,dscores[i]);
}  
    #endif
    C.clear();
    memset(inC, false, sizeof(inC));
    // construct C greedily until it's a vertex cover
    while (L.size() > 0)
    {
        u = max_element(dscores, dscores + n) - dscores;
        // TODO: break ties randomly
        add_to_C(u);
    }
    
        #ifdef DEBUG
        printf("L size is %d\n",L.size());
        #endif
    ub = C.size();
    
        #ifdef DEBUG
        printf("C,ub size is %d\n",ub);
        #endif
    Cstar = C;
    #ifdef DEBUG
    for(int i = 0 ; i < n ; ++i){
              printf("dscores[%d] is %d\n",i,dscores[i]);
}  
    #endif
    // remove some vertices from C
    rm_vertices(delta, step);

    // core loop
    tabuAdd = tabuRemove = -1;
    while (step < maxSteps)
    {
        ChooseExchangePair(&u, &v);
        #ifdef DEBUG
            printf("%d %d\n",u,v);
        #endif
        if (u == -1 && v == -1)
        {
            // update weights of edges in L
            for (set<Endpoints>::iterator it = L.begin(); it != L.end(); ++it)
            {
                int idx = it->idx;
                weights[idx]++;
            }
            #ifdef DEBUG
            printf(" C size is %d \n",C.size());
            #endif 
            // randomly choose u and v
            int r1 = rand() % C.size(),
                r2 = rand() % L.size(),
                r3 = rand() % 2;
            for (set<int>::iterator it = C.begin(); it != C.end(); ++it)
                if (0 == r1--)
                {
                    u = *it;
                    break;
                }
            for (set<Endpoints>::iterator it = L.begin(); it != L.end(); ++it)
            {
                int idx = it->idx;
                //weights[idx]++;
                if (0 == r2--)
                {
                    v = r3 == 0 ? idx2edps[idx].edp1 : idx2edps[idx].edp2;
                    break;
                }
            }
            UL = L;
        }
        else
        {
            // set tabu
            tabuAdd = u;
            tabuRemove = v;
        }
        // update C := C\{u}U{v}

        //to be debugged
        rm_from_C(u, step);
        add_to_C(v);

        // whether a new upper bound is found
        if (C.size() + L.size() < ub)
        {
            ub = C.size() + L.size();
            if (!L.empty())
            //to be debugged
                add_vertices();
            Cstar = C;
            rm_vertices(delta, step);
        }

        ++step;
    }
}

int main(int argc, char const *argv[])
{
    freopen("./mc2.in", "r", stdin);
    srand(time(NULL)); // set random seeds
    int i, j, k;
    int u, v;
    Edge curr_e;
    Endpoints curr_edps;
    while (scanf("%d%d", &n, &j) != EOF)
    {
        // new test case
        // initialize cG and G
        G.clear();
        cG.clear();
        G.resize(n);
        cG.resize(n);

        // read cG
        for (; j > 0; --j)
        {
            scanf("%d%d", &u, &v);
            --u;
            --v;
            if (u == v || cG[u].count(v)) // self-loop or multiple edges
                continue;
            cG[u].insert(v);
            cG[v].insert(u);
        }

        // obtain G
        idx2edps.clear();
        k = 0;
        for (u = 0; u < n; ++u)
        {
            v = u + 1;
            for (EdgeIter_cG it = cG[u].begin(); it != cG[u].end(); ++it)
            {
                while (v < *it)
                {
                    curr_e.idx = k;
                    curr_e.s = v;
                    G[u].insert(curr_e);
                    curr_e.s = u;
                    G[v].insert(curr_e);
                    curr_edps.idx = k;
                    curr_edps.edp1 = u;
                    curr_edps.edp2 = v;
                    curr_edps.unctime = 0;
                    idx2edps[k] = curr_edps; 
                    ++k;
                    ++v;
                }
                if (v == *it)
                    ++v;
            }
            while(v < n)
            {
                curr_e.idx = k;
                curr_e.s = v;
                G[u].insert(curr_e);
                curr_e.s = u;
                G[v].insert(curr_e);
                curr_edps.idx = k;
                curr_edps.edp1 = u;
                curr_edps.edp2 = v;
                curr_edps.unctime = 0;
                idx2edps[k] = curr_edps;
                ++k;
                ++v;
            }
        }
        // reset m 
        m = k;
        // search

        ewls(DELTA, MAXSTEPS);
        // print results
        printf("%d\n", n - Cstar.size());
        for (u = 0; u < n; ++u)
            if (inC[u] == false)
                printf("%d ", u + 1);
        printf("\n");
    }

    return 0;
}