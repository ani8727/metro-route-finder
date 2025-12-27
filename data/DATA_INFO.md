

# About the `data/` Folder

The `data/` folder contains all the data files used by the Metro Route Finder application. These files define the stations, connections, and any additional information needed for the app to function.

## Who should work on this folder?

- Anyone who wants to update, extend, or correct the metro network data (e.g., adding new stations, connections, or features).
- Contributors who want to add new data sources (like facilities, schedules, etc.) or improve data quality.
- Users who want to customize the metro map for their own city or use case.

## How to contribute or extend

- Follow the file formats described below for each data file.
- Document any new files or changes in this DATA_INFO.md for clarity.
- Test your changes by running the app and using the reload or restart feature.

# Data Files for Metro Route Finder

This file documents the data files stored in the `data/` folder, their formats, how to extend them, and why this approach is used. This is for all project users and contributors.


## Files in this folder

- `stations.txt` — list of stations
- `connections.txt` — list of undirected weighted connections between stations

---

## `stations.txt` format

CSV-like records, one station per line. Fields:

1. Station Name (string)
2. Metro Line (string) — e.g., Blue Line, Red Line
3. Zone (integer)
4. Latitude (decimal degrees) — optional
5. Longitude (decimal degrees) — optional

Example:
```
Rajiv Chowk,Blue Line,2,28.6329,77.2197
Yamuna Bank,Blue Line,2,28.6159,77.2494
```

Notes:
- Commas are used as separators. If your station names contain commas, wrap the name in quotes.
- Zone is used by fare calculator and network filters.

---

## `connections.txt` format

CSV-like records, one connection per line. Fields:

1. Station A (string)
2. Station B (string)
3. Distance in kilometers (decimal)

Example:
```
Rajiv Chowk,Yamuna Bank,2.5
Rajiv Chowk,Connaught Place,0.9
```

Notes:
- Connections are treated as undirected edges.
- Distances are used for shortest-path calculations (edge weights).

---


## Adding or updating data

1. Edit `stations.txt` to add or modify stations.
	- To add a new station, add a new line with the correct format.
	- Example: `New Station,Green Line,3,28.6000,77.2000`
2. Edit `connections.txt` to add or modify connections.
	- To connect two stations, add a new line with both station names and the distance.
	- Example: `New Station,Rajiv Chowk,3.2`
3. Start the app and select **Admin → Reload Data** to reload from files (or restart the app).

## Future Data Extensions (What to include next)

- To add new data sources (e.g., station facilities, accessibility, schedules), create a new file (e.g., `facilities.txt`) and update the code to load and use it.
- To add new station properties (e.g., opening hours), add new columns to `stations.txt` and update the Station class and file loader.
- For new types of connections (e.g., express lines, transfer times), add new columns or files and update the Graph logic.
- Always document new data files and formats in this file for clarity.


## Why use plain text/CSV files?

- **Simplicity:** Easy to read, edit, and version control.
- **Portability:** Works on any OS, no special software needed.
- **Extensibility:** Easy to add new columns or files as the project grows.
- **Transparency:** Anyone (even non-programmers) can view and update the data.

If the project grows, you can migrate to a database or more complex format, but this approach is ideal for learning, testing, and collaboration.

---