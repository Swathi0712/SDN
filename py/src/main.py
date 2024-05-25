import sys
sys.path.append(r'D:\SDN\py\src\switch')
from switch import Switch
sys.path.append(r'D:\SDN\py\src\controller')
from controller import Controller

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



