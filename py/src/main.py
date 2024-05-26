import sys
sys.path.insert(0, 'D:\\SDN\\py\\src\\switch')
from switch import Switch
sys.path.insert(0,'D:\\SDN\\py\\src\\controller')
# import controller
# from typing import TYPE_CHECKING 
# if TYPE_CHECKING:
from controller import Controller, RoutingTableEntry as rte


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

control.updateRoutingTable(update1)
control.updateRoutingTable(update2)





