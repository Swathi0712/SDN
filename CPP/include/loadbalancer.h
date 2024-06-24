#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "../switch/switch.h"
using namespace std;

class LoadBalancer{
    private:
        // Map switch id to the current load
        unordered_map<string, int> switchLoad;
    
    public:
        LoadBalancer(){}

        // Add switch to the load balancer
        void addSwitchToL(Switch& swt){
            // Initialise load to 0
            switchLoad[swt.getId()] = 0;
        }

        // Remove a switch from the load balancer
        void removeSwitchFromL(Switch& swt){
            switchLoad.erase(swt.getId());
        }

        // Update load metrics for a switch
        
};

#endif