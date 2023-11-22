#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAX_HOUSES = 30;
const int INF = INT_MAX;

// 边的结构体
struct Edge {
    int to;
    int weight;
};

// 图的结构体
struct Graph {
    vector<Edge> adj[MAX_HOUSES];
};

// Dijkstra算法
vector<int> dijkstra(const Graph& g, int start) {
    vector<int> dist(MAX_HOUSES, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : g.adj[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n; // 住户数量
    cout << "请输入住户数量（不超过30）: ";
    cin >> n;

    Graph g;

    // 输入住户能够自救的时间
    for (int i = 0; i < n; ++i) {
        int rescueTime;
        cout << "请输入第 " << i + 1 << " 个住户能够自救的时间：";
        cin >> rescueTime;

        // 将村庄与能够自救的时间作为节点和权重构建图
        if (i - rescueTime >= 0) {
            g.adj[i].push_back({i - rescueTime, 1});
        }
        if (i + rescueTime < n) {
            g.adj[i].push_back({i + rescueTime, 1});
        }
    }

    // 从起点（0号住户）开始计算最短路径
    vector<int> shortestPath = dijkstra(g, 0);

    // 输出到达每个住户的最短时间
    cout << "从村口出发到达每个住户的最短时间为：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "到达住户 " << i + 1 << " 的最短时间为：" << shortestPath[i] << " 时间单位" << endl;
    }

    return 0;
}
