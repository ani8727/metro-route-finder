# About the `include/` folder

This folder contains public header files (.h) that declare the interfaces used across the project. Below is a concise description of each header present in this project and what it exposes.

Headers (short):

- `include/Station.h`: Declares the `Station` class/struct (name, line, zone, coordinates) and public helper declarations (display, comparisons).
- `include/Graph.h`: Declares the `Graph` interface (add/remove stations and edges, load/save, `findShortestPath()` signature, helpers for printing and iterating the network).
- `include/SearchEngine.h`: Declares search APIs used by the UI (`searchByName`, `searchByLine`, `searchByZone`, `getAutocompleteSuggestions`).
- `include/FareCalculator.h`: Declares the `FareCalculator` API used to compute fares given path distance and zones.
- `include/UI.h`: Declares UI helper functions used by `main.cpp` and the interactive menus.

Header best-practices used here:

- Use include guards or `#pragma once` in each header.
- Keep headers minimal: prefer forward declarations when possible to reduce coupling and compile times.
- Do not use `using namespace` in headers; keep the public API names explicit.

Dependencies / Libraries:

- Headers only declare interfaces — implementations in `src/` include standard library headers like `<string>`, `<vector>`, `<unordered_map>`, `<queue>`, etc.
- No third-party external libraries are required.

How to extend:

1. Add `include/NewThing.h` with a minimal public API and include guards.
2. Implement `src/NewThing.cpp` and include only the headers it needs.
3. Update the build command if you add new source files.

---

## Built-in (Standard Library) — what the headers relate to

The header files in `include/` declare interfaces that are implemented in `src/`. The implementations typically use these standard-library facilities:

- Containers & strings: `<vector>`, `<string>`, `<map>`, `<unordered_map>`, `<unordered_set>` — used for station lists and adjacency structures.
- Algorithms & utilities: `<algorithm>`, `<utility>`, `<functional>` — for sorting, pair utilities and function objects.
- I/O & parsing: `<iostream>`, `<fstream>`, `<sstream>` — used by implementations to read `data/` files and print output.
- Concurrency & safety: The project does not use threading; headers avoid threading declarations. If extended, prefer `<mutex>` and other concurrency utilities.
- Priority structures: `<queue>` / `<priority_queue>` — used in algorithm implementations (not in headers themselves, but referenced by the API semantics).

These are "built-in" features — they keep headers stable and portable while allowing implementations to use efficient data structures.

---

## Advanced / rarely-used notes (for header design)

These are small, optional techniques you may apply in headers when the design needs them. Use sparingly:

- Forward declarations: reduce compile-time dependencies — declare `class Graph;` instead of including full headers when only pointers or references are used.
- `std::optional` in APIs: for functions that may not return a value (e.g., `findStation()`), prefer `std::optional<T>` instead of sentinel values.
- Custom comparator types: when declaring comparator types needed for containers exposed via the API, define them in headers so callers can use the same ordering.
- Inline helpers: small, performance-critical helpers can be declared `inline` in headers to avoid ODR issues while enabling optimization.

These are moderately advanced: apply them when you have specific needs (API clarity, compile-time performance, or small-API ergonomics).

---

## User-created lines & stations (short note)

While headers declare the public API, adding user data (lines, stations) is handled by the Graph and data-loading implementations. Quick notes for users who want to add data:

- Edit `data/stations.txt` and `data/connections.txt` to add persistent records.
- Station format: `StationName,Line,Zone[,lat,long]` (example: `Central Station,Blue,1,28.6139,77.2090`).
- Connection format: `StationA,StationB,DistanceMeters` (example: `Central Station,North Park,850`).
- After editing, restart the app or use Admin → Reload data to rebuild the in-memory graph.

Keep names consistent between stations and connections; headers define the API that the implementations use to parse and load these files.


