#include <iostream>
#include <vector>

using namespace std;

bool DFS(int v, vector<bool>& visited, vector<bool>& recStack, const vector<vector<int>>& graph, vector<int>& path, int& cycle_count, vector<vector<int>>& cycles)
{
    visited[v] = true;
    recStack[v] = true;
    path.push_back(v);

    for (int neighbor : graph[v])
    {
        if (!visited[neighbor])
        {
            if (DFS(neighbor, visited, recStack, graph, path, cycle_count, cycles))
                return true;
        }
        else if (recStack[neighbor])
        {
            // Cycle detected, increment cycle count and store the cycle path
            cycle_count++;
            int cycle_start = find(path.begin(), path.end(), neighbor) - path.begin();
            vector<int> cycle(path.begin() + cycle_start, path.end());
            cycles.push_back(cycle);
            recStack[v] = false; // reset recStack for backtracking
            return true;
        }
    }

    recStack[v] = false;
    path.pop_back();
    return false;
}

void findCycles(const vector<vector<int>>& graph, int& cycle_count, vector<vector<int>>& cycles)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);

    for (int v = 0; v < n; ++v)
    {
        if (!visited[v])
        {
            vector<int> path;
            if (DFS(v, visited, recStack, graph, path, cycle_count, cycles))
                return;
        }
    }
}

int main()
{
    int numNodes = 4; // 노드 수
    vector<vector<int>> graph(numNodes); // 인접 리스트로 그래프 표현

    // 방향 그래프 간선 추가
    graph[0].push_back(1);
    graph[1].push_back(2);
    graph[2].push_back(0);
    graph[2].push_back(3);
    // [2 -> 0 -> 1 -> 2] 경로가 반복
    // 경로랑 갯수 추가 보고서 작성 때 예시 잘 들기
    int cycle_count = 0;
    vector<vector<int>> cycles;
    findCycles(graph, cycle_count, cycles);

    cout << "총 사이클의 개수: " << cycle_count << endl;
    cout << "각 사이클의 경로:" << endl;
    for (const auto& cycle : cycles)
    {
        for (int node : cycle)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
