#include "Snap.h"
#include <map>
#include <utility>
#include <stdio.h>

// use of myInt to automatically count in Map
struct myInt {
  int val;
  myInt() :val(0)  {}
  myInt(int a) : val(a) {}
};

int main(int argc, char* argv[]) {
  // load as a multigraph
PNGraph G = TSnap::LoadEdgeList<PNGraph>(
  "/home/arischioppa/wiki-Vote.txt.gz", 0, 1);
 printf("Loaded graph\n");
 FILE* outfile;
 outfile = fopen("nodeDegrees.txt","w");
 fprintf(outfile,"OutDegree\tCount\n");
 std::map<int,myInt> degCount;
 for(auto nI = G->BegNI(); nI < G->EndNI(); nI++) {
   int deg = nI.GetOutDeg();
   // note that if key is absent gets initialized with the default constructor
   if(deg>0) degCount[deg].val++;
 }
 // export to tabular format
 for(auto mP = degCount.cbegin(); mP != degCount.cend(); mP++)
   fprintf(outfile, "%d\t%d\n", mP->first, mP->second.val);
 fclose(outfile);
   
}
