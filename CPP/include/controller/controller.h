#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../switch/switch.h"

using namespace std;

struct RoutingTableEntry{
    string destination;
    string nextHop;
    int cost;
};

class Controller{
    private:
        // Vector to store connected switches
        vector <Switch> switches;
        // Routing table maintained by the controller
        vector <RoutingTableEntry> routingTable;
    
    public:
        // method to send control message to switches
        void sendControlMessage(string message){
            cout << " Control message sent:" << message << endl;
        }

        void handleNetworkEvent(string event){
            cout << "Handling network event:" << event << endl;
        }

        // Add a new switch to the controller
        void addSwitch(const Switch& swt){
            switches.push_back(swt);
            cout << "Switch added to the conroller" << endl;
        }

        // Remove switch from the controller
        void removeSwitch(Switch& swt){
            bool found = false;
            for(auto it = switches.begin(); it != switches.end();it++){
                if((*it).getId()==swt.getId()){
                    switches.erase(it);
                    found = true;
                }

            }
            if(found){
                cout << "found" <<endl;
            }
            else{
                cout << "not found" << endl;
            }
        }

        // Method to Update the routing table based on received routing updates from the switches
        void updateRoutingTable(const vector<RoutingTableEntry> updates){
            for(const auto& entry: updates){
                // Check if entry is already available on the routing table
                auto it = find_if(routingTable.begin(), routingTable.end(), 
                [&](const RoutingTableEntry& ety){return ety.destination == entry.destination;});
                
                if(it!=routingTable.end()){
                    if(entry.cost < it->cost){
                        *it = entry;
                    }
                }
                else{
                    routingTable.push_back(entry);
                }
            }
        }
};
