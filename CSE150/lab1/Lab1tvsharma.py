#!/usr/bin/python
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.link import TCLink

class MyTopology(Topo):
  """
  A basic topology
  """
  def __init__(self):
    Topo.__init__(self)
    # Set Up Topology Here

    switch1 = self.addSwitch('s1')
    switch2 = self.addSwitch('s2')
    switch3 = self.addSwitch('s3')
    switch4 = self.addSwitch('s4')

    fridge = self.addHost('fridge', ip = '10.0.0.4/24')
    desktop = self.addHost('desktop', ip = '10.0.0.1/24')
    siri = self.addHost('siri', ip = '10.0.0.6/24')
    server = self.addHost('server',ip = '10.0.0.2/24')
    smartTV = self.addHost('smartTV',ip = '10.0.0.3/24')
    alexa = self.addHost('alexa',ip = '10.0.0.5/24' )


    self.addLink(siri, switch3, delay = "30ms")
    self.addLink(alexa, switch3, delay = "30ms")
    self.addLink(switch2, switch3, delay = "30ms")
    self.addLink(desktop, switch2, delay = "30ms")
    self.addLink(switch2, switch4, delay = "30ms ")
    self.addLink(switch2, switch1, delay = "30ms")
    self.addLink(server, switch4, delay = "30ms")
    self.addLink(smartTV, switch1, delay = "30ms")
    self.addLink(fridge, switch1, delay = "30ms")


if __name__ == '__main__':
  """
  If this script is run as an executable (by chmod +x), this is
  what it will do
  """
  topo = MyTopology() ## Creates the topology
  #net = Mininet( topo=topo ) ## Loads the topology
  net = Mininet(topo=topo, link=TCLink) ## Loads the topology
  net.start() ## Starts Mininet
  # Commands here will run on the simulated topology
  CLI(net)
  net.stop() ## Stops Mininet