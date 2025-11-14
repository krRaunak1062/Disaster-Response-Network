//Disaster manager :
#ifndef DISASTER_MANAGER_H
#define DISASTER_MANAGER_H

#include "graph.h"
#include "priority_dispatch.h"
#include "team_disaster.h"

#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

class Team {
public:
    string name;
    TeamType type;
    int location;
    bool available;

    Team() {}
    Team(const string &n, int loc, TeamType tp = UNKNOWN_TEAM)
        : name(n), location(loc), type(tp), available(true) {}
};

class AssignLog {
public:
    int disasterNode;
    int disasterUrgency;
    DisasterType disasterType;
    string teamName;
    TeamType teamType;
    int teamStartNode;
    long long travelTime;
    vector<int> path;
    bool success;
    bool rerouted;
};

class DisasterManager {
public:
    Graph graph;
    Graph originalGraph;

    unordered_map<string, Team> teams;
    vector<string> teamOrder;

    priority_queue<Disaster, vector<Disaster>, DisasterComparator> disasterPQ;
    vector<AssignLog> logs;

    int totalHandled = 0;
    int blockedRoadsEncountered = 0;
    int unreachableZones = 0;
    vector<long long> responseTimes;

    ofstream logfile;

    DisasterManager() {}

    void initGraph(const Graph &g) {
        graph = g;
        originalGraph = g;
    }

    void openLog(const string &filename) {
        logfile.open(filename);
    }

    void closeLog() {
        if (logfile.is_open()) logfile.close();
    }

    void addTeam(const Team &t) {
        teams[t.name] = t;
        teamOrder.push_back(t.name);
    }

    void pushDisaster(const Disaster &d) {
        disasterPQ.push(d);
    }

    void blockEdge(int u, int v) {
        graph.blockEdge(u, v);
        blockedRoadsEncountered++;
        if (logfile.is_open())
            logfile << "[Warning] Road Blocked: " << u << "-" << v << "\n";
    }

    void simulate() {
        while (!disasterPQ.empty()) {
            Disaster d = disasterPQ.top();
            disasterPQ.pop();

            DisasterType dtype = d.type;

            if (logfile.is_open()) {
                logfile << "\nHandling Disaster ID " << d.id
                        << " | Node " << d.node
                        << " | Type " << getDisasterTypeName(dtype)
                        << " | Urgency " << d.urgency << "\n";
            }

            vector<TeamType> requiredTeams = getRequiredTeamsForDisaster(dtype);

            for (TeamType ttype : requiredTeams) {
                string chosen = "";
                int chosenLoc = -1;
                long long bestDist = 1e9;

                pair<vector<long long>, vector<int>> res = graph.dijkstra(d.node);
                vector<long long> dist = res.first;
                vector<int> parent = res.second;

                for (size_t idx = 0; idx < teamOrder.size(); idx++) {
                    string nm = teamOrder[idx];
                    Team &tm = teams[nm];
                    if (!tm.available) continue;
                    if (tm.type != ttype) continue;
                    if (dist[tm.location] < bestDist) {
                        bestDist = dist[tm.location];
                        chosen = tm.name;
                        chosenLoc = tm.location;
                    }
                }

                AssignLog al;
                al.disasterNode = d.node;
                al.disasterUrgency = d.urgency;
                al.disasterType = dtype;
                al.teamType = ttype;
                al.rerouted = false;

                if (chosen.empty() || bestDist >= 1e9) {
                    al.success = false;
                    unreachableZones++;
                    al.teamName = "NONE";
                    al.teamStartNode = -1;
                    al.travelTime = -1;
                    logs.push_back(al);

                    if (logfile.is_open())
                        logfile << "No available team of type " << getTeamTypeName(ttype)
                                << " found for this disaster.\n";
                    continue;
                }

                vector<int> path = Graph::reconstructPath(chosenLoc, d.node, parent);

                pair<vector<long long>, vector<int>> origRes = originalGraph.dijkstra(d.node);
                vector<int> origPath = Graph::reconstructPath(chosenLoc, d.node, origRes.second);

                if (path.size() != origPath.size()) al.rerouted = true;
                else {
                    for (size_t i = 0; i < path.size(); i++) {
                        if (i >= origPath.size() || path[i] != origPath[i]) {
                            al.rerouted = true;
                            break;
                        }
                    }
                }

                teams[chosen].available = false;
                al.teamName = chosen;
                al.teamStartNode = chosenLoc;
                al.path = path;
                al.travelTime = bestDist;
                al.success = true;
                logs.push_back(al);

                totalHandled++;
                responseTimes.push_back(bestDist);

                if (logfile.is_open()) {
                    logfile << "Team Assigned: " << chosen
                            << " (" << getTeamTypeName(ttype) << ")"
                            << " from " << chosenLoc << " | Path: ";
                    for (size_t i = 0; i < path.size(); i++) logfile << path[i] << " ";
                    logfile << " | Time: " << bestDist;
                    if (al.rerouted) logfile << " [REROUTED]";
                    logfile << "\n";
                }

                teams[chosen].available = true;
            }
        }
    }

    void writeReport(const string &path) {
        ofstream reportFile(path);
        reportFile << "=== DISASTER RESPONSE REPORT ===\n";
        reportFile << "Total disasters handled: " << totalHandled << "\n";
        reportFile << "Unreachable locations: " << unreachableZones << "\n";
        reportFile << "Blocked roads: " << blockedRoadsEncountered << "\n\n";

        double avg = 0.0;
        if (!responseTimes.empty()) {
            long long sum = 0;
            for (size_t i = 0; i < responseTimes.size(); i++) sum += responseTimes[i];
            avg = (double)sum / responseTimes.size();
        }

        reportFile << fixed << setprecision(2);
        reportFile << "Average response time: " << avg << "\n\n";

        reportFile << "Detailed Assignments:\n";
        for (size_t i = 0; i < logs.size(); i++) {
            const AssignLog &al = logs[i];
            reportFile << "[" << i+1 << "] Node " << al.disasterNode
               << " | Type: " << getDisasterTypeName(al.disasterType)
               << " | Team: " << al.teamName
               << " (" << getTeamTypeName(al.teamType) << ")";
            if (!al.success) reportFile << " -> UNREACHABLE\n";
            else {
                reportFile << " | Time: " << al.travelTime << " | Path: ";
                for (size_t p = 0; p < al.path.size(); p++) reportFile << al.path[p] << " ";
                if (al.rerouted) reportFile << "[REROUTED]";
                reportFile << "\n";
            }
        }
        reportFile.close();
    }
};

#endif
