#include "Station.h"
#include <iostream>
#include <iomanip>

Station::Station(const std::string& n, const std::string& line, 
                 int zone, double lat, double lon)
    : name(n), metroLine(line), zoneNumber(zone), 
      latitude(lat), longitude(lon) {}

void Station::display() const {
    std::cout << "Name: " << name << " | Line: " << metroLine 
              << " | Zone: " << zoneNumber << std::endl;
}
