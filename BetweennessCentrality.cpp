#include "bfs.h"

BetweennessCentrality::BetweennessCentrality(string name, string outfile)
{
	input.assign(name);
	output.assign(outfile);
}

void BetweennessCentrality::read_Graph()
{
	fstream fp;
	string lixo;
	int x,y,i;
	
	fp.open(input.c_str());	
		fp >> lixo >> N;
		UndirectedGraph temp_G(N);
		g=temp_G;
		aux_G=temp_G;
		for(i=0;i<N;i++)
		{
//			fp >> lixo >> lixo >> lixo >> lixo;
			fp >> lixo >> lixo;
		}
		fp >> lixo;//*Edges
		while (fp >> x >> y >> lixo)//a b peso
		{
			add_edge(x-1, y-1,g);
			add_edge(x-1, y-1,aux_G);
		}
	fp.close();
	return;
}

void BetweennessCentrality::calc_Clustering()
{
	int greatest,nc;
	int iteration = 0;
	graph_traits < UndirectedGraph >::edge_iterator ei, ei_end, max_ei;
	vector<int> component(num_vertices(aux_G));
	vector<float> position(num_vertices(aux_G));
	vector<int>::size_type i;
	string name_f1, name_f2, name_f3;
	ofstream f1,f2,f3;

//defining the names of output files
	name_f1 = "dendro_" + output + ".dat";
	name_f2 = "n_comp_in_time_" + output + ".dat";
	f1.open(name_f1.c_str());
	f2.open(name_f2.c_str());

	brandes_betweenness_centrality(aux_G,get(&myVertex::vertex_centrality,aux_G),get(&myEdge::edge_centrality, aux_G));
	ec = get(&myEdge::edge_centrality, aux_G);
//until we have N components
	while(num_edges(aux_G) > 0)
	{
//to identify the greatest brandes betweenness edge
		greatest = 0;
		for (tie(ei, ei_end) = edges(aux_G); ei != ei_end; ++ei) 
		{
			if (ec[*ei] >= greatest)//in this case, we only identify one among the greatest bet_centralities. we can only remove one vertice
			{
				max_ei = ei;
				greatest = ec[*ei];
			}
		}
//to identify the clusters and print them to a file
		nc = connected_components(aux_G, &component[0]);
		f1 << iteration << " ";
		for (i=0;i!=component.size();++i)
		{
			position[i] = (((float)component[i]/nc)+((float)(component[i]+1)/nc));
			f1 << position[i] << " ";
		}
		f1 << endl;
////to remove the edge 'max_ei'
		remove_edge(*max_ei,aux_G);
////to print the number of components at the iteration
		f2 << iteration << " " << nc << endl;
		iteration++;
	}
	f1.close();f2.close();
	return;
} 

void BetweennessCentrality::calc_Clustering(int stop_iteration)
{
	int greatest;
	int iteration = 0;
	graph_traits < UndirectedGraph >::edge_iterator ei, ei_end, max_ei;
	vector<int> component(num_vertices(aux_G));
	vector<int>::size_type i,j;
	int nc;

	brandes_betweenness_centrality(aux_G,get(&myVertex::vertex_centrality,g),get(&myEdge::edge_centrality, aux_G));
	ec = get(&myEdge::edge_centrality, aux_G);
//until we have N components
	while((num_edges(aux_G) > 0)&&(iteration < stop_iteration))
	{
//to identify the greatest brandes betweenness edge
		greatest = 0;
		for (tie(ei, ei_end) = edges(aux_G); ei != ei_end; ++ei) 
		{
			if (ec[*ei] >= greatest)//in this case, we only identify one among the greatest bet_centralities. we can only remove one vertice
			{
				max_ei = ei;
				greatest = ec[*ei];
			}
		}
////to remove the edge 'max_ei'
		remove_edge(*max_ei,aux_G);
// working with the components

		iteration++;
	}
//to build the vector of components
	nc = connected_components(aux_G, &component[0]);

	for (i=0;i<(vector<int>::size_type)nc;i++)
	{
		vector<int> aux;
		for (j=0;j!=component.size();++j)
		{
			if (component[j]==(int)i) aux.push_back(j);
		}
		vec_Components.push_back(aux);
		aux.clear();
	}
	print_ColorMatrix();

	return;
} 

//to print the color matrix
void BetweennessCentrality::print_ColorMatrix()
{
	typedef UndirectedGraph::vertex_descriptor Vertex;
	UndirectedGraph G_copy(N);
	vector<Vertex> p(num_vertices(aux_G));
	typedef std::vector<Vertex>::value_type* Piter;
	typedef graph_traits<UndirectedGraph>::vertices_size_type t_d;
	t_d d[N];
	typedef vector<t_d> v1;
	typedef vector<v1> v2;
	v1 aux;
	v2 vec_d;
	int vert=0;
	vector<int>::size_type i,j,k,l;

	string name_f1, name_f2, name_f3, name_f4;
	ofstream f1,f2,f3,f4;

	name_f1 = "mc_" + output + "_orig.mat";
	name_f2 = "mc_" + output + "_reorg.mat";
	name_f3 = "vert_on_comp_" + output + ".dat";
	name_f4 = "new_seq_vert_" + output + ".dat";
	f1.open(name_f1.c_str());
	f2.open(name_f2.c_str());
	f3.open(name_f3.c_str());
	f4.open(name_f4.c_str());

	k=0;	
	Vertex s = *(vertices(aux_G).first);
	while (vert < N)
	{
		fill_n(d,N,0);
		p[s] = s;
		breadth_first_search(aux_G,s,
			visitor(make_bfs_visitor(make_pair(record_distances(d,on_tree_edge()),make_pair(record_predecessors(&p[0],on_tree_edge()),copy_graph(G_copy,on_examine_edge()))))) );
		#ifdef BOOST_OLD_STREAM_ITERATORS
		copy(d,d+N,ostream_iterator<int,char>(f1, " "));
		#else
		copy(d,d+N,ostream_iterator<int>(f1," "));
		#endif
		f1 << endl;
		for (i=0;i<(vector<int>::size_type)N;i++)
		{
			aux.push_back(d[i]);
		}
		vec_d.push_back(aux);
		aux.clear();
		vert++;
		s++;
	}
	f1.close();

	for (i=0;i<vec_Components.size();i++)
	{
		f3 << "COMPONENT " << i << endl;
		for (j=0;j<vec_Components.at(i).size();j++)
		{
			f3 << vec_Components.at(i).at(j) << " ";
		}
		f3 << endl;
	}
	f3.close();

//to sort the components vertices by the distance

	int aux_comp;
	for (i=0;i<vec_Components.size();i++)
	{
		if (vec_Components.at(i).size() > 2)
		{
			for (k=1;k<vec_Components.at(i).size() - 1;k++)
			{
				for (j=k+1;j<vec_Components.at(i).size();j++)
				{
					if (vec_d.at(vec_Components.at(i).at(0)).at(vec_Components.at(i).at(k)) > vec_d.at(vec_Components.at(i).at(0)).at(vec_Components.at(i).at(j)))
					{
						aux_comp = vec_Components.at(i).at(k);
						vec_Components.at(i).at(k) = vec_Components.at(i).at(j);
						vec_Components.at(i).at(j) = aux_comp;
					}
				}
			}
		}
	}

//to print the color matrix reorganized by the distance
	for (i=0;i<vec_Components.size();i++)
	{
		for (j=0;j<vec_Components.at(i).size();j++)
		{
			for (l=0;l<vec_Components.size();l++)
			{
				for (k=0;k<vec_Components.at(l).size();k++)
				{	
					f2 << vec_d.at(vec_Components.at(i).at(j)).at(vec_Components.at(l).at(k)) << " ";
				}
			}
			f2 << endl;
		}
	}
	f2.close();
//to identify the components vertices!
	f4 << "NEW ORDER OF VERTICES" << endl;
	for (i=0;i<vec_Components.size();i++)
		for (j=0;j<vec_Components.at(i).size();j++)
			f4 << vec_Components.at(i).at(j) << endl;
	f4.close();

	return;
}
