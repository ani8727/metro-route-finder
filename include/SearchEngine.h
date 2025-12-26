#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Station.h"

class SearchEngine {
private:
    const std::unordered_map<std::string, Station>& stationDB;
    
    // Helper - case insensitive compare
    static bool caseInsensitiveCompare(const std::string& str1, const std::string& str2);
    static bool containsSubstring(const std::string& str, const std::string& substr);

public:
    explicit SearchEngine(const std::unordered_map<std::string, Station>& db);
    
    // Search by station name (partial match, case-insensitive)
    std::vector<std::string> searchByName(const std::string& keyword) const;
    
    // Search by metro line
    std::vector<std::string> searchByLine(const std::string& lineName) const;
    
    // Search by zone
    std::vector<std::string> searchByZone(int zoneNumber) const;
    
    // Get suggestions (starts with prefix)
    std::vector<std::string> getAutocompleteSuggestions(const std::string& prefix) const;
    
    // Get nearest station by coordinates
    std::string getNearestStation(double latitude, double longitude) const;
};
