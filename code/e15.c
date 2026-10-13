#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STATIONS 200
#define MAX_NAME 30
#define INF 99999999
// ---------- 全局数据结构 ----------
typedef struct {
    int id;
    char name[MAX_NAME];
} Station;
int N, M;                       // 站点总数，边数
Station stations[MAX_STATIONS];
int graph[MAX_STATIONS][MAX_STATIONS]; // 邻接矩阵（距离×10，整数）
int all_pairs[MAX_STATIONS][MAX_STATIONS]; // Floyd 专用距离矩阵
// ---------- 票价计算 ----------
int calcFare(int distance_km) {
    if (distance_km <= 4) return 2;
    else if (distance_km <= 8) return 3;
    else if (distance_km <= 12) return 4;
    else if (distance_km <= 18) return 5;
    else if (distance_km <= 24) return 6;
    else if (distance_km <= 32) return 7;
    else if (distance_km <= 40) return 8;
    else if (distance_km <= 50) return 9;
    else if (distance_km <= 70) return 10;
    else if (distance_km <= 90) return 11;
    else if (distance_km <= 110) return 12;
    else if (distance_km <= 130) return 13;
    else return 13 + (distance_km - 130 + 19) / 20;
}
// ---------- 工具函数 ----------
int findStation(char *name) {
    for (int i = 0; i < N; i++)
        if (strcmp(stations[i].name, name) == 0) return i;
    return -1;
}
void initGraph() {
    for (int i = 0; i < MAX_STATIONS; i++)
        for (int j = 0; j < MAX_STATIONS; j++)
            graph[i][j] = (i == j) ? 0 : INF;
}
void addEdge(int u, int v, int weight_x10) {
    graph[u][v] = weight_x10;
    graph[v][u] = weight_x10;
}
// 递归打印路径（利用前驱数组）
void printPathHelper(int prev[], int start, int end) {
    if (end == start) {
        printf("%s", stations[start].name);
        return;
    }
    if (prev[end] == -1) {
       printf("无路径");
        return;
    }
    printPathHelper(prev, start, prev[end]);
    printf(" -> %s", stations[end].name);
}
// ============================================================
// 算法1：朴素 Dijkstra（O(N^2)）
// ============================================================
void dijkstra_naive(int start, int end) {
    int dist[MAX_STATIONS], prev[MAX_STATIONS], visited[MAX_STATIONS] = {0};
    for (int i = 0; i < N; i++) {
        dist[i] = graph[start][i];
        prev[i] = (graph[start][i] < INF && i != start) ? start : -1;
    }
    dist[start] = 0;
    visited[start] = 1;
    for (int i = 0; i < N - 1; i++) {
        int min = INF, u = -1;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] < INF) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }
    int km = (dist[end] + 5) / 10;  // 四舍五入
    printf("\n========== 算法1：朴素Dijkstra ==========\n");
   printf("最短里程: %.1f 公里\n", dist[end] / 10.0);
   printf("票价: %d 元\n", calcFare(km));
   printf("路径: ");
    printPathHelper(prev, start, end);
    printf("\n");
}
// ============================================================
// 算法2：堆优化 Dijkstra（使用手动二叉堆，O(E log V)）
// ============================================================
typedef struct {
    int node;
    int dist;
} HeapNode;
HeapNode heap[MAX_STATIONS * MAX_STATIONS];
int heapSize = 0;
void heapPush(int node, int dist) {
    heap[heapSize].node = node;
    heap[heapSize].dist = dist;
    int i = heapSize++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].dist <= heap[i].dist) break;
        HeapNode tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
        i = p;
    }
}
HeapNode heapPop() {
    HeapNode top = heap[0];
    heap[0] = heap[--heapSize];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < heapSize && heap[left].dist < heap[smallest].dist) smallest = left;
        if (right < heapSize && heap[right].dist < heap[smallest].dist) smallest = right;
        if (smallest == i) break;
        HeapNode tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
        i = smallest;
    }
    return top;
}
void dijkstra_heap(int start, int end) {
    int dist[MAX_STATIONS], prev[MAX_STATIONS];
    int visited[MAX_STATIONS] = {0};
    heapSize = 0;
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;
    heapPush(start, 0);
    while (heapSize > 0) {
        HeapNode cur = heapPop();
        int u = cur.node;
        if (visited[u]) continue;
        visited[u] = 1;
        if (u == end) break;
        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] < INF) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    heapPush(v, newDist);
                }
            }
        }
    }
    int km = (dist[end] + 5) / 10;
    printf("\n========== 算法2：堆优化Dijkstra ==========\n");
   printf("最短里程: %.1f 公里\n", dist[end] / 10.0);
   printf("票价: %d 元\n", calcFare(km));
   printf("路径: ");
    printPathHelper(prev, start, end);
    printf("\n");
}
// ============================================================
// 算法3：Floyd-Warshall 全源最短路径（O(N^3)）
// ============================================================
int floyd_prev[MAX_STATIONS][MAX_STATIONS]; // 前驱矩阵
void floyd_warshall() {
   // 初始化距离矩阵和前驱矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            all_pairs[i][j] = graph[i][j];
            floyd_prev[i][j] = (graph[i][j] < INF && i != j) ? i : -1;
        }
        all_pairs[i][i] = 0;
        floyd_prev[i][i] = -1;
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            if (all_pairs[i][k] >= INF) continue;
            for (int j = 0; j < N; j++) {
                if (all_pairs[k][j] >= INF) continue;
                int newDist = all_pairs[i][k] + all_pairs[k][j];
                if (newDist < all_pairs[i][j]) {
                    all_pairs[i][j] = newDist;
                    floyd_prev[i][j] = floyd_prev[k][j];  // 前驱更新
                }
            }
        }
    }
}
// 递归打印 Floyd 路径
void printFloydPath(int start, int end) {
    if (all_pairs[start][end] >= INF) {
       printf("无路径");
        return;
    }
    if (start == end) {
        printf("%s", stations[start].name);
        return;
    }
    int mid = floyd_prev[start][end];
    if (mid == -1 || mid == start) {
        printf("%s -> %s", stations[start].name, stations[end].name);
        return;
    }
    printFloydPath(start, mid);
    printf(" -> %s", stations[end].name);
}
void query_floyd(int start, int end) {
    int km = (all_pairs[start][end] + 5) / 10;
    printf("\n========== 算法3：Floyd-Warshall ==========\n");
   printf("最短里程: %.1f 公里\n", all_pairs[start][end] / 10.0);
   printf("票价: %d 元\n", calcFare(km));
   printf("路径: ");
    printFloydPath(start, end);
    printf("\n");
}
// ============================================================
// 主函数 —— 构建测试网络并交互查询
// ============================================================
int main() {
    initGraph();
   // ----- 构建成都地铁部分网络（13个站点，14条边）-----
    strcpy(stations[0].name, "火车北站");
    strcpy(stations[1].name, "人民北路");
    strcpy(stations[2].name, "骡马市");
    strcpy(stations[3].name, "天府广场");
    strcpy(stations[4].name, "锦江宾馆");
    strcpy(stations[5].name, "华西坝");
    strcpy(stations[6].name, "省体育馆");
    strcpy(stations[7].name, "倪家桥");
    strcpy(stations[8].name, "火车南站");
    strcpy(stations[9].name, "孵化园");
    strcpy(stations[10].name, "世纪城");
    strcpy(stations[11].name, "中医大省医院");
    strcpy(stations[12].name, "宽窄巷子");
    N = 13;
   // 边（距离单位：公里，存储时×10）
   // 1号线
    addEdge(0, 1, 12);  // 1.2km
    addEdge(1, 2, 9);   // 0.9km
    addEdge(2, 3, 8);   // 0.8km
    addEdge(3, 4, 11);  // 1.1km
    addEdge(4, 5, 9);   // 0.9km
    addEdge(5, 6, 10);  // 1.0km
    addEdge(6, 7, 13);  // 1.3km
    addEdge(7, 8, 15);  // 1.5km
    addEdge(8, 9, 20);  // 2.0km
    addEdge(9, 10, 18); // 1.8km
   // 2号线换乘
    addEdge(11, 12, 7); // 0.7km
    addEdge(12, 3, 8);  // 0.8km
   // 3号线连接（省体育馆 ↔ 中医大省医院）
    addEdge(6, 11, 15); // 1.5km
   // ----- 用户交互 -----
    printf("========== 成都地铁计费系统（三种算法对比）==========\n\n");
   printf("站点列表：\n");
    for (int i = 0; i < N; i++)
        printf("  %s\n", stations[i].name);
    char sName[MAX_NAME], eName[MAX_NAME];
    printf("\n 请输入起点站名: ");
    scanf("%s", sName);
   printf("请输入终点站名: ");
    scanf("%s", eName);
    int start = findStation(sName);
    int end = findStation(eName);
    if (start == -1 || end == -1) {
      printf("错误：站点不存在！\n");
        return 1;
    }
   // 执行三种算法
    dijkstra_naive(start, end);
    dijkstra_heap(start, end);
    floyd_warshall();       // 预计算全源
    query_floyd(start, end);
    return 0;
}