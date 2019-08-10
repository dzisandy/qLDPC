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
	
	if( (nrhs != 1) || (nlhs != 2) )
		mexErrMsgTxt("Usage: [girth, cyclesTable] = girthGet(H);");
	
	double *H = mxGetPr(prhs[0]);
	indx_t	M = mxGetM(prhs[0]);
	indx_t	N = mxGetN(prhs[0]);
	
	int *(*h) = NULL;
	h = new int*[M];
    for( int i=0; i < M; i++ ) 
		h[i]=new int[N];
	
	for ( int i = 0; i < M; ++i ) {
		for ( int j = 0; j < N; ++j ) {
			h[i][j] = (int)H[i + j*M];
		}
	}
	
	CyclesOfGraph cog(M, N, h);
	cog.getCyclesTable();
	
	plhs[0] = mxCreateDoubleScalar((double)cog.girth());
	plhs[1] = mxCreateDoubleMatrix(1, N, mxREAL);
	double *cyclesTable = mxGetPr(plhs[1]);
	
	for ( int i = 0; i < N; i++ )
		cyclesTable[i] = cog.cyclesTable[i];
	
	if( h != NULL ) {
    for( int i=0; i < M; i++ )
		delete [] h[i];
	delete [] h;
	h = NULL;
	}
}

