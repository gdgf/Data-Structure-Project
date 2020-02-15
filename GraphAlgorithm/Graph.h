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

// ͼ�ṹ�ĳ�ʼ��
void Graph_init(Graph& g, int n_vertices);
// ͼ�ṹ����
void Graph_destroy(Graph& g);

// ������ͼ�Ƿ���ͨ
bool Graph_is_connected(Graph& g);
// ������ͼ��ǿ��ͨ����
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

// ������ͼ����С������ - Prime�������С�������ı�
std::vector<Edge> Graph_MST_Prime(Graph& g);
// ������ͼ����С������ - Kruskal�������С�������ı�
std::vector<Edge> Graph_MST_Kruskal(Graph& g);

class circle_exist_error : public std::logic_error
{
public:
    circle_exist_error(const char *msg)
        : logic_error(msg)
    {
    }
};

// ----- ͼ��·�����ۼƳ������� -----
template <typename T>
struct AccumulateWeightType
{
    using type = T;
};

// �������Ȩͼ��·�����ȵ��ۼ�ֵ����Ӧ����������
template <>
struct AccumulateWeightType<bool>
{
    using type = int;
};

using AccType = AccumulateWeightType<WeightType>::type;

// �����޻�ͼ������������������У�������ȣ�
std::vector<int> Graph_topologic_sort(Graph& g);
// �����޻�ͼ�ؼ�·��
std::vector<Edge> Graph_critical_activity(Graph& g);

// ��Դ���·����Dijkstra�㷨������ĵ�һ���ǵ��ĵ㳤�ȣ��ĵڶ��������·���ϸýڵ��ǰһ���ڵ�
std::vector<std::pair<AccType, int>> Graph_shortest_path_single_Dijkstra(Graph& g, int root);
// ��ȫ��ȫ��·����Dijkstra�㷨�����һ�����󣬵�(i,j)��Ԫ���ǵ�i����j�ģ����·�����ȣ�ǰһ���ڵ㣩
std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Dijkstra(Graph& g);
// ��ȫ��ȫ��·����Floyd�㷨�����һ�����󣬵�(i,j)��Ԫ���ǵ�i����j�ģ����·�����ȣ�ǰһ���ڵ㣩
std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Floyd(Graph& g);

void Graph_print_path_single_Dijkstra(Graph& g, std::vector<std::pair<AccType, int>>& path, int dest);
void Graph_print_path_all_Dijkstra(Graph& g, std::vector<std::vector<std::pair<AccType, int>>>& path, int src, int dest);
void Graph_print_path_all_Floyd(Graph& g, std::vector<std::vector<std::pair<AccType, int>>>& paths, int src, int dest);