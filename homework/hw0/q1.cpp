#include "Snap.h"
#include <set>
#include <utility>

int main(int argc, char* argv[]) {
  // load as a multigraph
PNGraph G = TSnap::LoadEdgeList<PNGraph>(
  "/home/arischioppa/wiki-Vote.txt.gz", 0, 1);
 printf("Loaded graph\n");
// compute total number of nodes
printf("Number Nodes\t%d\n", G->GetNodes());
// iterate on edges to identify self nodes
std::set<int> selfNodes;
 for(auto eI = G->BegEI(); eI < G->EndEI(); eI++)
   if(eI.GetSrcNId() == eI.GetDstNId()) selfNodes.insert(eI.GetSrcNId());
printf("Number of nodes with self-edges\t%d\n", selfNodes.size());
// iterate on edges to identify directed edges
std::set<std::pair<int,int>> dirEdges;
 for(auto eI = G->BegEI(); eI < G->EndEI(); eI++)
   if(eI.GetSrcNId() != eI.GetDstNId()) dirEdges.insert(std::pair<int,int>(
								  eI.GetSrcNId(),eI.GetDstNId()));
printf("Number of directed edges\t%d\n", dirEdges.size());
// iterate on edges to identify undirected edges
std::set<std::pair<int,int>> undirEdges;
for(auto eI = G->BegEI(); eI < G->EndEI(); eI++) {
  int src = eI.GetSrcNId();
  int dest = eI.GetDstNId();
  if(src != dest) {
    if(src > dest) {
      int swap = src;
      src = dest;
      dest = swap;
    }
    undirEdges.insert(std::pair<int,int>(src,dest));
  }
 }
printf("Number of undirected edges\t%d\n", undirEdges.size());
// find reciprocated edges (brute force)
std::set<std::pair<int,int>> leftEdge, rightEdge;
int recEdge = 0;
for(auto eI = G->BegEI(); eI < G->EndEI(); eI++) {
  int src = eI.GetSrcNId();
  int dest = eI.GetDstNId();
  if(src != dest) {
    if(src < dest) leftEdge.insert(std::pair<int,int>(src,dest));
    else rightEdge.insert(std::pair<int,int>(src,dest));
  }
 }
for(auto sI = leftEdge.cbegin(); sI != leftEdge.cend(); sI++) {
  if(rightEdge.find(std::make_pair(sI->second,
				     sI->first))
     != rightEdge.cend()) recEdge++;
 }
							 
   printf("Number of reciprocated edges\t%d\n", recEdge);
// nodes with zero out-degree
// nodes with zero in-degree
std::set<int> zeroIn, zeroOut;
for(auto nI = G->BegNI(); nI < G->EndNI(); nI++) {
  if(nI.GetInDeg() == 0) zeroIn.insert(nI.GetId());
  if(nI.GetOutDeg() == 0) zeroOut.insert(nI.GetId());
 }
printf("Number of nodes with zero out-degree\t%d\n", zeroOut.size());
printf("Number of nodes with zero in-degree \t%d\n", zeroIn.size());
// nodes with out-degree > 10
// nodes with in-degree < 10
std::set<int> tenIn, tenOut;
for(auto nI = G->BegNI(); nI < G->EndNI(); nI++) {
  if(nI.GetInDeg() < 10) tenIn.insert(nI.GetId());
  if(nI.GetOutDeg() > 10) tenOut.insert(nI.GetId());
 }
printf("Number of nodes with out-degree > 10\t%d\n", tenOut.size());
printf("Number of nodes with in-degree < 10 \t%d\n", tenIn.size());

}
