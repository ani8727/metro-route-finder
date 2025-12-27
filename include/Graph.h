#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include "Station.h"

// Forward declaration for helper functions
inline void printHeader(const std::string& title);

struct PathInfo {
    std::vector<std::string> path;
    std::vector<std::string> metroLines;
    double totalDistance;
    int estimatedFare;
    int transferPoints;
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjList;
    std::unordered_map<std::string, Station> stations;
    
    // Helper for Dijkstra
    void reconstructPath(const std::unordered_map<std::string, std::string>& parent, 
                        const std::string& destination, PathInfo& result);
    std::string getCurrentLine(const std::string& from, const std::string& to);

public:
    Graph() = default;
    
    // Build graph
    void addStation(const std::string& name, const std::string& line, 
                   int zone, double lat = 0.0, double lon = 0.0);
    void addEdge(const std::string& station1, const std::string& station2, double distance);

    // Remove station and edge
    bool removeStation(const std::string& name);
    bool removeEdge(const std::string& station1, const std::string& station2);
    
    // Dijkstra's Algorithm - O((V+E)log V)
    PathInfo findShortestPath(const std::string& source, const std::string& destination);

    // BFS traversal from a station (returns order of visit)
    std::vector<std::string> bfs(const std::string& start) const;

    // DFS traversal from a station (returns order of visit)
    std::vector<std::string> dfs(const std::string& start) const;

    // Find all paths between two stations (backtracking/DFS)
    std::vector<std::vector<std::string>> findAllPaths(const std::string& source, const std::string& destination) const;

    // Detect cycles in the network (returns true if cycle exists)
    bool hasCycle() const;

    // Find connected components (returns list of components)
    std::vector<std::vector<std::string>> connectedComponents() const;

    // Compute Minimum Spanning Tree (Prim's algorithm, returns edges in MST)
    std::vector<std::tuple<std::string, std::string, double>> minimumSpanningTree() const;
    
    // Query methods
    bool hasStation(const std::string& name) const;
    const Station* getStation(const std::string& name) const;
    int getStationCount() const { return stations.size(); }
    int getEdgeCount() const;
    
    // Display methods
    void displayAllStations() const;
    void displayNetwork() const;
    void displayByMetroLine(const std::string& lineName) const;
    std::vector<std::string> getAllMetroLines() const;
    std::vector<std::string> getStationsByLine(const std::string& lineName) const;
    
    // Getters for UI
    const std::unordered_map<std::string, Station>& getStations() const { return stations; }
};

/*
 * Additional Algorithms/DSA exposed:
 * - BFS, DFS traversals
 * - All-paths search (backtracking)
 * - Cycle detection (DFS)
 * - Connected components (BFS/DFS)
 * - Minimum Spanning Tree (Prim's)
 * - Station/edge removal
 *
 * See implementation in src/Graph.cpp
 */
