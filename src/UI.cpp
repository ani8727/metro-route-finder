#include "UI.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void UI::printHeader(const std::string& title) {
    printSeparator('=', 60);
    std::cout << std::setw((60 + title.length()) / 2) << title << std::endl;
    printSeparator('=', 60);
}

void UI::printSeparator(char ch, int width) {
    std::cout << std::string(width, ch) << std::endl;
}

void UI::printSection(const std::string& title) {
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

void UI::displayMainMenu() {
    std::cout << "\n";
    printHeader("🚇 METRO ROUTE FINDER SYSTEM");
    std::cout << "\n  1. Find Shortest Route\n";
    std::cout << "  2. Search Stations\n";
    std::cout << "  3. View Stations by Metro Line\n";
    std::cout << "  4. Calculate Fare\n";
    std::cout << "  5. Display All Stations\n";
    std::cout << "  6. Display Metro Network\n";
    std::cout << "  7. Network Statistics\n";
    std::cout << "  8. Exit\n";
    printSeparator('-', 60);
    std::cout << "Enter your choice: ";
}

void UI::displaySearchMenu() {
    std::cout << "\n";
    printSection("SEARCH STATIONS");
    std::cout << "  1. Search by Name (Partial Match)\n";
    std::cout << "  2. Search by Metro Line\n";
    std::cout << "  3. Search by Zone\n";
    std::cout << "  4. Autocomplete\n";
    std::cout << "  5. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void UI::displayRouteMenu() {
    std::cout << "\n";
    printSection("ROUTE OPTIONS");
    std::cout << "  1. Shortest Distance\n";
    std::cout << "  2. Minimum Transfers\n";
    std::cout << "  3. Cheapest Fare\n";
    std::cout << "Enter your choice: ";
}

void UI::displayAnalyticsMenu() {
    std::cout << "\n";
    printSection("NETWORK ANALYTICS");
}

void UI::displayStationTable(const std::vector<std::string>& stations, 
                            const Graph& graph) {
    std::cout << "\n";
    printSection("SEARCH RESULTS");
    
    if (stations.empty()) {
        std::cout << "No stations found.\n";
        return;
    }
    
    std::cout << std::setw(3) << "No" << " | "
              << std::setw(35) << "Station" << " | "
              << std::setw(15) << "Metro Line" << " | "
              << std::setw(6) << "Zone\n";
    printSeparator('-', 70);
    
    for (size_t i = 0; i < stations.size(); i++) {
        const Station* station = graph.getStation(stations[i]);
        if (station) {
            std::cout << std::setw(3) << (i + 1) << " | "
                      << std::setw(35) << stations[i] << " | "
                      << std::setw(15) << station->getMetroLine() << " | "
                      << std::setw(6) << station->getZone() << "\n";
        }
    }
    printSeparator('-', 70);
}

void UI::displayRoute(const PathInfo& path, const Graph& graph) {
    std::cout << "\n";
    printHeader("✓ ROUTE FOUND");
    
    std::cout << "\nDistance: " << std::fixed << std::setprecision(1) 
              << path.totalDistance << " km\n";
    std::cout << "Estimated Fare: ₹" << path.estimatedFare << "\n";
    std::cout << "Transfer Points: " << path.transferPoints << "\n";
    
    std::cout << "\nMetro Lines Used: ";
    for (size_t i = 0; i < path.metroLines.size(); i++) {
        std::cout << path.metroLines[i];
        if (i < path.metroLines.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
    
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "DETAILED ROUTE:\n" << std::string(50, '-') << std::endl;
    
    std::string currentLine;
    for (size_t i = 0; i < path.path.size(); i++) {
        const Station* station = graph.getStation(path.path[i]);
        if (station) {
            std::string stationLine = station->getMetroLine();
            
            if (i == 0) {
                std::cout << "  START: " << path.path[i] << " (" << stationLine << ")\n";
                currentLine = stationLine;
            } else if (stationLine != currentLine) {
                std::cout << "  ↓\n  TRANSFER to " << stationLine << "\n";
                std::cout << "  → " << path.path[i] << "\n";
                currentLine = stationLine;
            } else {
                std::cout << "  → " << path.path[i] << "\n";
            }
        }
    }
    
    std::cout << "  END ✓\n";
    std::cout << std::string(50, '=') << std::endl;
}

void UI::displayMetroLines(const std::vector<std::string>& lines) {
    std::cout << "\n";
    printSection("AVAILABLE METRO LINES");
    
    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << lines[i] << "\n";
    }
    std::cout << "\n";
}

void UI::displayNetworkStats(int stations, int edges, 
                             const std::vector<std::string>& lines) {
    std::cout << "\n";
    printHeader("NETWORK STATISTICS");
    
    std::cout << "\nTotal Stations:      " << stations << "\n";
    std::cout << "Total Connections:   " << edges << "\n";
    std::cout << "Metro Lines:         " << lines.size() << "\n";
    
    std::cout << "\nMetro Lines:\n";
    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << lines[i] << "\n";
    }
    
    double density = (2.0 * edges) / (stations * (stations - 1));
    std::cout << "\nNetwork Density:     " << std::fixed << std::setprecision(3) 
              << density << "\n";
    
    std::cout << std::string(50, '=') << std::endl;
}

std::string UI::getStationInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return trimInput(input);
}

std::string UI::trimInput(const std::string& input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    size_t end = input.find_last_not_of(" \t\n\r");
    
    if (start == std::string::npos) return "";
    return input.substr(start, end - start + 1);
}
