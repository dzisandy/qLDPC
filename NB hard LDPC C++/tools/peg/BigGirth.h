#ifndef BIGGIRTH
#define BIGGIRTH 1

#include <cstdlib>
#include <iostream> // C++ I/O library header
#include "Random.h"

class NodesInGraph{
 public:
  int numOfConnectionParityBit;
  int *connectionParityBit;
  int numOfConnectionSymbolBit;
  int *connectionSymbolBit;
  int maxDegParity;

  NodesInGraph(void);
  ~NodesInGraph(void);
  void setNumOfConnectionSymbolBit(int deg);
  void initConnectionParityBit(void);
  void initConnectionParityBit(int deg);
};

class BigGirth {
 public:
  int M, N;
  int K;
  int EXPAND_DEPTH;
  const char *filename;
  int *(*H);

  int *localGirth;
  
  NodesInGraph *nodesInGraph;
  Random *myrandom;

  BigGirth(int m, int n, int *symbolDegSequence, int sglConcent, int tgtGirth);
  BigGirth(void);

  void loadH(void);

  ~BigGirth(void);

 private:
  int selectParityConnect(int kthSymbol, int mthConnection, int & cycle);
  void updateConnection(int kthSymbol);

};

#endif
