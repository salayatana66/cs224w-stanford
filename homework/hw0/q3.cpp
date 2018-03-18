#include "Snap.h"
#include <algorithm>
#include <vector>
#include <utility>

// to rank in descending order by pagerank
 bool myRanker(std::pair<TInt, TFlt> i,
		std::pair<TInt,TFlt> j)
 {
   return i.second > j.second;
 }

int main(int argc, char* argv[]) {
  // load as a multigraph
PNGraph G = TSnap::LoadEdgeList<PNGraph>(
  "/home/arischioppa/stackoverflow-Java.txt.gz", 0, 1);
// number of weakly connected components
 TCnComV weakly;
 TSnap::GetWccs(G,weakly);
 printf("Number of weakly connected components\t%d\n",
	weakly.Len());
 // number of nodes and edges in the largest
 // weakly connected component
 auto H = TSnap::GetMxWcc(G);
 printf("The largest connected component contains %d nodes and %d edges\n",
	H->GetNodes(), H->GetEdges());
 // compute pageRank scores
 TIntFltH Pr;
 TSnap::GetPageRank(G,Pr);
 // we will use a vector to sort the page ranks
 std::vector<std::pair<TInt,TFlt>> vec;
 for(auto p = Pr.BegI(); p != Pr.EndI(); p++)
   vec.push_back(std::make_pair(p.GetKey(),p.GetDat()));
  
 std::sort(vec.begin(),vec.end(),myRanker);
 for(int j = 1; j < 4; j++)
   printf("Node of %d-th PageRank: %d\t Rank: %f\n",
	  j, (int)vec[j-1].first, (float)vec[j-1].second);
 // Apply the Hits algorithm
 printf("==============================\n");
 printf(" Hits Algorigthm \n");
 printf("==============================\n");
 TIntFltH Hubs, Auths;
 TSnap::GetHits(G,Hubs,Auths);
 std::vector<std::pair<TInt,TFlt>> vecHubs, vecAuths;
 for(auto p = Hubs.BegI(); p != Hubs.EndI(); p++)
   vecHubs.push_back(std::make_pair(p.GetKey(),p.GetDat()));
 for(auto p = Auths.BegI(); p != Auths.EndI(); p++)
   vecAuths.push_back(std::make_pair(p.GetKey(),p.GetDat()));
 sort(vecHubs.begin(),vecHubs.end(),myRanker);
 sort(vecAuths.begin(),vecAuths.end(),myRanker);
 for(int j = 1; j < 4; j++)
   printf("Hub node of %d-th Rank: %d\t Rank: %f\n",
	  j, (int)vecHubs[j-1].first, (float)vecHubs[j-1].second);

 for(int j = 1; j < 4; j++)
   printf("Auth node of %d-th Rank: %d\t Rank: %f\n",
	  j, (int)vecAuths[j-1].first, (float)vecAuths[j-1].second);

   }
