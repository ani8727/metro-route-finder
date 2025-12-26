# Data Files for Metro Route Finder

This file documents the data files stored in the `data/` folder and their formats.

## files

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
2. Edit `connections.txt` to add or modify connections.
3. Start the app and select **Admin → Reload Data** to reload from files (or restart the app).

---