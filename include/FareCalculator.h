#pragma once
#include <string>

class FareCalculator {
private:
    static constexpr double BASE_FARE = 5.0;        // Initial fare in rupees
    static constexpr double COST_PER_KM = 0.8;      // Cost per km
    static constexpr double ZONE_SURCHARGE = 3.0;   // Extra per zone crossed

public:
    FareCalculator() = default;
    
    // Calculate fare based on distance and zones
    // Distance in km, maxZone is highest zone number in path
    int calculateFare(double distance, int maxZone) const;
    
    // Get detailed fare breakdown
    std::string getFareBreakdown(double distance, int maxZone) const;
    
    // Get round-trip fare
    int getRoundTripFare(double distance, int maxZone) const;
    
    // Get fare category
    std::string getFareCategory(int fare) const;
};
