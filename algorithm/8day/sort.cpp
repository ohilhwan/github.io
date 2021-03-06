#include <iostream>
#include <vector>
#include <cstdio>

#include <queue>

#define MAX_NODE 100000
#define MAX_EDGE 200000
#define INF 987654321

#define MIN(a, b) ((a)>(b)?(b):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))

using namespace std;
typedef long long ll;
/*
struct node { 
	int i;
	ll d;
};

struct pqueue{
	node heap[MAX_NODE*100];
	int size;

	pqueue() {
		size = 0;
	}

	void push(int i, ll d) {
		heap[++size].i = i;
		heap[size].d = d;
		
		int cur = size;
		while (cur > 1 && heap[cur].d < heap[cur/2].d) {
			node tmp = heap[cur];
			heap[cur] = heap[cur / 2];
			heap[cur / 2] = tmp;

			cur /= 2;
		}
	}

	node pop() {
		node ret = heap[1];
		heap[1] = heap[size--];
		
		int cur = 1;
		while (true) {
			int child = cur * 2;
			if (child < size && heap[child].d > heap[child + 1].d) child++;
			if (child > size || heap[child].d < heap[cur].d) break;

			node tmp = heap[cur];
			heap[cur] = heap[child];
			heap[child] = tmp;

			cur = child;
		}

		return ret;
	}

	bool empty() {
		return (size == 0);
	}

	void print() {
		cout << "pq\n";
		for (int i = 1; i <= size; i++) {
			cout << heap[i].i << ' ' << heap[i].d << endl;
		}
		cout << endl;
	}
};
*/
int n, m, c;
ll tsum, ans = INF;
//pqueue* q;
priority_queue<pair<int, ll> > q;
vector< pair<int, ll> > v[MAX_NODE];
ll dist[2][MAX_NODE + 1];

void dijkstra() {
	/*while (!q->empty()) {
		node cur = q->pop();

		int len = v[cur.i].size();

		for (int i = 0; i < len; i++) {
			int ca = cur.i;
			int cb = v[cur.i][i].first;
			if (dist[1][cb] > cur.d + v[cur.i][i].second) {
				dist[1][cb] = cur.d + v[cur.i][i].second;
				q->push(cb, dist[1][cb]);
			}			
		}
	}*/

	while (!q.empty()) {
		//node cur = q.pop();
		int idx = q.top().first;
		ll d = q.top().second;
		q.pop();

		int len = v[idx].size();

		for (int i = 0; i < len; i++) {
			int ca = idx;
			int cb = v[idx][i].first;
			if (dist[1][cb] > d + v[idx][i].second) {
				dist[1][cb] = d + v[idx][i].second;
				q.push(make_pair(cb, dist[1][cb]));
			}
		}
	}
}

void qsort(int start, int end) {
	if (start >= end) return;
	int left = start;
	int right = end;
	ll pivot = dist[1][(start + end) / 2];

	while (left <= right) {
		while (pivot > dist[1][left]) left++;
		while (pivot < dist[1][right]) right--;
		if (left <= right) {
			ll tmp = dist[0][left];
			dist[0][left] = dist[0][right];
			dist[0][right] = tmp;
			tmp = dist[1][left];
			dist[1][left] = dist[1][right];
			dist[1][right] = tmp;
			left++;
			right--;
		}
	}
	qsort(start, left - 1);
	qsort(left, end);
}

void func() {
	qsort(1, n);
	bool visit[MAX_NODE + 1] = { 0, };

	for (int i = 1; i <= n; i++) {
		int index = dist[0][i];
		ll x = dist[1][i];
		visit[index] = true;
		int len = v[index].size();

		for (int j = 0; j < len; j++) {
			if (visit[v[index][j].first]) {
				tsum -= v[index][j].second;
			}
		}
		ans = MIN(ans, c*x + tsum);
	}
}

int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(NULL);*/
	//freopen("input.txt", "r", stdin);

	int tC; //cin >> tC;
	scanf("%d", &tC);
	for (int tc = 1; tc <= tC; tc++) {
		//cin >> n >> m >> c;
		scanf("%d %d %d", &n, &m, &c);
		tsum = 0;
		ans = INF;

		//q = new pqueue();
		//q->push(1, 0);
		q.push(make_pair(1, 0));

		dist[0][0] = 0;
		dist[0][1] = 1;
		dist[1][0] = dist[1][1] = 0;
		
		for (int i = 2; i <= n; i++) {
			//q->push(i, INF);
			q.push(make_pair(i, INF));
			dist[0][i] = i;
			dist[1][i] = INF;
		}

		for (int i = 0; i < m; i++) {
			int a, b, w;
			//cin >> a >> b >> w;
			scanf("%d %d %d", &a, &b, &w);
			tsum += w;
			v[a].push_back(make_pair(b, w));
			v[b].push_back(make_pair(a, w));
		}

		dijkstra();

		func();

		printf("#%d %lld\n", tc, ans);
		//cout << '#' << tc << ' ' << ans << '\n';
		for (int i = 1; i <= n; i++)
			v[i].clear();

		//delete q;
	}
	return 0;
}
