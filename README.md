# DiffServ:
A base class in ns3 that simulates differentiated services.

## Requirements
Requires rapidxml header files `rapidxml.hpp` and `rapidxml_utils.hpp` (included).
An xml config file for the QoS simulation to run (SPQ or DRR), both examples are included.
The config file must include the following:
- **QoS Name:** SPQ or DRR
- **MaxPackets:** max packets that queue can hold
- **Priority:** priority of queue (if applicable)
- **Weight:** quantum level for queue (if applicable)
- **Default:** will take packets that have no match (true or false)
- **DestPort:** destination port to classify this queue

```
<QoS>
    <Name>SPQ</Name>
    <Queue no="1">
        <MaxPackets>12000</MaxPackets>
        <Priority>2</Priority>
        <Default>true</Default>
        <DestPort>7000</DestPort>
    </Queue>
    <Queue no="2">
        <MaxPackets>12000</MaxPackets>
        <Priority>1</Priority>
        <Default>false</Default>
        <DestPort>9000</DestPort>
    </Queue>
</QoS>
```

Note: it is up to the user to define weights that are above 0, otherwise DRR will not work as intended. It is also up to the user to define a default queue. If a default queue is not set, then packets that cannot be classified will be dropped (which may be intended). If multiple default queues are set, then the last queue added will act as the default queue (which may not be intended).

## Run
To run the SPQ simulation:
```
./ns3 run 'simulation --config=path/to/spq.xml'
```
To run the DRR simulation:
```
./ns3 run 'simulation --config=path/to/drr.xml'
```

## Design
DiffServ is an abstract base class that contains a `q_class`, which is a vector of TrafficClass pointers. Each TrafficClass essentially represents a queue. Each TrafficClass contains metadata such as the number of packets, weight (if applicable), priority level (if applicable),  if it's the default queue, the filters it uses for packet classification, and `m_queue`, the queue itself. Each filter inside the TrafficClass `filters` vector variable contains a vector of FilterElement pointers. FilterElement is an abstract class with subclasses for the following filters: SrcIPAddress, SrcMask, SrcPortNumber, DstIPAddress, DstMask, DstPortNumber, ProtocolNumber.

DiffServ is a subclass of ns3's **Queue** class. As such it overrides the following class methods: Enqueue, Dequeue, Remove, and Peek. All functions call on the methods DoEnqueue (private), DoDequeue (protected), DoRemove (private), and DoPeek (private), respectively. DiffServ has the following additional public virtual methods: Schedule, Classify, and AddQueue. These three methods can be overridden by DiffServ subclasses. Schedule() must be implemented in any subclass, as it is the one pure virtual method in DiffServ(). This is where a QoS mechanisims's behavior would be implemented - DoDequeue, DoRemove, and DoPeek all call on Schedule. Schedule returns a const packet from the queue that is to be serviced next. From here, DoDequeue and DoRemove will call on Classify() with this packet to get the index of the queue from which to dequeue or remove from. DoEnqueue simple calls on Classify() to get the index of the queue for which a packet should be classified.

**SPQ** is a subclass of DiffServ. It only implements Schedule so that ns3 can follow strict priority queueing. **DRR** is another subclass of DiffServ. It overrides Dequeue, Schedule, and AddQueue so that ns3 can follow deficit round robin queueing. AddQueue is implemented because after calling on DiffServ's AddQueue method, DRR needs to add an index to its deficit counter vector. For Dequeue, after calling on DiffServ's Dequeue method, DRR needs to update its active queue index and deficit counter vector.

## Resources
[RapidXML](https://github.com/Fe-Bell/RapidXML)<br>
[Efficient Fair Queuing using Deficit Round Robin](http://cs621.cs.usfca.edu/v/resources/drr.pdf)<br>
[Queue Class Reference](https://www.nsnam.org/docs/release/3.19/doxygen/classns3_1_1_queue.html)<br>
[LaTeX SIGCOMM 18](https://github.com/scyue/latex-sigcomm18)
