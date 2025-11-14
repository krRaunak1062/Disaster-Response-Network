//main:
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "graph.h"
#include "priority_dispatch.h"
#include "team_disaster.h"
#include "disaster_manager.h"

using namespace std;

// Function to create directories
void createDirectories() {
    #ifdef _WIN32
        system("mkdir ..\\input 2>nul");
        system("mkdir ..\\output 2>nul");
        system("mkdir ..\\logs 2>nul");
    #else
        system("mkdir -p ../input ../output ../logs");
    #endif
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Create directories first
    createDirectories();

    // Paths - FIXED: Use relative paths from current directory
    string cityMapFile = "../input/city_map.txt";
    string teamsFile = "../input/teams.txt";
    string eventsFile = "../input/events.txt";
    string logFile = "../logs/simulation_log.txt";
    string reportFile = "../output/report.txt";


    // Prepare manager
    DisasterManager manager;
    manager.openLog(logFile);

    // Read city map
    ifstream fcity(cityMapFile);
    if (!fcity.is_open()) {
        cerr << "Failed to open " << cityMapFile << "\n";
        cerr << "Creating sample input files...\n";
        
        // Create sample city_map.txt
        ofstream createCity(cityMapFile);
        createCity << "8 10\n";
        createCity << "1 2 5\n1 3 10\n2 4 7\n2 5 3\n3 6 6\n";
        createCity << "4 5 2\n5 7 6\n6 7 4\n4 6 5\n7 8 8\n";
        createCity.close();
        
        // Create sample teams.txt
        ofstream createTeams(teamsFile);
        createTeams << "T1 1 AMBULANCE\nT2 4 FIRE_TRUCK\nT3 3 POLICE\n";
        createTeams.close();
        
        // Create sample events.txt
        ofstream createEvents(eventsFile);
        createEvents << "DISASTER 7 9 FIRE_ACCIDENT\n";
        createEvents << "DISASTER 8 5 BUILDING_COLLAPSE\n";
        createEvents << "BLOCK 5 7\n";
        createEvents << "DISASTER 2 7 TRANSPORT_ACCIDENT\n";
        createEvents << "DISASTER 6 8 INDUSTRIAL_ACCIDENT\n";
        createEvents.close();
        
        cerr << "Sample files created. Please run the program again.\n";
        return 1;
    }

    int N, M;
    fcity >> N >> M;
    Graph g(N);
    for(int i = 0; i < M; i++) {
        int u, v, w;
        fcity >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    manager.initGraph(g);
    fcity.close();

    // Read teams
    ifstream fteams(teamsFile);
    if (!fteams.is_open()) {
        cerr << "Failed to open " << teamsFile << "\n";
        return 1;
    }
    string tname, ttypeStr;
    int tnode;
    while (fteams >> tname >> tnode >> ttypeStr) {
        TeamType tt = getTeamTypeFromName(ttypeStr);
        manager.addTeam(Team(tname, tnode, tt));
    }
    fteams.close();

    // Read events
    ifstream fevents(eventsFile);
    if (!fevents.is_open()) {
        cerr << "Failed to open " << eventsFile << "\n";
        return 1;
    }
    string line;
    int disasterCounter = 0;
    while(getline(fevents, line)) {
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        string type;
        ss >> type;
        if (type == "DISASTER") {
            int node, urgency;
            string dtypeStr;
            int id = ++disasterCounter;
            ss >> node >> urgency;
            if (ss >> dtypeStr) {
                DisasterType dt = getDisasterTypeFromName(dtypeStr);
                manager.pushDisaster(Disaster(node, urgency, id, dt));
            } else {
                manager.pushDisaster(Disaster(node, urgency, id, UNKNOWN_DISASTER));
            }
        } else if (type == "BLOCK") {
            int u, v;
            ss >> u >> v;
            manager.blockEdge(u, v);
        }
    }
    fevents.close();

    // Log initial state
    if (manager.logfile.is_open()) {
        manager.logfile << "Initial teams:\n";
        for (auto &tn : manager.teamOrder) {
            const Team &t = manager.teams[tn];
            manager.logfile << t.name << " at node " << t.location 
                           << " (" << getTeamTypeName(t.type) << ")\n";
        }
        manager.logfile << "Starting simulation...\n";
    }

    // Run simulation
    manager.simulate();

    // Write report
    manager.writeReport(reportFile);

    // Close log
    manager.closeLog();

    cout << "Simulation finished successfully!\n";
    cout << "Log file: " << logFile << "\n";
    cout << "Report file: " << reportFile << "\n";
    
    return 0;
}
