#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <vector>
#include <list>
#include <cstdint>
#include <algorithm>

#include <mex.h>
#include <matrix.h>
#include "GaloisField.h"
#include "Matrix.h"
#include "common.h"
#include "LDPC.h"
#include "ObjectHandle.h"

#define ABS(A) (((A) >= 0) ? (A) : -(A))
using namespace std;

//=======================================================================================================================================
//============================================================= Hard decision decoder ==================================================
//=======================================================================================================================================



// Majority Sequential decoding
bool MajoritySeq(LDPC& ldpc, vector<FieldElement>& r, int theta, vector<int>& y) {
    Matrix<FieldElement> S(1, ldpc.m);
    vector <int> msg(Q, 0);
	vector<FieldElement> c;
	int F = 0;
    int b = 1;
    int itr = 0;

    for (int i = 0; i < ldpc.m; ++i)
    {
        S(i) = 0;
        for (int j = 0; j < ldpc.row_weight[j]; ++j)
        {
            int k = ldpc.row_col(i,j);
            S(i) += ldpc.H(i, j)*r[k];
        }

    }
    while (b == 1) {
        b = 0;
        for (int i = 0; i < ldpc.n; i++) {
            for (int j = 0; j < ldpc.col_weight[i]; j++) {
                int k = ldpc.col_row(i, j);
                FieldElement temp = S(1,k)*(ldpc.H(k, i)^(-1));
                msg[temp.getElement()] += 1;
            }
        }

        int *p = &*max_element(msg.begin(), msg.end());
        auto a = reinterpret_cast<uintptr_t>(p);
        int z = msg[0];
        FieldElement element = FieldElement(distance(msg.begin(), max_element(msg.begin(), msg.end())));

        if (a - z > theta) {
            for (int i = 0; i < ldpc.n; i++) {
                r[i] = r[i] + element;
                b = 1;
            }
        }
    }
    F = 1;
    for (int i = 0; i < ldpc.n; i++) {
        c[i] = r[i];
		FieldElement temp2 = c[i];
		y[i] = temp2.getElement();
    }
    for (int i = 0; i < ldpc.m; i++) {
        if (S[i] == 0) {
            itr += 1;
        }

    }
    if (itr == ldpc.m) {
        F = 0;
    }
    return 0;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int command = (int) *(mxGetPr(prhs[0]));
	double* input = 0;
    switch (command) {
        case 0: {
            char buf[256];
            mxGetString(prhs[1], buf, 256);

            LDPC *pLdpc = new LDPC();
            pLdpc->init(buf);

            if (nlhs > 0) {
                plhs[0] = create_handle(pLdpc);
            }
            if (nlhs > 1) {
                plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
                *((double *) (mxGetPr(plhs[1]))) = pLdpc->n;
            }
            if (nlhs > 2) {
                plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
                *((double *) (mxGetPr(plhs[2]))) = pLdpc->m;
            }
            break;
        }
		case 1: {
			LDPC& ldpc = get_object<LDPC>(prhs[1]);
			
			vector<int> x;
			//vector<FieldElement> y;
			vector<int> y;
			vector<FieldElement> rx_cwd;
			// rx_cwd
            input = mxGetPr(prhs[2]);
            
            for(int i = 0; i < ldpc.n; ++i)
            {
                rx_cwd[i] = input[i];
            }
			// theta
			int theta = (int)*(mxGetPr(prhs[3]));
			
			bool result = true;
            result = MajoritySeq(ldpc, rx_cwd, theta, y);
                     
            /* denial flag */
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            *((double*)(mxGetPr(plhs[0]))) = result;
			
		    double* data = NULL;
		 
		     /* hard desicion */
		     plhs[1] = mxCreateDoubleMatrix(1, ldpc.n, mxREAL);
		     data = mxGetPr(plhs[1]);
		     for(int i = 0; i < ldpc.n; ++i)
		     {
			     data[i] = y[i];
		     }
			 break;
		}


    }
}
