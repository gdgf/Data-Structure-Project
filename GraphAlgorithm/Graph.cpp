#include "Graph.h"

#include <functional>
#include <numeric>
#include <type_traits>
#include <algorithm>
#include <stack>

#include <iostream>

void Graph_init(Graph& g, int n_vertices)
{
    if (g.adjacent_matrix != nullptr)
    {
        Graph_destroy(g);
    }
    g.adjacent_matrix = new WeightType*[n_vertices];
    for (int i = 0; i < n_vertices; i++)
    {
        g.adjacent_matrix[i] = new WeightType[n_vertices];
        if constexpr(std::is_same<WeightType, bool>::value)
        {
            // ��ʼ��ΪElem����Ԫ�ص�0ֵ
            std::fill(g.adjacent_matrix[i], g.adjacent_matrix[i] + n_vertices, false);
        }
        else
        {
            // ��ʼ��ΪElem����Ԫ�ص����ֵ
            std::fill(g.adjacent_matrix[i], g.adjacent_matrix[i] + n_vertices, std::numeric_limits<WeightType>::max());
        }
    }
    g.n_vertices = n_vertices;
}

void Graph_destroy(Graph& g)
{
    if (g.adjacent_matrix != nullptr)
    {
        for (int i = 0; i < g.n_vertices; i++)
        {
            delete[] g.adjacent_matrix[i];
        }
        g.adjacent_matrix = nullptr;
        g.n_vertices = 0;
    }
}

bool Graph_is_connected(Graph & g)
{
    if (g.n_vertices == 0)
        return true;

    int n = g.n_vertices;
    bool *visited = new bool[n];
    std::fill(visited, visited + n, false);
    int count = 0;
    std::function<void(int)> dfs = [&](int begin) -> void
    {
        visited[begin] = true;
        count++;
        for (int i = 0; i < n; i++)
        {
            if (g.adjacent_matrix[begin][i] != WeightType() && !visited[i])
            {
                dfs(i);
            }
        }
    };
    dfs(0);
    return count == n;
}

std::vector<std::vector<int>> Graph_connected_component(Graph & g)
{
    if (g.n_vertices == 0)
    {
        std::vector<std::vector<int>>();
    }

    const int n = g.n_vertices;
    // 1. ����������ȱ�����Ϊ���������ɭ�ֽ�������˳��˳�򱣴���inorder��
    int *inorder = new int[g.n_vertices];
    int count = 0;
    bool *visited = new bool[n];
    std::fill(visited, visited + n, false);
    std::function<void(int)> dfs = [&](int begin) -> void
    {
        visited[begin] = true;
        for (int i = 0; i < n; i++)
        {
            if (g.adjacent_matrix[begin][i] != WeightType() && !visited[i])
            {
                dfs(i);
            }
        }
        inorder[count++] = begin;
    };
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i);

    // 2. ����������ȱ���
    std::fill(visited, visited + n, false);
    std::function<void(int, std::vector<int>& component)> reverse_dfs =
        [&](int end, std::vector<int>& component) -> void
    {
        visited[end] = true;
        for (int i = 0; i < n; i++)
        {
            if (g.adjacent_matrix[i][end] != WeightType() && !visited[i])
            {
                reverse_dfs(i, component);
            }
        }
        component.push_back(end);
    };
    std::vector<std::vector<int>> result;
    for (int i = n - 1; i >= 0; i--)
    {
        if (!visited[inorder[i]])
        {
            std::vector<int> com;
            reverse_dfs(inorder[i], com);
            result.push_back(com);
        }
    }

    return result;
}

// Prime�㷨����С������
std::vector<Edge> Graph_MST_Prime(Graph & g)
{
    int n = g.n_vertices;
    if (n == 0)
    {
        return std::vector<Edge>();
    }

    int *pre = new int[n]; // V-U��ÿ���ڵ���V����СȨֵ�ߵ����ڽӵ�
    WeightType *min_weight = new WeightType[n]; // V - U��ÿ���ڵ���V����СȨֵ�ߵ�Ȩֵ
    std::fill(pre, pre + n, -1);
    if constexpr (std::is_same<WeightType, bool>::value) // ��Ȩͼ����ʼ��Ϊfalse
    {
        std::fill(min_weight, min_weight + n, false);
    }
    else // ��Ȩͼ����ʼ��ȨֵΪ���ֵ
    {
        std::fill(min_weight, min_weight + n, std::numeric_limits<WeightType>::max());
    }
    bool *visited = new bool[n];
    std::fill(visited, visited + n, false);
    
    std::vector<Edge> result;

    int cur = 0;
    for (int i = 0; i < n; i++)
    {
        if (pre[cur] != -1)
        {
            result.push_back(Edge(pre[cur], cur, g.adjacent_matrix[pre[cur]][cur]));
        }

        // ѡȡ����cur
        min_weight[cur] = WeightType();
        visited[cur] = true;
        WeightType next_min_weight = std::is_same<WeightType, bool>::value ?
            false : std::numeric_limits<WeightType>::max();
        int next = -1;
        for (int j = 0; j < n; j++)
        {
            // ����Ȩֵ�б�
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                // ��Ȩͼ����������
                if (g.adjacent_matrix[cur][j] && !min_weight[j])
                {
                    min_weight[j] = g.adjacent_matrix[cur][j];
                    pre[j] = cur;
                }
                if (!visited[j] && min_weight[j] != false)
                {
                    next = j;
                }
            }
            else // ��Ȩͼ����ֵ
            {
                if (g.adjacent_matrix[cur][j] < min_weight[j])
                {
                    min_weight[j] = g.adjacent_matrix[cur][j];
                    pre[j] = cur;
                }
                if (min_weight[j] != WeightType() && min_weight[j] < next_min_weight)
                {
                    next = j;
                    next_min_weight = min_weight[j];
                }
            }
        }
        cur = next;
    }

    return result;
}

std::vector<Edge> Graph_MST_Kruskal(Graph & g)
{
    int n = g.n_vertices;
    if (n == 0)
    {
        return std::vector<Edge>();
    }

    std::vector<Edge> edges;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                if (g.adjacent_matrix[i][j])
                {
                    edges.push_back(Edge(i, j, g.adjacent_matrix[i][j]));
                }
            }
            else
            {
                if (g.adjacent_matrix[i][j] != std::numeric_limits<WeightType>::max())
                {
                    edges.push_back(Edge(i, j, g.adjacent_matrix[i][j]));
                }
            }
        }
    }
    // ʹ�ÿ��������������
    if constexpr (std::is_same<WeightType, bool>::value) // ��Ȩͼ������ͨ�ı߷���ǰ��
    {
        auto begin = std::size_t(), end = edges.size() - 1;
        while (begin < end)
        {
            while (begin < end && !edges[begin].weight)
            {
                std::swap(edges[begin], edges[end]);
                end--;
            }
            begin++;
        }
    }
    else // ��Ȩͼ����ȨֵС�ı߷���ǰ��
    {
        std::sort(edges.begin(), edges.end(), [](auto lhs, auto rhs) -> auto
        {
            return lhs.weight < rhs.weight;
        });
    }

    // ÿ��ѡ����С�Ĳ����ɻ�·�ģ�������ȹ��첢�鼯
    int *ufs_parent = new int[n]; // ���鼯����ԭ�򣬵�isrootΪtrueʱ�������������򱣴游��
    bool *ufs_isroot = new bool[n];
    for (int i = 0; i < n; i++)
    {
        ufs_parent[i] = 1;
        ufs_isroot[i] = true;
    }

    // ���鼯����find
    std::function<int(int)> find = [&](int c) -> int
    {
        return ufs_isroot[c] ? c : ufs_parent[c] = find(ufs_parent[c]); // �۰뷨����̯(log*)n
    };

    // ���鼯����unite
    std::function<void(int, int)> unite = [&](int c1, int c2) -> void
    {
        auto r1 = find(c1), r2 = find(c2);

        if (ufs_parent[r2] < ufs_parent[r1]) // ����ԭ��С�ķ�����
        {
            std::swap(r1, r2);
        }
        ufs_parent[r2] += ufs_parent[r1];
        ufs_parent[r1] = r2;
        ufs_isroot[r1] = false;
    };

    std::vector<Edge> result;
    for (auto edge : edges)
    {
        if (find(edge.to) != find(edge.from))
        {
            result.push_back(edge);
            unite(edge.to, edge.from);
            if (result.size() == n)
            {
                break;
            }
        }
    }
    return result;
}

std::vector<int> Graph_topologic_sort(Graph & g)
{
    int n = g.n_vertices;
    if (n == 0) return std::vector<int>();
    
    std::stack<int> search_stack;
    int *indegree = new int[n];
    std::fill(indegree, indegree + n, 0);

    std::vector<int> result;

    // 1. ͳ��ÿ��������
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                indegree[i] += g.adjacent_matrix[j][i] ? 1 : 0;
            }
            else
            {
                indegree[i] += g.adjacent_matrix[j][i] !=
                    std::numeric_limits<WeightType>::max() ? 1 : 0;
            }
        }
        // ������Ϊ0�����뵽����ջ��
        if (indegree[i] == 0)
        {
            search_stack.push(i);
        }
    }
    while (!search_stack.empty())
    {
        auto cur = search_stack.top();
        search_stack.pop();
        result.push_back(cur);
        for (int i = 0; i < n; i++)
        {
            // ɾ�����
            int dec = 0;
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                dec = g.adjacent_matrix[cur][i] ? 1 : 0;
            }
            else
            {
                dec = g.adjacent_matrix[cur][i] < std::numeric_limits<WeightType>::max() ? 1 : 0;
            }
            if (dec == 1)
            {
                indegree[i] -= dec;
                if (indegree[i] == 0)
                {
                    search_stack.push(i);
                }
            }
        }
    }

    if (result.size() != n)
    {
        throw circle_exist_error("���ڻ�·!");
    }

    return result;
}


std::vector<Edge> Graph_critical_activity(Graph & g)
{
    int n = g.n_vertices;
    if (n == 0)
    {
        return std::vector<Edge>();
    }
    decltype(Graph_topologic_sort(g)) topo_list;
    try
    {
        topo_list = Graph_topologic_sort(g);
    }
    catch (circle_exist_error& e)   // ���ڻ�·
    {
        throw e;
    }

    AccType *ealiest = new AccType[n];
    AccType *latest = new AccType[n];
    std::fill(ealiest, ealiest + n, std::numeric_limits<AccType>::min());
    std::fill(latest, latest + n, std::numeric_limits<AccType>::max());

    // 1. �����������ʱ��
    ealiest[topo_list[0]] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int pre = topo_list[i];
        for (int j = 0; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                if (g.adjacent_matrix[pre][j] && ealiest[pre] + 1 > ealiest[j])
                {
                    ealiest[j] = ealiest[pre] + 1;
                }
            }
            else
            {
                if (g.adjacent_matrix[pre][j] != std::numeric_limits<WeightType>::max()
                    && ealiest[pre] + g.adjacent_matrix[pre][j] > ealiest[j])
                {
                    ealiest[j] = ealiest[pre] + g.adjacent_matrix[pre][j];
                }
            }
        }
    }

    // 2. �����������ʱ��
    latest[topo_list[n - 1]] = ealiest[topo_list[n - 1]];
    for (int i = n - 1; i > 0; i--)
    {
        int next = topo_list[i];
        for (int j = 0; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)  // ��Ȩ
            {
                if (g.adjacent_matrix[j][next] && latest[next] - 1 < latest[j])
                {
                    latest[j] = latest[next] - 1;
                }
            }
            else // ��Ȩ
            {
                if (g.adjacent_matrix[j][next] != std::numeric_limits<WeightType>::max() &&
                    latest[next] - g.adjacent_matrix[j][next] < latest[j])
                {
                    latest[j] = latest[next] - g.adjacent_matrix[j][next];
                }
            }

        }
    }

    auto result = std::vector<Edge>{};

    // 3. ����ؼ������Щ���翪ʼҲ����������������ʼ������
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                if (g.adjacent_matrix[i][j] && ealiest[i] == latest[j] - 1)
                {
                    result.push_back(Edge(i, j, true));
                }
            }
            else
            {
                if (g.adjacent_matrix[i][j] != std::numeric_limits<WeightType>::max()
                    && ealiest[i] == latest[j] - g.adjacent_matrix[i][j])
                {
                    result.push_back(Edge(i, j, g.adjacent_matrix[i][j]));
                }
            }
        }
    }

    return result;
}

std::vector<std::pair<AccType, int>> Graph_shortest_path_single_Dijkstra(Graph & g, int root)
{
    if (g.n_vertices == 0)
    {
        return std::vector<std::pair<int, AccType>>();
    }
    int n = g.n_vertices;

    std::vector<std::pair<AccType, int>> min_weight(n);
    bool *visited = new bool[n];
    std::fill(visited, visited + n, false);
    std::fill(min_weight.begin(), min_weight.end(), std::make_pair(std::numeric_limits<AccType>::max(), -1));

    int cur = root;
    min_weight[root].first = AccType();
    min_weight[root].second = -1;
    while (cur != -1)
    {
        visited[cur] = true;
        AccType next_min_weight = std::numeric_limits<AccType>::max();
        int next = -1;
        for (int j = 0; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value) // ��Ȩ
            {
                if (g.adjacent_matrix[cur][j] &&
                    1 + min_weight[cur].first < min_weight[j].first)
                {
                    min_weight[j] = { 1 + min_weight[cur].first, cur };
                }
            }
            else
            {
                if (g.adjacent_matrix[cur][j] != std::numeric_limits<WeightType>::max() &&
                    g.adjacent_matrix[cur][j] + min_weight[cur].first < min_weight[j].first)
                {
                    min_weight[j] = { g.adjacent_matrix[cur][j] + min_weight[cur].first, cur };
                }
            }

            if (!visited[j] && min_weight[j].first < next_min_weight)
            {
                next_min_weight = min_weight[j].first;
                next = j;
            }
        }
        cur = next;
    }

    return min_weight;
}

std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Dijkstra(Graph & g)
{
    if (g.n_vertices == 0)
    {
        return std::vector<std::vector<std::pair<AccType, int>>>();
    }
    int n = g.n_vertices;
    auto result = std::vector<std::vector<std::pair<AccType, int>>>();
    for (int i = 0; i < n; i++)
    {
        result.push_back(Graph_shortest_path_single_Dijkstra(g, i));
    }
    return result;
}

std::vector<std::vector<std::pair<AccType, int>>> Graph_shortest_path_all_Floyd(Graph & g)
{
    if (g.n_vertices == 0)
    {
        return std::vector<std::vector<std::pair<AccType, int>>>();
    }
    int n = g.n_vertices;
    auto result = std::vector<std::vector<std::pair<AccType, int>>>();
    // 1. ��ʼ��
    for (int i = 0; i < n; i++)
    {
        result.push_back(std::vector<std::pair<AccType, int>>(n));
        for (int j = 0; j < n; j++)
        {
            if constexpr (std::is_same<WeightType, bool>::value)
            {
                if (g.adjacent_matrix[i][j])
                {
                    result[i][j] = { 1, -1 };
                }
                else
                {
                    result[i][j] = { std::numeric_limits<AccType>::max(), -1 };
                }
            }
            else
            {
                if (g.adjacent_matrix[i][j] != std::numeric_limits<WeightType>::max())
                {
                    result[i][j] = { g.adjacent_matrix[i][j], -1 };
                }
                else
                {
                    result[i][j] = { std::numeric_limits<AccType>::max(), -1 };
                }
            }
        }
        result[i][i] = { AccType(), -1 };
    }

    // 2. �������·��
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (result[i][k].first != std::numeric_limits<AccType>::max() &&
                    result[k][j].first != std::numeric_limits<AccType>::max() &&
                    result[i][k].first + result[k][j].first < result[i][j].first)
                {
                    result[i][j] = { result[i][k].first + result[k][j].first, k };
                }
            }
        }
    }

    return result;
}

void Graph_print_path_single_Dijkstra(Graph & g, std::vector<std::pair<AccType, int>>& path, int dest)
{
    std::function<void(int, int)> helper = [&](int _to, int n) -> void
    {
        if (path[_to].second != -1)
        {
            helper(path[_to].second, n + 1);
        }
        if (path[_to].first == std::numeric_limits<AccType>::max())
        {
            std::cout << "X";
        }
        else
        {
            std::cout << _to;
        }
        if (n > 0)
        {
            std::cout << " -> ";
        }
    };

    helper(dest, 0);
}

void Graph_print_path_all_Dijkstra(Graph & g, std::vector<std::vector<std::pair<AccType, int>>>& paths, int src, int dest)
{
    Graph_print_path_single_Dijkstra(g, paths[src], dest);
}

void Graph_print_path_all_Floyd(Graph & g, std::vector<std::vector<std::pair<AccType, int>>>& paths, int src, int dest)
{
    std::function<void(int, int)> helper = [&](int _from, int _to) -> void
    {
        if (paths[_from][_to].second != -1)
        {
            helper(_from, paths[_from][_to].second);
            std::cout << " -> " << paths[_from][_to].second;
            helper(paths[_from][_to].second, _to);
        }
    };

    if (paths[src][dest].first == std::numeric_limits<AccType>::max())
    {
        std::cout << "X";
    }
    else
    {
        std::cout << src;
        helper(src, dest);
        if (src != dest)
        {
            std::cout << " -> " << dest;
        }
    }
}




