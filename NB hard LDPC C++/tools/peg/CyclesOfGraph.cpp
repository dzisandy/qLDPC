#include "CyclesOfGraph.h"

NodesOfGraph::NodesOfGraph(void) { parityConnections=NULL;symbolConnections=NULL;
}
NodesOfGraph::~NodesOfGraph(void) {
  delete [] parityConnections;
  delete [] symbolConnections;
  delete [] symbolMapping;

}

void NodesOfGraph::setParityConnections(int num, int *value) {
  numOfParityConnections=num;
  parityConnections=new int[num];
  for(int i=0;i<numOfParityConnections;i++){
    parityConnections[i]=value[i];
    //cout<<parityConnections[i]<<" ";
  }
  //cout<<endl;
}
void NodesOfGraph::setSymbolConnections(int num, int *value) {
  numOfSymbolConnections=num;
  symbolConnections=new int[num];
  for(int i=0;i<numOfSymbolConnections;i++){
    symbolConnections[i]=value[i];
    //cout<<symbolConnections[i]<<" ";
  }
  //cout<<endl;
}
void NodesOfGraph::setSymbolMapping(int num, int *value) {
  numOfSymbolMapping=num;
  //cout<<num<<endl;
  symbolMapping=new int[num];
  for(int i=0;i<numOfSymbolMapping;i++){
    symbolMapping[i]=value[i];
    //cout<<symbolMapping[i]<<" ";
  }
  //cout<<endl;
}

CyclesOfGraph::CyclesOfGraph(int mm, int n, int *(*h)){
  int i, j, k, m, index;
  M=mm;
  N=n;
  H=h;

  tmp=new int [N];
  med=new int [N];
  tmpCycles=new int [N];
  cyclesTable=new int [N];
  nodesOfGraph=new NodesOfGraph [N];

  //cout<<M<<" "<<N<<endl;
  /*
  for(i=0;i<M;i++){
    for(j=0;j<N;j++)
      cout<<H[i][j]<<" ";
    cout<<endl;
  }
  */
  for(i=0;i<N;i++){
    index=0;
    for(j=0;j<M;j++){
      if(H[j][i]==1){
	tmp[index]=j;
	index++;
      }
    }
    nodesOfGraph[i].setSymbolConnections(index, tmp);
  }
  for(i=0;i<M;i++){
    index=0;
    for(j=0;j<N;j++){
      if(H[i][j]==1){
	tmp[index]=j;
	index++;
      }
    }
    nodesOfGraph[i].setParityConnections(index, tmp);
  }
  for(i=0;i<N;i++){
    index=0;
    for(j=0;j<nodesOfGraph[i].numOfSymbolConnections;j++){
      for(k=0;k<nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].numOfParityConnections;k++){
	int t=0;
	for(m=0;m<index;m++){
	  if(nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].parityConnections[k]==tmp[m]){
	    t=1; break;
	  }
	}
	if(nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].parityConnections[k]==i) t=1;
	if(t==0) {
	  tmp[index]=nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].parityConnections[k];
	  index++;
	}
      }
    }
    nodesOfGraph[i].setSymbolMapping(index, tmp);
  }
}

CyclesOfGraph::~CyclesOfGraph(void){
  delete [] tmp;
  tmp=NULL;
  delete [] med;
  med=NULL;
  delete [] tmpCycles;
  tmpCycles=NULL;
  delete [] cyclesTable;
  cyclesTable=NULL;
  delete [] nodesOfGraph;
  nodesOfGraph=NULL;
}
  
void CyclesOfGraph::getCyclesTable(void) {
  int i, j, k, m, n, t, imed;
  for(i=0;i<N;i++){
    //special handlement for nodes having only one or zero connections
    if(nodesOfGraph[i].numOfSymbolConnections<=1) {
      cyclesTable[i]=2*N; 
      continue;
    }
    for(j=0;j<nodesOfGraph[i].numOfSymbolConnections-1;j++){ //-1 because the graph is undirected
      for(k=0;k<nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].numOfParityConnections;k++){
	tmp[k]=nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].parityConnections[k];
	//cout<<tmp[k]<<" ";
      }
      //cout<<endl;
      int cycles=2;
      int index=nodesOfGraph[nodesOfGraph[i].symbolConnections[j]].numOfParityConnections;
    LOOP:
      imed=0;
      for(k=0;k<index;k++){
	if(tmp[k]==i) continue;
	//cout<<"k="<<k<<" "<<tmp[k]<<endl;
	for(m=0;m<nodesOfGraph[tmp[k]].numOfSymbolConnections;m++){
	  for(n=0;n<nodesOfGraph[i].numOfSymbolConnections;n++){
	    if((n!=j)&&(nodesOfGraph[tmp[k]].symbolConnections[m]==nodesOfGraph[i].symbolConnections[n])){
	      cycles+=2;
	      goto OUTLOOP;
	    }
	  }
	}
	for(m=0;m<nodesOfGraph[tmp[k]].numOfSymbolMapping;m++){
	  t=0;
	  for(int l=0;l<imed;l++) {
	    if(nodesOfGraph[tmp[k]].symbolMapping[m]==med[l]){
	      t=1; break;
	    }
	  }
	  if(t==0){
	    med[imed]=nodesOfGraph[tmp[k]].symbolMapping[m];
	    //cout<<med[imed]<<endl;
	    imed++;
	  }
	}
      }
      index=imed;//cout<<index<<" "<<endl;
      for(k=0;k<index;k++) {
	tmp[k]=med[k];//cout<<tmp[k]<<" ";
      }
      //cout<<"j="<<j<<endl;
      cycles+=2;
      if(cycles>=2*N) //dead lock 
	goto OUTLOOP;
      else
	goto LOOP;
    OUTLOOP:
      tmpCycles[j]=cycles;
    }
    //for(j=0;j<nodesOfGraph[i].numOfSymbolConnections-1;j++) cout<<tmpCycles[j]<<" ";
    //cout<<endl;
    cyclesTable[i]=tmpCycles[0];
    for(j=1;j<nodesOfGraph[i].numOfSymbolConnections-1;j++){
      if(cyclesTable[i]>tmpCycles[j])
	cyclesTable[i]=tmpCycles[j];
    }
    //OUTPUT cycles per symbol node
    //cout<<"i="<<i<<" "<<cyclesTable[i]<<endl;
  }
}
    
int CyclesOfGraph::girth(void) {
  int girth=2*N;
  for(int i=0;i<N;i++) 
    if(girth>cyclesTable[i]) girth=cyclesTable[i];
  return(girth);
}



