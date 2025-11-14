//team_disaster:
#ifndef TEAM_DISASTER_H
#define TEAM_DISASTER_H

#include <string>
#include <vector>
using namespace std;

// Different types of teams we can have
enum TeamType {
    POLICE,         // Police team
    AMBULANCE,      // Ambulance team  
    FIRE_TRUCK,     // Fire truck team
    FOOD_TRUCK,     // Food supply team
    NDRF_TEAM,      // National Disaster Response Force team
    UNKNOWN_TEAM    // If we don't know the type
};

// Different types of disasters that can happen
enum DisasterType {
    INDUSTRIAL_ACCIDENT,    // Factory accident
    TRANSPORT_ACCIDENT,     // Car or train accident
    BUILDING_COLLAPSE,      // Building falls down
    FIRE_ACCIDENT,          // Fire emergency
    UNKNOWN_DISASTER        // If we don't know the type
};

// Function to convert team type to string name
string getTeamTypeName(TeamType team) {
    switch(team) {
        case POLICE: return "POLICE";
        case AMBULANCE: return "AMBULANCE";
        case FIRE_TRUCK: return "FIRE_TRUCK";
        case FOOD_TRUCK: return "FOOD_TRUCK";
        case NDRF_TEAM: return "NDRF_TEAM";
        default: return "UNKNOWN_TEAM";
    }
}

// Function to convert disaster type to string name
string getDisasterTypeName(DisasterType disaster) {
    switch(disaster) {
        case INDUSTRIAL_ACCIDENT: return "INDUSTRIAL_ACCIDENT";
        case TRANSPORT_ACCIDENT: return "TRANSPORT_ACCIDENT";
        case BUILDING_COLLAPSE: return "BUILDING_COLLAPSE";
        case FIRE_ACCIDENT: return "FIRE_ACCIDENT";
        default: return "UNKNOWN_DISASTER";
    }
}

// Function to convert string to team type
TeamType getTeamTypeFromName(const string &name) {
    if (name == "POLICE") return POLICE;
    if (name == "AMBULANCE") return AMBULANCE;
    if (name == "FIRE_TRUCK") return FIRE_TRUCK;
    if (name == "FOOD_TRUCK") return FOOD_TRUCK;
    if (name == "NDRF_TEAM") return NDRF_TEAM;
    return UNKNOWN_TEAM;
}

// Function to convert string to disaster type
DisasterType getDisasterTypeFromName(const string &name) {
    if (name == "INDUSTRIAL_ACCIDENT") return INDUSTRIAL_ACCIDENT;
    if (name == "TRANSPORT_ACCIDENT") return TRANSPORT_ACCIDENT;
    if (name == "BUILDING_COLLAPSE") return BUILDING_COLLAPSE;
    if (name == "FIRE_ACCIDENT") return FIRE_ACCIDENT;
    return UNKNOWN_DISASTER;
}

// Function to tell which teams are needed for each disaster type
vector<TeamType> getRequiredTeamsForDisaster(DisasterType disaster) {
    vector<TeamType> neededTeams;
    
    switch(disaster) {
        case INDUSTRIAL_ACCIDENT:
            neededTeams.push_back(NDRF_TEAM);
            neededTeams.push_back(FIRE_TRUCK);
            neededTeams.push_back(AMBULANCE);
            break;
            
        case TRANSPORT_ACCIDENT:
            neededTeams.push_back(POLICE);
            neededTeams.push_back(AMBULANCE);
            break;
            
        case BUILDING_COLLAPSE:
            neededTeams.push_back(NDRF_TEAM);
            neededTeams.push_back(AMBULANCE);
            neededTeams.push_back(FOOD_TRUCK);
            break;
            
        case FIRE_ACCIDENT:
            neededTeams.push_back(FIRE_TRUCK);
            neededTeams.push_back(AMBULANCE);
            break;
            
        default:
            neededTeams.push_back(AMBULANCE); // Default team
    }
    
    return neededTeams;
}

#endif
