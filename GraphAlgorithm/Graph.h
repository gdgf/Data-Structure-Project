#pragma once

#include <xutility>
#include <vector>
#include <stdexcept>

typedef int WeightType;

struct Graph
{
    WeightType **adjacent_matrix = nullptr;
    int n_vertices = 0;
};

// 图结构的初始化
void Graph_init(Graph& g, int n_vertices);
// 图结构析构
void Graph_destroy(Graph& g);

// 求无向图是否联通
bool Graph_is_connected(Graph& g);
// 求有向图的强连通分量
std::vector<std::vector<int>> Graph_connected_component(Graph& g);


struct Edge
{
    int from;
    int to;
    WeightType weight;

    constexpr Edge(int from = -1, int to = -1, WeightType weight =
        std::is_same<WeightType, bool>::value ? false : std::numeric_limits<WeightType>::max())
        : from(from), to(to), weight(weight)
    {
    }
};

// 求无向图的最小生成树 - Prime，输出最小生成树的边
std::vector<Edge> Graph_MST_Prime(Graph& g);
// 求无向图的最小生成树 - Kruskal，输出最小生成树的边
std::vector<Edge> Graph_MST_Kruskal(Graph& g);

class circle_exist_error : public std::logic_error
{
public:
    circle_exist_error(const char *msg)
        : logic_error(msg)
    {
    }
};

// ----- 图的路径的累计长度类型 -----
template <typename T>
struct AccumulateWeightType
{
    using type = T;
};

// 如果是无权图，路径长度的累加值类型应该是整数型
template <>
struct AccumulateWeightType<bool>
{
    using type = int;
};

using AccType = AccumulateWeightType<WeightType>::type;

// 有向无环图拓扑排序，输出拓扑序列（深度优先）
std::vector<int> Graph_topologic_sort(Graph& g);
// 有向无环图关键路径
std::vector<Edge> Graph_critical_activity(Graph& g);

// 求单源最短路径，Dijkstra算法。输出的第一个是到改点长度，的第二个是最短路径上该节点的前一个节点
std::vector<std::pair<AccType, int>> Graph_shortest_path_single_Dijkstra(Graph& g, int root);
// 求全局全体路径，Dijkstra算法。输出一个矩阵，第(i,j)个元素是第i到第j的（最短路径长度，前一个节点）
std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Dijkstra(Graph& g);
// 求全局全体路径，Floyd算法。输出一个矩阵，第(i,j)个元素是第i到第j的（最短路径长度，前一个节点）
std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Floyd(Graph& g);

void Graph_print_path_single_Dijkstra(Graph& g, std::vector<std::pair<AccType, int>>& path, int dest);
void Graph_print_path_all_Dijkstra(Graph& g, std::vector<std::vector<std::pair<AccType, int>>>& path, int src, int dest);
void Graph_print_path_all_Floyd(Graph& g, std::vector<std::vector<std::pair<AccType, int>>>& paths, int src, int dest);