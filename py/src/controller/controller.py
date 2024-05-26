import sys
sys.path.append(r'D:\SDN\py\src\switch')
from switch import Switch
import math

class RoutingTableEntry:
    # private members
    destination = ""
    nextHop = []       
    cost = math.inf
    
    def __init__(self, dest, nxtH, c):
        self.destination = dest
        self.nextHop = nxtH
        self.cost = c

# Create controller class
class Controller:
    # private members
    # List to store switch objects
    __switches = []
    __routingTable = [] 
    
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
            i.receiveControlMessage(message)
        print(" Control message sent to all switches ")
    
    # Method to handle network events
    def handleNetworkEvent(self, event):
        print("Handled network event:")
        # Perform actions based on network events
        if event == "Link Up":
            # Send a message to all switches to enable ports(Set status as Active)
            self.sendControlMessage("EnablePorts")
        elif event == "Link Down":
            # Send a message to all switches to disable ports(Set status as Inactive)
            self.sendControlMessage("DisablePorts")
            
    # Method to Update the routing table based on received routing updates from the switches
    def updateRoutingTable(self, updates):
        for entry in updates:
            it = None
            # Check if entry is already available on the routing table
            for idx, route in enumerate(self.__routingTable):
                if route.destination == entry.destination:
                    it = idx
                    break
           
            if(it!=None):
                if(entry.cost < self.__routingTable[it].cost):
                    self.__routingTable[it] = entry
                elif(entry.cost == self.__routingTable[it].cost):
                    self.__routingTable[it].nextHop.append(entry.nextHop[0])
            
            else:
                self.__routingTable.append(entry)
                
    # Method to perform routing based on destination IP Address
    
                
