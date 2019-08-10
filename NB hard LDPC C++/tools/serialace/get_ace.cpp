#include <mex.h>
#include <cmath>
#include <vector>
#include <algorithm> // for min
#ifdef PROFILE
#include <callgrind.h>
#endif

using namespace std;

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray * prhs[])
{
    if (nrhs<8) mexErrMsgTxt("Usage: get_ace(H_exp, H_q, cycles, factor, max_depth, H_base, rows, q)");
    double* H_exp = mxGetPr(prhs[0]);
    size_t m = mxGetM(prhs[0]), n = mxGetN(prhs[0]);
    double* H_q = mxGetPr(prhs[1]);
    const mxArray *cycles = prhs[2];
    int ncycles = (int)mxGetNumberOfElements(cycles);
    int factor = (int)mxGetScalar(prhs[3]);
    int max_depth = (int)mxGetScalar(prhs[4]);
    int base_m = (int)mxGetM(prhs[5]);
    //int base_n = mxGetN(prhs[5]);
    double *H_base = mxGetPr(prhs[5]);
    double *rows = mxGetPr(prhs[6]);
    int q = (int)mxGetScalar(prhs[7]);
    plhs[0] = mxCreateDoubleMatrix(1, max_depth/2-1, mxREAL);
    double* current_ace = mxGetPr(plhs[0]);
    for (int i=0; i<max_depth/2-1; i++)
        current_ace[i] = -1;
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_START_INSTRUMENTATION;
#endif
    for (int j=0; j<ncycles; j++) {
        mxArray *cycle_a = mxGetCell(cycles, j);
        int cycle_len = (int)mxGetNumberOfElements(cycle_a);
        double *cycle_p = mxGetPr(cycle_a);
        //int cycle[cycle_len+1];
        vector<int> cycle(cycle_len+1);
        for (int i=0; i<cycle_len; i++)
            cycle[i] = (int)cycle_p[i]-1;
        for (int i=1; i<cycle_len; i+=2)
            cycle[i] = (int)rows[cycle[i]-n]-1;
        cycle[cycle_len] = cycle[0];
        int log_det_off = 0, log_det_nb = 0;
        for (int i=0; i<cycle_len-1; i+=2) {
            log_det_off += (int)H_exp[cycle[i]*m + cycle[i+1]] - (int)H_exp[cycle[i+2]*m + cycle[i+1]];
            log_det_nb += (int)H_q[cycle[i]*m + cycle[i+1]] - (int)H_q[cycle[i+2]*m + cycle[i+1]];
        }

        int weight = 0;
        for (int l=0; l<cycle_len; l+=2)
            for (int k=0; k<base_m; k++)
                weight += (int)H_base[cycle[l]*base_m + k];
        int max_mult = min(factor, (int)floor(max_depth/cycle_len));
        for (int mult=1; mult<=max_mult; mult++)
            if (mult * log_det_off % factor == 0 && mult*log_det_nb%(q-1) == 0) {
                // we have a cycle => calculate ACE
                int ace = mult*weight - mult*cycle_len;
                int idx = mult*cycle_len/2 - 2;
                if (current_ace[idx] < 0 || ace < current_ace[idx])
                    current_ace[idx] = ace;
                break;
            }
    }
#ifdef PROFILE
    CALLGRIND_TOGGLE_COLLECT;
    CALLGRIND_STOP_INSTRUMENTATION;
#endif
}
