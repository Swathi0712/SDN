#include <iostream>
#include <chrono>
#include <cstdio>
#include "../include/northboundinterface.h"
#include "../include/controller/controller.h"
#include "../include/switch/switch.h"
#include <winsock2.h>
#include <cstddef>
#include <windows.h>
// #include "../include/cpp-httplib-master/cpp-httplib-master/httplib.h"
// #include "../include/httplib.h"
// #include "../../../../mys/ucrt64/include/c++/13.2.0/httplib.h"
#include <ctime>
using namespace std;

void logEvent(string event){
    Logger::getInstance().log(event);
};

auto printTime(){
 // Declaring argument for time() 
    time_t tt; 
  
    // Declaring variable to store return value of 
    // localtime() 
    struct tm* ti; 
  
    // Applying time() 
    time(&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 

    // Starting log event
    auto t = asctime(ti);

    return t;
};

int main(){
   
    logEvent(printTime());
    logEvent("\n----------------------------------:Staring Log:------------------------------------\n");
    // cout << asctime(ti);

    // Create a controller instance
    Controller control;

    // Create North Bound Interface instance
    NorthBoundInterface nbi(control);

    // Create switch instances
    Switch switch1("switch1", true);
    Switch switch2("switch2", true);

    // Add switches to the controller
    control.addSwitch(switch1);
    control.addSwitch(switch2);

    // Send control messages
    // control.sendControlMessage("Activate");

    // Log traffic
    switch1.logTraffic("Packet1");
    switch1.logTraffic("Packet2");
    switch2.logTraffic("Packet3");
    
    // Show traffic logs
    switch1.showTrafficLogs();
    switch2.showTrafficLogs();

    // Simulate network events
    vector <RoutingTableEntry> update1 = {
        {"destination_A", {"switch2"}, 2},   // Update from switch1 to switch2
        {"destination_B", {"switch2"}, 2}
    };

    vector <RoutingTableEntry> update2 = {
        {"destination_C", {"switch1"}, 2},   // Update from switch1 to switch2
        {"destination_B", {"switch1"}, 2}
    };

    // Test to update routing table in the controller
    // control.updateRoutingTable(update1);

    // Simulate routing based on destination IP address
    string nxtHop = control.route("destination_B");
    // cout << "Next hop for destination B: " << nxtHop <<endl;
    logEvent("Next hop for destination B: " + nxtHop + "\n");

    // control.updateRoutingTable(update2);
    string nxt = control.route("destination_B");
    // cout << "Next hop for destination B: " << nxt <<endl;
    logEvent("Next hop for destination B: " + nxt +"\n");

    // Start periodic updates with an interval of 5 seconds
    control.startPeriodicUpdate();

    // Testing handling of network events
    control.handleNetworkEvent("Link Up");
    control.handleNetworkEvent("Link Down");

    // Handling Link failure
    // control.handleLinkFailure("switch1");

    // Creating a thread for starting the server
    thread nbiThread([&nbi](){nbi.start(8000);});
    nbiThread.detach();

    // Keep the program running to observe periodic updates
    this_thread::sleep_for(chrono::seconds(600));

    
    // Stopping log event
    logEvent(printTime());
    logEvent("\n----------------------------------:Stopping Log:------------------------------------\n");

    return 0;
}
