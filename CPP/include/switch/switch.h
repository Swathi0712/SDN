#ifndef SWITCH_H 
#define SWITCH_H   

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Switch {
    private:
        string id;
        bool status;
        vector<string> trafficLogs;

    public:
        // Initialising Switch status and switch ID
        Switch(string switchID, bool switchStatus):id(switchID), status(switchStatus)
        {

        }

        // Function to set the status of the switch
        void setStatus(bool newStatus)
        {
            status = newStatus;
            cout << "New status:" << (status ? "on" : "off") << endl;
        }

        // Function to get the status of the switch
        bool getStatus()
        {
            return status;
        }
        string getId()
        {
            return id;
        }

        // Function to display received control message
        void receiveControlMessage(const string message)
        {
            cout << "Switch: " << id << " Received control message: " << message << endl;
        }

        void logTraffic(string traffic)
        {
            // Push to traffic logs
            trafficLogs.push_back(traffic);
            cout << "Switch: " << id << " Traffic logged: " << traffic << endl;
        }

        void showTrafficLogs()
        {
            // To print out the traffic logs from the log table
            cout << "Traffic log for switch: " << id << endl;
            for (auto log : trafficLogs)
            {
                cout << log << endl;
            }
        }
    };

#endif