#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../switch/switch.h"

using namespace std;

class Controller{
    private:
        vector <Switch> switches;
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
};
