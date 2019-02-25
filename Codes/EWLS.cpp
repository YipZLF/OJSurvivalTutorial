#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

#define cin fin

using namespace std;


struct Edge {
	int s;
	int e;
	int w;
	Edge(){}
	Edge(int ss, int ee, int ww) :s(ss), e(ee), w(ww){}
};

struct node{
	int next;
	int prev;
};

bool Gbar[760][760];
vector<int> G[760];
int weight[760][760];
Edge E[281000];
bool C[760];
bool rC[760];
int dscore[760];
node L[281000];
int uc[760];
int n, m, Csize, Lsize, tabuAdd, tabuDel, ub;
int delta, MaxStep;
int head, tail, UL;


inline int score(int u, int v) {
	return dscore[u] + dscore[v] + weight[u][v];
}

void randomS(int &u, int &v, int s, int e) {
	u = 0;
	v = 0;
	int r = rand() % n + 1;
	int i;
	for (i = r; i <= n; ++i) {
		if (C[i]){
			if (r % 2) {
				if (score(i, e) > 0 && (tabuAdd != i || tabuDel != e)) {
					u = i;
					v = e;
					break;
				}
				if (score(i, s) > 0 && (tabuAdd != i || tabuDel != s)) {
					u = i;
					v = s;
					break;
				}
			}
			else {
				if (score(i, s) > 0 && (tabuAdd != i || tabuDel != s)) {
					u = i;
					v = s;
					break;
				}
				if (score(i, e) > 0 && (tabuAdd != i || tabuDel != e)) {
					u = i;
					v = e;
					break;
				}
			}
		}
	}
	if (u == 0) {
		for (i = 1; i < r; ++i) {
			if (C[i]) {
				if (r % 2) {
					if (score(i, s) > 0 && (tabuAdd != i || tabuDel != s)) {
						u = i;
						v = s;
						break;
					}
					if (score(i, e) > 0 && (tabuAdd != i || tabuDel != e)) {
						u = i;
						v = e;
						break;
					}
				}
				else {
					if (score(i, e) > 0 && (tabuAdd != i || tabuDel != e)) {
						u = i;
						v = e;
						break;
					}
					if (score(i, s) > 0 && (tabuAdd != i || tabuDel != s)) {
						u = i;
						v = s;
						break;
					}
				}
			}
		}
	}
	return;
}


void Exchange(int &u, int &v) {
//cout<<"call Exchange"<<endl;
	u = 0;
	v = 0;
	
	if (!Lsize) {
		u = 1;
		while (!C[u]) ++u;
		v = u;
		return;
	cout<<"E not L"<<endl;
	}
	randomS(u, v, E[L[tail].prev].s, E[L[tail].prev].e);
	//cout<<"random oldest L"<<endl;
	//cout<<"UL = "<<UL<<"  head = "<<head<<endl;
	//UL = tail;
	while (UL != head) {
		UL = L[UL].prev;
		randomS(u, v, E[UL].s, E[UL].e);
		if (u != 0) return;
	}
	UL = L[tail].prev;
	
	
	/*vector<node> temp;
	for (int i = 0; i != m; ++i) {
		if (L[i]) temp.push_back(node(i, E[i].age));
	}
	sort(temp.begin(), temp.end());
	int vec_size = temp.size();
	for (int i = 0; i != vec_size; ++i) {
		randomS(u, v, E[temp[i].num].s, E[temp[i].num].e);
		if (u != 0) {
			temp.clear();
			return;
		}
	}
	temp.clear();*/
	return;
}

void AddPoint(int u) {
//cout<<"Add Point "<<u<<endl;
	C[u] = true;
	++Csize;
	dscore[u] = -dscore[u];
	int vec_size = G[u].size();
	for (int i = 0; i != vec_size; ++i) {
		Edge *Ep = E + G[u][i];
		int e;
		if (Ep->s == u) e = Ep->e;
		else e = Ep->s;
		if (C[e]) dscore[e] += Ep->w;
		else {
			dscore[e] -= Ep->w;
			--uc[e];
			--uc[u];
			--Lsize;
			int ln = L[G[u][i]].next;
			int lp = L[G[u][i]].prev;
			L[ln].prev = lp;
			UL = ln;
			if (head != G[u][i]) L[lp].next = ln;
			else {
				head = ln;
			}
		}
	}
	return;
}

void DelPoint(int u) {
//cout<<"Del Point "<<u<<endl;
	C[u] = false;
	--Csize;
	dscore[u] = -dscore[u];
	int vec_size = G[u].size();
	for (int i = 0; i != vec_size; ++i) {
		Edge *Ep = E + G[u][i];
		int e;
		if (Ep->s == u) e = Ep->e;
		else e = Ep->s;
		if (C[e]) dscore[e] -= Ep->w;
		else {
			dscore[e] += Ep->w;
			++uc[e];
			++uc[u];
			++Lsize;
			L[head].prev = G[u][i];
			L[G[u][i]].next = head;
			head = G[u][i];
			L[head].prev = -1;
		}
	}
	return;
}


void Greedy(){
//cout<<"Greedy"<<endl;
	while (Lsize) {
		int maxu = 0;
		int maxnum;
		for (int i = n; i >= 1; --i) {
			if (!C[i] && dscore[i] > maxu) {
				maxu = dscore[i];
				maxnum = i;
			}
		}
		AddPoint(maxnum);
		
	}
	return;
}


void Remove() {
	while (Csize > ub - delta) {
		int maxd = -1000000;
		int maxn;
		for (int i = 1; i <= n; ++i) {
			if (C[i] && dscore[i] > maxd) {
				maxd = dscore[i];
				maxn = i;
			}
		}
		DelPoint(maxn);
//cout<<"Remove point "<<maxn<<" and its dscoere is "<<maxd<<endl;
	}
	return;
}



int main() {
	ifstream fin;
	fin.open("mc2.in");
	srand(time(0));
	while (cin>>n) {
		delta = 1;
		MaxStep = 30000;
		memset(Gbar, 0, sizeof(Gbar));
		memset(G, 0, sizeof(G));
		memset(E, 0, sizeof(E));
		memset(C, 0, sizeof(C));
		memset(rC, 0, sizeof(rC));
		memset(uc, 0, sizeof(uc));
		memset(L, 0, sizeof(L));
		memset(weight, 0, sizeof(weight));
		memset(dscore, 0, sizeof(dscore));
		Csize = 0;
		cin>>m;
		for (int i = 0; i != m; ++i) {
			int x, y;
			cin>>x>>y;
			Gbar[x][y] = true;
			Gbar[y][x] = true;
		}
		
		int E_cnt = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				if (!Gbar[i][j]) {
					E[E_cnt].s = i;
					E[E_cnt].e = j;
					E[E_cnt].w = 1;
					G[i].push_back(E_cnt);
					G[j].push_back(E_cnt);
					weight[i][j] = 1;
					weight[j][i] = 1;
					E_cnt++;
				}
			}
		}
		m = E_cnt;
		Lsize = m;
		for (int i = 0; i != m; ++i) {
			L[i].next = i+1;
			L[i].prev = i-1;
		}
		L[m].prev = m-1;
		head = 0;
		tail = m;
		UL = L[tail].prev;
		for (int i = 1; i <= n; ++i) {
			dscore[i] = G[i].size();
			uc[i] = dscore[i];
		}
		
		Greedy();
		ub = Csize;
	//	for (int i = 1; i <= n; ++i) {
	//		rC[i] = C[i];
	//		if (!C[i]) cout<<i<<"  ";
	//	}
	//	cout<<endl;
		Remove();	
	
		int ret = 0;
		int step = 0;
		while (step < MaxStep) {
	//cout<<"step = "<<step<<endl;
	
	/*for (int i = head; i != tail; i = L[i].next) {
		cout<<i<<"  "<<L[i].prev<<"  "<<L[i].next<<endl;
	}
	cout<<tail<<"  "<<L[tail].prev<<"  "<<L[tail].next<<endl;*/
	
			int u, v;
			Exchange(u,v);
	//cout<<"Exchange "<<u<<"  "<<v<<endl;
			if (u != 0 && v != 0) {
				DelPoint(u);
				AddPoint(v);
				tabuAdd = v;
				tabuDel = u;
			}
			else {
				for (int i = 0; i != m; ++i) {
					for (int i = head; i != tail; i = L[i].next) {
						++E[i].w;
						++dscore[E[i].s];
						++dscore[E[i].e];
						++weight[E[i].s][E[i].e];
						++weight[E[i].e][E[i].s];
					}
				}
				int rr = rand() % Csize + 1;
				u = 0;
				int i = 0;
				while (rr) {
					u = ++i;
					if (C[u]) --rr;
				}
				rr = rand() % (n - Csize) + 1;
				i = 0;
				while (rr) {
					v = ++i;
					if (!C[v]) --rr;
				}
				DelPoint(u);
				AddPoint(v);
				tabuAdd = v;
				tabuDel = u;
			}
		//cout<<"ub = "<<ub<<"   Csize = "<<Csize<<"   Lsize = "<<Lsize<<"  C+L = "<<Csize+Lsize<<endl;
			if (Csize + Lsize < ub) {
	//	cout<<"ub is                                                       "<<Csize + Lsize<<endl;
				ub = Csize + Lsize;
				ret = Csize;
				for (int i = 1; i <= n; ++i) rC[i] = C[i];
				if (Lsize) {
					vector<int> temp;
					/*for (int i = 0; (i != m) && Lsize; ++i) {
						if (L[i]) {
							temp.push_back(i);
							L[i] = false;
							--Lsize;
							int t = E[i].s;
							rC[t] = true;
							++ret;
							int vec_size = G[t].size();
							for (int j = 0; j != vec_size; ++j) {
								if (!L[G[t][j]]) {
									temp.push_back(G[t][j]);
									L[G[t][j]] = false;
									--Lsize;
								}
							}
						}
					}*/
					while (Lsize) {
						int maxd = -10000;
						int maxn;
						for (int i = head; i != tail; i = L[i].next) {
							if (dscore[E[i].s] > maxd) {
								maxd = dscore[E[i].s];
								maxn = E[i].s;
							}
							if (dscore[E[i].e] > maxd) {
								maxd = dscore[E[i].e];
								maxn = E[i].e;
							}
						}
						rC[maxn] = true;
						AddPoint(maxn);
						temp.push_back(maxn);
					}
					for (int i = 0; i != temp.size(); ++i) DelPoint(temp[i]);
					temp.clear();
				}
				Remove();
			}
			
			++step;
		}
		cout<<n - ub<<endl;
		for (int i = 1; i <= n; ++i) {
			if (!rC[i]) cout<<i<<" ";
		}
		cout<<endl;
	}
	fin.close();
	return 0;
}