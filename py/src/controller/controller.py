import sys
sys.path.append(r'D:\SDN\py\src\switch')
from switch import Switch
sys.path.append(r'D:\SDN\py\src')
from logger import logEvent
import math
import threading
import time

class RoutingTableEntry:
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
    __loadBalancerIndex = {}
    
    # public members
    running = False
    
    # Constructor
    def __init__(self):
        self.running = True
        
    # Add a new switch to the controller
    def addSwitch(self, swt):
        self.__switches.append(swt)
        # print("Switch added to controller")
        logEvent("Switch added to controller")

    # Remove switch from the controller
    def removeSwitch(self, swt):
        found = False
        for i in self.__switches:
            if i.getId()==swt.getId():
                self.__switches.remove(i)
                found = True
        if(found):
            # print("found")
            logEvent("Switch: " + swt.getId() + "removed")
        else:
            # print("not found")
            logEvent("Switch:" +swt.getId() + "not found")

    # method to send control message to all switches
    def sendControlMessage(self, message):
        for i in self.__switches:
            i.receiveControlMessage(message)
        # print(" Control message sent to all switches ")
        logEvent(" Control message sent to all switches ")
    
    # Method to handle network events
    def handleNetworkEvent(self, event):
        # print("Handled network event:")
        logEvent("Handled network event:")
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
    def route(self, dest):
        for entry in self.__routingTable:
            if(entry.destination == dest):
                hops = entry.nextHop
                
                # Checking if the key exists in the dictionary
                if dest not in self.__loadBalancerIndex:
                    self.__loadBalancerIndex[dest] = 0
                
                index = self.__loadBalancerIndex[dest]%len(hops)
                self.__loadBalancerIndex[dest]+=1
                return hops[index]
    
        # If destination not found in routing table return "drop packet" 
        return "DROP PACKET"

    # Method to handle link failures
    def handleLinkFailure(self, failedLink):
        for entry in self.__routingTable:
            hops = entry.nextHop
            # Removing the failed link (switch) from the list of available next hops(switches)
            hops.remove(failedLink)
            # If next hops for a particular destination is empty then make its cost infinity
            if len(hops)==0:
                entry.cost = math.inf
                
        self.sendTriggeredUpdate()
        
    # Method to send triggered updates to switches
    def sendTriggeredUpdate(self):
        for swt in self.__switches:
            swt.receiveControlMessage(self.createUpdateMessage())
        # print("Triggered updates sent to all switches")
        logEvent("Triggered updates sent to all switches")
        
    # Method to create update message
    def createUpdateMessage(self):
        message = "Update: "
        for entry in self.__routingTable:
            for hop in entry.nextHop:
                message += " " +  entry.destination + ","  + hop  + "," + str(entry.cost) +"\n"
        return message       
    
    # Method to send periodic updates to switches
    def sendPeriodicUpdate(self):
        for swt in self.__switches:
            swt.receiveControlMessage(self.createUpdateMessage())
        logEvent("Periodic updates...")
        
    # Method to start periodic updates
    def startPeriodicUpdates(self):
        def f():
            # print(self.running)
            while self.running:
                self.sendPeriodicUpdate()
                time.sleep(5)
        global t1 
        t1 = threading.Thread(target=f)
        # t1.daemon = True
        t1.start()

    
    # Method to stop periodic updates
    def stopPeriodicUpdates(self):
        self.running = False
        t1.join()
        logEvent("Periodic Updates stopped")
          