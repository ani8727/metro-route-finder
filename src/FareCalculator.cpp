#include "FareCalculator.h"
#include <sstream>
#include <iomanip>

int FareCalculator::calculateFare(double distance, int maxZone) const {
    double fare = BASE_FARE;
    fare += distance * COST_PER_KM;
    fare += maxZone * ZONE_SURCHARGE;
    
    // Round to nearest rupee
    return static_cast<int>(fare + 0.5);
}

std::string FareCalculator::getFareBreakdown(double distance, int maxZone) const {
    std::ostringstream oss;
    
    double baseFare = BASE_FARE;
    double distanceFare = distance * COST_PER_KM;
    double zoneFare = maxZone * ZONE_SURCHARGE;
    double totalFare = baseFare + distanceFare + zoneFare;
    
    oss << "\n========== FARE BREAKDOWN ==========\n";
    oss << "Base Fare:          ₹" << std::fixed << std::setprecision(2) << baseFare << std::endl;
    oss << "Distance Charge:    ₹" << std::fixed << std::setprecision(2) 
        << distanceFare << " (" << distance << " km × ₹" << COST_PER_KM << "/km)" << std::endl;
    oss << "Zone Surcharge:     ₹" << std::fixed << std::setprecision(2) 
        << zoneFare << " (" << maxZone << " zones × ₹" << ZONE_SURCHARGE << ")" << std::endl;
    oss << "====================================\n";
    oss << "Total Fare:         ₹" << static_cast<int>(totalFare + 0.5) << std::endl;
    oss << "====================================\n";
    
    return oss.str();
}

int FareCalculator::getRoundTripFare(double distance, int maxZone) const {
    int onewayFare = calculateFare(distance, maxZone);
    return onewayFare * 2 - 5; // 5% discount on round trip
}

std::string FareCalculator::getFareCategory(int fare) const {
    if (fare <= 15) return "Economy";
    if (fare <= 30) return "Standard";
    if (fare <= 50) return "Premium";
    return "Long Distance";
}
