#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Sử dụng hằng số lớn thay cho vô cực để tránh tràn số (overflow) khi cộng
// trọng số. 1e9 = 1,000,000,000. Với n <= 50, w <= 1000, đường đi dài nhất <
// 50,000, nên 1e9 là đủ lớn.
const int INF = 1e9;

// Cấu trúc biểu diễn một cạnh kề trong danh sách kề
struct Edge {
    int to;      // Đỉnh đích của cạnh
    int weight;  // Trọng số của cạnh
};

/*
 * HÀM NỚI LỎNG (RELAXATION) - Theo đúng yêu cầu của phiếu (noi_long!)
 * Thực hiện kiểm tra xem đường đi từ u đến v qua cạnh (u, v, w)
 * có tốt hơn khoảng cách hiện tại đang lưu ở dist[v] hay không.
 * Trả về true nếu có cập nhật (tìm được đường ngắn hơn), ngược lại false.
 */
bool noi_long(int u, int v, int w, vector<int>& dist, vector<int>& parent) {
    // Nếu đỉnh u đã có đường đi và tổng trọng số mới nhỏ hơn khoảng cách hiện
    // tại của v
    if (dist[u] != INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;  // Cập nhật khoảng cách mới
        parent[v] = u;          // Lưu vết đỉnh cha để phục vụ truy vết
        return true;
    }
    return false;
}

/*
 * HÀM THUẬT TOÁN DIJKSTRA
 * Tìm đường đi ngắn nhất từ đỉnh nguồn s đến tất cả các đỉnh khác.
 */
void dijkstra(int n, int s, const vector<vector<Edge>>& adj, vector<int>& dist,
              vector<int>& parent) {
    // Khởi tạo mảng khoảng cách bằng vô cực, mảng cha bằng -1
    dist.assign(n + 1, INF);
    parent.assign(n + 1, -1);

    dist[s] = 0;  // Khoảng cách từ nguồn đến chính nó bằng 0

    // Hàng ưu tiên (Min-Heap) lưu cặp {khoảng_cách, đỉnh}.
    // Sử dụng greater<> để biến priority_queue mặc định (Max-Heap) thành
    // Min-Heap. C++ sẽ tự động so sánh phần tử đầu tiên (khoảng cách) trước,
    // đúng theo yêu cầu phiếu.
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int d = pq.top().first;   // Khoảng cách hiện tại
        int u = pq.top().second;  // Đỉnh đang xét
        pq.pop();

        // Kỹ thuật "Lazy Deletion": Bỏ qua nếu khoảng cách lấy ra từ hàng đợi
        // lớn hơn khoảng cách tốt nhất đã tìm thấy trước đó trong mảng dist.
        // Điều này giúp tránh xử lý lại các đỉnh đã được tối ưu.
        if (d > dist[u]) continue;

        // Duyệt tất cả các đỉnh kề của u
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            // Gọi hàm nới lỏng. Nếu tìm thấy đường ngắn hơn, đưa v vào hàng
            // đợi.
            if (noi_long(u, v, w, dist, parent)) {
                pq.push({dist[v], v});
            }
        }
    }
}

/*
 * HÀM TRUY VẾT ĐƯỜNG ĐI (TRACE PATH)
 * Dựa vào mảng parent để truy ngược từ đích t về nguồn s.
 */
void truy_vet(int s, int t, const vector<int>& dist,
              const vector<int>& parent) {
    // Trường hợp không có đường đi
    if (dist[t] == INF) {
        cout << "KHONG CO DUONG\n";
        return;
    }

    vector<int> path;
    int curr = t;

    // Truy ngược từ t về s bằng mảng parent
    while (curr != -1) {
        path.push_back(curr);
        if (curr == s) break;  // Dừng khi đã về tới nguồn
        curr = parent[curr];
    }

    // Đảo ngược mảng để được đường đi đúng thứ tự từ s -> t
    reverse(path.begin(), path.end());

    // In kết quả định dạng đúng yêu cầu: duong=[...]; tong=...
    cout << "duong=[";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i == path.size() - 1 ? "" : ", ");
    }
    cout << "]; tong=" << dist[t] << "\n";
}

int main() {
    // Tối ưu I/O trong C++ để đọc/ghi dữ liệu nhanh hơn
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // Nhập số đỉnh và số cạnh
    if (!(cin >> n >> m)) return 0;

    // Kiểm tra điều kiện biên theo phiếu: 1 <= n <= 50
    if (n < 1 || n > 50) {
        cout << "LOI: So dinh n phai nam trong khoang 1..50.\n";
        return 1;
    }

    vector<vector<Edge>> adj(n + 1);
    bool hasNegativeWeight = false;

    // Nhập danh sách cạnh
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        // Đánh dấu nếu phát hiện trọng số âm
        if (w < 0) {
            hasNegativeWeight = true;
        }

        // Đồ thị vô hướng nên thêm cạnh vào cả 2 chiều
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int s, t;
    cin >> s >> t;

    // KIỂM TRA ĐIỀU KIỆN BIÊN: Từ chối cạnh âm (Yêu cầu bắt buộc của phiếu)
    if (hasNegativeWeight) {
        cout << "LOI: Do thi chua canh co trong so am. Dijkstra khong the "
                "chay.\n";
        return 1;
    }

    // Kiểm tra nguồn và đích có hợp lệ không
    if (s < 1 || s > n || t < 1 || t > n) {
        cout << "LOI: Nguon hoac dich khong hop le.\n";
        return 1;
    }

    vector<int> dist, parent;

    // Gọi hàm chạy thuật toán
    dijkstra(n, s, adj, dist, parent);

    // In mảng khoảng cách (d)
    cout << "d=[";
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF)
            cout << "INF";
        else
            cout << dist[i];
        cout << (i == n ? "" : ", ");
    }
    cout << "];\n";

    // Gọi hàm in đường đi và tổng trọng số
    truy_vet(s, t, dist, parent);

    return 0;
}