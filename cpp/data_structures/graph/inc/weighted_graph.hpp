#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <edge_node.hpp>
#include <functional>
#include <algorithm>

struct edge_t
{
	size_t vertex;
	size_t adjacent;
	unsigned int weight;
};


class Graph
{
	size_t container_size; //Container size used for faster access, avoid colling vector size funtion
	unsigned int num_vertices; //Number of vertices in the graph
	unsigned int num_edges; //Number og edges in the graph
	bool directed;

	std::vector<std::shared_ptr<Edge_node>> edges; //Edges in the graph
	std::vector<unsigned int> degrees; // how many vertices are connected to the current node

	//Discovery containers
	std::vector<bool> discovered;
	std::vector<bool> processed;

	std::vector<std::optional<size_t>> parent;
	//for kruskal algorithm
	std::vector<unsigned int> uf_size;
	std::vector<size_t> uf_parent;
	std::vector<edge_t> uf_edges;


	//for prim algorithm
	std::vector<bool> in_tree;
	std::vector<unsigned int> distance;

	void init_containers()
	{
		for(size_t i=0;i<container_size;i++)
		{
			discovered[i]=false;
			processed[i]=false;
			parent[i]=std::nullopt;
			in_tree[i] = false;
			distance[i]=std::numeric_limits<unsigned int>::max();
			uf_size[i]=1;
			uf_parent[i]=i;


		}
	}

	void process_vertex_early(size_t vertex)
	{
		std::cout << "Process early vertex=" << vertex << std::endl;
	}

	void process_vertex_late(size_t vertex)
	{
		// std::cout << "Process late vertex=" << vertex << std::endl;
	}

	void process_edge(size_t vertex, size_t adjacent)
	{
		std::cout << "Process edge vertex:" << vertex << " adjacent: " << adjacent << std::endl;
	}

	void find_path(std::optional<size_t>start , std::optional<size_t> end)
	{
		if(start == end  || end == std::nullopt)
		{
			std::cout << start.value() << std::endl;
		} else {
			find_path(start,parent[end.value()]);
			std::cout << end.value() << std::endl;
		}
	}

	size_t find_root(size_t vertex)
	{
		if(uf_parent[vertex] == vertex)
		{
			return vertex;
		}
		return find_root(uf_parent[vertex]);
	}

	bool same_component(size_t s1, size_t s2)
	{
		return(find_root(s1) == find_root(s2));
	}

	void union_set(size_t s1, size_t s2)
	{
		size_t r1, r2; // roots

		r1 = find_root(s1);
		r2 = find_root(s2);

		if(r1 == r2)
		{
			return; //already in the same set
		}

		if(uf_size[r1] >= uf_parent[r2])
		{
			uf_size[r1] += uf_size[r2];
			uf_parent[r2] = r1;
		} else {
			uf_size[r2] += uf_size[r1];
			uf_parent[r1] = r2;
		}

	}

public:
	Graph()
	:	container_size{},num_vertices{},
		num_edges{},directed{false},edges{},degrees{},
		discovered{},processed{},parent{},
		in_tree{},distance{},uf_size{},uf_parent{},uf_edges{}

	{

	}

	void insert_edge(	unsigned int vertex, 
						unsigned int adjacent,
						unsigned int weight=0,
						bool directed = false
						 )
	{
		//We need to make sure the graph have enough space to allocate the vertex
		if(container_size == 0 || container_size-1 < vertex)
		{
			container_size = vertex+1;
			edges.resize(container_size,nullptr);
			degrees.resize(container_size,0);
			//Discovery containers
			discovered.resize(container_size,false);
			processed.resize(container_size,false);
			parent.resize(container_size);
			//prim containers
			in_tree.resize(container_size,false);
			distance.resize(container_size,std::numeric_limits<unsigned int>::max());
			//kruskal
			uf_size.resize(container_size,0);
			uf_parent.resize(container_size);

		}

		if(!edges[vertex])
		{
			num_vertices++;
		}

		std::shared_ptr<Edge_node> temp = std::shared_ptr<Edge_node>{new Edge_node(adjacent,weight,edges[vertex])};
		edges[vertex] = temp;
		degrees[vertex]++;

		if(!directed)
		{
			insert_edge(adjacent,vertex,weight,true);
		} else {
			num_edges++;
			uf_edges.push_back({vertex,adjacent,weight});
		}
	}

	void print(bool show_weight=false)
	{
		for(size_t i = 0; i < container_size;i++)
		{
			if(edges[i])
			{
				std::cout << "Vertex:" << i << " ";
				std::shared_ptr<Edge_node> temp_ptr= edges[i];
				while(temp_ptr)
				{
					std::cout << "A:" <<  temp_ptr->adjacent << " ";
					if(show_weight)
					{
						std::cout << "W:" <<  temp_ptr->weight << " ";
					}
					temp_ptr = temp_ptr->next;
				}
				std::cout << std::endl;
			}
		}
	}

	void print_parent()
	{
		for(size_t i =0; i<container_size; i++ )
		{
			std::cout << "Vertex:" << i <<" Parent:";
			if(parent[i])
					std::cout<< parent[i].value() << std::endl;  
			else

					std::cout<< "-" << std::endl; 
		}
	}



	void print_number_vetices()
	{
		std::cout << "Number of vertices: " << num_vertices << std::endl; 
	}

	unsigned int prim(size_t start)
	{
		size_t vertex = start;
		distance[vertex]=0;
		unsigned int local_dist;
		unsigned int weight = 0;
		std::shared_ptr<Edge_node> temp;

		init_containers();

		while(!in_tree[vertex])
		{
			//add it to the tree
			in_tree[vertex]=true;
			if(vertex != start)
			{
				std::cout << "Edge " << parent[vertex].value() << " to " << vertex << std::endl;
				weight += local_dist;
			}

			//Populate the distance of all vertices connected to the current vertex and populate the parent
			temp =  edges[vertex];
			while(temp)
			{
				unsigned int candidate = temp->adjacent;
				if((distance[candidate] > temp->weight) && (!in_tree[candidate]))
				{
					distance[candidate] = temp->weight;
					parent[candidate] = vertex;
				}
				temp = temp->next;
			}

			//Select the
			local_dist = std::numeric_limits<unsigned int>::max();
			for(size_t i = 0 ; i <= num_vertices; i++)
			{
				if((!in_tree[i]) && (local_dist > distance[i]))
				{
					std::cout << "i=" << i << " local_dist=" << local_dist << " distance[i]=" << distance[i] << std::endl;
					local_dist = distance[i];
					vertex=i;
				}
			}

		}
		return weight;
	}

	void print_kruskal_edges()
	{
		for(size_t i=0;i<num_edges;i++)
		{
			std::cout << "vertex:" << uf_edges[i].vertex
				<< " adjacent:" << uf_edges[i].adjacent
				<< " weight: " << uf_edges[i].weight << std::endl;
		}
	}

	unsigned int kruskal()
	{
		unsigned int weight = 0;
		init_containers();
		std::sort(uf_edges.begin(),uf_edges.end(),
				[](auto a, auto b){return (a.weight < b.weight);});

		for(size_t i = 0; i <num_edges; i++)
		{
			if(!same_component(uf_edges[i].vertex,uf_edges[i].adjacent))
			{
				std::cout << "Edge from " << uf_edges[i].vertex << " to " << uf_edges[i].adjacent << std::endl;
				weight += uf_edges[i].weight;
				union_set(uf_edges[i].vertex,uf_edges[i].adjacent);
			}
		}
		return weight;
	}

};