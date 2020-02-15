#include <iostream>

#include "Graph.h"

using namespace std;

int main()
{
    Graph g;
    //Graph_init(g, 5);

    //g.adjacent_matrix[0][1] = g.adjacent_matrix[1][0] = 8;
    //g.adjacent_matrix[0][3] = g.adjacent_matrix[3][0] = 4;
    //
    //g.adjacent_matrix[1][2] = g.adjacent_matrix[2][1] = 2;
    //g.adjacent_matrix[1][3] = g.adjacent_matrix[3][1] = 5;
    //g.adjacent_matrix[1][4] = g.adjacent_matrix[4][1] = 12;

    //g.adjacent_matrix[2][3] = g.adjacent_matrix[3][2] = 11;
    //g.adjacent_matrix[2][4] = g.adjacent_matrix[4][2] = 6;

    //g.adjacent_matrix[3][4] = g.adjacent_matrix[4][3] = 3;


    //auto result = Graph_MST_Prime(g);
    //for (auto i : result)
    //{
    //    std::cout << "<" << i.from << ", " << i.to << "> : " << i.weight << std::endl;
    //}

    //std::cout << "-----------" << std::endl;

    //result = Graph_MST_Kruskal(g);
    //for (auto i : result)
    //{
    //    std::cout << "<" << i.from << ", " << i.to << "> : " << i.weight << std::endl;
    //}

    //Graph_init(g, 6);

    //g.adjacent_matrix[0][1] = true;
    //g.adjacent_matrix[0][2] = true;
    //g.adjacent_matrix[0][3] = true;
    //g.adjacent_matrix[2][1] = true;
    //g.adjacent_matrix[2][4] = true;
    //g.adjacent_matrix[3][2] = true;
    //g.adjacent_matrix[3][4] = true;
    //g.adjacent_matrix[5][3] = true;
    //g.adjacent_matrix[5][4] = true;

    //auto result = Graph_topologic_sort(g);

    //for (auto i : result)
    //{
    //    std::cout << i << " ";
    //}
    //std::cout << std::endl;

    //Graph_init(g, 9);

    //g.adjacent_matrix[0][1] = 3;
    //g.adjacent_matrix[0][2] = 10;
    //g.adjacent_matrix[1][3] = 9;
    //g.adjacent_matrix[1][4] = 13;
    //g.adjacent_matrix[2][4] = 12;
    //g.adjacent_matrix[2][5] = 7;
    //g.adjacent_matrix[3][6] = 8;
    //g.adjacent_matrix[3][7] = 4;
    //g.adjacent_matrix[4][7] = 6;
    //// g.adjacent_matrix[5][7] = 11;
    //g.adjacent_matrix[6][8] = 2;
    //g.adjacent_matrix[7][8] = 5;

    //auto result = Graph_critical_activity(g);
    //for (auto i : result)
    //{
    //    std::cout << "<" << i.from << ", " << i.to << "> : " << i.weight << std::endl;
    //}

    //Graph_init(g, 6);
    //g.adjacent_matrix[0][1] = 20;
    //g.adjacent_matrix[0][2] = 60;
    //g.adjacent_matrix[0][4] = 10;
    //g.adjacent_matrix[0][5] = 65;
    //g.adjacent_matrix[1][2] = 30;
    //g.adjacent_matrix[1][3] = 70;
    //g.adjacent_matrix[2][3] = 40;
    //g.adjacent_matrix[3][4] = 35;
    //g.adjacent_matrix[4][5] = 20;
    //g.adjacent_matrix[5][2] = 15;
    //g.adjacent_matrix[5][3] = 80;

    //auto result = Graph_shortest_path_single_Dijkstra(g, 0);
    //for (auto i : result)
    //{
    //    std::cout << "Length: " << i.first << " Pre: " << i.second << std::endl;
    //}

    //std::cout << "-----------" << std::endl;

    //auto result2 = Graph_shortest_path_all_Dijkstra(g);
    //for (int i = 0; i < 6; i++)
    //{
    //    std::cout << "src: " << i << std::endl;
    //    for (int j = 0; j < 6; j++)
    //    {
    //        Graph_print_path_all_Dijkstra(g, result2, i, j);
    //        std::cout << std::endl;
    //    }
    //}

    //std::cout << "-----------" << std::endl;

    //auto result3 = Graph_shortest_path_all_Floyd(g);
    //for (int i = 0; i < 6; i++)
    //{
    //    std::cout << "src: " << i << std::endl;
    //    for (int j = 0; j < 6; j++)
    //    {
    //        Graph_print_path_all_Floyd(g, result3, i, j);
    //        std::cout << std::endl;
    //    }
    //}


    Graph_init(g, 3);
    g.adjacent_matrix[0][1] = 2;
    g.adjacent_matrix[0][2] = 8;
    g.adjacent_matrix[1][2] = 4;
    g.adjacent_matrix[2][0] = 5;
    
    auto result = Graph_shortest_path_single_Dijkstra(g, 0);
    for (auto i : result)
    {
        std::cout << "Length: " << i.first << " Pre: " << i.second << std::endl;
    }

    std::cout << "-----------" << std::endl;

    auto result2 = Graph_shortest_path_all_Dijkstra(g);
    for (int i = 0; i < 3; i++)
    {
        std::cout << "src: " << i << std::endl;
        for (int j = 0; j < 3; j++)
        {
            Graph_print_path_all_Dijkstra(g, result2, i, j);
            std::cout << std::endl;
        }
    }

    std::cout << "-----------" << std::endl;

    auto result3 = Graph_shortest_path_all_Floyd(g);
    for (int i = 0; i < 3; i++)
    {
        std::cout << "src: " << i << std::endl;
        for (int j = 0; j < 3; j++)
        {
            Graph_print_path_all_Floyd(g, result3, i, j);
            std::cout << std::endl;
        }
    }


    return 0;
}
