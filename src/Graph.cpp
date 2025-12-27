#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <iomanip>

#include <stack>
#include <set>
#include <tuple>

void Graph::addStation(const std::string& name, const std::string& line,
                       int zone, double lat, double lon) {
    if (stations.find(name) == stations.end()) {
        stations[name] = Station(name, line, zone, lat, lon);
        if (adjList.find(name) == adjList.end()) {
            adjList[name] = std::vector<std::pair<std::string, double>>();
        }
    }
}

void Graph::addEdge(const std::string& station1, const std::string& station2, 
                    double distance) {
    if (stations.find(station1) != stations.end() && 
        stations.find(station2) != stations.end()) {
        adjList[station1].push_back({station2, distance});
        adjList[station2].push_back({station1, distance});
    }
}

// Remove a station and all its edges
bool Graph::removeStation(const std::string& name) {
    if (stations.find(name) == stations.end()) return false;
    stations.erase(name);
    adjList.erase(name);
    for (std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
        std::vector<std::pair<std::string, double> >& v = it->second;
        v.erase(std::remove_if(v.begin(), v.end(), [&](const std::pair<std::string, double>& p) { return p.first == name; }), v.end());
    }
    return true;
}

// Remove an edge between two stations
bool Graph::removeEdge(const std::string& station1, const std::string& station2) {
    bool found = false;
    if (adjList.find(station1) != adjList.end()) {
        auto& v = adjList[station1];
        auto it = std::remove_if(v.begin(), v.end(), [&](const auto& p) { return p.first == station2; });
        if (it != v.end()) { v.erase(it, v.end()); found = true; }
    }
    if (adjList.find(station2) != adjList.end()) {
        auto& v = adjList[station2];
        auto it = std::remove_if(v.begin(), v.end(), [&](const auto& p) { return p.first == station1; });
        if (it != v.end()) { v.erase(it, v.end()); found = true; }
    }
    return found;
}
// BFS traversal from a station
std::vector<std::string> Graph::bfs(const std::string& start) const {
    std::vector<std::string> order;
    if (!hasStation(start)) return order;
    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        std::string curr = q.front(); q.pop();
        order.push_back(curr);
        for (const auto& edge : adjList.at(curr)) {
            if (visited.insert(edge.first).second) {
                q.push(edge.first);
            }
        }
    }
    return order;
}

// DFS traversal from a station
std::vector<std::string> Graph::dfs(const std::string& start) const {
    std::vector<std::string> order;
    if (!hasStation(start)) return order;
    std::unordered_set<std::string> visited;
    std::stack<std::string> s;
    s.push(start);
    while (!s.empty()) {
        std::string curr = s.top(); s.pop();
        if (visited.insert(curr).second) {
            order.push_back(curr);
            for (const auto& edge : adjList.at(curr)) {
                if (!visited.count(edge.first)) s.push(edge.first);
            }
        }
    }
    return order;
}

// Helper for all-paths (recursive)
void findAllPathsUtil(const std::string& u, const std::string& d, std::unordered_set<std::string>& visited,
                      std::vector<std::string>& path, std::vector<std::vector<std::string>>& paths,
                      const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjList) {
    visited.insert(u);
    path.push_back(u);
    if (u == d) {
        paths.push_back(path);
    } else {
        auto it = adjList.find(u);
        if (it != adjList.end()) {
            for (const auto& edge : it->second) {
                if (!visited.count(edge.first)) {
                    findAllPathsUtil(edge.first, d, visited, path, paths, adjList);
                }
            }
        }
    }
    path.pop_back();
    visited.erase(u);
}

// Find all paths between two stations
std::vector<std::vector<std::string>> Graph::findAllPaths(const std::string& source, const std::string& destination) const {
    std::vector<std::vector<std::string>> paths;
    if (!hasStation(source) || !hasStation(destination)) return paths;
    std::unordered_set<std::string> visited;
    std::vector<std::string> path;
    findAllPathsUtil(source, destination, visited, path, paths, adjList);
    return paths;
}

// Helper for cycle detection
bool hasCycleUtil(const std::string& v, const std::string& parent,
                  std::unordered_set<std::string>& visited,
                  const std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adjList) {
    visited.insert(v);
    auto it = adjList.find(v);
    if (it != adjList.end()) {
        for (const auto& edge : it->second) {
            if (!visited.count(edge.first)) {
                if (hasCycleUtil(edge.first, v, visited, adjList)) return true;
            } else if (edge.first != parent) {
                return true;
            }
        }
    }
    return false;
}

// Detect cycles in the network
bool Graph::hasCycle() const {
    std::unordered_set<std::string> visited;
    for (const auto& pair : adjList) {
        if (!visited.count(pair.first)) {
            if (hasCycleUtil(pair.first, "", visited, adjList)) return true;
        }
    }
    return false;
}

// Find connected components
std::vector<std::vector<std::string>> Graph::connectedComponents() const {
    std::vector<std::vector<std::string>> components;
    std::unordered_set<std::string> visited;
    for (const auto& pair : adjList) {
        if (!visited.count(pair.first)) {
            std::vector<std::string> comp;
            std::queue<std::string> q;
            q.push(pair.first);
            visited.insert(pair.first);
            while (!q.empty()) {
                std::string curr = q.front(); q.pop();
                comp.push_back(curr);
                for (const auto& edge : adjList.at(curr)) {
                    if (visited.insert(edge.first).second) {
                        q.push(edge.first);
                    }
                }
            }
            components.push_back(comp);
        }
    }
    return components;
}

// Minimum Spanning Tree (Prim's algorithm)
std::vector<std::tuple<std::string, std::string, double>> Graph::minimumSpanningTree() const {
    std::vector<std::tuple<std::string, std::string, double>> mst;
    if (stations.empty()) return mst;
    std::unordered_set<std::string> inMST;
    auto cmp = [](const std::tuple<double, std::string, std::string>& a,
                  const std::tuple<double, std::string, std::string>& b) {
        return std::get<0>(a) > std::get<0>(b);
    };
    std::priority_queue<std::tuple<double, std::string, std::string>,
                        std::vector<std::tuple<double, std::string, std::string>>,
                        decltype(cmp)> pq(cmp);
    // Start from any station
    std::string start = stations.begin()->first;
    inMST.insert(start);
    for (std::vector<std::pair<std::string, double> >::const_iterator it = adjList.at(start).begin(); it != adjList.at(start).end(); ++it) {
        pq.push(std::make_tuple(it->second, start, it->first));
    }
    while (!pq.empty() && inMST.size() < stations.size()) {
        double weight;
        std::string u, v;
        std::tie(weight, u, v) = pq.top(); pq.pop();
        if (inMST.count(v)) continue;
        inMST.insert(v);
        mst.push_back(std::make_tuple(u, v, weight));
        for (std::vector<std::pair<std::string, double> >::const_iterator it2 = adjList.at(v).begin(); it2 != adjList.at(v).end(); ++it2) {
            if (!inMST.count(it2->first)) {
                pq.push(std::make_tuple(it2->second, v, it2->first));
            }
        }
    }
    return mst;
}

bool Graph::hasStation(const std::string& name) const {
    return stations.find(name) != stations.end();
}

const Station* Graph::getStation(const std::string& name) const {
    auto it = stations.find(name);
    return (it != stations.end()) ? &it->second : nullptr;
}

int Graph::getEdgeCount() const {
    int count = 0;
    for (const auto& pair : adjList) {
        count += pair.second.size();
    }
    return count / 2; // undirected graph
}

std::string Graph::getCurrentLine(const std::string& from, const std::string& to) {
    auto it = stations.find(to);
    if (it != stations.end()) {
        return it->second.getMetroLine();
    }
    return "Unknown";
}

void Graph::reconstructPath(const std::unordered_map<std::string, std::string>& parent,
                            const std::string& destination, PathInfo& result) {
    std::vector<std::string> path;
    std::string current = destination;
    
    while (!current.empty()) {
        path.push_back(current);
        auto it = parent.find(current);
        if (it == parent.end() || it->second.empty()) {
            break;
        }
        current = it->second;
    }
    
    std::reverse(path.begin(), path.end());
    result.path = path;
    
    // Extract metro lines used
    std::unordered_set<std::string> linesSet;
    for (const auto& station : path) {
        auto stIt = stations.find(station);
        if (stIt != stations.end()) {
            linesSet.insert(stIt->second.getMetroLine());
        }
    }
    
    for (const auto& line : linesSet) {
        result.metroLines.push_back(line);
    }
    
    // Count transfers
    if (path.size() > 1) {
        result.transferPoints = 0;
        std::string currentLine = stations.find(path[0])->second.getMetroLine();
        for (size_t i = 1; i < path.size(); i++) {
            std::string nextLine = stations.find(path[i])->second.getMetroLine();
            if (nextLine != currentLine) {
                result.transferPoints++;
                currentLine = nextLine;
            }
        }
    }
}

// Dijkstra's Algorithm - O((V+E)log V)
PathInfo Graph::findShortestPath(const std::string& source, 
                                  const std::string& destination) {
    PathInfo result;
    result.totalDistance = -1;
    result.estimatedFare = 0;
    result.transferPoints = 0;
    
    if (!hasStation(source) || !hasStation(destination)) {
        return result;
    }
    
    std::unordered_map<std::string, double> distance;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;
    
    // Priority queue: (distance, station)
    auto cmp = [](const std::pair<double, std::string>& a, 
                  const std::pair<double, std::string>& b) {
        return a.first > b.first;
    };
    std::priority_queue<std::pair<double, std::string>, 
                       std::vector<std::pair<double, std::string>>,
                       decltype(cmp)> pq(cmp);
    
    // Initialize
    for (const auto& station : stations) {
        distance[station.first] = 1e9;
    }
    distance[source] = 0;
    parent[source] = "";
    pq.push({0, source});
    
    // Dijkstra's main loop
    while (!pq.empty()) {
        double currentDist = pq.top().first;
        std::string currentStation = pq.top().second;
        pq.pop();
        
        if (visited.find(currentStation) != visited.end()) {
            continue;
        }
        visited.insert(currentStation);
        
        if (currentStation == destination) {
            break;
        }
        
        if (currentDist > distance[currentStation]) {
            continue;
        }
        
        // Check neighbors
        for (const auto& edge : adjList[currentStation]) {
            const auto& neighbor = edge.first;
            double weight = edge.second;
            if (visited.find(neighbor) == visited.end()) {
                double newDist = currentDist + weight;
                if (newDist < distance[neighbor]) {
                    distance[neighbor] = newDist;
                    parent[neighbor] = currentStation;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }
    
    if (distance[destination] >= 1e9) {
        return result; // No path found
    }
    
    result.totalDistance = distance[destination];
    reconstructPath(parent, destination, result);
    
    // Calculate fare based on zones
    int maxZone = 0;
    for (const auto& station : result.path) {
        maxZone = std::max(maxZone, getStation(station)->getZone());
    }
    result.estimatedFare = 10 + (int)(maxZone * 3) + (int)(result.totalDistance * 1.5);
    
    return result;
}

void Graph::displayAllStations() const {
    std::cout << "\n";
    printHeader("ALL STATIONS IN METRO NETWORK");
    
    std::vector<std::pair<std::string, Station>> stationList;
    for (const auto& station : stations) {
        stationList.push_back({station.first, station.second});
    }
    
    std::sort(stationList.begin(), stationList.end());
    
    std::cout << std::setw(3) << "No" << " | "
              << std::setw(30) << "Station Name" << " | "
              << std::setw(15) << "Metro Line" << " | "
              << std::setw(5) << "Zone" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    int count = 1;
    for (const auto& pair : stationList) {
        std::cout << std::setw(3) << count << " | "
                  << std::setw(30) << pair.first << " | "
                  << std::setw(15) << pair.second.getMetroLine() << " | "
                  << std::setw(5) << pair.second.getZone() << std::endl;
        count++;
    }
    std::cout << std::string(70, '=') << std::endl;
}

void Graph::displayNetwork() const {
    std::cout << "\n";
    printHeader("METRO NETWORK STRUCTURE");
    
    for (const auto& pair : adjList) {
        std::string station = pair.first;
        std::cout << "\n" << station << " (" 
                  << stations.find(station)->second.getMetroLine() << ")" << std::endl;
        std::cout << "  Connected to:" << std::endl;
        for (const auto& edge : pair.second) {
            std::string neighbor = edge.first;
            double distance = edge.second;
            std::cout << "    -> " << neighbor << " (" 
                      << std::fixed << std::setprecision(1) << distance << " km)" << std::endl;
        }
    }
    std::cout << "\n" << std::string(50, '=') << std::endl;
}

void Graph::displayByMetroLine(const std::string& lineName) const {
    std::cout << "\n";
    printHeader("STATIONS ON " + lineName);
    
    std::vector<std::string> lineStations;
    for (const auto& pair : stations) {
        if (pair.second.getMetroLine() == lineName) {
            lineStations.push_back(pair.first);
        }
    }
    
    std::sort(lineStations.begin(), lineStations.end());
    
    if (lineStations.empty()) {
        std::cout << "No stations found on this line.\n";
        return;
    }
    
    std::cout << "\nStations on " << lineName << ":\n";
    for (size_t i = 0; i < lineStations.size(); i++) {
        std::cout << std::setw(2) << (i + 1) << ". " << lineStations[i] << std::endl;
    }
    std::cout << "\nTotal: " << lineStations.size() << " stations\n";
    std::cout << std::string(50, '=') << std::endl;
}

std::vector<std::string> Graph::getAllMetroLines() const {
    std::unordered_set<std::string> linesSet;
    for (const auto& station : stations) {
        linesSet.insert(station.second.getMetroLine());
    }
    
    std::vector<std::string> lines(linesSet.begin(), linesSet.end());
    std::sort(lines.begin(), lines.end());
    return lines;
}

std::vector<std::string> Graph::getStationsByLine(const std::string& lineName) const {
    std::vector<std::string> result;
    for (const auto& pair : stations) {
        if (pair.second.getMetroLine() == lineName) {
            result.push_back(pair.first);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

inline void printHeader(const std::string& title) {
    std::cout << std::string(50, '=') << std::endl;
    std::cout << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
