#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <atomic>
#include <unordered_map>
#include "../switch/switch.h"
#include "../logger.h"
using namespace std;
// using namespace this_thread;

struct RoutingTableEntry{
    string destination;
    vector <string> nextHop;
    int cost;
};

class Controller{
    private:
        // Vector to store connected switches
        vector <Switch> switches;

        // Routing table maintained by the controller
        vector <RoutingTableEntry> routingTable;

        // Representing infinite cost
        const int INF = 1e9;

        atomic <bool> running;

        // Index for round robin load balancing
        unordered_map <string, int> loadBalancerIndex;

        // function to log events to the network log
        void logEvent(string event){
            Logger::getInstance().log(event);
        }
    
    public:
        // Constructor initialising the atomic flag
        Controller(){
            running = true;
        }

        // Destructor to stop periodic updates
        ~Controller(){
            stopPeriodicUpdates();
        }

        // Add a new switch to the controller
        void addSwitch(const Switch& swt){
            switches.push_back(swt);
            // cout << "Switch added to the conroller" << endl;
            logEvent("Switch added to the conroller\n");
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
                // cout << "found" <<endl;
                logEvent("Switch: " + swt.getId() + " removed\n");
            }
            else{
                // cout << "not found" << endl;
                logEvent("Switch: " + swt.getId() + " not found\n");
            }
        }

        // method to send control message to all switches
        void sendControlMessage(string message){
            for(auto& st:switches){
                st.receiveControlMessage(message);
            }
            // cout << " Control message sent to all switches" << endl;
            logEvent("Control message sent to all switches\n");
        }

        // Method to handle network events
        void handleNetworkEvent(string event){
            // cout << "Handled network event:" << event << endl;

            logEvent("Handled network event: " + event + "\n");

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

        // Method to Update the routing table based on received routing updates from the switches
        void updateRoutingTable(const vector<RoutingTableEntry> updates){
            for(const auto& entry: updates){
                // Check if entry is already available on the routing table
                auto it = find_if(routingTable.begin(), routingTable.end(), [&](const RoutingTableEntry& ety)
                {return ety.destination == entry.destination;});
                
                if(it!=routingTable.end()){
                    if(entry.cost < it->cost){
                        *it = entry;
                    }
                    else if(entry.cost == it->cost){
                        it->nextHop.push_back(entry.nextHop[0]);
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
                    auto& hops = entry.nextHop;
                    if(!hops.empty()){
                        int index = loadBalancerIndex[destination]%hops.size();
                        loadBalancerIndex[destination]++;
                        return hops[index];
                    }
                }
            }
            // If destination not found in routing table return "drop packet" 
            logEvent("DROP PACKET " + destination + "\n");
            return "DROP PACKET";
        }

        // Method to handle link failures
        void handleLinkFailure(string failedLink){
            for(auto& entry: routingTable){
                auto& hops = entry.nextHop;
                // Removing the failed link (switch) from the list of available next hops(switches)
                hops.erase(remove(hops.begin(), hops.end(), failedLink), hops.end());
                //  If next hops for a particular destination is empty then make its cost infinity
                if(hops.empty()){
                    entry.cost=INF;
                }
            }
            sendTriggeredUpdate();
        }

        // Method to send triggered updates to switches
        void sendTriggeredUpdate(){
            for(auto& swt:switches){
                swt.receiveControlMessage( createUpdateMessage());
            }
            // cout << "Triggered updates sent to all switches" << endl;
            logEvent("Triggered updates sent to all switches\n");
        }

        // Method to create update message
        string createUpdateMessage(){
            string message = "Update: ";
            for(auto& entry:routingTable){
                for(auto& hop: entry.nextHop){
                    message += " " + entry.destination + " ," + hop + " ," + to_string(entry.cost) + "\n";
                }
            }
            return message;
        }

        // Method to send periodic updates to switches
        void sendPeriodicUpdates(){
            for(auto& swt:switches){
                swt.receiveControlMessage( createUpdateMessage());
            }
            // cout << "Periodic update..." << endl;
            logEvent("Periodic updates sent...\n");
        }
        
        // Method to start periodic updates
        void startPeriodicUpdate(){
            cout<<"starting periodic updates...";
            auto f = [&](){
                while(running){
                    sendPeriodicUpdates();
                    this_thread::sleep_for(chrono::seconds(5));
                }
            };
            std::thread(f).detach();
            
            
        }

        // Method to stop periodic updates
        void stopPeriodicUpdates(){
            running =  false;
        } 
};
