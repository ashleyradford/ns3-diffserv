#ifndef SIMULATION_H
#define SIMULATION_H

#include "diff_serv.h"
#include "drr.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "spq.h"

struct QosData
{
    std::string name;
    uint32_t count;
    std::vector<uint32_t> max_packets;
    std::vector<uint32_t> priorities;
    std::vector<uint32_t> weights;
    std::vector<bool> defaults;
    std::vector<uint32_t> dest_ports;

    QosData() : count(0) {}
};

class Simulation {
    public:
        QosData data;
        Ptr<SPQ> spq;
        Ptr<DRR> drr;

        uint32_t parseConfigs(std::string filename);
        void printConfigs(QosData data);
        void initializeSPQ();
        void initializeDRR();
};

uint32_t Simulation::parseConfigs(std::string filename) {
    // check that file can be opened, parse the xml file
    try {
        rapidxml::file<> xmlFile(filename.c_str());
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());

        // get the qos and name elements
        rapidxml::xml_node<>* qosNode = doc.first_node("QoS");
        rapidxml::xml_node<>* nameNode = qosNode->first_node("Name");
        data.name = std::string(nameNode->value());

        // check QoS mechanism
        if (std::string(nameNode->value()) != "SPQ" && std::string(nameNode->value()) != "DRR") {
            std::cout << "Not a valid QoS mechanism" << std::endl;
            return 1;
        }

        for (rapidxml::xml_node<>* queueNode = qosNode->first_node("Queue"); queueNode; queueNode = queueNode->next_sibling()) {
            // max packets spec
            rapidxml::xml_node<>* maxPacketsNode = queueNode->first_node("MaxPackets");
            if (maxPacketsNode) {
                data.max_packets.push_back(std::stoul(maxPacketsNode->value()));
            }
            // priority spec
            rapidxml::xml_node<>* priorityNode = queueNode->first_node("Priority");
            if (priorityNode) {
                data.priorities.push_back(std::stoul(priorityNode->value()));
            }
            // weight spec
            rapidxml::xml_node<>* weightNode = queueNode->first_node("Weight");
            if (weightNode) {
                data.weights.push_back(std::stoul(weightNode->value()));
            }
            // default spec
            rapidxml::xml_node<>* defaultNode = queueNode->first_node("Default");
            if (defaultNode) {
                data.defaults.push_back(std::string(defaultNode->value()) == "true");
            }
            // port spec
            rapidxml::xml_node<>* destPortNode = queueNode->first_node("DestPort");
            if (destPortNode) {
                data.dest_ports.push_back(std::stoul(destPortNode->value()));
            }
            // total queue count
            data.count++;
        }

        // free the memory
        doc.clear();
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to parse config file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void Simulation::printConfigs(QosData data) {
    std::cout << "QoS: " << data.name << std::endl;
    std::cout << "Max Packets: " << std::endl;
    for (int i = 0; i < data.max_packets.size(); i++) {
        std::cout << "  " << data.max_packets[i] << std::endl;
    }
    std::cout << "Priorities: " << std::endl;
    for (int i = 0; i < data.priorities.size(); i++) {
        std::cout << "  " << data.priorities[i] << std::endl;
    }
    std::cout << "Weights: " << std::endl;
    for (int i = 0; i < data.weights.size(); i++) {
        std::cout << "  " << data.weights[i] << std::endl;
    }
    std::cout << "Defaults: " << std::endl;
    for (int i = 0; i < data.defaults.size(); i++) {
        std::cout << "  " << data.defaults[i] << std::endl;
    }
    std::cout << "Dest Ports: " << std::endl;
    for (int i = 0; i < data.dest_ports.size(); i++) {
        std::cout << "  " << data.dest_ports[i] << std::endl;
    }
}

void Simulation::initializeSPQ() {
    // create instance of object
    spq = CreateObject<SPQ>();

    // populate SPQ class
    for (int i = 0; i < data.count; i++)
    {
        // create and add filters
        DstPortNumber *dstport_fe = new DstPortNumber(data.dest_ports[i]);
        Filter *f1 = new Filter();
        f1->AddElement(dstport_fe);

        // add traffic class values
        TrafficClass *trafficClass = new TrafficClass();
        trafficClass->SetMaxPackets(data.max_packets[i]);
        trafficClass->SetPriorityLevel(data.priorities[i]);
        trafficClass->SetDefault(data.defaults[i]);
        trafficClass->AddFilter(f1);
        
        // add traffic class to spq
        spq->AddQueue(trafficClass);
    }
}

void Simulation::initializeDRR() {
    // create instance of object
    drr = CreateObject<DRR>();

    // populate DRR class
    for (int i = 0; i < data.count; i++)
    {
        // create and add filters
        DstPortNumber *dstport_fe = new DstPortNumber(data.dest_ports[i]);
        Filter *f1 = new Filter();
        f1->AddElement(dstport_fe);

        // add traffic class values
        TrafficClass *trafficClass = new TrafficClass();
        trafficClass->SetMaxPackets(data.max_packets[i]);
        trafficClass->SetWeight(data.weights[i]);
        trafficClass->SetDefault(data.defaults[i]);
        trafficClass->AddFilter(f1);

        // add traffic class to drr
        drr->AddQueue(trafficClass);
    }
}

#endif // SIMULATION_H
