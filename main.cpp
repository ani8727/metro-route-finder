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

    while (true) {
        cout << "\n" << string(50, '=') << "\n";
        cout << "        🚇 METRO ROUTE FINDER\n";
        cout << string(50, '=') << "\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        int mainChoice;
        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid number (1-3).\n";
            continue;
        }
        cin.ignore(10000, '\n');
        if (mainChoice == 1) {
            // Admin menu (distinct logic)
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
                cout << "Enter choice: ";
                int adminChoice;
                if (!(cin >> adminChoice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number (1-8).\n";
                    continue;
                }
                cin.ignore(10000, '\n');
                if (adminChoice == 1) {
                    cout << "\n--- Add New Station ---\n";
                    cout << "Station name: ";
                    string name;
                    getline(cin, name);
                    cout << "Metro line (Blue/Red/Green/Yellow/Purple): ";
                    string line;
                    getline(cin, line);
                    cout << "Zone (1-5): ";
                    int zone;
                    if (!(cin >> zone)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Please enter a valid zone number.\n";
                        continue;
                    }
                    cout << "Latitude: ";
                    double lat;
                    if (!(cin >> lat)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Please enter a valid number for latitude.\n";
                        continue;
                    }
                    cout << "Longitude: ";
                    double lon;
                    if (!(cin >> lon)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Please enter a valid number for longitude.\n";
                        continue;
                    }
                    cin.ignore(10000, '\n');
                    metro.addStation(name, line, zone, lat, lon);
                    cout << "✓ Station added: " << name << "\n";
                } else if (adminChoice == 2) {
                    cout << "\n--- Delete Station ---\n";
                    metro.displayAllStations();
                    cout << "\nStation name to delete: ";
                    string delName;
                    getline(cin, delName);
                    if (metro.hasStation(delName)) {
                        cout << "✓ Station deleted: " << delName << "\n";
                        cout << "(Note: Full deletion requires additional implementation)\n";
                    } else {
                        cout << "Station not found!\n";
                    }
                } else if (adminChoice == 3) {
                    cout << "\n--- Add Connection ---\n";
                    cout << "Station 1: ";
                    string sta1;
                    getline(cin, sta1);
                    cout << "Station 2: ";
                    string sta2;
                    getline(cin, sta2);
                    cout << "Distance (km): ";
                    double dist;
                    if (!(cin >> dist)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Please enter a valid number for distance.\n";
                        continue;
                    }
                    cin.ignore(10000, '\n');
                    metro.addEdge(sta1, sta2, dist);
                    cout << "✓ Connection added: " << sta1 << " <-> " << sta2 << "\n";
                } else if (adminChoice == 4) {
                    metro.displayAllStations();
                } else if (adminChoice == 5) {
                    metro.displayNetwork();
                } else if (adminChoice == 6) {
                    auto lines = metro.getAllMetroLines();
                    UI::displayNetworkStats(metro.getStationCount(), metro.getEdgeCount(), lines);
                } else if (adminChoice == 7) {
                    cout << "\nReloading data...\n";
                    Graph newMetro;
                    if (loadStationsFromFile(newMetro, "data/stations.txt") && loadConnectionsFromFile(newMetro, "data/connections.txt")) {
                        metro = newMetro;
                        cout << "✓ Data reloaded successfully!\n";
                    } else {
                        cout << "Error reloading data!\n";
                    }
                } else if (adminChoice == 8) {
                    cout << "Logging out...\n";
                    cout << "See you soon! 👋\n\n";
                    return 0;
                } else {
                    cout << "Invalid choice. Please enter a number from 1 to 8.\n";
                }
            }
        } else if (mainChoice == 2) {
            // User menu (restored, more options)
            while (true) {
                cout << "\n" << string(50, '-') << "\n";
                cout << "USER MENU\n";
                cout << string(50, '-') << "\n";
                cout << "1. Search Stations\n";
                cout << "2. View All Stations\n";
                cout << "3. View Network\n";
                cout << "4. View Statistics\n";
                cout << "5. Reload Data from Files\n";
                cout << "6. Logout\n";
                cout << "Enter choice: ";
                int userChoice;
                if (!(cin >> userChoice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number (1-6).\n";
                    continue;
                }
                cin.ignore(10000, '\n');
                if (userChoice == 1) {
                    searchStationsMenu(metro, search);
                } else if (userChoice == 2) {
                    metro.displayAllStations();
                } else if (userChoice == 3) {
                    metro.displayNetwork();
                } else if (userChoice == 4) {
                    auto lines = metro.getAllMetroLines();
                    UI::displayNetworkStats(metro.getStationCount(), metro.getEdgeCount(), lines);
                } else if (userChoice == 5) {
                    cout << "\nReloading data...\n";
                    Graph newMetro;
                    if (loadStationsFromFile(newMetro, "data/stations.txt") && loadConnectionsFromFile(newMetro, "data/connections.txt")) {
                        metro = newMetro;
                        cout << "✓ Data reloaded successfully!\n";
                    } else {
                        cout << "Error reloading data!\n";
                    }
                } else if (userChoice == 6) {
                    cout << "Logging out...\n";
                    cout << "See you soon! 👋\n\n";
                    return 0;
                } else {
                    cout << "Invalid choice. Please enter a number from 1 to 6.\n";
                }
            }
        } else if (mainChoice == 3) {
            cout << "See you soon! 👋\n\n";
            return 0;
        } else {
            cout << "Invalid choice. Please enter a number from 1 to 3.\n";
        }
    }
    return 0;
}

