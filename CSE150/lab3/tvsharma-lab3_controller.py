# Lab3 Skeleton

from pox.core import core

import pox.openflow.libopenflow_01 as of

log = core.getLogger()

class Routing (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection
    # This binds our PacketIn event listener
    connection.addListeners(self)

  def drop (self, packet, duration = None): 
    if duration is not None:
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = duration[30]
      msg.hard_timeout = duration[30]
      self.connection.send(msg)
    
  def accept (self, event, end_port): 
    msg = of.ofp_packet_out()
    msg.actions.append(of.ofp_action_output(port = end_port))
    msg.data = event.ofp
    msg.in_port = event.port
    self.connection.send(msg)

  def do_routing (self, packet, packet_in, port_on_switch, switch_id, event):
    # port_on_switch - the port on which this packet was received
    # switch_id - the switch which received this packet

    datacenter = ["200.20.1.1", "200.20.1.2", "200.20.1.3"]
    ITdepartment = ["200.20.4.6", "200.20.4.7"]
    OTdepartment = ["200.20.3.4", "200.20.3.5"]
    salesdepartment = ["200.20.2.8", "200.20.2.10", "200.20.2.9"]
    #ip to port {ip: port } 
    iptoPort ={"200.20.1.1":5,"200.20.1.2":6,"200.20.1.3":7,"200.20.2.8":2,"200.20.2.10":4,"200.20.2.9":3,"200.20.3.4":11, "200.20.3.5":10,"200.20.4.7":9,"200.20.4.6":8}
    ipv4 = packet.find("ipv4")
    icmp = packet.find("icmp")
    tcp = packet.find("tcp")
    udp = packet.find("udp")

    #print ipv4
    #find the protocol
    #if the subnet values math 
      #assign end_port
      #accept()
    
    # It the packet is of IPV4 
    if(ipv4):
      src_ip = packet.payload.srcip
      dst_ip = packet.payload.dstip
      # print dst_ip
      # print src_ip
      # print switch_id
      # print port_on_switch
    # If the packet is ICMP protocolsudo ~/pox/pox.py misc.lab3_controller
    print "hi"
    print icmp
    if(icmp):
      # subnet to subnet communication
      print switch_id
      if switch_id == 1:
        if dst_ip in OTdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
          return
      if switch_id == 2: 
        if dst_ip in ITdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
          return
        # Rule 1 ---------------------------------
        if dst_ip in salesdepartment: 
          # send to the core switch (on port 13)
          self.accept(event, 13)
      if switch_id == 3:
        if dst_ip in datacenter:
          self.accept(event, iptoPort[str(dst_ip)])
          return
      if switch_id == 4:
        print "arrived in the switch 4 - sales dept"
        print switch_id
        if dst_ip in salesdepartment: 
          self.accept(event, iptoPort[str(dst_ip)])
          return
        # Rule 1 ----------------------------------
        if dst_ip in ITdepartment: 
          # send to the core switch (on port 15)
          print "prepare to be sent to the core switch"
          print dst_ip
          self.accept(event, 15)
          return
      # core switch communication
      elif switch_id is not [1,2,3,4]: 
        # if in coreswitch cases -> end dst ITdepartment or end dst salesdepartment
        if dst_ip in ITdepartment: 
          print "arrived at the core switch"
          print switch_id
          self.accept(event, 13)
          return
        if dst_ip in salesdepartment:
          self.accept(event, 15)
          return

    # If the packet is TCP protocol
    if(tcp):
      # subnet to subnet communication
      if switch_id == 1:
        if dst_ip in OTdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
        # Rule 2 ----------------------------------
        if dst_ip in ITdepartment or dst_ip in datacenter:
          # send to the core switch (on port 12)
          self.accept(event, 12)    
      if switch_id == 2:
        if dst_ip in ITdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
        # Rule 2 ----------------------------------
        if dst_ip in OTdepartment or dst_ip in datacenter:
          # send to the core switch (on port 13)
          self.accept(event, 13)
      if switch_id == 3:
        if dst_ip in datacenter:
          self.accept(event, iptoPort[str(dst_ip)])
        # Rule 2 ----------------------------------
        if dst_ip in ITdepartment or dst_ip in OTdepartment:
          # send to the core switch (on port 14)
          self.accept(event, 14)
      if switch_id == 4:
        if dst_ip in salesdepartment: 
          self.accept(event, iptoPort[str(dst_ip)])  
          return

      # core switch communication
      elif switch_id not in [1,2,3,4]: 
        # if the dst ip is in the OT department
        if dst_ip in OTdepartment:
          self.accept(event, 12)
          return
        # if the dst ip is in the IT department
        if dst_ip in ITdepartment:
          self.accept(event, 13)
          return
        # if the dst ip is in the data center
        if dst_ip in datacenter:
          self.accept(event, 14)
          return

    # If the packet is UDP protocol
    if(udp):
      # Allow communication between same subnets
      if switch_id == 1:
        if dst_ip in OTdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
          return
        # send to the core switch (on port 12)
        if dst_ip in datacenter:
          self.accept(event, 12)
      if switch_id == 2:
        if dst_ip in ITdepartment:
          self.accept(event, iptoPort[str(dst_ip)])
          return
        # send to the core switch (on port 13)
        if dst_ip in datacenter: 
          self.accept(event, 13)
      if switch_id == 3:
        if dst_ip in datacenter:
          self.accept(event, iptoPort[str(dst_ip)])
          return
        # send to the core switch (on port 14)
        if dst_ip in OTdepartment or dst_ip in ITdepartment: 
          self.accept(event, 14)
      if switch_id == 4:
        if dst_ip in salesdepartment: 
          self.accept(event, iptoPort[str(dst_ip)])
          return
      # core switch communication
      if switch_id not in [1,2,3,4]:
        # if dst_ip is OTdepartment 
        if dst_ip in OTdepartment:
          self.accept(event, 12)
          return
        # else if dst ip is in the datacenter
        elif dst_ip in datacenter:
          self.accept(event, 14)
          return
        # else if the dst ip is in the IT department
        if dst_ip in ITdepartment:
          self.accept(event, 13)
          return
    # Rule 4 
    else:
      self.drop(packet)
      return

  def _handle_PacketIn (self, event):
    """
    Handles packet in messages from the switch.
    """
    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return

    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_routing(packet, packet_in, event.port, event.dpid, event)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Routing(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)