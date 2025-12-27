
# About the `src/` folder (updated snapshot)

## Working with and Extending the Project

This folder contains all the C++ source files that implement the main logic of the Metro Route Finder. To add new features, fix bugs, or extend the project, follow these practical guidelines:

- To add a new function or feature:
  1. Declare the new function or class in the appropriate header file in `include/` (or create a new header if needed).
  2. Implement the logic in a `.cpp` file here in `src/`.
  3. Use minimal includes and forward declarations to keep compile times fast.
  4. If you add a new `.cpp` file, update the build command or project file so it is compiled.
  5. Document any new files or major changes in this `src_info.md` for clarity.

- When using new standard or third-party libraries, mention them in the relevant file comments and here if they are important for understanding the codebase.

- For new data or file formats, coordinate with the `data/` and `include/` folders and update their info files as needed.

- Centralize file parsing and data loading logic in `Graph.cpp` or a dedicated loader to avoid duplication.

- Keep code modular: each `.cpp` should focus on a single responsibility (e.g., graph logic, fare calculation, UI helpers).

These practices help keep the project organized, easy to understand, and ready for future improvements by anyone working on the repository.

This file is an up-to-date snapshot describing the C++ translation units currently present in `src/`, the headers they implement, the data files they reference, and the main standard-library facilities they commonly use.

Files (current):

- `FareCalculator.cpp`
  - Implements: `include/FareCalculator.h`
  - Responsibility: fare rules and computation (consumes distances from `data/connections.txt`).
  - Common headers used: `<cmath>`, `<numeric>`, `<string>`

- `Graph.cpp`
  - Implements: `include/Graph.h`
  - Responsibility: adjacency-list graph model, file loading (`data/stations.txt` and `data/connections.txt`), mutation APIs (`addStation`, `addEdge`) and `findShortestPath()` (Dijkstra).
  - Common headers used: `<unordered_map>`, `<vector>`, `<queue>`, `<limits>`, `<fstream>`, `<sstream>`

  - Additional algorithms: BFS, DFS, all-paths, cycle detection, connected components, minimum spanning tree (Prim's), station/edge removal. Uses STL containers and classic DSA patterns.

- `SearchEngine.cpp`
  - Implements: `include/SearchEngine.h`
  - Responsibility: station search (by name/line/zone), autocomplete suggestions, and helper filters used by the UI.
  - Common headers used: `<string>`, `<vector>`, `<algorithm>`, `<unordered_map>`

- `Station.cpp`
  - Implements: `include/Station.h`
  - Responsibility: `Station` methods (metadata accessors, `display()`, comparisons).
  - Common headers used: `<string>`, `<iostream>`

- `UI.cpp`
  - Implements: `include/UI.h`
  - Responsibility: console menus, input helpers, and small presentation helpers used by `main.cpp`.
  - Common headers used: `<iostream>`, `<string>`, `<vector>`

Notes:

- `main.cpp` resides at the project root and orchestrates the app flow (Admin/User login, main menu). It is compiled together with `src/*.cpp`.
- All `src/` files are C++ source files (`.cpp`) implementing the public interfaces declared in `include/` headers.
- The canonical data files are in `data/`:
  - `data/stations.txt` — station records (format: `StationName,Line,Zone[,lat,long]`).
  - `data/connections.txt` — connections and distances (format: `StationA,StationB,DistanceMeters`).

Guidance for contributors:

- When adding a new feature:
  1. Add `include/Whatever.h` (the public API).
  2. Implement `src/Whatever.cpp` using minimal includes and forward declarations where possible.
  3. Update the project build command if you add new `.cpp` files.

- Centralize file parsing in `Graph.cpp` or a dedicated loader if you plan to reuse parsing logic.

For exact data format and examples see [data/DATA_INFO.md](../data/DATA_INFO.md#L1).
