/*
MC EWLS算法
组员：叶子凌锋、曹颖康、马清川、俞一凡
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>

#define DELTA 1
#define MAXSTEPS 10

using namespace std;
const int MAXE = 260000;
const int MAXV =  800;
int eNum;
int vNum;

int tabuAdd, tabuRemove;

struct node {
    vector<int> edge;
    node() { }
};
set<int> C;
/*
使用邻接矩阵存图
*/
node N[MAXV];
bool G[MAXV][MAXV];       
bool inC[MAXV];
bool inS[MAXV];          
int edge[MAXV][MAXV];     

struct Edge {
    /*
    pPrev和pSucc分别表示前继和后继
    */
    bool isCovered;
    int edp1;
    int edp2;
    int w;
    Edge * pPrev;
    Edge * pSucc;
    void init(int u, int v) {
        edp1 = u;
        edp2 = v;
        isCovered = false;
        pPrev = NULL;
        pSucc = NULL;
        w = 1;
    }
    Edge() {
        isCovered = false;
        pPrev = NULL;
        pSucc = NULL;
        w = 1;
    }
    Edge(int u, int v) : edp1(u), edp2(v) {
        isCovered = false;
        pPrev = NULL;
        pSucc = NULL;
        w = 1;
    }
};

int w[MAXE];
Edge myEdge[MAXE];
int dscore[MAXE];

// 使用双向链表
// 记录L和UL
struct doubleList {
    Edge * head;
    Edge * tail;
    Edge * pUnchecked;
    int size;
    doubleList() {
        size = 0;
        head = new Edge();
        tail = new Edge();
        pUnchecked = head;
        head->pPrev = NULL;
        head->pSucc = tail;
        tail->pPrev = head;
        tail->pSucc = NULL;
    }

    //双向链表的操作
    void init();
    void insert(Edge *);
    void remove(Edge *);
    bool empty();
    void update(int, int);
    ~doubleList() {
        if (head) {
            delete head;
        }
        if (tail) {
            delete tail;
        }
    }
}L;

void doubleList::insert(Edge * e) {
    if (head->pSucc != tail) {
        e->pSucc = head->pSucc;
        head->pSucc->pPrev = e;
    }
    else {  
        // e是L中第一条边
        e->pSucc = tail;
        tail->pPrev = e;
        pUnchecked = e;      
    }
    head->pSucc = e;
    e->pPrev = head;
    size ++;
}
void doubleList::init() {
    size = 0;
    head->pPrev = NULL;
    head->pSucc = tail;
    tail->pPrev = head;
    tail->pSucc = NULL;
}
void doubleList::update(int addv, int removev) {
    if (addv != -1) {
        for (int i = 0; i < N[addv].edge.size(); ++i) {
            int e = N[addv].edge[i];
            if (!myEdge[e].isCovered) {    
                // 原来未覆盖的边变成覆盖
                myEdge[e].isCovered = true;
                remove(&myEdge[e]);
            }
        }
    }
    if (removev != -1) {
        for (int i = 0; i < N[removev].edge.size(); ++i) {
            int e = N[removev].edge[i];
            int v1 = myEdge[e].edp1;
            int v2 = myEdge[e].edp2;
            if (myEdge[e].isCovered && inC[v1] == 0 && inC[v2] == 0) {
                // 原来覆盖的边变成未覆盖
                myEdge[e].isCovered = false;
                insert(&myEdge[e]);
            }
        }
    }
}
void doubleList::remove(Edge *e) {
    e->pPrev->pSucc = e->pSucc;
    e->pSucc->pPrev = e->pPrev;
    if (pUnchecked == e) {   
        pUnchecked = e->pPrev;
    }
    size --;
}
bool doubleList::empty() {
    if(size)
        return true;
    else 
        return false;
}


void add(int v)
{
    C.insert(v);
    inC[v] = 1;
    dscore[v] = -dscore[v]; // update dscore.
    int i,e,n;
    
    int edge_count = N[v].edge.size();
    
    for (i=0; i<edge_count; ++i)
    {
        e = N[v].edge[i];
        n = myEdge[e].edp1 == v ? myEdge[e].edp2 : myEdge[e].edp1;
        
        if (inC[n] == 0)//this adj isn't in cover set
        {
            dscore[n] -= myEdge[e].w;
        }
        else
        {
            dscore[n] += myEdge[e].w;
        }
    }
}

void remove(int v)
{
    C.erase(v);
    inC[v] = 0;
    dscore[v] = -dscore[v];

    
    int i,e,n;
    int edge_count = N[v].edge.size();
    for (i=0; i < edge_count; ++i)
    {
        e = N[v].edge[i];
        n = myEdge[e].edp1 == v ? myEdge[e].edp2 : myEdge[e].edp1;
        
        if (inC[n]==0)
        {
            dscore[n] += myEdge[e].w;
       }
        else
        {
            dscore[n] -= myEdge[e].w;
        }
    }
}
int score(int u, int v) { 
    int s = dscore[u] + dscore[v];
    if (edge[u][v] >= 0) {
        s += w[edge[u][v]];
    }
    return s;
}


pair<int, int> ChooseExchangePair() {
    set<pair <int, int> > S;
     
    Edge * token = L.tail->pPrev; 
    if (token != L.head) {
        for (set<int>::iterator it = C.begin(); it != C.end(); it++) {
            if (score(*it, token->edp1) > 0) {
                S.insert(make_pair(*it, token->edp1));
            }
            if (score(*it, token->edp2) > 0) {
                S.insert(make_pair(*it, token->edp2));
            }
        }
    }
    if (S.size() != 0) {

        if (*S.begin() != make_pair(tabuRemove, tabuAdd)) {
            return *S.begin();
        }
        else {
            if (*S.rbegin() != make_pair(tabuRemove, tabuAdd)) {
                return *S.rbegin();
            }
        }
    }
    // 当L中年龄最大的边不满足条件时，从UL中按照年龄从大到小搜索
    while (L.pUnchecked != L.head) {
        Edge * it = L.pUnchecked;
        L.pUnchecked = L.pUnchecked->pPrev;
        for (set<int>::iterator it2 = C.begin(); it2 != C.end(); it2++) {
            if (score(*it2, it->edp1) > 0) {
                S.insert(make_pair(*it2, it->edp1));
            }
            if (score(*it2, it->edp2) > 0) {
                S.insert(make_pair(*it2, it->edp2));
            }
        }
        if (S.size() != 0) {
            if (*S.begin() != make_pair(tabuRemove, tabuAdd)) {
                return *S.begin();
            }
            else {
                if (*S.rbegin() != make_pair(tabuRemove, tabuAdd)) {
                    return *S.rbegin();
                }
            }
        }
    }
    //如果找不到的话
    return make_pair(0, 0);
}

set<int> CC;
void buildC() {
    int temp;
    for (int i = 0; i < eNum; i++) {
        if (myEdge[i].isCovered == 0) {
            int v1 = myEdge[i].edp1;
            int v2 = myEdge[i].edp2;
            if (inC[v1]) {
                temp = v2;
            }
            else {
                temp = v1;
            }
            add(temp);
            L.update(temp, -1);
        }
    }
}

void expandC() {    
// 把C扩展成一个点覆盖
    Edge * p = L.tail->pPrev;
    while (p != L.head) {   // 将L中所有边都覆盖
        int v1 = p->edp1;
        int v2 = p->edp2;
        p = p->pPrev;
        if (inC[v1] == 0 && inC[v2] == 0) {
            int v1d = N[v1].edge.size();  // v1连边个数
            int v2d = N[v2].edge.size();
            if (v1d > v2d) {
                C.insert(v1);
                inC[v1] = 1;
            }
            else {
                C.insert(v2);
                inC[v2] = 1;
            }
        }
    }
}

void update_inC() {      // 重置inC 即标记C中顶点
    memset(inC, 0, sizeof(inC));
    for (auto & i : C) {
        inC[i] = 1;
    }
}

set<int> ewls() {
    /*
    算法核心：返回一个集合S
    // DELTA: adjust size of C
    // MAXSTEPS: maximum number of steps
    */
    int step = 0;
    for (int i = 0; i < eNum; i++) {
        L.insert(&myEdge[i]);
    }
    C.clear();
    buildC();
    int ub = C.size();
    set<int> CFinal = C;
    int max = -999999;
    int res = -1;
    for (int i = 0; i < DELTA; i++) {
        max = -999999;
        // greedy strategy:
    // choose a vertex that covers most uncovered edges each time
        for (set<int>::iterator it = C.begin(); it != C.end(); it++) {
            if (dscore[*it] > max) {
                max = dscore[*it];
                res = *it;
            }
        }
        remove(res);
        L.update(-1, res);
    }
    
    while (step < MAXSTEPS * vNum) {
        pair<int, int> exchangePair;
        if ((exchangePair = ChooseExchangePair()) != make_pair(0, 0)) {
            int u = exchangePair.first;
            int v = exchangePair.second;
            //            C.erase(u);
            //            C.insert(v);
            remove(u);
            add(v);
            tabuAdd = u;
            tabuRemove = v;
            L.update(v, u);
        }
        else {
            Edge * p = L.head->pSucc;
            Edge * k = p;
            while(p != L.tail) {
                if (!p->isCovered) {
                    p->w++;
                    // 更新w(e)的同时要更新dscore
                    int v1 = p->edp1;
                    int v2 = p->edp2;
                    dscore[v1]++;
                    dscore[v2]++;
                    k = p;
                }
                p  = p->pSucc;
            }
            // int randSub = rand() % C.size();
            // set<int>::const_iterator it(C.begin());
            // advance(it, randSub);
            // int dv = *it;
            int dv = *C.rbegin();
            //            C.erase(*it);
            //            C.insert(myEdge[k].edp1);
            remove(dv);
            add(k->edp1);
            L.update(k->edp1, dv);
        }
        if (C.size() + L.size < ub) {
            ub = C.size() + L.size;
            // update_UL();
            if (L.empty()) CFinal = C;
            else {
                CC = C;
                // buildC();
                expandC();
                ub = C.size();      // update ub.(一个顶点v可能覆盖L中多条边 所以ub可以进一步改进)
                CFinal = C;
                C = CC;
                update_inC();
            }
            int decNum = C.size() - (ub - DELTA);
            if (ub <= DELTA) {
                decNum = 1;
            }
            for (int i = 0; i < decNum; i++) {
                max = -999999;
                for (set<int>::iterator it = C.begin(); it != C.end(); it++) {
                    if (dscore[*it] > max) {
                        max = dscore[*it];
                        res = *it;
                    }
                }
                //                C.erase(res);
                remove(res);
                L.update(-1, res);
            }
        }
        step++;
    }
    return CFinal;
}
void buildG(int n, int m) {

    vNum = n;
    eNum = 0;
    C.clear();
    memset(inC, NULL, sizeof(inC));
    memset(inS, NULL, sizeof(inS));
    for (int i = 0; i < MAXV; ++i) {
        for (int j = 0; j < MAXV; ++j) {
            edge[i][j] = -1;
            G[i][j] = 1;
        }
    }
    L.init();
    for (int i = 0; i < MAXV; ++i) {
        N[i].edge.clear();
    }

    // 求补图
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 0;
    }
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (G[u][v] == 1) {
                int i = eNum;
                edge[u][v] = edge[v][u] = i;
                myEdge[i].init(u, v);
                w[i] = 1;
                N[u].edge.push_back(i);
                N[v].edge.push_back(i);
                eNum ++;
            }
        }
    }
    for (int i = 1; i <= n; ++i){
        // dscore[v]表示从C中删除/增加v对cost的变化的负数
        // 初始dscore[v]即v上连边数
        dscore[i] = N[i].edge.size();
    }
}
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        buildG(n, m);
        set<int> S = ewls();
        printf("%d\n", n - (int)S.size());
        for (auto & r : S) {
            inS[r] = true;
        }
        // 最小点覆盖的余集就是最大团
        for (int i = 1; i <= n; ++i) {
            if (!inS[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }
    return 0;
}