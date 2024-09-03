#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.node import RemoteController

class final_topo(Topo):
  def build(self):

    # laptop1 = self.addHost('Laptop1',mac="00:00:00:00:00:10", ip='10.0.0.10/24',defaultRoute="Laptop1-eth1")

    # switch1 = self.addSwitch('s1')

    # self.addLink(laptop1, switch1, port1=1, port2=2)
   
    #Switches and links
    coreswitch =  self.addSwitch('s0')
    switch1 = self.addSwitch('s1')
    switch2 = self.addSwitch('s2')
    switch3 = self.addSwitch('s3')
    switch4 = self.addSwitch('s4')
    self.addLink(switch1,coreswitch, port1=12, port2=12)
    self.addLink(switch2,coreswitch, port1=13, port2=13)
    self.addLink(switch3,coreswitch, port1=14, port2=14)
    self.addLink(switch4,coreswitch, port1=15, port2=15)

   
    #Sales Department with links
    laptop1 = self.addHost('Laptop1', mac="00:00:00:00:00:08", ip='200.20.2.8/24', defaultRoute="Laptop1-eth1")
    printer = self.addHost('Printer', mac="00:00:00:00:00:10", ip='200.20.2.10/24', defaultRoute="Printer-eth1")
    laptop2 = self.addHost('Laptop2', mac="00:00:00:00:00:09", ip='200.20.2.9/24', defaultRoute="Laptop2-eth1")
    self.addLink(laptop1,switch4, port1=1, port2=2)
    self.addLink(printer,switch4, port1=1, port2=4)
    self.addLink(laptop2,switch4,port1=1, port2=3)

    #OT Department with links
    workstation1 = self.addHost('ws1', mac="00:00:00:00:00:04", ip='200.20.3.4/24', defaultRoute="ws1-eth1")
    workstation2 = self.addHost('ws2', mac="00:00:00:00:00:05", ip='200.20.3.5/24', defaultRoute="ws2-eth1")
    self.addLink(workstation1,switch1, port1=1, port2=11)
    self.addLink(workstation2,switch1, port1=1, port2=10)
   
    #IT Department with links
    workstation3 = self.addHost('ws3', mac="00:00:00:00:00:07", ip='200.20.4.7/24', defaultRoute="ws3-eth1")
    workstation4 = self.addHost('ws4', mac="00:00:00:00:00:06", ip='200.20.4.6/24', defaultRoute="ws4-eth1")
    self.addLink(workstation3,switch2, port1=1, port2=9)
    self.addLink(workstation4,switch2, port1=1, port2=8)
   
    #Data Center with links
    Server2 = self.addHost('Serv2', mac="00:00:00:00:00:01", ip='200.20.1.1/24', defaultRoute="Serv2-eth1")
    WebServer = self.addHost('ServWeb', mac="00:00:00:00:00:02", ip='200.20.1.2/24', defaultRoute="ServWeb-eth1")
    DNSServer = self.addHost('ServDNS', mac = "00:00:00:00:00:03", ip='200.20.1.3/24', defaultRoute="ServDNS-eth1")
    self.addLink(Server2,switch3, port1=1, port2=5)
    self.addLink(WebServer,switch3, port1=1, port2=6)
    self.addLink(DNSServer,switch3, port1=1, port2=7)

def configure():
  topo = final_topo()

  net = Mininet(topo=topo, controller=RemoteController)
  net.start()
  # use static ARP
  net.staticArp() 
  CLI(net)
  
  net.stop()


if __name__ == '__main__':
  configure()