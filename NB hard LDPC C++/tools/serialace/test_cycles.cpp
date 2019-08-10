#include <vector>
#include <set>
#include <mex.h>
#include <algorithm>
#ifdef PROFILE
#include <callgrind.h>
#endif

using namespace std;

vector<bool> blocked;
vector<vector<size_t>> A;
vector<set<size_t>> B;
vector<size_t> stack;
size_t s;
size_t depth;
int next_v;
vector<vector<size_t>> res1, res2, res3;

#include <functional>
extern void list_paths(int u, int t, int md, vector<size_t>& path, vector<int> &blocked, const vector<vector<size_t>> &G, const function<void(const vector<size_t>&)>& output);

void append2(const vector<size_t>& v)
{
    res2.push_back(v);
}

void append3(const vector<size_t>& v)
{
    res3.push_back(v);
}

void unblock(size_t u) {
    blocked[u] = false;
    for (size_t w : B[u])
        if (blocked[w]) unblock(w);
    B[u].clear();
}

bool circuit(size_t v) {
    bool f = false;
    stack.push_back(v);
    blocked[v] = true;
    for (size_t w : A[v])
        if (w == s) {
            stack.push_back(w);
            if (stack.size() <= depth+1 && stack[1] == next_v && stack.size() > 3) res1.push_back(stack);
            stack.pop_back();
            f = true;
        } else if (!blocked[w])
            if (circuit(w)) f = true;
    if (f) unblock(v);
    else for (size_t w : A[v]) B[w].insert(v);
    stack.pop_back();
    return f;
}

bool circuit(size_t v, size_t col, int max_depth, vector<size_t>& stack, vector<int>& blocked, const vector<vector<size_t>>& A, vector<vector<size_t>>& Bidx, vector<vector<int>> &Bmask, const function<void(const vector<size_t>&)>& calc_ace);

template<typename T>
void fillA(const T* H, size_t m, size_t n) {
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            if (H[i + j*m]) {
                A[j].push_back(i+n);
                A[i+n].push_back(j);
            }
}

mxArray* toCell(const vector<vector<size_t>>& v)
{
    mxArray *res = mxCreateCellMatrix(1,(mwSize)v.size());
    for (size_t i=0; i<v.size(); i++) {
        mxArray *result = mxCreateDoubleMatrix(1,(mwSize)v[i].size(),mxREAL);
        double *data = mxGetPr(result);
        for (size_t j=0; j<v[i].size(); j++)
            data[j] = (double)v[i][j]+1;
        mxSetCell(res, (mwIndex)i, result);
    }
    return res;
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray * prhs[])
{
    if (nrhs < 4)
        mexErrMsgIdAndTxt("getCycles:not_enough_input_arguments", "Usage: getCycles(<vertex>, <matrix H>, <depth>, <next_v>");
    s = (size_t)mxGetScalar(prhs[0])-1;
    size_t m = mxGetM(prhs[1]);
    size_t n = mxGetN(prhs[1]);
    depth = (size_t)mxGetScalar(prhs[2]);
    next_v = (int)mxGetScalar(prhs[3])+n-1;
    if (next_v >= m+n)
        mexErrMsgIdAndTxt("getCycles:bad_next", "Not such check node");
    blocked = vector<bool>(m+n);
    A = vector<vector<size_t>>(m+n);
    B = vector<set<size_t>>(m+n);
    stack.clear();
    res1.clear();
    res2.clear();
    res3.clear();
    if (mxIsLogical(prhs[1])) fillA(mxGetLogicals(prhs[1]), m, n);
    else if (mxIsDouble(prhs[1]) && !mxIsComplex(prhs[1])) fillA(mxGetPr(prhs[1]), m, n);
    else mexErrMsgIdAndTxt("getCycles:type_not_supported", "Only double and logical are supported for matrix H");
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_START_INSTRUMENTATION;
#endif
    circuit(s);
    vector<int> bl(m+n, 0);
    stack.clear();
    stack.push_back(s);
    int Asz = A[s].size();
    for (int i=0; i<A[s].size(); i++) if (A[s][i] == next_v) {
        swap(A[s][i], A[s].back());
        A[s].pop_back();
        break;
    }
    if (A[s].size() != Asz - 1) {
        mexPrintf("%d-variable and %d-check node are not adjacent\n", s+1, next_v-n+1);
        return;
    }
    for (int i=0; i<A[next_v].size(); i++) if (A[next_v][i] == s) {
        swap(A[next_v][i], A[next_v].back());
        A[next_v].pop_back();
        break;
    }
    list_paths(next_v, s, depth, stack, bl, A, append2);
    stack.clear();
    stack.push_back(s);
    bl.assign(m+n,0);
    vector<vector<int>> Bmask(A.size(), vector<int>(A.size(), 0));
    vector<vector<size_t>> Bidx(A.size(), vector<size_t>());
    circuit(next_v, s, depth, stack, bl, A, Bidx, Bmask, append3);
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;
#endif
    sort(res1.begin(), res1.end());
    sort(res2.begin(), res2.end());
    sort(res3.begin(), res3.end());
    plhs[0] = toCell(res1);
    plhs[1] = toCell(res2);
    plhs[2] = toCell(res3);
}
