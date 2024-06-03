#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <cstddef>

// Undefine the 'byte' macro from Windows headers
#undef byte
#include "../include/controller/controller.h"
#include "../include/northboundInterface.h"
#include "../include/switch/switch.h"
#include <ctime>
#include <thread>
#include <chrono>
// #include <northboundInterface.h>
// #include "httplib.h"
using namespace std;
using namespace std::this_thread;


void logEvent(string event){
    Logger::getInstance().log(event);
};

string printTime(){
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
    NorthboundInterface nbi;

    // Create switch instances
    Switch switch1("switch1", true);
    Switch switch2("switch2", true);

    // Add switches to the controller
    control.addSwitch(switch1);
    control.addSwitch(switch2);

    // Send control messages
    control.sendControlMessage("Activate");

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
    control.updateRoutingTable(update1);

    // Simulate routing based on destination IP address
    string nxtHop = control.route("destination_B");
    // cout << "Next hop for destination B: " << nxtHop <<endl;
    logEvent("Next hop for destination B: " + nxtHop + "\n");

    control.updateRoutingTable(update2);
    string nxt = control.route("destination_B");
    // cout << "Next hop for destination B: " << nxt <<endl;
    logEvent("Next hop for destination B: " + nxt +"\n");
    
    control.startPeriodicUpdate();
    
    // Testing handling of network events
    control.handleNetworkEvent("Link Up");
    control.handleNetworkEvent("Link Down");

    // Handling Link failure
    control.handleLinkFailure("switch1"); 

    // Start periodic updates with an interval of 5 seconds
    cout<<"starting the server..."<<endl;
    // NorthboundInterface nbi;
    std::thread nbiThread([&nbi]() {
        nbi.start(8080); // Start the northbound interface on port 8080
    });
    nbiThread.detach();
    // Keep the program running to observe periodic updates

    this_thread::sleep_for(chrono::seconds(30));
    
    // Stopping log event
    logEvent(printTime());
    logEvent("\n----------------------------------:Stopping Log:------------------------------------\n");

    //     // Clean up Winsock
    // WSACleanup();

    return 0;
}
