#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

// This is the file where the student should do their work.


#include "graph.decl.h"
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

auto find_edge(const std::vector<GraphEdge> &edges, size_t origin, size_t destination) -> std::pair<double, bool>;

/**
 * Returns the number of verticies in the graph.
 */
size_t Graph::nvertices() const {
    return vertices.size(); 
    
}
/**
 * Returns the number of edges in the graph.
 */
size_t Graph::nedges() const { 
    return edges.size();
}

void Graph::assign(const std::vector<std::string> & vertices, const std::vector<GraphEdge> & edges) {

    // Remove any data currently stored in the graph.
    this->vertices.clear();
    this->edges.clear();
    this->v_lut.clear();

    // resize the vectors.
    this->vertices.resize(vertices.size());
    this->edges.resize(edges.size());
    
    // Replace with the graph described by the vertex vector, vertices
    // and edge vector, edges passed in.
    
    std::transform(vertices.begin(), vertices.end(), this->vertices.begin(), [this, count=0](const auto &vertex) mutable {
            this->v_lut.insert({vertex, count++});
            return vertex;
    });

    std::copy(edges.begin(), edges.end(), this->edges.begin());

}

bool Graph::edge_exists(size_t origin, size_t destination) const {
    return find_edge(this->edges, origin, destination).second;
}

double Graph::edge_weight(size_t origin, size_t destination) const {

    // Gets the edge in the graph, if the edge is found, edge_info will have its weight.
    // If the edge is not found, edge_info the weight inside edge_info will be INFINITY.
    std::pair<double, bool> edge_info = find_edge(this->edges, origin, destination);
    return edge_info.first;
}

std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> undirected_adjacency_list;

    // Loop through each edgeto find the edges contain the passed in vertex.
    for (const auto &edge :edges) {
        if (edge.origin == vertex || edge.destination == vertex) {
            // Get the vertex on the other side.
            size_t other_size_vertex = edge.origin == vertex ? edge.destination : edge.origin;

            // Add the AdjListEdge to the adjacency list.
            undirected_adjacency_list.emplace_back(other_size_vertex, edge.weight);
        }
    }
    
  return undirected_adjacency_list;
}

/**
 * Returns a std::vector containing an AdjListEdge 
 * for each edge that starts at the vertex with the index passed in.
 */
std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> in_adj_list;

    // Loop through each edge to find the edges with vertex as the origin.
    for (const auto &edge :edges) {
        if (edge.destination == vertex) {
            // Add the AdjListEdge to the adjacency list.
            in_adj_list.emplace_back(edge.origin, edge.weight);
        }
    }
    
  return in_adj_list;
     
}

/**
 * Returns a std::vector containing an AdjListEdge 
 * for each edge that ends at the vertex with the index passed in.
 */
std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> out_adj_list;


    // Loop through each edge to find the edges with vertex as the destination.
    for (const auto &edge :edges) {
        if (edge.origin == vertex) {
            // Add the AdjListEdge to the adjacency list.
            out_adj_list.emplace_back(edge.destination, edge.weight);
        }
    }
    
  return out_adj_list;
}



std::vector <double> Graph::weighted_adjacency_matrix() const {
    std::vector<double> weighted_adj_matrix(nvertices() * nvertices(), INFINITY);
    for (const auto& edge : edges) {
        weighted_adj_matrix[edge.origin * nvertices() + edge.destination] = edge.weight;
    }
    



    return weighted_adj_matrix;
}

/**
 *
 */
std::vector <bool> Graph::unweighted_adjacency_matrix() const {
    std::vector<bool> unweighted_adj_matrix(nvertices() * nvertices(), false);
    for (const auto& edge : edges) {
        unweighted_adj_matrix[edge.origin * nvertices() + edge.destination] = true;
    }
    return unweighted_adj_matrix;
}

/**
 * Gets the label of the vertex with matching index.
 */
std::string Graph::v_label(size_t vertex) const {
    return vertices[vertex];
}
/**
 * Gets the index of the vertex with matching label.
 */
ssize_t Graph::v_index(const std::string &label) const {
    auto it = v_lut.find(label);
    return it->second;
}

template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {

    std::vector<bool> visited(nvertices(), false);
    std::queue<size_t> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        size_t current = q.front(); 
        q.pop();
         
        // Visit the vertex.
        visitfn(current);

        // get all the adjacent vertices 
        std::vector<AdjListEdge> neighbors = out_adjacency_list(current);

        std::sort(neighbors.begin(), neighbors.end(),[](const auto &a, const auto &b) {
                    return a.vertex < b.vertex;
        });

        // add the adjcent vertices
        for (const auto &adjlistedge : neighbors) {
            if (visited[adjlistedge.vertex] == false) {
                q.push(adjlistedge.vertex);
                visited[adjlistedge.vertex] = true;
            }
        }
    }
    
}

/**
 * Depth first search graph traversal.
 */
template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    std::vector<bool> visited(nvertices(), false);
     
    // Using std::function here so I can use recursion here.
    std::function<void(size_t)> dfs = [&](size_t current) {
        // Visit the current vertex
        visitfn(current);

        visited[current] = true;

        // Get all the adjacent vertices
        std::vector<AdjListEdge> neighbors = out_adjacency_list(current);

        // Sort so that we can choose the vertices in ascending order to match output.
        std::sort(neighbors.begin(), neighbors.end(), [](const auto& a, const auto& b) {
            return a.vertex < b.vertex;
        });

        // Add the adjacent vertices
        for (const auto& adjlistedge : neighbors) {
            if (visited[adjlistedge.vertex] == false) { 
                dfs(adjlistedge.vertex);
            }
        }
    };

    dfs(start);
}

/**
 * Topological sort algorithm on graph.
 */
std::vector<size_t> Graph::toposort() const {

    // Using the three states method for cycle detection.
    enum states { unvisited, visiting, visited };

    // Vector to hold the order of vertices determined by the algorithm.  
    std::vector<size_t> valid_ordering;  
    std::vector<states> _visited(nvertices(), unvisited);


    // Using std::function again for recursion
    std::function<bool(size_t)> dfs = [&](size_t current) {

        // if the current vector is has a visiting state, we know there is a cycle and can return
        if (_visited[current] == visiting) { return true; }
        // Already proccessed this vertex.
        if (_visited[current] == visited) { return false; }

        _visited[current] = visiting;

        // Get all the adjacent vertices
        std::vector<AdjListEdge> neighbors = out_adjacency_list(current);

        // Sort so that we can choose the vertices in ascending order to match output.
        std::sort(neighbors.begin(), neighbors.end(), [](const auto& a, const auto& b) {
            return a.vertex > b.vertex;
        });

        // Add the adjacent vertices
        for (const auto& adjlistedge : neighbors) {
            if (_visited[adjlistedge.vertex] == visiting) {
                return true; 
            }
            if (_visited[adjlistedge.vertex] == unvisited) { 
                if(dfs(adjlistedge.vertex)) return true;

            }
        }
        // Set the vertex to visited after all adjacent vertices are fully visited.
        _visited[current] = visited;
        valid_ordering.push_back(current);
        return false;
    };

    // Check for vertices not yet visited.
     for (size_t i = 0; i < nvertices(); ++i) {
        if (_visited[i] == unvisited) {
            if (dfs(i)) {
                return {};
            }
        }
    }
    

     // The valid ordering is the reversed version of the vector
     // since elements in topo sort get placed in reverse order.
    return std::vector<size_t>(valid_ordering.rbegin(), valid_ordering.rend());
}
    
/**
 * Implementation of dijkstras algorithm 
 * to find the shortest path to all nodes starting from start.
 */
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
     
    for (const auto &edge : edges) {
        if (edge.weight < 0) {
            std::cout << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
            return {};
        }
    }
    std::vector<dijkstra_row> result;

    // Fill the vector of dijkstra rows with initial values.
    for (size_t i = 0; i < nvertices(); ++i) {
        if (i == start) {
            result.emplace_back(i, false, 0, -1);
        }
        else {
            result.emplace_back(i, false, INFINITY, -1);
        }
    }

    // custome compare for priority queue that compares the pairs by their weights.
    //
    struct {
        bool operator()(const std::pair<size_t, double> left, const std::pair<size_t, double> right) const { return left.second > right.second; }
    } compare_weights_less;

     
    // Create the priority queue.
    std::priority_queue<std::pair<size_t, double>, std::vector<std::pair<size_t, double>>, decltype(compare_weights_less)> pq(compare_weights_less);
    pq.push({start, 0.0});

    // visit all the vertices in the graph, relaxing the adjacent vertices.
    while (!pq.empty()) {
        // Get the vertex with the minimum weight.
        auto current = pq.top().first;
        pq.pop();

        // Vertex has already been visited, dont need to process any further.
        if (result[current].visited == true) {
            continue;
        }


        // Loop through each adjacent vertex, updating it in the result vector if we can relax it.
        for (const auto &neighbor : out_adjacency_list(current)) {
            size_t neighbor_vertex = neighbor.vertex;
            double edge_weight = neighbor.weight;

            // Get the distance from the current node to the adjacent node.
            double new_weight = result[current].shortest_known + edge_weight;
            // If the weight if less that the current shortest known weight.
            // Then we update the result vector.
            if (new_weight < result[neighbor_vertex].shortest_known) {
                result[neighbor_vertex].shortest_known = new_weight;
                result[neighbor_vertex].came_from = current;
                // add it to the priority queue.
                pq.push({neighbor_vertex, new_weight});
            }
        }

    }

    return result;
}



auto find_edge(const std::vector<GraphEdge> &edges, size_t origin, size_t destination) -> std::pair<double, bool>  {
    for (const auto& edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return {edge.weight,true};
        }
    }
    return {INFINITY, false};
}
#endif /* NIU_CSCI340_GRAPH_H */

