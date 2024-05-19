#include <iostream>
#include "../include/controller/controller.h"
#include "../include/switch/switch.h"
using namespace std;

int main(){
    // Create a controller instance
    Controller control;

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
    return 0;
}
