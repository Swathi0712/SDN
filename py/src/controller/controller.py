import sys
sys.path.append(r'D:\SDN\py\src\switch')
from switch import Switch

# Create controller class
class Controller:
    # private members
    # List to store switch objects
    __switches = []

    # public members
    # Add a new switch to the controller
    def addSwitch(self, swt):
        self.__switches.append(swt)
        print("Switch added to controller")
    
    # Remove switch from the controller
    def removeSwitch(self, swt):
        found = False
        for i in self.__switches:
            if i.getId()==swt.getId():
                self.__switches.remove(i)
                found = True
        if(found):
            print("found")
        else:
            print("not found")

    # method to send control message to all switches
    def sendControlMessage(self, message):
        for i in self.__switches:
            i.receivedControlMessage(message)
        print(" Control message sent to all switches ")
    
    # Method to handle network events