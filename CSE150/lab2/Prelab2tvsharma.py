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

    fridge = self.addHost('fridge')
    desktop = self.addHost('desktop')
    siri = self.addHost('siri')
    server = self.addHost('server')
    smartTV = self.addHost('smartTV')
    alexa = self.addHost('alexa')


    self.addLink(siri, switch3)
    self.addLink(alexa, switch3, bw=5)
    self.addLink(switch2, switch3)
    self.addLink(desktop, switch2)
    self.addLink(switch2, switch4)
    self.addLink(switch2, switch1)
    self.addLink(server, switch4)
    self.addLink(smartTV, switch1)
    self.addLink(fridge, switch1)


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