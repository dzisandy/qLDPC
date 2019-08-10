#include <vector>
#include <functional>
using namespace std;

void unblock(size_t u, vector<int>& blocked, vector<vector<size_t>>& Bidx, vector<vector<int>> & Bmask) {
    blocked[u] = false;
    for (size_t w : Bidx[u]) {
        if (blocked[w]) unblock(w, blocked, Bidx, Bmask);
        Bmask[u][w] = 0;
    }
    //Bmask[u].assign(blocked.size(), 0);
    Bidx[u].clear();
}

bool circuit(size_t v, size_t col, int max_depth, vector<size_t>& stack, vector<int>& blocked, const vector<vector<size_t>>& A, vector<vector<size_t>>& Bidx, vector<vector<int>> &Bmask, const function<void(const vector<size_t>&)>& calc_ace) {
    bool f = false;
    stack.push_back(v);
    blocked[v] = true;
    for (size_t w : A[v])
        if (w == col) {
            stack.push_back(w);
            if (stack.size() > 3 && stack.size() <= max_depth+1) calc_ace(stack);
            stack.pop_back();
            f = true;
        } else if (!blocked[w])
            if (circuit(w, col, max_depth, stack, blocked, A, Bidx, Bmask, calc_ace)) f = true;
    if (f) unblock(v, blocked, Bidx, Bmask);
    else for (size_t w : A[v]) if (!Bmask[w][v]) {
        Bmask[w][v] = 1;
        Bidx[w].push_back(v);
    }
    stack.pop_back();
    return f;
}


