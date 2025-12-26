# Metro Route Finder

Simple C++ metro routing system with Dijkstra's algorithm.

# Metro Route Finder

Metro Route Finder is an educational, intermediate-level C++ project that demonstrates graph algorithms, software design, and small-scale route planning. It models a metro network as an undirected, weighted graph and uses Dijkstra's algorithm to find shortest paths between stations. The project is designed for learning and interview preparation: it showcases efficient data-structures (hash maps, priority queues), clean module separation, and a small interactive UI.

Project goals:
- Demonstrate Dijkstra's shortest-path implementation and its trade-offs.
- Show clear separation of responsibilities (Graph, SearchEngine, FareCalculator, UI).
- Provide a small, editable dataset and a menu-driven interface for experimentation.

Who it's for:
- Students practicing algorithms and C++
- Interview candidates preparing system-design + DSA exercises
- Hobbyists building simple route planners or learning graph algorithms

Key Characteristics:
- Language: C++17 (standard library only)
- Data-driven: station and connection CSV files in `data/`
- Modular: easy to extend (add heuristics, caching, UI)

---

## Features (short)

- Dijkstra's algorithm for weighted shortest paths
- Station search (name/line/zone/autocomplete)
- Simple fare calculator (distance + zone)
- Admin mode (in-memory add/delete, reload from files)
- Clean, file-based dataset under `data/`

## Project Structure

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
├── data/                 # Data files
│   ├── stations.txt
│   ├── connections.txt
│   └── DATA_INFO.md      # Data format and editing instructions
├── main.cpp              # Entry point with Admin/User login
└── README.md
```

## Data files

All data files live in `data/`. See `data/DATA_INFO.md` for formats and examples.

---

## Login modes

1) Admin — manage the dataset in-memory, add/delete stations, add connections, and reload data from files.
2) User — interactive route finding, search, fare calculation, and network display.

---

## Detailed Features

- Graph representation: adjacency list with weighted edges
- Search engine: case-insensitive substring search + autocomplete
- Fare calculator: base fare + distance + zone multipliers
- UI: menu-driven console interface

---

## Quick Start & Run (bottom)

This section explains how to build and run the project locally. It's replicated at the end of the file for convenience.

---

## Quick Start — Build & Run

1. Build (Windows example with g++):

```powershell
g++ -std=c++17 -o metro main.cpp src/*.cpp -I include
```

2. Run the executable:

```powershell
.
\metro.exe
```

3. Usage:

- On start, choose `1` for Admin or `2` for User.
- Admin actions are in-memory; edit `data/` files to persist changes.

Notes:

- Data files are in the `data/` folder: `stations.txt`, `connections.txt`.
- Admin "Reload data" restores the graph from files.
- To permanently change the dataset, edit the files in `data/` and restart the app.

---

For detailed data formats, see [data/DATA_INFO.md](data/DATA_INFO.md#L1).

