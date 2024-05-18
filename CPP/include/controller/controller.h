#include <iostream>
#include <string>

using namespace std;

class Controller{
    public:
        // method to send control message to switches
        void sendControlMessage(string message){
            cout << " Control message sent:" << message << endl;
        }

        void handleNetworkEvent(string event){
            cout << "Handling network event:" << event << endl;
        }

};

// int main()
// {
//     // creating an instance
//     Controller controller; 
//     // send a control message
//     controller.sendControlMessage("message");

// }