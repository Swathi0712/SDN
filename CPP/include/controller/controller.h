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
        // method to send control message to all switches
        void sendControlMessage(string message){
            // cout << " Control message sent:" << message << endl;
            for(auto& st:switches){
                st.receiveControlMessage(message);
            }
            cout << " Control message sent to all switches" << endl;
        }

        // Method to handle network events
        void handleNetworkEvent(string event){
            cout << "Handled network event:" << event << endl;
            // Perform actions based on network events
            if(event == "Link Up"){
                // Send a message to all switches to enable ports(Set status as Active)
                sendControlMessage("EnablePorts");
            }
            else if(event == "Link Down" ){
                // Send a message to all switches to disable ports(Set status as Inactive)
                sendControlMessage("DisablePorts");
            }
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

        // Method to perform routing based on destination IP Address
        string route(string destination){
            for(const auto& entry: routingTable){
                if(destination==entry.destination){
                    return entry.nextHop;
                }
            }
            // If destination not found in routing table return "drop packet" 
            return "DROP PACKET";
        }
};
