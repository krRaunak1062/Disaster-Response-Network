#  Smart Disaster Management System  
A C++ Simulation using Graphs, Priority Queues, and Route Optimization.

## 👥 Team Members  
- *Raunak Kumar*  - B24CS1062
- *Priyanshu Khedekar*  - B24CS1059
- *Palthyavath Jalendhar*  - B24CS1051
- *Tushar Mina* - B24EE1081

---

#  1. Project Overview  

Disaster situations such as *fires, building collapses, transport accidents, and industrial accidents* require fast and optimized response from different emergency teams.  
Our project simulates a *smart city disaster management system* that:

- Models the city as a *weighted graph*
- Tracks *real-time disasters*, their urgency, and required teams
- Assigns the most optimal emergency team using *shortest path routing (Dijkstra)*
- Handles *road blocks* and automatically reroutes teams
- Maintains detailed *logs and reports*
- Uses *priority-based dispatching* to ensure high-urgency disasters are handled first

This is a real-life inspired application commonly used in:
- National Disaster Response systems  
- Smart Cities  
- Emergency Service Coordination  

---

#  2. Features  

### Core Functionalities
- Dynamic graph-based city navigation  
- Shortest path routing using *Dijkstra’s algorithm*  
- Automatic rerouting on *blocked roads*  
- Priority queue-based disaster scheduling  
- Team availability and assignment tracking  
- Final *analysis report* and *simulation logs*

###  Disaster Types Supported
- INDUSTRIAL_ACCIDENT  
- TRANSPORT_ACCIDENT  
- BUILDING_COLLAPSE  
- FIRE_ACCIDENT  

###  Team Types
- POLICE  
- AMBULANCE  
- FIRE_TRUCK  
- FOOD_TRUCK  
- NDRF_TEAM  

---

#  3. Data Structures & Algorithms Used  

| Component | Why Used? |
|---------- |-----------|
| *Graph (Adjacency List)*     | Efficient for sparse city networks, enables fast traversal |
| *Dijkstra’s Algorithm*       | Computes shortest travel time for teams |
| *Priority Queue (Max-Heap)*  | Ensures highest urgency disaster is always handled first |
| *BFS Reachability*           | Used to check if a blocked route still allows connectivity |
| **Hash Map (unordered_map)** | O(1) access to team information |
| *Vector*                     | Storing logs, paths, ordering of teams |

###  Design Choices
- *Weighted graph* chosen because roads have travel times.  
- *Dijkstra instead of BFS* because shortest weighted path is required.  
- *Priority Queue* ensures realistic urgency-based scheduling.  
- *Storing original graph* allows reroute detection (normal vs rerouted path).  

---

#  4. Repository Structure  
        SmartDisasterManagement/
        │
        ├── src/
        │ ├── main.cpp
        │ ├── graph.h
        │ ├── team_disaster.h
        │ ├── priority_dispatch.h
        │ ├── disaster_manager.h
        │
        ├── input/
        │ ├── city_map.txt
        │ ├── teams.txt
        │ ├── events.txt
        │
        ├── output/
        │ ├── report.txt
        │
        ├── logs/
        │ ├── simulation_log.txt
        │
        └── README.md


---

#  5. How the System Works (Flow)

1. *Load City Map*  
   Creates a graph of nodes (locations) and weighted edges (roads), from the inputs given on input folder/and its files. 

2. *Load Teams*  
   Each team has:
   - Name
   - Starting location
   - Team type  
   Stored in a hash map.

3. *Read Events*  
   Two types:
   - DISASTER location urgency type
   - BLOCK u v  

4. *Push disasters into priority queue*

5. *Simulation Loop*  
   For each disaster (highest urgency first):
   - Determine required teams  
   - Find nearest available team  
   - Compute shortest route using Dijkstra  
   - Detect rerouting if roads are blocked  
   - Log assignment  

6. *Generate:*
   - simulation_log.txt
   - report.txt

---

# 6. Easy Sample Input

Inside the input/ folder.

### *city_map.txt*  (sample input)
        7 8
        1 2 4
        1 3 6
        2 4 5
        3 4 2
        3 5 7
        4 6 3
        5 7 4
        6 7 6
    

### *teams.txt*       (sample input)
        T1 1 AMBULANCE
        T2 3 FIRE_TRUCK
        T3 5 POLICE
        T4 4 NDRF_TEAM
        T5 7 FOOD_TRUCK


### *events.txt*      (sample input)
        DISASTER 6 9 FIRE_ACCIDENT
        BLOCK 4 6
        DISASTER 7 8 BUILDING_COLLAPSE
        DISASTER 2 5 TRANSPORT_ACCIDENT


---

#  7. Sample Output (report.txt)
    === DISASTER RESPONSE REPORT ===
        Total disasters handled: 7
        Unreachable locations: 0
        Blocked roads: 1

        Average response time: 12.57

        Detailed Assignments:
        [1] Node 6 | Type: FIRE_ACCIDENT | Team: T2 (FIRE_TRUCK) | Time: 17 | Path: 3 5 7 6 [REROUTED]
        [2] Node 6 | Type: FIRE_ACCIDENT | Team: T1 (AMBULANCE) | Time: 23 | Path: 1 3 5 7 6 [REROUTED]
        [3] Node 7 | Type: BUILDING_COLLAPSE | Team: T4 (NDRF_TEAM) | Time: 13 | Path: 4 3 5 7 [REROUTED]
        [4] Node 7 | Type: BUILDING_COLLAPSE | Team: T1 (AMBULANCE) | Time: 17 | Path: 1 3 5 7 
        [5] Node 7 | Type: BUILDING_COLLAPSE | Team: T5 (FOOD_TRUCK) | Time: 0 | Path: 7 
        [6] Node 2 | Type: TRANSPORT_ACCIDENT | Team: T3 (POLICE) | Time: 14 | Path: 5 3 4 2 
        [7] Node 2 | Type: TRANSPORT_ACCIDENT | Team: T1 (AMBULANCE) | Time: 4 | Path: 1 2 

---
    # simulation.txt (sample output)
        [Warning] Road Blocked: 4-6
        Initial teams:
        T1 at node 1 (AMBULANCE)
        T2 at node 3 (FIRE_TRUCK)
        T3 at node 5 (POLICE)
        T4 at node 4 (NDRF_TEAM)
        T5 at node 7 (FOOD_TRUCK)
        Starting simulation...

        Handling Disaster ID 1 | Node 6 | Type FIRE_ACCIDENT | Urgency 9
        Team Assigned: T2 (FIRE_TRUCK) from 3 | Path: 3 5 7 6  | Time: 17 [REROUTED]
        Team Assigned: T1 (AMBULANCE) from 1 | Path: 1 3 5 7 6  | Time: 23 [REROUTED]

        Handling Disaster ID 2 | Node 7 | Type BUILDING_COLLAPSE | Urgency 8
        Team Assigned: T4 (NDRF_TEAM) from 4 | Path: 4 3 5 7  | Time: 13 [REROUTED]
        Team Assigned: T1 (AMBULANCE) from 1 | Path: 1 3 5 7  | Time: 17
        Team Assigned: T5 (FOOD_TRUCK) from 7 | Path: 7  | Time: 0

        Handling Disaster ID 3 | Node 2 | Type TRANSPORT_ACCIDENT | Urgency 5
        Team Assigned: T3 (POLICE) from 5 | Path: 5 3 4 2  | Time: 14
        Team Assigned: T1 (AMBULANCE) from 1 | Path: 1 2  | Time: 4

#  8. Compilation & Running

### *Compile*
        g++ main.cpp -o main

### *run*
        .\main 

### Output files generated:
Simulation finished successfully!
Log file: ../logs/simulation_log.txt
Report file: ../output/report.txt

# 9. Team Contributions 

### *Priyanshu Khedekar*  
- Implemented graph structure & Dijkstra algorithm  
- Integrated road block handling and rerouting logic  
- Designed input/output format and sample test cases  

### *Raunak Kumar*  
- Developed disaster priority system  
- Implemented Disaster and Team modules  
- Helped in simulation loop and testing  

### *Palthyavath Jalendhar*  
- Worked on disaster-team mapping logic  
- Wrote code for required team assignments  
- Helped create final report generation  

### *Tushar Mina*  
- Handled file I/O, directory management and main.cpp  
- Ensured reproducibility & repo structure  
- Created simulation logging system  

---

# 10. Future Improvements

- Add real-time GUI visualization  
- Add pathfinding algorithm for faster routing  
- Simulate live traffic and road congestion  
- Add machine learning for disaster prediction  

---

# 11. License
This project is for academic purposes. Usage allowed for learning and research.

---

# Thank You  
This project successfully demonstrates the usage of *advanced DSA concepts* in a real-world scenario.
