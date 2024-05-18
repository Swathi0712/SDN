#include <iostream>
#include <string>
using namespace std;

class Switch{
    private:
        string id;
        bool status;
    public:
        // Initialising Switch status and switch ID
        Switch(string switchID, bool switchStatus){
            id = switchID;
            status = switchStatus;
        }
        // Function to set the status of the switch
        void setStatus(bool newStatus){
            status = newStatus;
            cout << "New status:" << (status?"on":"off") <<endl;
        }
        // Function to get the status of the switch
        bool getStatus(){
            return status;
        }
        string getId(){
            return id;
        }
        // Function to display received control message
        void receiveControlMessage(const string message){
            cout << "switch" << id << "Received control message" << message << endl;
        }
        void logTraffic(string traffic){
            // Push to traffic logs

        }
        void showTrafficLogs(){
            // To print out the traffic logs from the log table
        }

};