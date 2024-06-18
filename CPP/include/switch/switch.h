#ifndef SWITCH_H 
#define SWITCH_H   

#include <iostream>
#include <string>
#include <vector>
#include "../logger.h"
using namespace std;

class Switch {
    private:
        string id;
        bool status;
        string ip;
        vector<string> trafficLogs;
        void logEvent(string event){
            Logger::getInstance().log(event);
        }

    public:
        // Initialising Switch status and switch ID
        Switch(string switchID, bool switchStatus):id(switchID), status(switchStatus)
        {

        }

        // Allocate IP to a switch
        void setIP(string i_p){
            ip = i_p;
        }

        string getIP(){
            return ip;
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
            // cout << "Switch: " << id << " Received control message:\n " << message << endl;
            logEvent("Switch: " + id + " Received control message:\n " + message + "\n");
        }

        void logTraffic(string traffic)
        {
            // Push to traffic logs
            trafficLogs.push_back(traffic);
            // cout << "Switch: " << id << " Traffic logged: " << traffic << endl;
            logEvent("Switch: " + id + " Traffic logged: " + traffic + "\n");
        }

        void showTrafficLogs()
        {
            // To print out the traffic logs from the log table
            // cout << "Traffic log for switch: " << id << endl;
            logEvent("Traffic log for switch: " + id + "\n");
            for (auto log : trafficLogs)
            {
                // cout << log << endl;
                logEvent(log + "\n");
            }
        }
    };

#endif