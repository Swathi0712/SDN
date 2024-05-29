import sys
# sys.path.append(r'D:\SDN\py\src\controller')
# from controller import controller
sys.path.append(r'D:\SDN\py\src')
from logger import logEvent

class Switch:
    # private members
    __id = None
    __status = None
    __trafficLogs = []

    # public members
    # initialising switch Id and status
    def __init__(self, switchId , switchStatus):
        self.__id = switchId
        self.__status = switchStatus

    # Function to set the status of the switch
    def setStatus(self, newStatus):
        self.__status = newStatus
        # print("New status: ", "on" if self.__status == True else "Off")
        logEvent("New Status:" + f"{"on" if self.__status == True else "Off"}" )
    
    # Function to get the status of the switch
    def getStatus(self):
        return self.__status
    
    def getId(self):
        return self.__id
    
    # Function to display received control message
    def receiveControlMessage(self, message):
        logEvent("Switch: " + self.__id + "Received control message" + message)

    # Push to traffic logs
    def logTraffic(self, traffic):
        self.__trafficLogs.append(traffic)
        logEvent("Switch: " +  self.__id + "Traffic logged " + traffic)
    
    # To print out the traffic logs from the log table
    def showTrafficLogs(self):
        logEvent("Traffic log for switch: " + self.__id)
        for log in self.__trafficLogs:
            logEvent(log)
    