#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;

class graph {
protected:
	vector<bool> used;
	ll n = 0;
public:
	graph(ll n) : n(n) {}
	virtual vector<ll> get_connected_vertices(ll u) = 0;
	virtual bool are_vertices_connected(ll u, ll v) = 0;
	void dfs(ll u, bool flag = false) {
		if (flag) {
			used.clear();
			used.resize(n);
		}
		used[u] = true;
		auto list = get_connected_vertices(u);
		for (auto x : list)
			if (!used[x])
				dfs(x);
	}
	void bfs(ll u) {
		used.clear();
		used.resize(n);
		queue<ll> q;
		q.push(u);
		while (!q.empty()) {
			u = q.front();
			q.pop();
			auto list = get_connected_vertices(u);
			for (auto x : list) {
				if (!used[x]) {
					used[x] = true;
					q.push(x);
				}
			}
		}
	}
};

class list_graph : public graph {
	vector<vector<ll>> list;
public:
	list_graph(vector<pair<ll, ll>> edges, ll n) : graph(n) {
		list.resize(n);
		for (const auto& edge : edges)
			list[edge.first].push_back(edge.second);
	}
	vector<ll> get_connected_vertices(ll u) {
		return list[u];
	}
	bool are_vertices_connected(ll u, ll v) {
		for (auto x : list[u])
			if (x == v)
				return true;
		return false;
	}
};

class list_matrix : graph {
	vector<vector<bool>> matrix;
public:
	list_matrix(vector<pair<ll, ll>> edges, ll n) : graph(n) {
		matrix.resize(n, vector<bool>(n));
		for (const auto& edge : edges)
			matrix[edge.first][edge.second] = true;
	}
	vector<ll> get_connected_vertices(ll u) {
		vector<ll> res;
		for (ll i = 0; i < n; i++)
			if (matrix[u][i] == 1)
				res.push_back(i);
		return res;
	}
	bool are_vertices_connected(ll u, ll v) {
		return matrix[u][v];
	}
};

int main() {
	
}