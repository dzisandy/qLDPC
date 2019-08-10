
#include <mex.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "BigGirth.h"
#include "Random.h"

using namespace std;

NodesInGraph::NodesInGraph(void) {
  connectionParityBit = NULL;
  connectionSymbolBit = NULL;
}

void NodesInGraph::setNumOfConnectionSymbolBit(int deg) {
  if( deg <= 0 ) mexErrMsgTxt("Error: Wrong NodesInGraph::setNumOfConnectionSymbolBit()");
  numOfConnectionSymbolBit = deg;
  connectionSymbolBit = new int[deg];
}
void NodesInGraph::initConnectionParityBit(void) {
  maxDegParity=10000;
  numOfConnectionParityBit=0;
  connectionParityBit=new int[1];//dummy memory, actually not used
}
void NodesInGraph::initConnectionParityBit(int deg) {
  maxDegParity=deg;
  numOfConnectionParityBit=0;
  connectionParityBit=new int[1];//dummy memory, actually not used
}
NodesInGraph::~NodesInGraph(void) {
    delete [] connectionParityBit;
    delete [] connectionSymbolBit;
}

BigGirth::BigGirth(void) : H(NULL) { }

BigGirth::BigGirth(int M, int N, int *symbolDegSequence, int sglConcent, int tgtGirth) : H(NULL) {
  int i, j, k, m, index, localDepth=100;
  int *mid;

  EXPAND_DEPTH=(tgtGirth-4)/2; 
  if(EXPAND_DEPTH<0) EXPAND_DEPTH=0;

  //      corresponds to depth l in the PEG paper;  
  //      the target girth = 2*EXPAND_DEPTH+4
  //      if set large, then GREEDY algorithm

  myrandom=new Random();  //(12345678l, 987654321lu);

  this->M=M;
  this->N=N;

  mid=new int[M];

  localGirth=new int[N];

  nodesInGraph=new NodesInGraph [N];
  for(i=0;i<N;i++)
    nodesInGraph[i].setNumOfConnectionSymbolBit(symbolDegSequence[i]);

  j=0;
  for(k=0;k<N;k++) j+=symbolDegSequence[k];
  k=j/M;
  for(i=0;i<M;i++) mid[i]=k;
  for(i=0;i<j-k*M;i++) mid[i]++;
  k=0; for(i=0;i<M;i++) k+=mid[i];
  if(k!=j) mexErrMsgTxt("Wrong in computing maxDegParity!");

  for(i=0;i<M;i++) {
    if(sglConcent==0) nodesInGraph[i].initConnectionParityBit(mid[i]);
    else  nodesInGraph[i].initConnectionParityBit(); 
  } 
      
  for(k=0;k<N;k++){
    m=1000000;index=-1;
    for(i=0;i<M;i++){
      if(nodesInGraph[i].numOfConnectionParityBit<m && nodesInGraph[i].numOfConnectionParityBit<nodesInGraph[i].maxDegParity) {
	m=nodesInGraph[i].numOfConnectionParityBit;
	index=i;
      }
    }
    nodesInGraph[k].connectionSymbolBit[0]=index;//least connections of parity bit

    int iter=0; 
  ITER:
    localGirth[k]=100;
    for(m=1;m<nodesInGraph[k].numOfConnectionSymbolBit;m++){
      nodesInGraph[k].connectionSymbolBit[m]=selectParityConnect(k, m, localDepth);
      localGirth[k]=(localGirth[k]>localDepth)?localDepth:localGirth[k];      
      if(k>0 && localGirth[k]<localGirth[k-1] && iter<20) {iter++; goto ITER;}
      if(localGirth[k]==0 && iter<30) {iter++; goto ITER;}
    }
    //if((k+1)%100==0) {
    updateConnection(k);
  }

  delete [] mid;

  loadH();

}

BigGirth::~BigGirth(void) {
  if(H!=NULL) {
    for(int i=0;i<M;i++)
      delete [] H[i];
    delete [] H;
    H=NULL;
  }  
  delete [] localGirth;
  delete [] nodesInGraph;
  nodesInGraph=NULL;
  delete myrandom;
}

int BigGirth::selectParityConnect(int kthSymbol, int mthConnection, int & cycle) {
  int i, j, k, index, mincycles, numCur, cpNumCur;
  int *tmp, *med;
  int *current;//take note of the covering parity bits

  mincycles=0;
  tmp=new int[M]; med=new int[M];

  numCur=mthConnection;
  current=new int[mthConnection];
  for(i=0;i<mthConnection;i++) current[i]=nodesInGraph[kthSymbol].connectionSymbolBit[i];

LOOP:
  mincycles++;
  for(i=0;i<M;i++) tmp[i]=0;
  //maintain 
  for(i=0;i<mthConnection;i++) tmp[nodesInGraph[kthSymbol].connectionSymbolBit[i]]=1;
  for(i=0;i<numCur;i++){
    for(j=0;j<nodesInGraph[current[i]].numOfConnectionParityBit;j++){
      for(k=0;k<nodesInGraph[nodesInGraph[current[i]].connectionParityBit[j]].numOfConnectionSymbolBit;k++){
        tmp[nodesInGraph[nodesInGraph[current[i]].connectionParityBit[j]].connectionSymbolBit[k]]=1;
      }
    }
  }

  index=0; cpNumCur=0;
  for(i=0;i<M;i++) {
    if(tmp[i]==1) cpNumCur++;
    if(tmp[i]==1 || nodesInGraph[i].numOfConnectionParityBit>=nodesInGraph[i].maxDegParity) 
      index++;   
  }
  if(cpNumCur==numCur) {//can not expand any more
    //additional handlement to select one having least connections
    j=10000000; //dummy number
    for(i=0;i<M;i++){
      if(tmp[i]==0 && nodesInGraph[i].numOfConnectionParityBit<j && nodesInGraph[i].numOfConnectionParityBit<nodesInGraph[i].maxDegParity)
	j=nodesInGraph[i].numOfConnectionParityBit;
    }
    for(i=0;i<M;i++){
      if(tmp[i]==0){
	if(nodesInGraph[i].numOfConnectionParityBit!=j || nodesInGraph[i].numOfConnectionParityBit>=nodesInGraph[i].maxDegParity){
	  tmp[i]=1;
	}
      }
    }
    index=0;
    for(i=0;i<M;i++) if(tmp[i]==1) index++;
    //----------------------------------------------------------------
    j=(*myrandom).uniform(0, M-index)+1; //randomly selected
    index=0;
    for(i=0;i<M;i++){
      if(tmp[i]==0) index++;
      if(index==j) break;
    }
    delete [] tmp; tmp=NULL;
    delete [] current; current=NULL;
    return(i);
  }
  else if(index==M || mincycles>EXPAND_DEPTH){//covering all parity nodes or meet the upper bound on cycles
    
    cycle=mincycles-1;
    for(i=0;i<M;i++) tmp[i]=0;
    for(i=0;i<numCur;i++) tmp[current[i]]=1;
    index=0;
    for(i=0;i<M;i++) if(tmp[i]==1) index++;
    if(index!=numCur) {cout<<"Error in the case of (index==M)"<<endl;exit(-1);}
    //additional handlement to select one having least connections
    j=10000000; 
    for(i=0;i<M;i++){
      if(tmp[i]==0 && nodesInGraph[i].numOfConnectionParityBit<j && nodesInGraph[i].numOfConnectionParityBit<nodesInGraph[i].maxDegParity)
	j=nodesInGraph[i].numOfConnectionParityBit;
    }
    for(i=0;i<M;i++){
      if(tmp[i]==0){
	if(nodesInGraph[i].numOfConnectionParityBit!=j || nodesInGraph[i].numOfConnectionParityBit>=nodesInGraph[i].maxDegParity){
	  tmp[i]=1;
	}
      }
    }
      
    index=0;
    for(i=0;i<M;i++) if(tmp[i]==1) index++;
   
    j=(*myrandom).uniform(0, M-index)+1;
    index=0;
    for(i=0;i<M;i++){
      if(tmp[i]==0) index++;
      if(index==j) break;
    }
    delete [] tmp; tmp=NULL;
    delete [] current; current=NULL;
    return(i);
  }
  else if(cpNumCur>numCur && index!=M){
    delete [] current;
    current=NULL;
    numCur=cpNumCur;
    current=new int[numCur];
    index=0;
    for(i=0;i<M;i++) {
      if(tmp[i]==1) {current[index]=i; index++;}
    }
    goto LOOP;
  }
  else {
    mexErrMsgTxt("Error: BigGirth::selectParityConnect()");
  }
}


void BigGirth::updateConnection(int kthSymbol){
  int i, j, m;
  int *tmp;

  for(i=0;i<nodesInGraph[kthSymbol].numOfConnectionSymbolBit;i++){
    m=nodesInGraph[kthSymbol].connectionSymbolBit[i];//m [0, M) parity node
    tmp=new int[nodesInGraph[m].numOfConnectionParityBit+1];
    for(j=0;j<nodesInGraph[m].numOfConnectionParityBit;j++)
      tmp[j]=nodesInGraph[m].connectionParityBit[j];
    tmp[nodesInGraph[m].numOfConnectionParityBit]=kthSymbol;

    delete [] nodesInGraph[m].connectionParityBit;
    nodesInGraph[m].connectionParityBit=NULL;
    nodesInGraph[m].numOfConnectionParityBit++; //increase by 1
    nodesInGraph[m].connectionParityBit=new int[nodesInGraph[m].numOfConnectionParityBit];
    for(j=0;j<nodesInGraph[m].numOfConnectionParityBit;j++)
      nodesInGraph[m].connectionParityBit[j]=tmp[j];
    delete [] tmp;
    tmp=NULL;
  }
}

void BigGirth::loadH(void){
  int i, j;
  if(H==NULL) {
    H=new int*[M];
    for(i=0;i<M;i++) H[i]=new int[N];
  }

  for(i=0;i<M;i++){
    for(j=0;j<N;j++){
      H[i][j]=0;
    }
  }
  for(i=0;i<M;i++){
    for(j=0;j<nodesInGraph[i].numOfConnectionParityBit;j++){
      H[i][nodesInGraph[i].connectionParityBit[j]]=1;
    }
  }
}

