#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <stdio.h>

using namespace std;

typedef vector<int> vi;

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define ITE(v) typeof(b.begin())
#define FORIT(it,v) for(ITE(v) it=v.begin();it!=v.end();it++)

vi split(string s,string sp){
  vi v;
  char * pch = strtok (&s[0],&sp[0]);
  while (pch != NULL){
      v.push_back(atoi(pch));
      pch = strtok (NULL,&sp[0]);
    }
  return v;
}

class Tree{

public:
  int n;
  int ** nodes;
  int * nodesValue;
  int * maxNodes;
  int * E;
  int * L;
  int K;
  int * M; // RMQ heap for L

  Tree(int number){
    n=number;
    nodesValue = (int *)malloc(sizeof(int)*n);
    nodes = (int **)malloc(sizeof(int *)*n);
    maxNodes = (int *)malloc(sizeof(int)*n);
    memset(maxNodes,0,sizeof(maxNodes));
    E = (int *)malloc((2*n-1)*sizeof(int));
    L = (int *)malloc((2*n-1)*sizeof(int));
    int N=2*n-1;
    int power = log(N)/log(2);
    K=2*pow(2,power+1);
    M = (int *)malloc((K+1)*sizeof(int));
    memset(M,-1,sizeof(M));
  }
  
  void initialization(){
    string s("");
    string separator(" ");
    int i=0;

    getline(cin,s);
    vi values=split(s," ");
    FOR(i,0,values.size()){nodesValue[i]=values[i];}
    while (getline(cin,s)){
      vi v= split(s,separator);
      maxNodes[v[0]]=v.size()-1;
      nodes[v[0]] = (int *)malloc(sizeof(int)*(v.size()-1));
      FOR(j,1,v.size()){
        nodes[v[0]][j-1]=v[j];
      }
    }  
  }
  
  void display(){
    FOR(i,0,2*n-1){ cout << E[i]<<' '; }
    cout << endl;
    FOR(i,0,2*n-1){ cout << L[i]<<' '; }
    cout << endl;
    FOR(i,0,K+1){ cout << M[i]<<' ';}
    cout <<endl;
  }



  int EulerTour(int indiceNode,int index,int level){
    E[index]=nodesValue[indiceNode];
    L[index]=level;
    FOR(i,0,maxNodes[indiceNode]){
      index = index+1;
      int new_level = level+1;
      index = EulerTour(nodes[indiceNode][i],index++,new_level);
      index++;
      L[index]=level;
      E[index]=nodesValue[indiceNode];
    }
    return index;
  }


  int ancestor(int mini,int maxi){
    int i(0);
    while (i<2*n-1 && (E[i]!=mini && E[i]!=maxi)){i++;}
    int index_min = i;
    int other=(E[i]==mini)?maxi:mini;
    while(E[i]!=other){i++;}
    int index_max= i;
    //cout << index_min <<' '<<index_max<<endl;
    //cout << minIndexLevel(index_min,index_max) <<endl;
    //cout << query(1,0,(2*n-1)-1,index_min,index_max) <<endl;
    return E[query(1,0,(2*n-1)-1,index_min,index_max)];
  }


  int minIndexLevel(int i,int j){ // TODO: implement it in the RMQ way : implementation in O(n)
    int index=i;
    int minLevel = L[index];
    FOR(k,i,j){ if (L[k]<minLevel){minLevel=L[k];index=k;} }
    return index;
  }

  //RMQ initializiation on the L array:
  void RMQInitialization(int node,int b,int e,int N){
    if (b==e){M[node]=b;}
    else{
      RMQInitialization(2*node,b,(b+e)/2,N);
      RMQInitialization(2*node+1,(b+e)/2+1,e,N);
      if (L[M[2*node]]<=L[M[2*node+1]]){M[node]=M[2*node];}
      else { M[node]=M[2*node+1];}
    }
  }

  int query(int node, int b,int e, int i, int j){  //return the index of the minimum level between i and j
    int p1,p2;
    if (i>e || j<b ){return -1;}
    if (b>=i && e <=j) {return M[node];}
    p1=query(2*node,b,(b+e)/2,i,j);
    p2=query(2*node+1,(b+e)/2+1,e,i,j);
    if (p1==-1){return p2;}
    if (p2==-1){return p1;}
    if (L[p1]<=L[p2]){return p1;}
    else {return p2;} 
  }


};


int main(int argc, char * argv []){
  int n(0);
  string number("");
  getline(cin,number);
  n=atoi(&number[0]);
  Tree tree = Tree(n);
  tree.initialization();
  int a = tree.EulerTour(0,0,0);
  int N=2*n-1;
  tree.RMQInitialization(1,0,N-1,N);

  int N_Tests(0);
  FILE * tests;
  tests=fopen("tests.txt","r");
  fscanf(tests,"%d",&N_Tests);
  cout << "A" <<"\t"<<"B"<<"\t"<<"Ancestor"<<endl;
  FOR(i,0,N_Tests){
    int a(0),b(0);
    fscanf(tests,"%d %d",&a,&b);
    cout << a << "\t"<< b <<"\t"<<tree.ancestor(min(a,b),max(a,b))<<endl;
  }

  return 0;
}
