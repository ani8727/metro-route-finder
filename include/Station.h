#pragma once
#include <string>

class Station {
private:
    std::string name;
    std::string metroLine;
    int zoneNumber;
    double latitude;
    double longitude;

public:
    // Constructor
    Station(const std::string& n = "", const std::string& line = "", 
            int zone = 1, double lat = 0.0, double lon = 0.0);
    
    // Getters
    const std::string& getName() const { return name; }
    const std::string& getMetroLine() const { return metroLine; }
    int getZone() const { return zoneNumber; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    
    // Comparison operator for sorting
    bool operator<(const Station& other) const { 
        return name < other.name; 
    }
    
    // Display
    void display() const;
};
