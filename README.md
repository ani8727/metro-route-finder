# Metro Route Finder

Simple C++ metro routing system with Dijkstra's algorithm.

## 🚀 Quick Start

### Compile
```bash
g++ -std=c++17 -o metro main.cpp src/*.cpp -I include
```

### Run
```bash
metro.exe
```

## � Login System

**Two User Types:**

### 1️⃣ ADMIN MODE
- Add new stations
- Delete stations
- Add connections
- View all stations
- View network
- View statistics
- Reload data from files

### 2️⃣ USER MODE
- Find Shortest Route (Dijkstra's)
- Search Stations (4 types)
- View by Metro Line
- Calculate Fare
- Display All Stations
- Display Network
- Network Statistics

## 📁 Project Structure

```
metro-route-finder/
├── include/              # Headers
│   ├── Station.h
│   ├── Graph.h           (Dijkstra's algorithm)
│   ├── SearchEngine.h
│   ├── FareCalculator.h
│   └── UI.h
├── src/                  # Implementation
│   ├── Station.cpp
│   ├── Graph.cpp         ⭐ Core algorithm
│   ├── SearchEngine.cpp
│   ├── FareCalculator.cpp
│   └── UI.cpp
├── data/                 # Data
│   ├── stations.txt      (35 stations)
│   └── connections.txt   (30+ connections)
└── main.cpp              (Entry point with login)
```

## 🎮 Startup Flow

```
🚇 METRO ROUTE FINDER
1. Admin Login        → Manage system
2. User Login         → Use metro finder
3. Exit               → Quit app
```

## 📊 Algorithm

**Dijkstra's Shortest Path**
- Time: O((V+E) log V)
- Space: O(V + E)
- Using: Priority queue + unordered_map

## 💾 Data

- **35 Stations** across 5 metro lines
- **30+ Connections** with distances
- Format: CSV files

## ✨ Features

- Dual login system (Admin/User)
- Shortest path finding
- Multi-type search
- Fare calculation
- Station management
- Network visualization
- Statistics display

---

**Language**: C++17 | **Size**: ~300 KB | **Build**: < 5 seconds
