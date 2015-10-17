#ifndef _BETWEENNESS_CENTRALITY_
#define _BETWEENNESS_CENTRALITY_

#include <boost/config.hpp>
#include <boost/property_map.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/connected_components.hpp>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace boost;
using namespace std;

struct myVertex//properties of the vertex
{
	string name;
	float lat;
	float lon;	
	double vertex_centrality;
};

struct myEdge
{
	double edge_weight;
	double edge_centrality;	
};

typedef adjacency_list<vecS, vecS, undirectedS,	myVertex, myEdge,listS> UndirectedGraph;//using vector data structure
typedef adjacency_list<vecS, vecS, bidirectionalS, myVertex, myEdge,listS> DirectedGraph;//using vector data structure
typedef boost::property_map<UndirectedGraph, double myVertex::*>::type vertCentr;
typedef boost::property_map<UndirectedGraph, double myEdge::*>::type edgeCentr; 

class BetweennessCentrality
{
	private:
		int N;//number of vertices
		string input,output;
		edgeCentr ec;
		UndirectedGraph g, aux_G;
		void print_ColorMatrix(void);
		vector< vector<int> > vec_Components;
	public:
		void read_Graph(void);
		void calc_Clustering(void);	
		void calc_Clustering(int);	
		void create_ColorMatrix(void);
		BetweennessCentrality(string,string);
		~BetweennessCentrality(){};
};

#endif
