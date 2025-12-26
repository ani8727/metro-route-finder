#pragma once
#include <string>
#include <vector>
#include "Graph.h"

class UI {
public:
    // Menu displays
    static void displayMainMenu();
    static void displaySearchMenu();
    static void displayRouteMenu();
    static void displayAnalyticsMenu();
    
    // Pretty printing
    static void printHeader(const std::string& title);
    static void printSeparator(char ch = '=', int width = 50);
    static void printSection(const std::string& title);
    
    // Display results
    static void displayStationTable(const std::vector<std::string>& stations, const Graph& graph);
    static void displayRoute(const PathInfo& path, const Graph& graph);
    static void displayMetroLines(const std::vector<std::string>& lines);
    static void displayNetworkStats(int stations, int edges, const std::vector<std::string>& lines);
    
    // Input helpers
    static std::string getStationInput(const std::string& prompt);
    static std::string trimInput(const std::string& input);
};
