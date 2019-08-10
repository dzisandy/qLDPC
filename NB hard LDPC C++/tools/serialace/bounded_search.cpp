#include <vector>
#include <utility>
#include <deque>
#include <tuple>
#include <cassert>
#include <functional>

using namespace std;

//pair<vector<int>, vector<int>>
void
bfs(const vector<vector<size_t>> & G, const vector<int>& blocked, int s, int md, vector<int>& parent, vector<int>& depth)
{
    //static vector<int> depth(G.size(), G.size());
    //static vector<int> parent(G.size(), -1);
    depth.assign(G.size(), G.size());
    parent.assign(G.size(), -1);
    depth[s] = 0;
    static deque<int> q;
    q.clear();
    q.push_back(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        int d = depth[u]+1;
        for (int v : G[u]) if (depth[v] > d && !blocked[v]) {
            depth[v] = d;
            parent[v] = u;
            if (d < md) q.push_back(v);
        }
    }
    //return make_pair(parent, depth);
}

void mark_tree(const vector<vector<size_t>>& G, const vector<int>& parent, vector<int> &mark, int root, int value)
{
    mark[root] = value;
    for (int i : G[root])
        if (parent[i] == root)
            mark_tree(G, parent, mark, i, value);
}

bool check_tree(const vector<vector<size_t>>& G, const vector<int>& parent, const vector<int> &mark, int root, const vector<int> &depth_s, const vector<int>& depth_t, int md)
{
    for (size_t v : G[root])
        if (mark[v] > mark[root] && depth_s[root] + depth_t[v] < md) return true;
        else if (parent[v] == root)
            if (check_tree(G, parent, mark, v, depth_s, depth_t, md)) return true;
    return false;
}

vector<size_t> lcp(int s, int t, int md, const vector<int>& blocked, const vector<vector<size_t>>& G, vector<int>& depth_t) {
    if (s == t) {
        return vector<size_t>(1,s);
    }
    static vector<int> depth_s, parent_s, parent_t;
    bfs(G, blocked, s, md, parent_s, depth_s);
    //tie(parent_s, depth_s) = bfs(G, blocked, s, md);
    if (parent_s[t] < 0) {
        return vector<size_t>();
    }
    bfs(G, blocked, t, md, parent_t, depth_t);
    //tie(parent_t, depth_t) = bfs(G, blocked, t, md);
    int p = t;
    int i = depth_s[t]+1;
    assert(depth_s[t] >= 0);
    static vector<size_t> path;
    path.resize(i);
    path[--i] = p;
    while (p != s) {
        p = parent_s[p];
        path[--i] = p;
    }
    static vector<int> mark;
    mark.assign(G.size(), -1);
    for (int i=0; i<path.size()-1; i++) {
        mark[path[i]] = i;
        for (int u : G[path[i]])
            if (parent_s[u] == path[i] && u != path[i+1])
                mark_tree(G, parent_s, mark, u, i);
    }
    mark_tree(G, parent_s, mark, path.back(), path.size()-1);
    for (int i=0; i<path.size()-1; i++)
        for (size_t u : G[path[i]])
            if (parent_s[u] == path[i] && u != path[i+1])
                if (check_tree(G, parent_s, mark, u, depth_s, depth_t, md)) {
                    path.resize(i+1);
                    return path;
                }
    return path;
}

void list_paths(int u, int t, int md, vector<size_t>& path, vector<int> &blocked, const vector<vector<size_t>> &G, const function<void(const vector<size_t>&)>& output)
{
    if (u == t) {
        path.push_back(u);
        output(path);
        path.pop_back();
        return;
    }
    if (md > G.size()) md = G.size();
    int len = path.size();
    static vector<int> depth;
    const vector<size_t> path2 = lcp(u,t,md-1,blocked,G,depth);
    if (path2.size() == 0) return;
    path.insert(path.end(), path2.begin(), path2.end());
    if (path.back() == t) output(path);
    else {
        for (int v : path2) blocked[v] = true;
        //vector<int> depth, parent;
        //bfs(G, blocked, t, md - path2.size() - 1, parent, depth);
        //tie(parent, depth) = bfs(G, blocked, t, md - path2.size() - 1);
        vector<int> good_neigbours; // To overcome static depth
        good_neigbours.reserve(G[path2.back()].size());
        for (int v : G[path2.back()])
            if (!blocked[v] && depth[v] < md - path2.size())
                good_neigbours.push_back(v);
        for (int v : good_neigbours)
            list_paths(v, t, md - path2.size(), path, blocked, G, output);
        for (int v : path2) blocked[v] = false;
    }
    path.resize(len);
}

void list_paths(int s, int t, int md, const vector<vector<size_t>> &G, const function<void(const vector<size_t>&)>& output)
{
    vector<int> blocked(G.size(), 0);
    vector<size_t> path;
    list_paths(s,t,md, path, blocked, G, output);
}
