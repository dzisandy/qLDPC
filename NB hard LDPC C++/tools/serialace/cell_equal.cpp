#include <mex.h>
#include <set>
#include <vector>

using namespace std;

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray * prhs[])
{
    if (nrhs<2) {
        mexErrMsgTxt("two arguments required");
    }
    if (!mxIsCell(prhs[0]) || !mxIsCell(prhs[1]))
        mexErrMsgTxt("only cell array accepted");
    size_t N = mxGetM(prhs[0])*mxGetN(prhs[0]);
    if (mxGetM(prhs[1])*mxGetN(prhs[1]) != N) {
        plhs[0] = mxCreateLogicalScalar(false);
        return;
    }
    set<vector<double>> s;
    for (size_t i=0; i<N; i++) {
        mxArray *d = mxGetCell(prhs[0], (mwIndex)i);
        double* data = mxGetPr(d);
        size_t len = mxGetN(d) * mxGetM(d);
        s.insert(vector<double>(data, data+len));
    }
    for (size_t i=0; i<N; i++) {
        mxArray *d = mxGetCell(prhs[1], (mwIndex)i);
        double* data = mxGetPr(d);
        size_t len = mxGetN(d) * mxGetM(d);
        vector<double> vec(data, data+len);
        auto it = s.find(vec);
        if (it != s.end()) s.erase(it);
        else {
            plhs[0] = mxCreateLogicalScalar(false);
            return;
        }
    }
    plhs[0] = mxCreateLogicalScalar(true);
}
