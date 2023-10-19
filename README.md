# simultor_for_data_monitor
Hi there
I am here to make a simulator for testing my Data Monitor app that i explained it in itself repository.
Data Monitor is listening on a UDP socket. the app generate a set of random numbers as current, voltage, rpm and ..., in order to transmite this set to Data Monitor.
the transmition is perform over an udp connetion. connection system is master-slave system base.
so I decide to be deep about detail for learning purpose.
okey so let is begin with that question "what is a simulator and when you use it?"
simulator is a set of operations and components integerated to simulate one or many funations that create or define an entity or system.
today we works a lot of simulators like video games, movies and etc.
when you need a simulator? every time you can`t examine your system or device in real world becasue of expensive failures and costs. 
our simulator uses udp connection to transmite data from one point to another. in fact our connection is like point-to-point or peer-to-peer connection type but is not.
because connection implemented based on master-slave protcol system. I will explain in more.
connection type determine our policy of communication based on what we want.

1.peer-to-peer communication
Peer-to-peer (P2P) is a decentralized communications model in which each party has the same capabilities and either party can initiate a communication session.

![images](https://github.com/neji78/udp_transmission_simulator_qt_widget/assets/91015552/698a0774-f7ad-418f-990f-1f09f9022b93)
