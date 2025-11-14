//priority_dispatch:
#ifndef PRIORITY_DISPATCH_H
#define PRIORITY_DISPATCH_H

#include <queue>
#include <vector>
#include <string>
#include "team_disaster.h"

using namespace std;

struct Disaster {
    int node;
    int urgency;
    int id;
    DisasterType type;

    Disaster(int location, int urgentLevel, int disasterId, DisasterType disasterType = UNKNOWN_DISASTER) {
        node = location;
        urgency = urgentLevel;
        id = disasterId;
        type = disasterType;
    }
};

struct DisasterComparator {
    bool operator()(const Disaster &a, const Disaster &b) {
        if(a.urgency != b.urgency) return a.urgency < b.urgency;
        return a.id > b.id;
    }
};

#endif
