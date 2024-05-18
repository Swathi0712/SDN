#include <iostream>
#include <string>

using namespace std;

class Controller{
    public:
        // method to send control message to switches
        void sendControlMessage(string message){
            cout << " Control message sent:" << message << endl;
        }

};

// int main()
// {
//     // creating an instance
//     Controller controller; 
//     // send a control message
//     controller.sendControlMessage("message");

// }