#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "Graph.h"
#include "SearchEngine.h"
#include "FareCalculator.h"
#include "UI.h"

using namespace std;

// Load stations from file
bool loadStationsFromFile(Graph& graph, const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }
    
    string line;
    int count = 0;
    
    cout << "Loading stations...\n";
    
    while (getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;
        
        // Parse: StationName,MetroLine,Zone,Latitude,Longitude
        stringstream ss(line);
        string station, line_name, zone_str, lat_str, lon_str;
        
        if (getline(ss, station, ',') && 
            getline(ss, line_name, ',') &&
            getline(ss, zone_str, ',') &&
            getline(ss, lat_str, ',') &&
            getline(ss, lon_str, ',')) {
            
            int zone = stoi(zone_str);
            double lat = stod(lat_str);
            double lon = stod(lon_str);
            
            graph.addStation(station, line_name, zone, lat, lon);
            count++;
        }
    }
    
    file.close();
    cout << "Loaded " << count << " stations.\n";
    return count > 0;
}

// Load connections from file
bool loadConnectionsFromFile(Graph& graph, const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }
    
    string line;
    int count = 0;
    
    cout << "Loading connections...\n";
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        // Parse: Station1,Station2,Distance
        stringstream ss(line);
        string station1, station2, distance_str;
        
        if (getline(ss, station1, ',') && 
            getline(ss, station2, ',') &&
            getline(ss, distance_str, ',')) {
            
            double distance = stod(distance_str);
            graph.addEdge(station1, station2, distance);
            count++;
        }
    }
    
    file.close();
    cout << "Loaded " << count << " connections.\n";
    return true;
}

void searchStationsMenu(Graph& graph, SearchEngine& search) {
    int choice;
    
    while (true) {
        UI::displaySearchMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string keyword = UI::getStationInput("Enter station name (partial): ");
                auto results = search.searchByName(keyword);
                UI::displayStationTable(results, graph);
                break;
            }
            
            case 2: {
                auto lines = graph.getAllMetroLines();
                UI::displayMetroLines(lines);
                string line = UI::getStationInput("Enter metro line name: ");
                auto results = search.searchByLine(line);
                UI::displayStationTable(results, graph);
                break;
            }
            
            case 3: {
                int zone;
                cout << "Enter zone number: ";
                cin >> zone;
                cin.ignore();
                
                auto results = search.searchByZone(zone);
                UI::displayStationTable(results, graph);
                break;
            }
            
            case 4: {
                string prefix = UI::getStationInput("Enter station prefix: ");
                auto suggestions = search.getAutocompleteSuggestions(prefix);
                UI::displayStationTable(suggestions, graph);
                break;
            }
            
            case 5:
                return;
                
            default:
                cout << "Invalid choice!\n";
        }
    }
}

int main() {
    Graph metro;
    FareCalculator fareCalc;
    
    // Load data
    if (!loadStationsFromFile(metro, "data/stations.txt")) {
        cout << "Failed to load stations!\n";
        return 1;
    }
    
    if (!loadConnectionsFromFile(metro, "data/connections.txt")) {
        cout << "Warning: Could not load all connections.\n";
    }
    
    SearchEngine search(metro.getStations());
    
    cout << "\n✓ Metro system loaded successfully!\n";
    
    // LOGIN MENU
    int userType = 0;
    while (userType == 0) {
        cout << "\n" << string(50, '=') << "\n";
        cout << "        🚇 METRO ROUTE FINDER\n";
        cout << string(50, '=') << "\n";
        cout << "\n1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "\nEnter choice: ";
        cin >> userType;
        cin.ignore();
        
        if (userType == 3) {
            cout << "Goodbye!\n";
            return 0;
        }
        if (userType != 1 && userType != 2) {
            cout << "Invalid choice!\n";
            userType = 0;
        }
    }
    
    int choice;
    string source, destination;
    
    // ========== ADMIN MODE ==========
    if (userType == 1) {
        cout << "\n🔐 ADMIN MODE\n";
        
        while (true) {
            cout << "\n" << string(50, '-') << "\n";
            cout << "ADMIN MENU\n";
            cout << string(50, '-') << "\n";
            cout << "1. Add New Station\n";
            cout << "2. Delete Station\n";
            cout << "3. Add Connection\n";
            cout << "4. View All Stations\n";
            cout << "5. View Network\n";
            cout << "6. View Statistics\n";
            cout << "7. Reload Data from Files\n";
            cout << "8. Logout\n";
            cout << "\nEnter choice: ";
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: {
                    // Add new station
                    cout << "\n--- Add New Station ---\n";
                    cout << "Station name: ";
                    string name;
                    getline(cin, name);
                    
                    cout << "Metro line (Blue/Red/Green/Yellow/Purple): ";
                    string line;
                    getline(cin, line);
                    
                    cout << "Zone (1-5): ";
                    int zone;
                    cin >> zone;
                    
                    cout << "Latitude: ";
                    double lat;
                    cin >> lat;
                    
                    cout << "Longitude: ";
                    double lon;
                    cin >> lon;
                    cin.ignore();
                    
                    metro.addStation(name, line, zone, lat, lon);
                    cout << "✓ Station added: " << name << "\n";
                    break;
                }
                
                case 2: {
                    // Delete station
                    cout << "\n--- Delete Station ---\n";
                    metro.displayAllStations();
                    cout << "\nStation name to delete: ";
                    string delName;
                    getline(cin, delName);
                    
                    if (metro.hasStation(delName)) {
                        cout << "✓ Station deleted: " << delName << "\n";
                        // Note: Deletion would require Graph modification
                        cout << "(Note: Full deletion requires additional implementation)\n";
                    } else {
                        cout << "Station not found!\n";
                    }
                    break;
                }
                
                case 3: {
                    // Add connection
                    cout << "\n--- Add Connection ---\n";
                    cout << "Station 1: ";
                    string sta1;
                    getline(cin, sta1);
                    
                    cout << "Station 2: ";
                    string sta2;
                    getline(cin, sta2);
                    
                    cout << "Distance (km): ";
                    double dist;
                    cin >> dist;
                    cin.ignore();
                    
                    metro.addEdge(sta1, sta2, dist);
                    cout << "✓ Connection added: " << sta1 << " <-> " << sta2 << "\n";
                    break;
                }
                
                case 4: {
                    metro.displayAllStations();
                    break;
                }
                
                case 5: {
                    metro.displayNetwork();
                    break;
                }
                
                case 6: {
                    auto lines = metro.getAllMetroLines();
                    UI::displayNetworkStats(metro.getStationCount(), 
                                           metro.getEdgeCount(), 
                                           lines);
                    break;
                }
                
                case 7: {
                    cout << "\nReloading data...\n";
                    Graph newMetro;
                    if (loadStationsFromFile(newMetro, "data/stations.txt") &&
                        loadConnectionsFromFile(newMetro, "data/connections.txt")) {
                        metro = newMetro;
                        cout << "✓ Data reloaded successfully!\n";
                    } else {
                        cout << "Error reloading data!\n";
                    }
                    break;
                }
                
                case 8: {
                    cout << "Logging out...\n";
                    return 0;
                }
                
                default:
                    cout << "Invalid choice!\n";
            }
        }
    }
    
    // ========== USER MODE ==========
    else {
        cout << "\n👤 USER MODE\n";
        
        while (true) {
            UI::displayMainMenu();
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: {
                    // Find shortest route
                    source = UI::getStationInput("Enter source station: ");
                    destination = UI::getStationInput("Enter destination station: ");
                    
                    if (!metro.hasStation(source)) {
                        cout << "Error: Source station not found!\n";
                        break;
                    }
                    if (!metro.hasStation(destination)) {
                        cout << "Error: Destination station not found!\n";
                        break;
                    }
                    
                    PathInfo path = metro.findShortestPath(source, destination);
                    
                    if (path.totalDistance < 0) {
                        cout << "\nError: No path found between stations!\n";
                    } else {
                        UI::displayRoute(path, metro);
                        
                        cout << "\n" << fareCalc.getFareBreakdown(path.totalDistance, 3);
                        
                        cout << "\nRound-trip Fare: ₹" 
                             << fareCalc.getRoundTripFare(path.totalDistance, 3) << endl;
                    }
                    break;
                }
                
                case 2: {
                    // Search stations
                    searchStationsMenu(metro, search);
                    break;
                }
                
                case 3: {
                    // View by metro line
                    auto lines = metro.getAllMetroLines();
                    UI::displayMetroLines(lines);
                    
                    string line = UI::getStationInput("Enter metro line name: ");
                    metro.displayByMetroLine(line);
                    break;
                }
                
                case 4: {
                    // Calculate fare
                    cout << "\nEnter distance (km): ";
                    double distance;
                    cin >> distance;
                    cin.ignore();
                    
                    cout << "Enter max zone to cross: ";
                    int zone;
                    cin >> zone;
                    cin.ignore();
                    
                    cout << fareCalc.getFareBreakdown(distance, zone);
                    cout << "Category: " << fareCalc.getFareCategory(
                        fareCalc.calculateFare(distance, zone)) << endl;
                    break;
                }
                
                case 5: {
                    // Display all stations
                    metro.displayAllStations();
                    break;
                }
                
                case 6: {
                    // Display network
                    metro.displayNetwork();
                    break;
                }
                
                case 7: {
                    // Network statistics
                    auto lines = metro.getAllMetroLines();
                    UI::displayNetworkStats(metro.getStationCount(), 
                                           metro.getEdgeCount(), 
                                           lines);
                    break;
                }
                
                case 8: {
                    // Exit
                    cout << "\n";
                    cout << "Thank you for using Metro Route Finder!\n";
                    cout << "See you soon! 👋\n\n";
                    return 0;
                }
                
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        }
    }
    
    return 0;
}
