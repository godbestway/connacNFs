#/usr/bin/python
from mininet.cli import CLI
from mininet.log import setLogLevel, info, error
from mininet.net import Mininet
from mininet.topo import SingleSwitchTopo, Topo
from mininet.node import RemoteController, OVSSwitch, Node, CPULimitedHost
from mininet.link import Link, TCIntf, Intf, TCLink
from mininet.util import custom

class StandaloneSwitch(OVSSwitch):
    def __init__(self, name, **params):
        OVSSwitch.__init__(self, name, failMode='standalone', **params)
    def start(self, controllers):
        return OVSSwitch.start(self, [ ])

class LinuxRouter( Node ):
    #"A Node with IP forwarding enabled."

    def config( self, **params ):
        super( LinuxRouter, self).config( **params )
        # Enable forwarding on the router
        self.cmd( 'sysctl net.ipv4.ip_forward=1' )

    def terminate( self ):
        self.cmd( 'sysctl net.ipv4.ip_forward=0' )
        super( LinuxRouter, self ).terminate()

class NetworkTopo( Topo ):
    "A LinuxRouter connecting three IP subnets"

    def build( self, **_opts ):
        print "*** Creating nodes ***"
#        r0 = self.addNode('r0',ip='10.0.0.254/24', cls=LinuxRouter)
        #h1 = self.addHost( 'h1', mac='00:00:00:00:00:01', ip='10.0.0.1/24',defaultRoute='via 10.0.0.254')
        h1 = self.addHost( 'h1', mac='00:00:00:00:00:01', ip='10.0.10.2/24')
        s3 = self.addSwitch( 's3', mac='00:00:00:00:00:08' )
#        self.addLink( h1, r0, intfName2='r0-eth1', params2={ 'ip' : '10.0.0.254/24' } )

        self.addLink(h1, s3)

        s1 = self.addSwitch( 's1', mac='00:00:00:00:00:05' )
        #h2 = self.addHost( 'h2', mac='00:00:00:00:00:02', ip='10.0.10.1/24',defaultRoute='via 10.0.10.254' )
        h2 = self.addHost( 'h2', mac='00:00:00:00:00:02', ip='10.0.10.1/24' )
        self.addLink(h2, s3, intfName1='h2-eth0')
 #       self.addLink( h2, r0,intfName1 = 'h2-eth0',intfName2='r0-eth2', params2={ 'ip' : '10.0.10.254/24' } )

        self.addLink(h2, s1, intfName1='h2-eth1')

        h3 = self.addHost( 'h3', mac='00:00:00:00:00:03', ip='192.168.0.1/24' )
        h4 = self.addHost( 'h4', mac='00:00:00:00:00:04', ip='192.168.0.3/24' )
        

        self.addLink(h3, s1)
        self.addLink(h4, s1,intfName1='h4-eth0')

        s2 = self.addSwitch( 's2', mac='00:00:00:00:00:06' )

        self.addLink(h4, s2,intfName1='h4-eth1')
        h5 = self.addHost( 'h5', mac='00:00:00:00:00:07', ip='10.20.0.1/24' )
       
        self.addLink(h5, s2)
def run():
    "Test linux router"
    topo = NetworkTopo()
    net = Mininet(controller=RemoteController,topo = topo,switch=StandaloneSwitch)
    h2 = net.get('h2')
    h2.cmd('ifconfig h2-eth1 192.168.0.2 netmask 255.255.255.0')
    h4 = net.get('h4')
    h4.cmd('ifconfig h4-eth1 10.20.0.2 netmask 255.255.255.0')
    net.start()
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    run()

