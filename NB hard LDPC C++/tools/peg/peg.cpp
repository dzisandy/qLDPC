/************************************************************************/
/*                                                                      */
/*        Free software: Progressive edge-growth (PEG) algorithm        */
/*        Created by Xiaoyu Hu                                          */
/*                   Evangelos Eletheriou                               */
/*                   Dieter Arnold                                      */
/*        IBM Research, Zurich Research Lab., Switzerland               */
/*                                                                      */
/*        The C++ sources files have been compiled using xlC compiler   */
/*        at IBM RS/6000 running AIX. For other compilers and platforms,*/
/*        minor changes might be needed.                                */
/*                                                                      */
/*        Bug reporting to: xhu@zurich.ibm.com                          */
/**********************************************************************/

////
// Modified by F. P. Beekhof; 2008 / 08 / 19
////
#include <mex.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include "BigGirth.h"
#include "Random.h"
#include "CyclesOfGraph.h"

const double EPS = 1e-6;

typedef long indx_t;

using namespace std;

/* main function that interfaces with MATLAB */
void mexFunction(
				 int            nlhs,
				 mxArray       *plhs[],
				 int            nrhs,
				 const mxArray *prhs[] ) {
	
	if( (nrhs != 4) || (nlhs != 1) )
		mexErrMsgTxt("Usage: H = peg(M, N, LDeg, L);");
	
	int sglConcent=1;  // default to non-strictly concentrated parity-check distribution
	int targetGirth=100000; // default to greedy PEG version
	double *H = NULL;
	
	int M = (int)mxGetScalar(prhs[0]);
	int N = (int)mxGetScalar(prhs[1]);
	
	double *LDeg = mxGetPr(prhs[2]);
	indx_t	LDegNum = mxGetN(prhs[2]);
	double *L = mxGetPr(prhs[3]);
	indx_t	LNum = mxGetN(prhs[3]);
	
	if( LDegNum != LNum )
		mexErrMsgTxt("Error: Number of LDeg must equal number of L");
	
	std::vector<int> degSeq(N);
	int m = (int) LNum;
	std::vector<int> deg(m);
	std::vector<double> degFrac(m);
	
	for( int i=0; i < m; i++ ) deg[i] = LDeg[i];
	for( int i=0; i < m; i++ ) degFrac[i] = L[i];

	double dtmp = 0.0;
	for( int i=0; i < m; i++ ) dtmp += degFrac[i];
	if( abs(dtmp-1.0) > EPS )
		mexErrMsgTxt("Error: Invalid degree distribution (node perspective): sum != 1.0");

	for( int i=1; i < m; ++i ) degFrac[i] += degFrac[i-1];
	for( int i=0; i < N; ++i ) {
		dtmp = double(i)/double(N);
		int j;
		for( j=m-1; j >= 0; --j ) {
			if( dtmp > degFrac[j] ) break;
		}
		if( dtmp < degFrac[0] ) degSeq[i] = deg[0];
		else degSeq[i] = deg[j+1];
	}

	BigGirth bigGirth(M, N, &degSeq[0], sglConcent, targetGirth);

	plhs[0] = mxCreateDoubleMatrix(M, N, mxREAL);
	H = mxGetPr(plhs[0]);
	
	for ( int i = 0; i < M; ++i ) {
		for ( int j = 0; j < N; ++j ) {
			H[i + j*M] = bigGirth.H[i][j];
		}
	}
	
}

