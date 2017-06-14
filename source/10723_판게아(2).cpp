#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<algorithm>

using namespace std;
typedef long long ll;

template<class T>
struct splnode {
	typedef splnode<T> node_t;
	typedef pair<T, pair<int, int>> edge;

	int idx;
	edge e;
	pair<T, int> dp;

	node_t* P;
	node_t* C[2];

	int flip;
	node_t* pp;

	splnode(int id) : idx(id), P(NULL), flip(0), pp(NULL), e(), dp(){
		C[0] = C[1] = NULL;
		fix();
	}

	splnode(int id, int u, int v, ll c) : idx(id), P(NULL), flip(0), pp(NULL), e({ c, { u, v } }), dp(){
		C[0] = C[1] = NULL;
		fix();
	}

	splnode(const splnode& other){
		idx = other.idx;
		e = other.e;
		dp = other.dp;
		P = other.P;
		for (int i = 0; i < 2; i++) C[i] = other.C[i];
		flip = other.flip;
		pp = other.pp;
	}

	/* Fix the parent pointers of our children.  Additionally if we have any
	* extra data we're tracking (e.g. sum of subtree elements) now is the time to
	* update them (all of the children will already be up to date). */
	void fix() {
		dp = { e.first, idx };
		for (int i = 0; i < 2; i++){
			if (C[i]){
				C[i]->P = this;
				dp = max(dp, C[i]->dp);
			}
		}
	}

	/* Push the flip bit down the tree. */
	void push_flip() {
		if (!flip) return;
		flip = 0;
		swap(C[0], C[1]);
		if (C[0]) C[0]->flip ^= 1;
		if (C[1]) C[1]->flip ^= 1;
	}

	/* Return the direction of this relative its parent. */
	int up() {
		return !P ? -1 : (P->C[0] == this ? 0 : 1);
	}

	/* Simple zig step in the 'c' direction when we've reached the root. */
	void zig(int c) {
		node_t* X = C[c];
		if (X->P = P) P->C[up()] = X;
		C[c] = X->C[1 - c];
		X->C[1 - c] = this;
		fix(); X->fix();
		if (P) P->fix();
		swap(pp, X->pp);
	}

	/* Zig zig in the 'c' direction both times. */
	void zigzig(int c) {
		node_t* X = C[c];
		node_t* Y = X->C[c];
		if (Y->P = P) P->C[up()] = Y;
		C[c] = X->C[1 - c];
		X->C[c] = Y->C[1 - c];
		Y->C[1 - c] = X;
		X->C[1 - c] = this;
		fix(); X->fix(); Y->fix();
		if (P) P->fix();
		swap(pp, Y->pp);
	}

	/* Zig zag first in the 'c' direction then in the '1-c' direciton. */
	void zigzag(int c) {
		node_t* X = C[c];
		node_t* Y = X->C[1 - c];
		if (Y->P = P) P->C[up()] = Y;
		C[c] = Y->C[1 - c];
		X->C[1 - c] = Y->C[c];
		Y->C[1 - c] = this;
		Y->C[c] = X;
		fix(); X->fix(); Y->fix();
		if (P) P->fix();
		swap(pp, Y->pp);
	}

	/* Splay this up to the root.  Always finishes without flip set. */
	node_t* splay() {
		for (push_flip(); P;) {
			/* Reorganize flip bits so we can rotate as normal. */
			if (P->P) P->P->push_flip();
			P->push_flip();
			push_flip();

			int c1 = up();
			int c2 = P->up();
			if (c2 == -1) {
				P->zig(c1);
			}
			else if (c1 == c2) {
				P->P->zigzig(c1);
			}
			else {
				P->P->zigzag(c2);
			}
		}
		return this;
	}

	/* Return the max element of the subtree rooted at this. */
	node_t* last() {
		push_flip();
		return C[1] ? C[1]->last() : splay();
	}

	/* Return the min element of the subtree rooted at this. */
	node_t* first() {
		push_flip();
		return C[0] ? C[0]->first() : splay();
	}
};

template<class T>
struct linkcut {
	typedef splnode<T> node_t;
	typedef pair<T, pair<int, int>> edge;

	linkcut(int n){
		for (int i = 0; i < n; i++) node.emplace_back(i);
	}

	void link(int u, int v) {
		make_root(v);
		node[v].pp = &node[u];
	}

	void cut(int u, int v) {
		make_root(u);
		node[v].splay();
		if (node[v].pp) {
			node[v].pp = NULL;
		}
		else {
			node[v].C[0]->P = NULL;
			node[v].C[0] = NULL;
			node[v].fix();
		}
	}

	/* Move u to root of represented tree. */
	void make_root(int u) {
		access(u);
		node[u].splay();
		if (node[u].C[0]) {
			node[u].C[0]->P = NULL;
			node[u].C[0]->flip ^= 1;
			node[u].C[0]->pp = &node[u];

			node[u].C[0] = NULL;
			node[u].fix();
		}
	}

	/* Move u to root aux tree.  Return the root of the root aux tree. */
	node_t* access(int u) {
		node_t* x, *pp;
		for (x = node[u].splay(); x->pp; x = pp) {
			pp = x->pp->splay();
			x->pp = NULL;
			if (pp->C[1]) {
				pp->C[1]->P = NULL;
				pp->C[1]->pp = pp;
			}
			pp->C[1] = x;
			pp->fix();
		}
		return x;
	}

	vector<node_t> node;

	void add_edge(int idx){
		pair<int, int> p = node[idx].e.second;
		link(p.first, idx); link(idx, p.second);
	}

	void cut_edge(int idx){
		pair<int, int> p = node[idx].e.second;
		cut(p.first, idx); cut(idx, p.second);
	}

	ll query(int idx){
		edge e = node[idx].e;
		int u = e.second.first, v = e.second.second;
		ll c = e.first;
		if (u == v) return 0;

		make_root(u);
		access(v);
		node[v].splay();

		pair<T, int> dp = node[v].C[0]->dp;
		if (dp.first > c){
			cut_edge(dp.second);
			add_edge(idx);
			return c - dp.first;
		}
		return 0;
	}
};

int main(){
	int T; scanf("%d", &T);
	while (T--){
		int n, m; scanf("%d%d", &n, &m);
		linkcut<ll> lc(n);

		ll here = 0;
		for (int i = 1; i <= n - 1; i++){
			int u; ll c;
			scanf("%d%lld", &u, &c);
			lc.node.emplace_back(lc.node.size(), i, u, c);
			here += c;
		}

		for (int i = 0; i < m; i++){
			int u, v; ll c;
			scanf("%d%d%lld", &u, &v, &c);
			lc.node.emplace_back(lc.node.size(), u, v, c);
		}

		for (int i = n; i <= 2 * n - 2; i++)
			lc.add_edge(i);

		ll ans = 0;
		for (int i = 0; i < m; i++){
			int idx = 2 * n - 1 + i;
			here += lc.query(idx);
			ans ^= here;
		}

		printf("%lld\n", ans);
	}
}