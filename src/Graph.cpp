#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <iomanip>

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
