/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011-2012 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ahmed Waliullah Kazi
 */


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/name.h"

using namespace ns3;

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  AnnotatedTopologyReader topologyReader ("", 1);
  topologyReader.SetFileName ("src/ndnSIM/examples/topologies/topo-39.txt");
  topologyReader.Read ();

  // Getting containers for the consumer/producer
  // There needs to be 1-1 matching (in terms name (e.g., "1" "2") of the nodes) with the topology file.
  
  Ptr<Node> consprods[31] = { 
    Names::Find<Node> ("8"), Names::Find<Node> ("9"),
  	Names::Find<Node> ("10"), Names::Find<Node> ("11"),
  	Names::Find<Node> ("12"), Names::Find<Node> ("13"),
    Names::Find<Node> ("14"), Names::Find<Node> ("15"),        
  	Names::Find<Node> ("16"), Names::Find<Node> ("17"),
    Names::Find<Node> ("18"), Names::Find<Node> ("19"),  	
    Names::Find<Node> ("20"), Names::Find<Node> ("21"),
  	Names::Find<Node> ("22"), Names::Find<Node> ("23"),
  	Names::Find<Node> ("24"), Names::Find<Node> ("25"),
    Names::Find<Node> ("26"), Names::Find<Node> ("27"),
  	Names::Find<Node> ("28"), Names::Find<Node> ("29"),
  	Names::Find<Node> ("30"), Names::Find<Node> ("31"),
    Names::Find<Node> ("32"), Names::Find<Node> ("33"),
  	Names::Find<Node> ("34"), Names::Find<Node> ("35"),
    Names::Find<Node> ("36"), Names::Find<Node> ("37"),
  	Names::Find<Node> ("38")
  };

  Ptr<Node> cores[8] = { 
    Names::Find<Node> ("0"), Names::Find<Node> ("1"), 
    Names::Find<Node> ("2"), Names::Find<Node> ("3"),
    Names::Find<Node> ("4"), Names::Find<Node> ("5"), 
    Names::Find<Node> ("6"), Names::Find<Node> ("7")        
  };

  for (int i=0; i<=30; i++) {
  
     // Install CCNx stack on all edge nodes
        ndn::StackHelper ccnxHelper;
        
		ccnxHelper.SetContentStore ("ns3::ndn::cs::Nocache");
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "50"); /* Cache Size 50 */
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "500"); /* Cache Size 500 */
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "2000"); /* Cache Size 2000 */
		
		ccnxHelper.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");
		ccnxHelper.SetPit ("ns3::ndn::pit::Persistent", "MaxSize", "0");        
        
		ccnxHelper.Install (consprods[i]);  
  }

  for (int i=0; i<=7; i++) {
        // Install CCNx stack on core nodes
        ndn::StackHelper ccnxHelper;

        ccnxHelper.SetContentStore ("ns3::ndn::cs::Nocache");
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "50"); /* Cache Size 50 */
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "500"); /* Cache Size 500 */
		//ccnxHelper.SetContentStore ("ns3::ndn::cs::Lru", "MaxSize", "2000"); /* Cache Size 2000 */
		
		ccnxHelper.SetForwardingStrategy ("ns3::ndn::fw::BestRoute");
		ccnxHelper.SetPit ("ns3::ndn::pit::Persistent", "MaxSize", "0");    

        ccnxHelper.Install (cores[i]);       
   }  

  ndn::AppHelper consumerHelper ("ns3::ndn::ConsumerZipfMandelbrot39");

  consumerHelper.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper.SetAttribute ("StartTime", StringValue ("0.03")); 
  consumerHelper.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper.SetPrefix ("/");
  consumerHelper.Install (consprods[0]);
  
  ndn::AppHelper consumerHelper1 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper1.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper1.SetAttribute ("StartTime", StringValue ("0.06"));
  consumerHelper1.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper1.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper1.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper1.SetPrefix ("/"); 
  consumerHelper1.Install (consprods[1]);
 
  ndn::AppHelper consumerHelper2 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper2.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper2.SetAttribute ("StartTime", StringValue ("0.09"));
  consumerHelper2.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper2.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper2.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper2.SetPrefix ("/");
  consumerHelper2.Install (consprods[2]); 

  ndn::AppHelper consumerHelper3 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper3.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper3.SetAttribute ("StartTime", StringValue ("0.12"));
  consumerHelper3.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper3.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper3.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper3.SetPrefix ("/");
  consumerHelper3.Install (consprods[3]); 

  ndn::AppHelper consumerHelper4 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper4.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper4.SetAttribute ("StartTime", StringValue ("0.15"));
  consumerHelper4.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper4.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper4.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper4.SetPrefix ("/");
  consumerHelper4.Install (consprods[4]); 

  ndn::AppHelper consumerHelper5 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper5.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper5.SetAttribute ("StartTime", StringValue ("0.18"));
  consumerHelper5.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper5.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper5.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper5.SetPrefix ("/");
  consumerHelper5.Install (consprods[5]); 

  ndn::AppHelper consumerHelper6 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper6.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper6.SetAttribute ("StartTime", StringValue ("0.21"));
  consumerHelper6.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper6.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper6.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper6.SetPrefix ("/");
  consumerHelper6.Install (consprods[6]); 

  ndn::AppHelper consumerHelper7 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper7.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper7.SetAttribute ("StartTime", StringValue ("0.24"));
  consumerHelper7.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper7.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper7.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper7.SetPrefix ("/");
  consumerHelper7.Install (consprods[7]); 

  ndn::AppHelper consumerHelper8 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper8.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper8.SetAttribute ("StartTime", StringValue ("0.27"));
  consumerHelper8.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper8.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper8.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper8.SetPrefix ("/");
  consumerHelper8.Install (consprods[8]); 

  ndn::AppHelper consumerHelper9 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper9.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper9.SetAttribute ("StartTime", StringValue ("0.30"));
  consumerHelper9.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper9.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper9.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper9.SetPrefix ("/");
  consumerHelper9.Install (consprods[9]); 

  ndn::AppHelper consumerHelper10 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper10.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper10.SetAttribute ("StartTime", StringValue ("0.33"));
  consumerHelper10.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper10.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper10.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper10.SetPrefix ("/");
  consumerHelper10.Install (consprods[10]); 

  ndn::AppHelper consumerHelper11 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper11.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper11.SetAttribute ("StartTime", StringValue ("0.36"));
  consumerHelper11.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper11.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper11.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper11.SetPrefix ("/");
  consumerHelper11.Install (consprods[11]); 

  ndn::AppHelper consumerHelper12 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper12.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper12.SetAttribute ("StartTime", StringValue ("0.39"));
  consumerHelper12.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper12.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper12.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper12.SetPrefix ("/");
  consumerHelper12.Install (consprods[12]); 

  ndn::AppHelper consumerHelper13 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper13.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper13.SetAttribute ("StartTime", StringValue ("0.42"));
  consumerHelper13.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper13.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper13.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper13.SetPrefix ("/");
  consumerHelper13.Install (consprods[13]); 

  ndn::AppHelper consumerHelper14 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper14.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper14.SetAttribute ("StartTime", StringValue ("0.45"));
  consumerHelper14.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper14.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper14.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper14.SetPrefix ("/");
  consumerHelper14.Install (consprods[14]); 

  ndn::AppHelper consumerHelper15 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper15.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper15.SetAttribute ("StartTime", StringValue ("0.48"));
  consumerHelper15.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper15.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper15.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper15.SetPrefix ("/");
  consumerHelper15.Install (consprods[15]); 

  ndn::AppHelper consumerHelper16 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper16.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper16.SetAttribute ("StartTime", StringValue ("0.51"));
  consumerHelper16.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper16.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper16.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper16.SetPrefix ("/");
  consumerHelper16.Install (consprods[16]); 

  ndn::AppHelper consumerHelper17 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper17.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper17.SetAttribute ("StartTime", StringValue ("0.54"));
  consumerHelper17.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper17.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper17.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper17.SetPrefix ("/");
  consumerHelper17.Install (consprods[17]); 

  ndn::AppHelper consumerHelper18 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper18.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper18.SetAttribute ("StartTime", StringValue ("0.57"));
  consumerHelper18.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper18.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper18.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper18.SetPrefix ("/");
  consumerHelper18.Install (consprods[18]); 

  ndn::AppHelper consumerHelper19 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper19.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper19.SetAttribute ("StartTime", StringValue ("0.60"));
  consumerHelper19.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper19.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper19.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper19.SetPrefix ("/");
  consumerHelper19.Install (consprods[19]); 

  ndn::AppHelper consumerHelper20 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper20.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper20.SetAttribute ("StartTime", StringValue ("0.63"));
  consumerHelper20.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper20.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper20.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper20.SetPrefix ("/");
  consumerHelper20.Install (consprods[20]);

  ndn::AppHelper consumerHelper21 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper21.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper21.SetAttribute ("StartTime", StringValue ("0.66"));
  consumerHelper21.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper21.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper21.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper21.SetPrefix ("/");
  consumerHelper21.Install (consprods[21]);

  ndn::AppHelper consumerHelper22 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper22.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper22.SetAttribute ("StartTime", StringValue ("0.69"));
  consumerHelper22.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper22.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper22.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper22.SetPrefix ("/");
  consumerHelper22.Install (consprods[22]);

  ndn::AppHelper consumerHelper23 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper23.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper23.SetAttribute ("StartTime", StringValue ("0.72"));
  consumerHelper23.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper23.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper23.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper23.SetPrefix ("/");
  consumerHelper23.Install (consprods[23]);

  ndn::AppHelper consumerHelper24 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper24.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper24.SetAttribute ("StartTime", StringValue ("0.75"));
  consumerHelper24.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper24.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper24.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper24.SetPrefix ("/");
  consumerHelper24.Install (consprods[24]);

  ndn::AppHelper consumerHelper25 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper25.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper25.SetAttribute ("StartTime", StringValue ("0.78"));
  consumerHelper25.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper25.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper25.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper25.SetPrefix ("/");
  consumerHelper25.Install (consprods[25]);

  ndn::AppHelper consumerHelper26 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper26.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper26.SetAttribute ("StartTime", StringValue ("0.81"));
  consumerHelper26.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper26.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper26.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper26.SetPrefix ("/");
  consumerHelper26.Install (consprods[26]);

  ndn::AppHelper consumerHelper27 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper27.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper27.SetAttribute ("StartTime", StringValue ("0.84"));
  consumerHelper27.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper27.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper27.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper27.SetPrefix ("/");
  consumerHelper27.Install (consprods[27]);

  ndn::AppHelper consumerHelper28 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper28.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper28.SetAttribute ("StartTime", StringValue ("0.87"));
  consumerHelper28.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper28.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper28.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper28.SetPrefix ("/");
  consumerHelper28.Install (consprods[28]);

  ndn::AppHelper consumerHelper29 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper29.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper29.SetAttribute ("StartTime", StringValue ("0.90"));
  consumerHelper29.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper29.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper29.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper29.SetPrefix ("/");
  consumerHelper29.Install (consprods[29]);

  ndn::AppHelper consumerHelper30 ("ns3::ndn::ConsumerZipfMandelbrot39");
  
  consumerHelper30.SetAttribute ("Frequency", StringValue ("0.032")); // 0.032 interests a second
  consumerHelper30.SetAttribute ("StartTime", StringValue ("0.93"));
  consumerHelper30.SetAttribute ("StopTime", StringValue ("25000.0"));
  consumerHelper30.SetAttribute ("Randomize", StringValue ("exponential"));
  consumerHelper30.SetAttribute ("NumberOfContents", StringValue ("10000")); // Content Space
  consumerHelper30.SetPrefix ("/");
  consumerHelper30.Install (consprods[30]);

  ndn::AppHelper producerHelper ("ns3::ndn::Producer");
  producerHelper.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper.SetPrefix ("/8");
  producerHelper.Install (consprods[0]);

  ndn::AppHelper producerHelper1 ("ns3::ndn::Producer");
  producerHelper1.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper1.SetPrefix ("/9");
  producerHelper1.Install (consprods[1]);

  ndn::AppHelper producerHelper2 ("ns3::ndn::Producer");
  producerHelper2.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper2.SetPrefix ("/10");
  producerHelper2.Install (consprods[2]);

  ndn::AppHelper producerHelper3 ("ns3::ndn::Producer");
  producerHelper3.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper3.SetPrefix ("/11");
  producerHelper3.Install (consprods[3]);

  ndn::AppHelper producerHelper4 ("ns3::ndn::Producer");
  producerHelper4.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper4.SetPrefix ("/12");
  producerHelper4.Install (consprods[4]);

  ndn::AppHelper producerHelper5 ("ns3::ndn::Producer");
  producerHelper5.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper5.SetPrefix ("/13");
  producerHelper5.Install (consprods[5]);

  ndn::AppHelper producerHelper6 ("ns3::ndn::Producer");
  producerHelper6.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper6.SetPrefix ("/14");
  producerHelper6.Install (consprods[6]);

  ndn::AppHelper producerHelper7 ("ns3::ndn::Producer");
  producerHelper7.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper7.SetPrefix ("/15");
  producerHelper7.Install (consprods[7]);

  ndn::AppHelper producerHelper8 ("ns3::ndn::Producer");
  producerHelper8.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper8.SetPrefix ("/16");
  producerHelper8.Install (consprods[8]);

  ndn::AppHelper producerHelper9 ("ns3::ndn::Producer");
  producerHelper9.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper9.SetPrefix ("/17");
  producerHelper9.Install (consprods[9]);

  ndn::AppHelper producerHelper10 ("ns3::ndn::Producer");
  producerHelper10.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper10.SetPrefix ("/18");
  producerHelper10.Install (consprods[10]);

  ndn::AppHelper producerHelper11 ("ns3::ndn::Producer");
  producerHelper11.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper11.SetPrefix ("/19");
  producerHelper11.Install (consprods[11]);

  ndn::AppHelper producerHelper12 ("ns3::ndn::Producer");
  producerHelper12.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper12.SetPrefix ("/20");
  producerHelper12.Install (consprods[12]);

  ndn::AppHelper producerHelper13 ("ns3::ndn::Producer");
  producerHelper13.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper13.SetPrefix ("/21");
  producerHelper13.Install (consprods[13]);

  ndn::AppHelper producerHelper14 ("ns3::ndn::Producer");
  producerHelper14.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper14.SetPrefix ("/22");
  producerHelper14.Install (consprods[14]);

  ndn::AppHelper producerHelper15 ("ns3::ndn::Producer");
  producerHelper15.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper15.SetPrefix ("/23");
  producerHelper15.Install (consprods[15]);

  ndn::AppHelper producerHelper16 ("ns3::ndn::Producer");
  producerHelper16.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper16.SetPrefix ("/24");
  producerHelper16.Install (consprods[16]); 

  ndn::AppHelper producerHelper17 ("ns3::ndn::Producer");
  producerHelper17.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper17.SetPrefix ("/25");
  producerHelper17.Install (consprods[17]);

  ndn::AppHelper producerHelper18 ("ns3::ndn::Producer");
  producerHelper18.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper18.SetPrefix ("/26");
  producerHelper18.Install (consprods[18]); 

  ndn::AppHelper producerHelper19 ("ns3::ndn::Producer");
  producerHelper19.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper19.SetPrefix ("/27");
  producerHelper19.Install (consprods[19]);

  ndn::AppHelper producerHelper20 ("ns3::ndn::Producer");
  producerHelper20.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper20.SetPrefix ("/28");
  producerHelper20.Install (consprods[20]);

  ndn::AppHelper producerHelper21 ("ns3::ndn::Producer");
  producerHelper21.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper21.SetPrefix ("/29");
  producerHelper21.Install (consprods[21]); 

  ndn::AppHelper producerHelper22 ("ns3::ndn::Producer");
  producerHelper22.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper22.SetPrefix ("/30");
  producerHelper22.Install (consprods[22]); 

  ndn::AppHelper producerHelper23 ("ns3::ndn::Producer");
  producerHelper23.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper23.SetPrefix ("/31");
  producerHelper23.Install (consprods[23]);

  ndn::AppHelper producerHelper24 ("ns3::ndn::Producer");
  producerHelper24.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper24.SetPrefix ("/32");
  producerHelper24.Install (consprods[24]); 

  ndn::AppHelper producerHelper25 ("ns3::ndn::Producer");
  producerHelper25.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper25.SetPrefix ("/33");
  producerHelper25.Install (consprods[25]); 

  ndn::AppHelper producerHelper26 ("ns3::ndn::Producer");
  producerHelper26.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper26.SetPrefix ("/34");
  producerHelper26.Install (consprods[26]); 

  ndn::AppHelper producerHelper27 ("ns3::ndn::Producer");
  producerHelper27.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper27.SetPrefix ("/35");
  producerHelper27.Install (consprods[27]); 

  ndn::AppHelper producerHelper28 ("ns3::ndn::Producer");
  producerHelper28.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper28.SetPrefix ("/36");
  producerHelper28.Install (consprods[28]); 

  ndn::AppHelper producerHelper29 ("ns3::ndn::Producer");
  producerHelper29.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper29.SetPrefix ("/37");
  producerHelper29.Install (consprods[29]); 

  ndn::AppHelper producerHelper30 ("ns3::ndn::Producer");
  producerHelper30.SetAttribute ("PayloadSize", StringValue("1024"));  
  producerHelper30.SetPrefix ("/38");
  producerHelper30.Install (consprods[30]); 

  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ccnxGlobalRoutingHelper;
  ccnxGlobalRoutingHelper.InstallAll ();

  //Calculate and install FIBs
  ccnxGlobalRoutingHelper.AddOrigins ("/8", consprods[0]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/9", consprods[1]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/10", consprods[2]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/11", consprods[3]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/12", consprods[4]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/13", consprods[5]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/14", consprods[6]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/15", consprods[7]);
  ccnxGlobalRoutingHelper.AddOrigins ("/16", consprods[8]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/17", consprods[9]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/18", consprods[10]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/19", consprods[11]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/20", consprods[12]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/21", consprods[13]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/22", consprods[14]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/23", consprods[15]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/24", consprods[16]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/25", consprods[17]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/26", consprods[18]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/27", consprods[19]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/28", consprods[20]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/29", consprods[21]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/30", consprods[22]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/31", consprods[23]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/32", consprods[24]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/33", consprods[25]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/34", consprods[26]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/35", consprods[27]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/36", consprods[28]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/37", consprods[29]); 
  ccnxGlobalRoutingHelper.AddOrigins ("/38", consprods[30]); 
 
  ccnxGlobalRoutingHelper.CalculateRoutes ();

  Simulator::Stop (Seconds (35000.0));

  ndn::AppDelayTracer::InstallAll ("app-delays-trace.txt");
  ndn::CsTracer::InstallAll ("cs-trace.txt", Seconds (34999.0));  
  
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
