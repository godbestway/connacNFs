#/usr/bin/python

from mininet.cli import CLI
from mininet.log import setLogLevel, info, error
from mininet.net import Mininet
from mininet.topo import SingleSwitchTopo
from mininet.node import RemoteController, OVSSwitch, Node, CPULimitedHost,OVSKernelSwitch
from mininet.link import Link, TCIntf, Intf, TCLink
from mininet.util import custom

class StandaloneSwitch(OVSSwitch):
    def __init__(self, name, **params):
        OVSSwitch.__init__(self, name, failMode='standalone', **params)
    def start(self, controllers):
        return OVSSwitch.start(self, [ ])

if __name__ == '__main__':
    setLogLevel( 'info' )

    # Create rate limited interface
    #intf = custom(TCIntf, bw=50)
    #host = custom(CPULimitedHost, sched='cfs', cpu=0.1)

    # Create data network
   # net = Mininet(topo=SingleSwitchTopo( k=5 ), switch=OVSSwitch,
    #        controller=RemoteController, intf=intf, host=host, 
     #       autoSetMacs=True, autoStaticArp=True)
    
    "Create a network."
    net = Mininet( controller=RemoteController, link=Link, switch=StandaloneSwitch )
    print "*** Creating nodes ***"
    h1 = net.addHost( 'h1', mac='00:00:00:00:00:01', ip='192.168.0.1/24' )

    h2 = net.addHost( 'h2', mac='00:00:00:00:00:02', ip='192.168.0.2/24')

    h3 = net.addHost( 'h3', mac='00:00:00:00:00:03', ip='10.0.0.2/24' )
#    h4 = net.addHost( 'h4', mac='00:00:00:00:00:06', ip='10.0.0.3/24' )

    s1 = net.addSwitch( 's1', mac='00:00:00:00:00:04' )
    s2 = net.addSwitch( 's2', mac='00:00:00:00:00:05' )
    
    net.addLink(h1, s1)
#    net.addLink(h4, s1) 
    net.addLink(h3, s2) 
    
    Link(h2, s1, intfName1='h2-eth0')
    Link(h2, s2, intfName1='h2-eth1')
    h2.cmd('ifconfig h2-eth1 10.0.0.1 netmask 255.255.255.0')
    
    #s1.cmd("ifconfig s1:1 10.0.0.254")
    #h1.cmd("route add default gw 10.0.0.2")
    #h4.cmd("route add default gw 10.0.0.2")
    #h3.cmd("route add default gw 10.0.10.2")
    #h2.cmd("sysctl -w net.ipv4.ip_forward=1")
    #gate = Node( 'gate')
    #link = net.addLink(gate, s1)
    #link.intf1.setIP('10.0.0.254', 24)


    # Run network
    net.start()

    CLI( net )
    net.stop()
