#include <vector>
#include <set>
#include <mex.h>
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
vector<vector<size_t>> res;

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
        if (w == s && stack.size() > 2) {
            if (stack.size() < depth) res.push_back(stack);
            f = true;
        } else if (!blocked[w])
            if (circuit(w)) f = true;
    if (f) unblock(v);
    else for (size_t w : A[v]) B[w].insert(v);
    stack.pop_back();
    return f;
}

template<typename T>
void fillA(const T* H, size_t m, size_t n) {
    for (size_t i=0; i<m; i++)
        for (size_t j=0; j<n; j++)
            if (H[i + j*m]) {
                A[j].push_back(i+n);
                A[i+n].push_back(j);
            }
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray * prhs[])
{
    if (nrhs < 3)
        mexErrMsgIdAndTxt("getCycles:not_enough_input_arguments", "Usage: getCycles(<vertex>, <matrix H>, <depth>");
    s = (size_t)mxGetScalar(prhs[0])-1;
    size_t m = mxGetM(prhs[1]);
    size_t n = mxGetN(prhs[1]);
    depth = (size_t)mxGetScalar(prhs[2]);
    blocked = vector<bool>(m+n);
    A = vector<vector<size_t>>(m+n);
    B = vector<set<size_t>>(m+n);
    stack.clear();
    res.clear();
    if (mxIsLogical(prhs[1])) fillA(mxGetLogicals(prhs[1]), m, n);
    else if (mxIsDouble(prhs[1]) && !mxIsComplex(prhs[1])) fillA(mxGetPr(prhs[1]), m, n);
    else mexErrMsgIdAndTxt("getCycles:type_not_supported", "Only double and logical are supported for matrix H");
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_START_INSTRUMENTATION;
#endif
    circuit(s);
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;
#endif
    plhs[0] = mxCreateCellMatrix(1,(mwSize)res.size());
    for (size_t i=0; i<res.size(); i++) {
        mxArray *result = mxCreateDoubleMatrix(1,(mwSize)res[i].size(),mxREAL);
        double *data = mxGetPr(result);
        for (size_t j=0; j<res[i].size(); j++)
            data[j] = (double)res[i][j]+1;
        mxSetCell(plhs[0], (mwIndex)i, result);
    }
}
