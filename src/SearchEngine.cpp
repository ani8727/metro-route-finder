#include "SearchEngine.h"
#include <cctype>
#include <algorithm>
#include <cmath>

SearchEngine::SearchEngine(const std::unordered_map<std::string, Station>& db)
    : stationDB(db) {}

bool SearchEngine::caseInsensitiveCompare(const std::string& str1, 
                                         const std::string& str2) {
    if (str1.length() != str2.length()) return false;
    
    for (size_t i = 0; i < str1.length(); i++) {
        if (std::tolower(str1[i]) != std::tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

bool SearchEngine::containsSubstring(const std::string& str, 
                                    const std::string& substr) {
    std::string strLower = str;
    std::string substrLower = substr;
    
    std::transform(strLower.begin(), strLower.end(), strLower.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    std::transform(substrLower.begin(), substrLower.end(), substrLower.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    
    return strLower.find(substrLower) != std::string::npos;
}

std::vector<std::string> SearchEngine::searchByName(const std::string& keyword) const {
    std::vector<std::string> results;
    
    for (const auto& pair : stationDB) {
        if (containsSubstring(pair.first, keyword)) {
            results.push_back(pair.first);
        }
    }
    
    std::sort(results.begin(), results.end());
    return results;
}

std::vector<std::string> SearchEngine::searchByLine(const std::string& lineName) const {
    std::vector<std::string> results;
    
    for (const auto& pair : stationDB) {
        if (caseInsensitiveCompare(pair.second.getMetroLine(), lineName)) {
            results.push_back(pair.first);
        }
    }
    
    std::sort(results.begin(), results.end());
    return results;
}

std::vector<std::string> SearchEngine::searchByZone(int zoneNumber) const {
    std::vector<std::string> results;
    
    for (const auto& pair : stationDB) {
        if (pair.second.getZone() == zoneNumber) {
            results.push_back(pair.first);
        }
    }
    
    std::sort(results.begin(), results.end());
    return results;
}

std::vector<std::string> SearchEngine::getAutocompleteSuggestions(
    const std::string& prefix) const {
    std::vector<std::string> results;
    std::string prefixLower = prefix;
    std::transform(prefixLower.begin(), prefixLower.end(), prefixLower.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    
    for (const auto& pair : stationDB) {
        std::string nameLower = pair.first;
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        if (nameLower.find(prefixLower) == 0) {
            results.push_back(pair.first);
        }
    }
    
    std::sort(results.begin(), results.end());
    return results;
}

std::string SearchEngine::getNearestStation(double latitude, double longitude) const {
    double minDistance = 1e9;
    std::string nearest;
    
    for (const auto& pair : stationDB) {
        double dist = std::sqrt(
            std::pow(pair.second.getLatitude() - latitude, 2) +
            std::pow(pair.second.getLongitude() - longitude, 2)
        );
        
        if (dist < minDistance) {
            minDistance = dist;
            nearest = pair.first;
        }
    }
    
    return nearest;
}
