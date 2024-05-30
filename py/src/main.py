import sys
import time
import datetime
sys.path.insert(0, 'D:\\SDN\\py\\src\\switch')
from switch import Switch
sys.path.insert(0,'D:\\SDN\\py\\src\\controller')
from controller import Controller, RoutingTableEntry as rte
sys.path.insert(0,'D:\\SDN\\py\\src\\northboundinterface.py')
from northboundinterface import NorthBoundInterface
from logger import logEvent
# import controller
# from typing import TYPE_CHECKING 
# if TYPE_CHECKING:

# using now() to get current time
current_time = datetime.datetime.now()
logEvent(current_time)
logEvent("------------------------------------Starting log event----------------------------------------")

# Create a controller instance
control = Controller()

# Create switch instances
switch1 = Switch("switch1", True)
switch2 = Switch("switch2", True)

# Add switch to the controller
control.addSwitch(switch1)
control.addSwitch(switch2)

# Send control message to all switches
control.sendControlMessage("Activate")

# Log traffic
switch1.logTraffic("Packet1")
switch1.logTraffic("Packet2")
switch2.logTraffic("Packet3")

# Show traffic logs
switch1.showTrafficLogs()
switch2.showTrafficLogs()

# Simulate network events
e1 = rte("destination_A", ["switch2"], 2)
e2 = rte("destination_B", ["switch2"], 2)
update1 = [e1, e2]

e3 = rte("destination_A", ["switch1"], 2)
e4 = rte("destination_B", ["switch1"], 2)
update2 = [e3, e4]

# Test to update routing table in the controller
control.updateRoutingTable(update1)
control.updateRoutingTable(update2)

# Simulate routing based on destination IP address
nxtHop = control.route("destination_B")
logEvent("Next hop for destination B: " + nxtHop)

# Testing handling of network events
control.handleNetworkEvent("Link Up")
control.handleNetworkEvent("Link Down")

# Handling Link failure
control.handleLinkFailure("switch2")

# Start periodic updates with an interval of 5 seconds
control.startPeriodicUpdates()

# try:
#     while(True):
#         time.sleep(5)
# except KeyboardInterrupt:
#     control.running = False

time.sleep(15)
control.stopPeriodicUpdates()

logEvent("----------------------------------Stopping log event---------------------------------")
# using now() to get current time
current_time = datetime.datetime.now()
logEvent(current_time)
