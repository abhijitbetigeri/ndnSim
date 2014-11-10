/* Program: dumb-bell-network.cc
Function: Create a dumb bell topology of network with two routers and 4 leafs
Project 2: NS-3 Based NDN Simulation
Professor: Dr. Hussein Badr
Students: Vasudevan Nagendra, Abhijith Betigeri
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/name.h"

using namespace ns3;

int main (int argc, char *argv[])
{

  CommandLine cmd;
  cmd.Parse (argc, argv);

  AnnotatedTopologyReader topologyReader ("", 1);
  topologyReader.SetFileName ("topo-dumbbell.txt");
  topologyReader.Read ();

  // Getting containers for the consumer/producer/routers
  Ptr<Node> consumer1 = Names::Find<Node> ("Consumer1");
  Ptr<Node> consumer2 = Names::Find<Node> ("Consumer2");
  Ptr<Node> producer1 = Names::Find<Node> ("Producer1");
  Ptr<Node> producer2 = Names::Find<Node> ("Producer2");
  Ptr<Node> nodea = Names::Find<Node> ("NodeA");
  Ptr<Node> nodeb = Names::Find<Node> ("NodeB");

  // Install CCNx stack on all the nodes 
  ndn::StackHelper ndnHelper1;
  ndnHelper1.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");
  ndnHelper1.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "10"); 
  //ndnHelper1.SetContentStore ("ns3::ndn::cs::Nocache");
  ndnHelper1.Install (nodea);  
  ndnHelper1.Install (nodeb);  

  ndn::StackHelper ndnHelper2;
  ndnHelper2.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");
  ndnHelper2.SetContentStore ("ns3::ndn::cs::Nocache");
  ndnHelper2.Install (consumer1);  
  ndnHelper2.Install (consumer2);  
  ndnHelper2.Install (producer1);  
  ndnHelper2.Install (producer2);  
  
  // Setting Configurations on Consumer 1 
  ndn::AppHelper consumerHelper1 ("ns3::ndn::ConsumerCbr");
  consumerHelper1.SetAttribute ("Frequency", StringValue ("1")); // 1 interests a second
  consumerHelper1.SetAttribute ("StartTime", StringValue ("0"));
  consumerHelper1.SetAttribute ("StopTime", StringValue ("5.0"));
  consumerHelper1.SetPrefix ("/prefix1");
  consumerHelper1.Install (consumer1); 

  ndn::AppHelper consumerHelper1b ("ns3::ndn::ConsumerCbr");
  consumerHelper1b.SetAttribute ("Frequency", StringValue ("1")); // 1 interests a second
  consumerHelper1b.SetAttribute ("StartTime", StringValue ("1"));
  consumerHelper1b.SetAttribute ("StopTime", StringValue ("5.0"));
  consumerHelper1b.SetPrefix ("/prefix2");
  consumerHelper1b.Install (consumer1); 

  // Setting Configurations on Consumer 2 
  ndn::AppHelper consumerHelper2 ("ns3::ndn::ConsumerCbr");
  consumerHelper2.SetAttribute ("Frequency", StringValue ("1")); // 1 interests a second
  consumerHelper2.SetAttribute ("StartTime", StringValue ("0"));
  consumerHelper2.SetAttribute ("StopTime", StringValue ("5.0"));
  consumerHelper2.SetPrefix ("/prefix2");
  consumerHelper2.Install (consumer2); 

  ndn::AppHelper consumerHelper2b ("ns3::ndn::ConsumerCbr");
  consumerHelper2b.SetAttribute ("Frequency", StringValue ("1")); // 1 interests a second
  consumerHelper2b.SetAttribute ("StartTime", StringValue ("1"));
  consumerHelper2b.SetAttribute ("StopTime", StringValue ("5.0"));
  consumerHelper2b.SetPrefix ("/prefix1");
  consumerHelper2b.Install (consumer2); 

  // Setting Attributes on Producer1 
  ndn::AppHelper producerHelper1 ("ns3::ndn::Producer");
  producerHelper1.SetAttribute ("PayloadSize", StringValue("1024"));
  producerHelper1.SetPrefix ("/prefix1");
  producerHelper1.Install (producer1); 
  
  // Setting Attributes on Producer2 
  ndn::AppHelper producerHelper2 ("ns3::ndn::Producer");
  producerHelper2.SetAttribute ("PayloadSize", StringValue("1024"));
  producerHelper2.SetPrefix ("/prefix2");
  producerHelper2.Install (producer2);
  
  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll ();
  ndnGlobalRoutingHelper.AddOrigins ("/prefix1", producer1);
  ndnGlobalRoutingHelper.AddOrigins ("/prefix2", producer2);

  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes ();
 
  //Stop the operations after 7 seconds 
  Simulator::Stop (Seconds (7.0));
  
  // Enabling logger modules
  ndn::L3AggregateTracer::InstallAll ("aggregate-trace1.txt", Seconds (0.5));
  ndn::L3RateTracer::InstallAll ("rate-trace1.txt", Seconds (0.5));
  ndn::AppDelayTracer::InstallAll ("app-delays-trace.txt");
  ndn::CsTracer::InstallAll ("cs-trace.txt", Seconds (6.5));  

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
