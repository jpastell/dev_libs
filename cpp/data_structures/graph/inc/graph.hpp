#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <queue>
#include <optional>
#include <edge_node.hpp>

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

	// //for DFS
	size_t time;
	std::vector<size_t> entry_time;
	std::vector<size_t> exit_time;
	bool finished;

	void init_disocery_containers()
	{
		finished = false;
		for(size_t i=0;i<container_size;i++)
		{
			discovered[i]=false;
			processed[i]=false;
			parent[i]=std::nullopt;
			entry_time[i]=0;
			exit_time[i]=0;
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

	void process_efge_dfs(size_t vertex, size_t adjacent)
	{
		if(parent[adjacent] != vertex)
		{
			std::cout << "Cycle from " << adjacent << " to " << vertex << std::endl;
			find_path(adjacent,vertex);
			finished = true;
		}
	}

public:
	Graph()
	:	container_size{},num_vertices{},
		num_edges{},directed{false},edges{},degrees{},
		discovered{},processed{},parent{},time{},entry_time{},exit_time{},finished{false}

	{

	}

	void insert_edge(	unsigned int vertex, 
						unsigned int adjacent,
						bool directed = false )
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
			//DFS
			entry_time.resize(container_size,0);
			exit_time.resize(container_size,0);
		}
		std::shared_ptr<Edge_node> temp = std::shared_ptr<Edge_node>{new Edge_node(adjacent,0,edges[vertex])};
		edges[vertex] = temp;
		degrees[vertex]++;
		num_vertices++;

		if(!directed)
		{
			insert_edge(adjacent,vertex,true);
		} else {
			num_edges++;
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

	void print_time()
	{
		for(size_t i =0; i<container_size; i++ )
		{
			std::cout << "Vertex:" << i << " entry time:"
				<< entry_time[i] << " exit time:" << exit_time[i] << std::endl;

		}
	}

	void breadth_first_serach(size_t start)
	{
		init_disocery_containers();
		std::shared_ptr<Edge_node> temp;
		std::queue<size_t> q;
		q.push(start);
		discovered[start] = true;
		while(!q.empty())
		{
			auto vertex = q.front();
			q.pop();
			process_vertex_early(vertex);
			processed[vertex] = true;
			temp=edges[vertex];
			while(temp)
			{
				auto adjacent = temp->adjacent;
				if(!processed[adjacent] || directed)
				{
					process_edge(vertex,adjacent);
				}
				if(!discovered[adjacent])
				{
					q.push(adjacent);
					discovered[adjacent]=true;
					parent[adjacent] = vertex;
				}
				temp=temp->next;
			}
			process_vertex_late(vertex);
		}

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

	void depth_first_serach_rec(size_t vertex)
	{
		std::shared_ptr<Edge_node> temp;

		if(finished) return;

		discovered[vertex]=true;
		entry_time[vertex]=(++time);
		process_vertex_early(vertex);
		temp = edges[vertex];
		while(temp)
		{
			size_t adjacent = temp->adjacent;

			std::cout << "adjacent:" << adjacent << " discovered[adjacent]:" << discovered[adjacent] << " ";
			if(!discovered[adjacent])
			{
				parent[adjacent] = vertex;
				std::cout << "1" << "--- ";
				process_efge_dfs(vertex,adjacent);
				depth_first_serach_rec(adjacent);
			}
			else if (((!processed[adjacent]) && (parent[vertex] != adjacent)) || directed)
			{
				std::cout << "2" << "--- ";
				process_efge_dfs(vertex,adjacent);
			}

			if(finished) return;
			temp = temp->next;
		}
		process_vertex_late(vertex);
		exit_time[vertex]=(++time);
		processed[vertex] = true;

	}

	void depth_first_serach(size_t vertex)
	{
		init_disocery_containers();
		depth_first_serach_rec(vertex);
	}


};