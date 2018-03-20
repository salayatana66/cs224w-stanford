#include "Snap.h"
#include <set>
#include <utility>

int n = 5242;
int m = 14484;


int main(int argc, char* argv[]) {
  srand(17);
  //--------------------------------
  // 1.
  // allocate memory for graph
  auto G = new TUNGraph(n,m);
   FILE* outfile;
   outfile = fopen("/mnt/notebooks/EReny.txt","w");
  // add vertices
  for(int i = 0; i < n; ++i) G->AddNode(i);
  // start adding random edges
  // use a set to keep track of them
  std::set<std::pair<int,int>> S;
  int added_edges = 0;
  while(added_edges < m) {
    int a = rand() % n;
    int b = rand() % n;
    if( a != b) {
      if(a > b) std::swap(a,b);
      auto edge = std::make_pair(a,b);
      if(S.find(edge) == S.end()) {
	// add edge
	G->AddEdge(a,b);
	S.insert(edge);
	fprintf(outfile,"%d\t%d\n",a,b);
	added_edges++;
      }
    }
  }
  printf("EReny Graph added with %d edges and %d nodes\n", G->GetEdges(), G->GetNodes());
  fclose(outfile);
  //--------------------------------
  // 2.
  delete G;
  G = new TUNGraph(n,m);
  outfile = fopen("/mnt/notebooks/SmallWorld.txt","w");
    // add vertices
  for(int i = 0; i < n; ++i) G->AddNode(i);
  // add cyclic edges
  for(int i = 0; i < n; ++i) {
    G->AddEdge(i,(i+1) % n);
    fprintf(outfile,"%d\t%d\n",i,(i+1)%n);
  }
  // add double cyclic edges
  for(int i = 0; i < n; ++i) {
    G->AddEdge(i,(i+2) % n);
    fprintf(outfile,"%d\t%d\n",i,(i+2)%n);
  }
  
  // add 4000 edges at random
  std::set<std::pair<int,int>> S2;
  added_edges = 0;
  while(added_edges < 4000) {
    int a = rand() % n;
    int b = rand() % n;
    if( a != b) {
      if(a > b) std::swap(a,b);
      if( (b-a) > 2) {
      auto edge = std::make_pair(a,b);
      if(S2.find(edge) == S2.end()) {
	// add edge
	G->AddEdge(a,b);
	S2.insert(edge);
	fprintf(outfile,"%d\t%d\n",a,b);
	added_edges++;
      }
      }
    }
  }
  
  printf("Small World added with %d edges and %d nodes\n", G->GetEdges(), G->GetNodes());
  fclose(outfile);

  // Load the QuantumCosmology Graph
  // note use of generic programming to load undirected graph
  PUNGraph H = TSnap::LoadEdgeList<PUNGraph>(TStr("/mnt/notebooks/ca-GrQc.txt"),0,1,'\t');
				 
  // delete self-edges
  for(auto I = H->BegEI(); I != H->EndEI(); I++) {
    if(I.GetSrcNId() == I.GetDstNId()) H->DelEdge(I.GetSrcNId(),I.GetDstNId());
  }
    printf("Quantum Cosmology collaboration added with %d edges and %d nodes\n", H->GetEdges(), H->GetNodes());
}
