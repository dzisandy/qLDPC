#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <errno.h>
#include <vector>
#include <list>

#include <mex.h>
#include <matrix.h>

#include "Matrix.h"
#include "common.h"
#include "LDPC.h"
#include "ObjectHandle.h"

#define ABS(A) (((A) >= 0) ? (A) : -(A))
using namespace std;

//=======================================================================================================================================
//============================================================= Hard desicion decoders ==================================================
//=======================================================================================================================================

// Threshold decoding
bool Threshold(LDPC& ldpc, const vector<FieldElement>& x, int max_iter, int theta, vector<FieldElement>& y, int* number_of_iter)
{
    Matrix<FieldElement>  R_msgs(ldpc.m, ldpc.rmax);
    Matrix<FieldElement>  Q_msgs(ldpc.m, ldpc.rmax);
    list<int> affected_rows;
    
    for (int i = 0; i < ldpc.n; ++i)
    {
        y[i] = x[i];
        
        for (int j = 0; j < ldpc.col_weight[i]; ++j)
        {
            Q_msgs(ldpc.msgs_col(i,j)) = y[i];
        }
    }

    for (int j = 0; j < ldpc.m; j++)
    {
        affected_rows.push_back(j);
    }

    for (int loop = 0; loop < max_iter; ++loop)
    {
        // Update Q
        for (int i = 0; i < ldpc.n; i++)
        {
            // Update R
            for (list<int>::const_iterator it = affected_rows.begin(); it != affected_rows.end(); ++it)
            {
                int j = *it;
                FieldElement sum;
                for (int k = 0; k < ldpc.row_weight[j]; k++)
                {
                    sum += Q_msgs(j, k)*ldpc.H(j,k);
                }
                for (int k = 0; k < ldpc.row_weight[j]; k++)
                {
                    R_msgs(j,k) = sum + Q_msgs(j, k)*ldpc.H(j,k); // Minus not defined
                    R_msgs(j,k) = R_msgs(j,k)*(ldpc.H(j,k)^(-1));
                }
            }
            affected_rows.clear();
            vector<int> result(Q, 0);
            for (int k = 0; k < ldpc.col_weight[i]; k++)
            {
                result[R_msgs(ldpc.msgs_col(i,k)).getElement()] += 1;
            }
            int max = 0;
            int index = -1;
            for (int k = 0; k < Q; k++)
            {
                if (result[k] >= max)
                {
                    max = result[k];
                    index = k;
                }
            }
            if (max - result[0] >=  theta){
                if (y[i].getElement() != index)
                {
                    y[i] = FieldElement(index);
                    for (int k = 0; k < ldpc.col_weight[i]; k++)
                    {
                        Q_msgs(ldpc.msgs_col(i,k)) = y[i];
                        affected_rows.push_back(ldpc.col_row(i,k));
                    }
                }
            } 
        }
    }

    if (number_of_iter)
    {
        *number_of_iter = max_iter;
    }
    return 0;
}

// Majority decoding
bool Majority(LDPC& ldpc, const vector<FieldElement>& x, int max_iter, vector<FieldElement>& y, int* number_of_iter)
{
    Matrix<FieldElement>  R_msgs(ldpc.m, ldpc.rmax);
    Matrix<FieldElement>  Q_msgs(ldpc.m, ldpc.rmax);
    
    for (int i = 0; i < ldpc.n; ++i)
    {
        y[i] = x[i];
        
        for (int j = 0; j < ldpc.col_weight[i]; ++j)
        {
            Q_msgs(ldpc.msgs_col(i,j)) = y[i];
        }
    }

    for (int loop = 0; loop < max_iter; ++loop)
    {
        // Update R
        for (int j = 0; j < ldpc.m; j++)
        {
            FieldElement sum;
            for (int k = 0; k < ldpc.row_weight[j]; k++)
            {
                sum += Q_msgs(j, k)*ldpc.H(j,k);
            }
            for (int k = 0; k < ldpc.row_weight[j]; k++)
            {
                R_msgs(j,k) = sum + Q_msgs(j, k)*ldpc.H(j,k); // Minus not defined
                R_msgs(j,k) = R_msgs(j,k)*(ldpc.H(j,k)^(-1));
            }
        }
        // Update Q
        for (int i = 0; i < ldpc.n; i++)
        {
            vector<int> result(Q, 0);
            for (int k = 0; k < ldpc.col_weight[i]; k++)
            {
                result[R_msgs(ldpc.msgs_col(i,k)).getElement()] += 1;
            }
            int max = 0;
            int index = -1;
            for (int k = 0; k < Q; k++)
            {
                if (result[k] >= max)
                {
                    max = result[k];
                    index = k;
                }
            }
            y[i] = index;
            for (int k = 0; k < ldpc.col_weight[i]; k++)
		    {
		        Q_msgs(ldpc.msgs_col(i,k)) = y[i];
	        }
        }
    }

    if (number_of_iter)
    {
        *number_of_iter = max_iter;
    }
    return 1;
}

// Majority Sequential decoding
bool MajoritySeq(LDPC& ldpc, const vector<FieldElement>& x, int max_iter, vector<FieldElement>& y, int* number_of_iter)
{
    Matrix<FieldElement>  R_msgs(ldpc.m, ldpc.rmax);
    Matrix<FieldElement>  Q_msgs(ldpc.m, ldpc.rmax);
    list<int> affected_rows;
    
    for (int i = 0; i < ldpc.n; ++i)
    {
        y[i] = x[i];
        
        for (int j = 0; j < ldpc.col_weight[i]; ++j)
        {
            Q_msgs(ldpc.msgs_col(i,j)) = y[i];
        }
    }

    for (int j = 0; j < ldpc.m; j++)
    {
        affected_rows.push_back(j);
    }

    for (int loop = 0; loop < max_iter; ++loop)
    {
        // Update Q
        for (int i = 0; i < ldpc.n; i++)
        {
            // Update R
            for (list<int>::const_iterator it = affected_rows.begin(); it != affected_rows.end(); ++it)
            {
                int j = *it;
                FieldElement sum;
                for (int k = 0; k < ldpc.row_weight[j]; k++)
                {
                    sum += Q_msgs(j, k)*ldpc.H(j,k);
                }
                for (int k = 0; k < ldpc.row_weight[j]; k++)
                {
                    R_msgs(j,k) = sum + Q_msgs(j, k)*ldpc.H(j,k); // Minus not defined
                    R_msgs(j,k) = R_msgs(j,k)*(ldpc.H(j,k)^(-1));
                }
            }
            affected_rows.clear();
            vector<int> result(Q, 0);
            for (int k = 0; k < ldpc.col_weight[i]; k++)
            {
                result[R_msgs(ldpc.msgs_col(i,k)).getElement()] += 1;
            }
            int max = 0;
            int index = -1;
            for (int k = 0; k < Q; k++)
            {
                if (result[k] >= max)
                {
                    max = result[k];
                    index = k;
                }
            }
            if (y[i].getElement() != index)
            {
                y[i] = FieldElement(index);
                for (int k = 0; k < ldpc.col_weight[i]; k++)
		        {
		            Q_msgs(ldpc.msgs_col(i,k)) = y[i];
	                affected_rows.push_back(ldpc.col_row(i,k));
                }
            }
        }
    }

    if (number_of_iter)
    {
        *number_of_iter = max_iter;
    }
    return 1;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int command = (int)*(mxGetPr(prhs[0]));
    switch(command)
    {
        case 0:
        {
            char buf[256];
            mxGetString(prhs[1], buf, 256); 
             
            LDPC* pLdpc = new LDPC();
            pLdpc->init(buf);
            
            if (nlhs > 0)
            {
	            plhs[0] = create_handle(pLdpc);
            }
            if (nlhs > 1)
            {
                plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
                *((double*)(mxGetPr(plhs[1]))) = pLdpc->n;
            }
            if (nlhs > 2)
            {	
                plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
                *((double*)(mxGetPr(plhs[2]))) = pLdpc->m;
            }
            break;   
        }
        /* Hard desicion decoders */
        
        case 5:
        case 6:
        case 7:
        {
            LDPC& ldpc = get_object<LDPC>(prhs[1]);

            vector<FieldElement> x(ldpc.n);
            vector<FieldElement> y(ldpc.n);

            double* input = mxGetPr(prhs[2]);
            int iMaxNumberOfIterations = (int)*(mxGetPr(prhs[3]));
            
            for(int i = 0; i < ldpc.n; ++i)
            {
                x[i] = FieldElement((int)input[i]);
            }
         
            int number_of_iter = 0;
         
            bool result = true;
            if (command == 5)
            {
                result = Majority(ldpc, x, iMaxNumberOfIterations, y, &number_of_iter);
            }
            else if (command == 6)
            {
                result = MajoritySeq(ldpc, x, iMaxNumberOfIterations, y, &number_of_iter);
            }
            else if (command == 7)
            {
                double* thetas = mxGetPr(prhs[4]);
                int thetas_num = (int)mxGetScalar(prhs[5]);
                
               for (int itr = 0; itr < thetas_num; itr++)
               {
                result = Threshold(ldpc, x, iMaxNumberOfIterations, thetas[itr], y, &number_of_iter);
                if (result == 1)
                {
                    break;
                }
                x = y; 
               }
            }
                     
            /* denial flag */
            plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
            *((double*)(mxGetPr(plhs[0]))) = result;
         
            /* number of iterations */
		    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
		    *((double*)(mxGetPr(plhs[1]))) = number_of_iter;
		 
		    double* data = NULL;
		 
            /* hard desicion */
            plhs[2] = mxCreateDoubleMatrix(1, ldpc.n, mxREAL);
            data = mxGetPr(plhs[2]);
            //printf("data = ");
            for(int i = 0; i < ldpc.n; ++i)
            {
                data[i] = y[i].getElement();
                //printf("%d ", data[i]);
            }
            //printf("\n");

            break;
        }
        default:
        break;
    }
}


// Trash 

//Threshold //w(S) = 0 -> return 1; else return 0;
// bool Threshold(LDPC& ldpc, const vector<FieldElement>& x, int theta, vector<FieldElement>& y)
// {
//     vector<FieldElement> S(ldpc.m);
//     int b = 1;
//     int syndromeWeight = 0;
// 
//     
//     for (int i = 0; i < ldpc.n; ++i)
//     {
//         y[i] = x[i];
//     }
//     
//     //Update syndrome
//     for (int ii = 0; ii < ldpc.m; ++ii)
//     {
//         S[ii] = 0;
//         for (int j = 0; j < ldpc.row_weight[ii]; ++j)
//         {
//             {
//             S[ii] += ldpc.H(ii, j)*x[ldpc.row_col(ii,j)];
//             }
//         }
//         //y[i] = S[i];
//     }
//     
//     while (b == 1)
//     {
//         b = 0;        
//         for (int i = 0; i < ldpc.n; i++)
//         {
//             vector<int> counter(Q);
//             for (int k = 0; k < ldpc.col_weight[i]; k++)
//             {
//                 FieldElement msg = ((ldpc.H(k,i))^(-1))*S[k];
//                 counter[msg.getElement()]+= 1;
//             }
//             int z = counter[0];
//             int a = 0;
//             int idx = -1;
//             for (int ii = 1; ii < counter.size(); ii++){
//                 if (counter[ii] >= a ){
//                     a = counter[ii];
//                     idx = ii;
//                 }
//             }
//             FieldElement m = idx;
//             if (a - z > theta)
//             {
//                 y[i] = y[i] + m;
//                 for (int ii = 0; ii < ldpc.m; ++ii)
//                 {
//                     S[ii] = 0;
//                     for (int j = 0; j < ldpc.row_weight[ii]; ++j)
//                     {
//                        S[ii] += ldpc.H(ii, j)*y[ldpc.row_col(ii,j)];
//                     }
//                 }
//                 b = 1;
//             }
//         }
//         
//         int syndromeWeight_temp = 0;
//         for (int ii = 0; ii < ldpc.m; ++ii)
//         {
//             if (S[ii].getElement() != 0)
//                 syndromeWeight_temp += 1; 
//         }
//         if (syndromeWeight_temp > syndromeWeight)
//         {
//             return 0;
//             
//         }
//         else
//         {
//             syndromeWeight = syndromeWeight_temp;
//         }
//     }
//     if (syndromeWeight == 0)
//     {
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }
