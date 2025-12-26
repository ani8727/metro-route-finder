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

## About This Project

Metro Route Finder is an educational C++ project that demonstrates graph algorithms and software design for small-scale route planning. It implements Dijkstra's shortest-path algorithm on a simple undirected weighted graph of metro stations and connections. The project is aimed at interview preparation and learning core data-structures and algorithms (graphs, priority queues, hashing), as well as clean C++ project organization.

Key highlights:
- Modular design with separate components for graph management, searching, fare calculation and UI.
- File-based data input (CSV-like) so you can extend or replace the dataset easily.
- Simple admin mode for adding stations/connections (in-memory) and reloading data from files.

## Quick Start — Extended

1. Build (Windows example with g++):
```powershell
g++ -std=c++17 -o metro main.cpp src/*.cpp -I include
```

2. Run the executable:
```powershell
./metro.exe
```

3. When the app starts choose:
- `1` Admin Login — to add/delete stations or reload from `data/` files.
- `2` User Login — to use route finding and search features.

Notes:
- Data files live in the `data/` folder (`stations.txt`, `connections.txt`).
- Admin additions (via menu) are applied in-memory; use "Reload data" to restore from files.
- To permanently update the dataset, edit the files in `data/` and then use the reload option or restart the app.

## Data files (where to find them)

All input data is under the `data/` folder. See `data/DATA_INFO.md` for exact file formats and sample records.


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
