
# Metro Route Finder

Simple C++ metro routing system with Dijkstra's algorithm.

---

## About this Project

This repository contains a modular, data-driven C++ application for metro route finding and fare calculation. The codebase is organized for easy extension and maintenance. Anyone interested in adding new features, updating data, or learning from the code can get started quickly using the notes below.

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

## Algorithms & Data Structures Showcased

- **Dijkstra's Algorithm** (shortest path)
- **Breadth-First Search (BFS)** (reachability, traversal)
- **Depth-First Search (DFS)** (traversal, cycle detection)
- **All-paths search** (backtracking/DFS)
- **Cycle detection** (DFS)
- **Connected components** (BFS/DFS)
- **Minimum Spanning Tree (Prim's algorithm)**
- **Graph mutation** (add/remove stations/edges)
- **STL containers:** `unordered_map`, `vector`, `queue`, `stack`, `set`, `tuple`, `priority_queue`

All algorithms are implemented in `Graph` and can be used for interview prep or as a reference for classic DSA patterns in C++.

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


## Extending and Maintaining the Project

- To add new algorithms or features, declare them in the appropriate header in `include/` and implement them in `src/`.
- Use the public API for BFS, DFS, MST, etc. in your own code or for further UI integration.
- When adding new data fields or files, update the relevant info files in `data/` and adjust the code as needed.
- Keep this README and the info files up to date with any major changes or additions.
- If you use new libraries or dependencies, mention them in the relevant file comments and here if important.


## Data files

All data files live in `data/`. See `data/DATA_INFO.md` for formats and examples. To update the metro network, edit `stations.txt` and `connections.txt` as described in the data info file.

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

---

## Contributing or Customizing

- To add new features, follow the structure: declare in `include/`, implement in `src/`, and document in the relevant info files.
- For new data or formats, coordinate changes across `data/`, `include/`, and `src/` as needed.
- Keep documentation up to date so others can easily understand and build on your work.

