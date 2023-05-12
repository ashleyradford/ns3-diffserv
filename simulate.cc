#include "simulation.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/udp-client-server-helper.h"

// Default Network Topology
//
//      10.1.1.0          10.1.2.0
// n0 -------------- r -------------- n1
//    point-to-point   point-to-point
//       4 Mbps            1 Mbps
//

using namespace ns3;

int
main(int argc, char* argv[])
{
    // ------------------- Initiliaze QoS Mechanism -------------------

    // check for specified config file
    if (argc < 2) {
        std::cout << "No config file provided." << std::endl;
        return 1;
    }

    // ns3 command line
    CommandLine cmd;
    std::string config_file = "";
    cmd.AddValue("config", "Config filepath.", config_file);
    cmd.Parse(argc, argv);

    // parse the xml file
    Simulation sim;
    if (sim.parseConfigs(config_file)) {
        return 1;
    }

    // prep and run simulations
    if (sim.data.name == "SPQ") {
        std::cout << "Initializing SPQ object" << std::endl;
        sim.initializeSPQ();
    } else if (sim.data.name == "DRR") {
        std::cout << "Initializing DRR object" << std::endl;
        sim.initializeDRR();
    }

    // ------------------- Build the Topology -------------------

    // create three nodes
    Ptr<Node> n0 = CreateObject<Node>();
    Ptr<Node> r = CreateObject<Node>();
    Ptr<Node> n1 = CreateObject<Node>();

    NodeContainer crNodes(n0, r);
    NodeContainer rsNodes(r, n1);
    NodeContainer all(n0, r, n1);

    // create a PointToPoint channel and set its parameters
    PointToPointHelper pointToPoint1, pointToPoint2;
    pointToPoint1.SetDeviceAttribute("DataRate", StringValue("4Mbps")); // set link capacity
    pointToPoint1.SetChannelAttribute("Delay", StringValue("10ms"));    // set prop delay
    pointToPoint2.SetDeviceAttribute("DataRate", StringValue("1Mbps")); // set link capacity
    pointToPoint2.SetChannelAttribute("Delay", StringValue("10ms"));    // set prop delay

    // create net devices (or the interfaces for the nodes)
    NetDeviceContainer devices1, devices2;
    devices1 = pointToPoint1.Install(crNodes); // install channel between nodes 0 and 1
    devices2 = pointToPoint2.Install(rsNodes); // install channel between nodes 1 and 2

    // install and assign IPv4 addresses.
    InternetStackHelper stack;
    stack.Install(all);

    Ipv4AddressHelper address1, address2;
    address1.SetBase("10.1.1.0", "255.255.255.0");
    address2.SetBase("10.1.2.0", "255.255.255.0");

    Ipv4InterfaceContainer interfaces1 = address1.Assign(devices1);
    Ipv4InterfaceContainer interfaces2 = address2.Assign(devices2);

    // add global routing
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // set up the spq
    Ptr<PointToPointNetDevice> crDevice = r->GetDevice(1)->GetObject<PointToPointNetDevice>();
    if (sim.data.name == "SPQ") {
        crDevice->SetQueue(sim.spq);
    } else if (sim.data.name == "DRR") {
        crDevice->SetQueue(sim.drr);
    }

    // ------------------- Add UDP Applications -------------------

    if (sim.data.name == "SPQ") {
        // create UdpServer applications on n1
        UdpServerHelper server1(sim.data.dest_ports[0]);
        UdpServerHelper server2(sim.data.dest_ports[1]);

        ApplicationContainer apps1 = server1.Install(all.Get(2));
        apps1.Start(Seconds(0.0));
        apps1.Stop(Seconds(40.0));
        ApplicationContainer apps2 = server2.Install(all.Get(2));
        apps1.Start(Seconds(0.0));
        apps2.Stop(Seconds(40.0));

        // create UdpClient applications on n0
        uint32_t maxPacketSize = 1000;
        Time interPacketInterval = Seconds(0.001);
        uint32_t maxPacketCount = 8000;

        UdpClientHelper client1(interfaces2.GetAddress(1), sim.data.dest_ports[0]);
        client1.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
        client1.SetAttribute("Interval", TimeValue(interPacketInterval));
        client1.SetAttribute("PacketSize", UintegerValue(maxPacketSize));

        UdpClientHelper client2(interfaces2.GetAddress(1), sim.data.dest_ports[1]);
        client2.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
        client2.SetAttribute("Interval", TimeValue(interPacketInterval));
        client2.SetAttribute("PacketSize", UintegerValue(maxPacketSize));

        apps1 = client1.Install(all.Get(0));
        apps1.Start(Seconds(1.0));
        apps1.Stop(Seconds(40.0));

        apps2 = client2.Install(all.Get(0));
        apps2.Start(Seconds(12.0));
        apps2.Stop(Seconds(40.0));

        pointToPoint1.EnablePcap("pcap-files/spq-client-to-router", devices1.Get(1));
        pointToPoint2.EnablePcap("pcap-files/spq-router-to-server", devices2.Get(0));

    } else if (sim.data.name == "DRR") {
        // create UdpServer applications on n1
        UdpServerHelper server1(sim.data.dest_ports[0]);
        UdpServerHelper server2(sim.data.dest_ports[1]);
        UdpServerHelper server3(sim.data.dest_ports[2]);

        ApplicationContainer apps1 = server1.Install(all.Get(2));
        apps1.Start(Seconds(1.0));
        apps1.Stop(Seconds(40.0));
        ApplicationContainer apps2 = server2.Install(all.Get(2));
        apps1.Start(Seconds(1.0));
        apps2.Stop(Seconds(40.0));
        ApplicationContainer apps3 = server3.Install(all.Get(2));
        apps1.Start(Seconds(1.0));
        apps2.Stop(Seconds(40.0));

        // create UdpClient applications on n0
        uint32_t maxPacketSize = 1000;
        Time interPacketInterval = Seconds(0.001);
        uint32_t maxPacketCount = 8000;

        UdpClientHelper client1(interfaces2.GetAddress(1), sim.data.dest_ports[0]);
        client1.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
        client1.SetAttribute("Interval", TimeValue(interPacketInterval));
        client1.SetAttribute("PacketSize", UintegerValue(maxPacketSize));

        UdpClientHelper client2(interfaces2.GetAddress(1), sim.data.dest_ports[1]);
        client2.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
        client2.SetAttribute("Interval", TimeValue(interPacketInterval));
        client2.SetAttribute("PacketSize", UintegerValue(maxPacketSize));

        UdpClientHelper client3(interfaces2.GetAddress(1), sim.data.dest_ports[2]);
        client3.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
        client3.SetAttribute("Interval", TimeValue(interPacketInterval));
        client3.SetAttribute("PacketSize", UintegerValue(maxPacketSize));

        apps1 = client1.Install(all.Get(0));
        apps1.Start(Seconds(2.0));
        apps1.Stop(Seconds(40.0));

        apps2 = client2.Install(all.Get(0));
        apps2.Start(Seconds(2.0));
        apps2.Stop(Seconds(40.0));

        apps3 = client3.Install(all.Get(0));
        apps3.Start(Seconds(2.0));
        apps3.Stop(Seconds(40.0));

        pointToPoint1.EnablePcap("pcap-files/drr-client-to-router", devices1.Get(1));
        pointToPoint2.EnablePcap("pcap-files/drr-router-to-server", devices2.Get(0));
    }

    // ------------------- Run the Simulation -------------------

    Simulator::Run();
    Simulator::Destroy();
}
