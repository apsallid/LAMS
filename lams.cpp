#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <Event.hh>
#include <Intensity.hh>
// #include <Time.hh>
#include <AnalyzePhd.hh>
#include <BetaCalculation.hh>
#include <Cycle.hh>
#include <Led.hh>
#include "TH2F.h"
#include "TFile.h"
#include <DataReader.hh>
#include <BuildLAMPSEvent.hh>
#include <MonitorPhd.hh>
#include <TransmissionLength.hh>



int main(int argc, char **argv)
{ 
  //The user before a run should set the following parameters:
  //1. TimeStart -> In the start of main. 
  //The time in second that we start monitor and analysis of events.
  //2. TimeEnd -> In the start of main. 
  //The time in second that we stop monitor and analysis of events.
  //3. DistancesToBeProccessed -> In the start of main. 
  //The different distances that the measurements are taken.
  //4. Threshold -> In the start of main. 
  //Below this parameter the events are disgarded.
  //5. maxpc383nm -> In the start of AnalyzePhd::analysisph1 and AnalyzePhd::analysisph2.
  // This defines the boundaries of the leds plateau. There is one parameter for every led. 
  //6. maxpc400nm -> In the start of AnalyzePhd::analysisph1 and AnalyzePhd::analysisph2.
  //7. maxpc470nm -> In the start of AnalyzePhd::analysisph1 and AnalyzePhd::analysisph2.
  //8. maxpc525nm -> In the start of AnalyzePhd::analysisph1 and AnalyzePhd::analysisph2.
  //9. ledoncriticalvalueph1 -> In the start of AnalyzePhd::analysisph1. 
  //Parameter that defines if a led is on. Above this the led is on and below the led is off. 
  //10. ledoncriticalvalueph2 -> In the start of AnalyzePhd::analysisph2. Same as 9. for the second photodiode. 
  //11. clockcriticalvalueph1 -> In the start of AnalyzePhd::analysisph1.
  // Parameter that causes the program to understand that a new cycle is about to start.
  //12. clockcriticalvalueph2 -> In the start of AnalyzePhd::analysisph2. Same as 11. for the second photodiode. 
  //13. The bool parameters in the start of main. Bool parameters that 
  // gives the freedom to monitor the data, build event object, analyze the data or calculate beta.

  // To programma gia na treksei prepei aparaitita na yparxei sto antistixo folder toulaxiston ena arxeio txt me 
  // ta dedomena. Auto to arxeio prepei na einai tis morfis: LAMS_dis10.txt gia ta deka metra, 
  // LAMS_dis15.txt gia ta dekapente metra,LAMS_dis17.txt gia ta dekaepta metra,LAMS_dis22.txt gia ta eikosidio metra.
  // Episis, ta periexomena tou ka8e arxeiou prepei na exei treis stiles kai ka8e mia stili na periexei 
  // dekaeksadikous arithmous. Stin prwti stili einai ena counter pou auksanei kati ena ka8e 256 grammes. 
  // Xrisimopoieitai gia na elex8ei an exoun xa8ei gegonota. H deuteri stili einai ta dedomena apo tin 
  // prwti photodiodo kai i triti stili dinei ta dedomena gia tin deuteri photodiodo. 

  // Apo tin stigmi pou to programma treksei paragei ta eksis root files:
  // 1. LAMS_dis*.root
  // opou * einai i apostasi stin opoia anaferetai to file, diladi 10,15,17,22. 
  // Periexei dio plot. Einai ousiastika to monitor twn data gia tis dio photodiodous. Ena plot gia ka8e photodiodo. 
  // 2. Phd1_Check_*_m.root
  // opou * einai i apostasi stin opoia anaferetai to file, diladi 10,15,17,22. 
  // Se auto to file briskontai 17 plots pou elegxoun tin prwti photodiodo. 
  // Sigkekrimena, deixnetai o xronos pou anaboun ta led, o xronos enos kiklou oxi mono apo tin arxi tou 
  // alla kai apo tin arxi apo ka8e led, o xronos pou pernaei apo tin stigmi pou sbinei ena led 
  // mexri na anapsei to epomeno kai telos plot pou dinoun to intensity gia ka8e led. 
  // Apo auto to teleutaio plot pairnei kapoios to mean kai to rms kai sinexizei tin analisi. 
  // 3. Phd2_Check_*_m.root
  // omoia me to 2. alla gia tin deuteri photodiodo.  
  // 4. Beta.root
  // Periexei dio plot, ena gia ka8e photodiodo. Apeikonizetai I_L/I_S = f (R_S^2/R_L^2) me simeia gia ola ta leds 
  // etsi wste na elex8ei an exoume tin R^2 simperifora sta test pou eginan ston aera. 
  // 5. BetaHistosPH1.root 
  // Periexei pente plot gia tin prwti photodiodo. Yparxei ena plot gia ka8e ledaki pou dinei tis times tou
  // bita sinarstisi tou DL. An exoun ginei treis apostaseis perimenoume tria simeia, an tesseris apostaseis
  // perimenoume eksi simeia. Akoma periexetai kai to pio simantiko plot tou transmission length sinartisi tou
  // wavelength.Gia na ginei kai gia ta dio source (diladi kai gia ta oxtw miki kimatos) o xristis exei dio 
  // epiloges. Eite 8a treksei kai tis dio source kai 8a kanei draw same apo to root eite 8a paei stin mia 
  // source apo tis dio kai exontas ta apotelesmata tis allis 8a ta kanei fill me to xeri. 
  // 6. BetaHistosPH2.root 
  // omoia me 5 gia tin deuteri photodiodo. 

  bool MonitorPhotodiodes = true;
  bool build_lamps_event = true;
  bool AnalyzePhotodiodes = true;
  bool CalculateBeta = true;
  
//   int TimeStart = 0; int TimeEnd = 1250; // Give the time window in sec 

//   std::vector<Time> TimeStart;
//   std::vector<Time> TimeEnd;
  //4100 m
//   TimeStart.push_back(1,10,4100,7720);
//   TimeStart.push_back(1,15,4100,6240);
//   TimeStart.push_back(1,17,4100,6240);
//   TimeStart.push_back(1,22,4100,6120);

//   TimeEnd.push_back(1,10,4100,8340);
//   TimeEnd.push_back(1,15,4100,7440);
//   TimeEnd.push_back(1,17,4100,7440);
//   TimeEnd.push_back(1,22,4100,7320);

//   TimeStart.push_back(2,10,4100,5560);
//   TimeStart.push_back(2,15,4100,6600);
//   TimeStart.push_back(2,17,4100,5700);
//   TimeStart.push_back(2,22,4100,5810);

//   TimeEnd.push_back(2,10,4100,6780);
//   TimeEnd.push_back(2,15,4100,7800);
//   TimeEnd.push_back(2,17,4100,6900);
//   TimeEnd.push_back(2,22,4100,7020);
//   //3400 m
//   TimeStart.push_back(1,10,3400,9820);
//   TimeStart.push_back(1,15,3400,8340);
//   TimeStart.push_back(1,17,3400,8460);
//   TimeStart.push_back(1,22,3400,8220);

//   TimeEnd.push_back(1,10,3400,10440);
//   TimeEnd.push_back(1,15,3400,8940);
//   TimeEnd.push_back(1,17,3400,9060);
//   TimeEnd.push_back(1,22,3400,8820);

//   TimeStart.push_back(2,10,3400,7620);
//   TimeStart.push_back(2,15,3400,8820);
//   TimeStart.push_back(2,17,3400,7800);
//   TimeStart.push_back(2,22,3400,8400);

//   TimeEnd.push_back(2,10,3400,8220);
//   TimeEnd.push_back(2,15,3400,9420);
//   TimeEnd.push_back(2,17,3400,8400);
//   TimeEnd.push_back(2,22,3400,9000);
//   //2500 m
//   TimeStart.push_back(1,10,2500,11570);
//   TimeStart.push_back(1,15,2500,10080);
//   TimeStart.push_back(1,17,2500,10260);
//   TimeStart.push_back(1,22,2500,9900);

//   TimeEnd.push_back(1,10,2500,12180);
//   TimeEnd.push_back(1,15,2500,10680);
//   TimeEnd.push_back(1,17,2500,10860);
//   TimeEnd.push_back(1,22,2500,10500);

//   TimeStart.push_back(2,10,2500,9240);
//   TimeStart.push_back(2,15,2500,10680);
//   TimeStart.push_back(2,17,2500,9360);
//   TimeStart.push_back(2,22,2500,10200);

//   TimeEnd.push_back(2,10,2500,9840);
//   TimeEnd.push_back(2,15,2500,11280);
//   TimeEnd.push_back(2,17,2500,9960);
//   TimeEnd.push_back(2,22,2500,10800);

  std::map<int, std::map<int, std::map<int,int> > > TimeStart; //TimeStart[dep][source][distance]
  std::map<int, std::map<int, std::map<int,int> > > TimeEnd; //TimeEnd[dep][source][distance]
// 2500 m
  TimeStart[2500][1][10]= 11570;
  TimeStart[2500][1][15]= 10080;
  TimeStart[2500][1][17]= 10260;
  TimeStart[2500][1][22]= 9900;
  TimeEnd[2500][1][10]= 12180;
  TimeEnd[2500][1][15]= 10680;
  TimeEnd[2500][1][17]= 10860;
  TimeEnd[2500][1][22]= 10500;
  TimeStart[2500][2][10]= 9240;
  TimeStart[2500][2][15]= 10680;
  TimeStart[2500][2][17]= 9360;
  TimeStart[2500][2][22]= 10200;
  TimeEnd[2500][2][10]= 9840;
  TimeEnd[2500][2][15]= 11280;
  TimeEnd[2500][2][17]= 9960;
  TimeEnd[2500][2][22]= 10800;
//3400 m
  TimeStart[3400][1][10]= 9820;
  TimeStart[3400][1][15]= 8340;
  TimeStart[3400][1][17]= 8460;
  TimeStart[3400][1][22]= 8220;
  TimeEnd[3400][1][10]= 10440;
  TimeEnd[3400][1][15]= 8940;
  TimeEnd[3400][1][17]= 9060;
  TimeEnd[3400][1][22]= 8820;
  TimeStart[3400][2][10]= 7620;
  TimeStart[3400][2][15]= 8810;
  TimeStart[3400][2][17]= 7800;
  TimeStart[3400][2][22]= 8400;
  TimeEnd[3400][2][10]= 8220;
  TimeEnd[3400][2][15]= 9420;
  TimeEnd[3400][2][17]= 8400;
  TimeEnd[3400][2][22]= 9000;
  //4100 m
  TimeStart[4100][1][10]= 7710; 
  TimeStart[4100][1][15]= 6240;
  TimeStart[4100][1][17]= 6240;
  TimeStart[4100][1][22]= 6120;
  TimeEnd[4100][1][10]= 8340;
  TimeEnd[4100][1][15]= 7440;
  TimeEnd[4100][1][17]= 7440;
  TimeEnd[4100][1][22]= 7320;
  TimeStart[4100][2][10]= 5560; 
  TimeStart[4100][2][15]= 6600;
  TimeStart[4100][2][17]= 5700;
  TimeStart[4100][2][22]= 5810;
  TimeEnd[4100][2][10]= 6780;
  TimeEnd[4100][2][15]= 7800;
  TimeEnd[4100][2][17]= 6900;
  TimeEnd[4100][2][22]= 7020;

//500-1000
  TimeStart[5001000][1][10]= 2340; 
  TimeStart[5001000][1][15]= 2040;
  TimeStart[5001000][1][17]= 1800;
  TimeStart[5001000][1][22]= 1620;

  TimeEnd[5001000][1][10]= 2940;
  TimeEnd[5001000][1][15]= 2640;
  TimeEnd[5001000][1][17]= 2460;
  TimeEnd[5001000][1][22]= 2220;

  TimeStart[5001000][2][10]= 1500; 
  TimeStart[5001000][2][15]= 1860;
  TimeStart[5001000][2][17]= 1260;
  TimeStart[5001000][2][22]= 1740;

  TimeEnd[5001000][2][10]= 2100;
  TimeEnd[5001000][2][15]= 2580;
  TimeEnd[5001000][2][17]= 1860;
  TimeEnd[5001000][2][22]= 2160;

//1000-1500
  TimeStart[10001500][1][10]= 2940; 
  TimeStart[10001500][1][15]= 2640;
  TimeStart[10001500][1][17]= 2430;
  TimeStart[10001500][1][22]= 2220;

  TimeEnd[10001500][1][10]= 3660;
  TimeEnd[10001500][1][15]= 3240;
  TimeEnd[10001500][1][17]= 2940;
  TimeEnd[10001500][1][22]= 2820;

  TimeStart[10001500][2][10]= 2100; 
  TimeStart[10001500][2][15]= 2580;
  TimeStart[10001500][2][17]= 1860;
  TimeStart[10001500][2][22]= 2150;

  TimeEnd[10001500][2][10]= 2700;
  TimeEnd[10001500][2][15]= 3120;
  TimeEnd[10001500][2][17]= 2460;
  TimeEnd[10001500][2][22]= 2640;

//1500-2000
  TimeStart[15002000][1][10]= 3660; 
  TimeStart[15002000][1][15]= 3240;
  TimeStart[15002000][1][17]= 2930;
  TimeStart[15002000][1][22]= 2820;

  TimeEnd[15002000][1][10]= 4380;
  TimeEnd[15002000][1][15]= 3900;
  TimeEnd[15002000][1][17]= 3540;
  TimeEnd[15002000][1][22]= 3420;

  TimeStart[15002000][2][10]= 2700; 
  TimeStart[15002000][2][15]= 3120;
  TimeStart[15002000][2][17]= 2460;
  TimeStart[15002000][2][22]= 2640;

  TimeEnd[15002000][2][10]= 3300;
  TimeEnd[15002000][2][15]= 3720;
  TimeEnd[15002000][2][17]= 3060;
  TimeEnd[15002000][2][22]= 3180;

//2000-2500
  TimeStart[20002500][1][10]= 4380; 
  TimeStart[20002500][1][15]= 3900;
  TimeStart[20002500][1][17]= 3540;
  TimeStart[20002500][1][22]= 3420;

  TimeEnd[20002500][1][10]= 5000;
  TimeEnd[20002500][1][15]= 4320;
  TimeEnd[20002500][1][17]= 4440;
  TimeEnd[20002500][1][22]= 3960;

  TimeStart[20002500][2][10]= 3300; 
  TimeStart[20002500][2][15]= 3720;
  TimeStart[20002500][2][17]= 3060;
  TimeStart[20002500][2][22]= 3180;

  TimeEnd[20002500][2][10]= 3600;
  TimeEnd[20002500][2][15]= 4320;
  TimeEnd[20002500][2][17]= 3600;
  TimeEnd[20002500][2][22]= 3600;

//2500-3400
  TimeStart[25003400][1][10]= 5000; 
  TimeStart[25003400][1][15]= 4320;
  TimeStart[25003400][1][17]= 4440;
  TimeStart[25003400][1][22]= 3960;
  TimeEnd[25003400][1][10]= 6600;
  TimeEnd[25003400][1][15]= 5400;
  TimeEnd[25003400][1][17]= 5040;
  TimeEnd[25003400][1][22]= 5100;

  TimeStart[25003400][2][10]= 3600; 
  TimeStart[25003400][2][15]= 4290;
  TimeStart[25003400][2][17]= 3600;
  TimeStart[25003400][2][22]= 3600;

  TimeEnd[25003400][2][10]= 4740;
  TimeEnd[25003400][2][15]= 5300;
  TimeEnd[25003400][2][17]= 4860;
  TimeEnd[25003400][2][22]= 4800;

//3400-4100
  TimeStart[34004100][1][10]= 6600; 
  TimeStart[34004100][1][15]= 5400;
  TimeStart[34004100][1][17]= 5040;
  TimeStart[34004100][1][22]= 5090;

  TimeEnd[34004100][1][10]= 7740;
  TimeEnd[34004100][1][15]= 6240;
  TimeEnd[34004100][1][17]= 6240;
  TimeEnd[34004100][1][22]= 6120;

  TimeStart[34004100][2][10]= 4740; 
  TimeStart[34004100][2][15]= 5580;
  TimeStart[34004100][2][17]= 4860;
  TimeStart[34004100][2][22]= 4800;

  TimeEnd[34004100][2][10]= 5580;
  TimeEnd[34004100][2][15]= 6600;
  TimeEnd[34004100][2][17]= 5700;
  TimeEnd[34004100][2][22]= 5820;

//4100-3400
  TimeStart[41003400][1][10]= 8340; 
  TimeStart[41003400][1][15]= 7440;
  TimeStart[41003400][1][17]= 7440;
  TimeStart[41003400][1][22]= 7320;

  TimeEnd[41003400][1][10]= 9840;
  TimeEnd[41003400][1][15]= 8340;
  TimeEnd[41003400][1][17]= 8460;
  TimeEnd[41003400][1][22]= 8220;

  TimeStart[41003400][2][10]= 6780; 
  TimeStart[41003400][2][15]= 7800;
  TimeStart[41003400][2][17]= 6900;
  TimeStart[41003400][2][22]= 7020;

  TimeEnd[41003400][2][10]= 7620;
  TimeEnd[41003400][2][15]= 8820;
  TimeEnd[41003400][2][17]= 7800;
  TimeEnd[41003400][2][22]= 8400;
//3400-2500
  TimeStart[34002500][1][10]= 10440; 
  TimeStart[34002500][1][15]= 8940;
  TimeStart[34002500][1][17]= 9060;
  TimeStart[34002500][1][22]= 8820;

  TimeEnd[34002500][1][10]= 11580;
  TimeEnd[34002500][1][15]= 10080;
  TimeEnd[34002500][1][17]= 10260;
  TimeEnd[34002500][1][22]= 9900;

  TimeStart[34002500][2][10]= 8220; 
  TimeStart[34002500][2][15]= 9420;
  TimeStart[34002500][2][17]= 8400;
  TimeStart[34002500][2][22]= 9000;

  TimeEnd[34002500][2][10]= 9240;
  TimeEnd[34002500][2][15]= 10680;
  TimeEnd[34002500][2][17]= 9360;
  TimeEnd[34002500][2][22]= 10200;
//2500-2000
  TimeStart[25002000][1][10]= 12180; 
  TimeStart[25002000][1][15]= 10680;
  TimeStart[25002000][1][17]= 10860;
  TimeStart[25002000][1][22]= 10500;

  TimeEnd[25002000][1][10]= 12600;
  TimeEnd[25002000][1][15]= 11340;
  TimeEnd[25002000][1][17]= 11580;
  TimeEnd[25002000][1][22]= 11100;

  TimeStart[25002000][2][10]= 9840; 
  TimeStart[25002000][2][15]= 11280;
  TimeStart[25002000][2][17]= 9960;
  TimeStart[25002000][2][22]= 10800;

  TimeEnd[25002000][2][10]= 10620;
  TimeEnd[25002000][2][15]= 11880;
  TimeEnd[25002000][2][17]= 10320;
  TimeEnd[25002000][2][22]= 11400;
//2000-1500
  TimeStart[20001500][1][10]= 12590; 
  TimeStart[20001500][1][15]= 10680;
  TimeStart[20001500][1][17]= 11580;
  TimeStart[20001500][1][22]= 11100;

  TimeEnd[20001500][1][10]= 13200;
  TimeEnd[20001500][1][15]= 11520;
  TimeEnd[20001500][1][17]= 11900;
  TimeEnd[20001500][1][22]= 11700;

  TimeStart[20001500][2][10]= 10620; 
  TimeStart[20001500][2][15]= 11880;
  TimeStart[20001500][2][17]= 10320;
  TimeStart[20001500][2][22]= 11400;

  TimeEnd[20001500][2][10]= 11160;
  TimeEnd[20001500][2][15]= 12540;
  TimeEnd[20001500][2][17]= 11160;
  TimeEnd[20001500][2][22]= 12000;
//1500-1000
  TimeStart[15001000][1][10]= 13190; 
  TimeStart[15001000][1][15]= 11820;
  TimeStart[15001000][1][17]= 11890;
  TimeStart[15001000][1][22]= 11700;

  TimeEnd[15001000][1][10]= 13800;
  TimeEnd[15001000][1][15]= 12240;
  TimeEnd[15001000][1][17]= 12380;
  TimeEnd[15001000][1][22]= 12240;

  TimeStart[15001000][2][10]= 11160; 
  TimeStart[15001000][2][15]= 12540;
  TimeStart[15001000][2][17]= 11160;
  TimeStart[15001000][2][22]= 12000;

  TimeEnd[15001000][2][10]= 11820;
  TimeEnd[15001000][2][15]= 13140;
  TimeEnd[15001000][2][17]= 11760;
  TimeEnd[15001000][2][22]= 12720;
//1000-500
  TimeStart[1000500][1][10]= 13200; 
  TimeStart[1000500][1][15]= 11820;
  TimeStart[1000500][1][17]= 11890;
  TimeStart[1000500][1][22]= 11700;

  TimeEnd[1000500][1][10]= 13800;
  TimeEnd[1000500][1][15]= 12240;
  TimeEnd[1000500][1][17]= 12380;
  TimeEnd[1000500][1][22]= 12240;

  TimeStart[1000500][2][10]= 11160; 
  TimeStart[1000500][2][15]= 12540;
  TimeStart[1000500][2][17]= 11160;
  TimeStart[1000500][2][22]= 12000;

  TimeEnd[1000500][2][10]= 11820;
  TimeEnd[1000500][2][15]= 13140;
  TimeEnd[1000500][2][17]= 11760;
  TimeEnd[1000500][2][22]= 12720;




  //Sources that will be processed
  std::vector<int> SourcesToBeProccessed;

  SourcesToBeProccessed.push_back(1);
  SourcesToBeProccessed.push_back(2);

  //Depths that will be processed
  std::vector<int> DepthsToBeProccessed;

  DepthsToBeProccessed.push_back(4100);
  DepthsToBeProccessed.push_back(3400);
  DepthsToBeProccessed.push_back(2500);
  DepthsToBeProccessed.push_back(5001000);
  DepthsToBeProccessed.push_back(10001500);
  DepthsToBeProccessed.push_back(15002000);
  DepthsToBeProccessed.push_back(20002500);
  DepthsToBeProccessed.push_back(25003400);
  DepthsToBeProccessed.push_back(34004100);
  DepthsToBeProccessed.push_back(25002000);
  DepthsToBeProccessed.push_back(34002500);
  DepthsToBeProccessed.push_back(41003400);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);
  DepthsToBeProccessed.push_back(20001500);


  //Distances that will be processed
  std::vector<int> DistancesToBeProccessed;

    DistancesToBeProccessed.push_back(10);
    DistancesToBeProccessed.push_back(15);
    DistancesToBeProccessed.push_back(17); 
    DistancesToBeProccessed.push_back(22);
  
  // These parameters define the first events that will be thrown and the total number that will be processed
//   int FirstEventsToDisregard = 100*TimeStart; int TotalEvents=100*(TimeEnd-TimeStart);
  // This parameter is the user defined threshold
  int Threshold = 5;
  // Beta Related Parameters
  std::map<int,std::map<int, std::vector<Intensity> > >phdiod1int;
  std::map<int,std::map<int, std::vector<Intensity> > >phdiod2int;

  std::map<int,std::map<int, double> > led383int1; std::map<int,std::map<int, double> > led383intrms1;
  std::map<int,std::map<int, double> > led400int1; std::map<int,std::map<int, double> > led400intrms1;
  std::map<int,std::map<int, double> > led470int1; std::map<int,std::map<int, double> > led470intrms1;
  std::map<int,std::map<int, double> > led525int1; std::map<int,std::map<int, double> > led525intrms1;

  std::map<int,std::map<int, double> > led383int2; std::map<int,std::map<int, double> > led383intrms2;
  std::map<int,std::map<int, double> > led400int2; std::map<int,std::map<int, double> > led400intrms2;
  std::map<int,std::map<int, double> > led470int2; std::map<int,std::map<int, double> > led470intrms2;  
  std::map<int,std::map<int, double> > led525int2; std::map<int,std::map<int, double> > led525intrms2;

  std::map<int,std::map<int, double> > led375int1; std::map<int,std::map<int, double> > led375intrms1;
  std::map<int,std::map<int, double> > led425int1; std::map<int,std::map<int, double> > led425intrms1;
  std::map<int,std::map<int, double> > led450int1; std::map<int,std::map<int, double> > led450intrms1;
  std::map<int,std::map<int, double> > led495int1; std::map<int,std::map<int, double> > led495intrms1;

  std::map<int,std::map<int, double> > led375int2; std::map<int,std::map<int, double> > led375intrms2;
  std::map<int,std::map<int, double> > led425int2; std::map<int,std::map<int, double> > led425intrms2;
  std::map<int,std::map<int, double> > led450int2; std::map<int,std::map<int, double> > led450intrms2;  
  std::map<int,std::map<int, double> > led495int2; std::map<int,std::map<int, double> > led495intrms2;

  // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

  // Loop over Sources
  for (std::vector<int>::iterator sou=SourcesToBeProccessed.begin(); sou!=SourcesToBeProccessed.end(); ++sou) {
 
    // Loop over Distances
    for (std::vector<int>::iterator dis=DistancesToBeProccessed.begin(); dis!=DistancesToBeProccessed.end(); ++dis) {

//       int tmstart; int tmend;
//       for (std::vector<Time>::iterator tms=TimeStart.begin();tms!=TimeStart.end(); ++tms) {
// 	if( (*tms).GetSource()==(*sou) && (*tms).GetDistance()==(*dis)  && (*tms).GetDepth()==(*dep)){
// 	  tmstart=(*tms).GetTimeValue(); 
// 	} 
//       }
//       for (std::vector<Time>::iterator tme=TimeEnd.begin();tme!=TimeEnd.end(); ++tme) {
// 	if( (*tme).GetSource()==(*sou) && (*tme).GetDistance()==(*dis)  && (*tme).GetDepth()==(*dep)){
// 	  tmend=(*tme).GetTimeValue(); 
// 	} 
//       }


      int FirstEventsToDisregard = 100*TimeStart[(*dep)][(*sou)][(*dis)];int TotalEvents = 100*(TimeEnd[(*dep)][(*sou)][(*dis)]-TimeStart[(*dep)][(*sou)][(*dis)]);
//       int FirstEventsToDisregard = 100*tmstart;int TotalEvents = 100*(tmend-tmstart);

      // Build the LAMPS Event Object 
      if (build_lamps_event){
	// Calculate
	BuildLAMPSEvent build_events(  (*sou), (*dis), FirstEventsToDisregard, TotalEvents, Threshold );
	std::vector<Event*> Events = build_events.calculateEvents();


	std::cout<< "Depth " << (*dep) << " Source " << (*sou) << " Distance " << (*dis) << std::endl;	
	std::cout<< "------------------------------------------------------------------------------"<< std::endl;
	std::cout << " TOTAL EVTS " << Events.size() << std::endl;
	
	// 	 for (std::vector<Event*>::iterator e = Events.begin(); e != Events.end(); ++e) {
	// 	     std::cout<< (*e)->GetPhdiode1() << std::endl;
	// 	 }
	
	
 	 // Make Histos
	
	 //Monitor the Data from the Photodiodes
	if (MonitorPhotodiodes){
	  MonitorPhd mnph ( (*dep), (*sou),(*dis) );
	  mnph.monitorwindow(Events,FirstEventsToDisregard,TotalEvents);
	 }
	
	//Analyze the Data from the Photodiodes
	if (AnalyzePhotodiodes){
	  AnalyzePhd anph ( (*dep), (*sou), (*dis),Events);
	  phdiod1int = anph.analysisph1(Threshold,FirstEventsToDisregard,TotalEvents);
	  phdiod2int = anph.analysisph2(Threshold,FirstEventsToDisregard,TotalEvents);
	  anph.phdiffs(Threshold,FirstEventsToDisregard,TotalEvents);
	}
	
	for (std::vector<Intensity>::iterator in = phdiod1int[(*dep)][(*sou)].begin(); in != phdiod1int[(*dep)][(*sou)].end(); ++in ){
	  switch ( (*in).GetWLength() ){
	  case 383: 
	    led383int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led383intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 400: 
	    led400int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led400intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 470: 
	    led470int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led470intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 525: 
	    led525int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led525intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	   case 375: 
	     led375int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led375intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 425: 
	     led425int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led425intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 450: 
	     led450int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led450intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 495: 
	     led495int1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led495intrms1[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	  }
	  
	}
	
	for (std::vector<Intensity>::iterator in = phdiod2int[(*dep)][(*sou)].begin(); in != phdiod2int[(*dep)][(*sou)].end(); ++in ){
	  switch ( (*in).GetWLength() ){
	  case 383: 
	    led383int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led383intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 400: 
	    led400int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led400intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 470: 
	    led470int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led470intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	  case 525: 
	    led525int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	    led525intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	    break;
	   case 375: 
	     led375int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led375intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 425: 
	     led425int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led425intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 450: 
	     led450int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led450intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	   case 495: 
	     led495int2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetMean() ) );
	     led495intrms2[(*dep)].insert( std::map<int,double>::value_type( (*in).GetDistance() , (*in).GetRMS() ) );
	     break;
	  }
	  
	}
	
	
	for (std::vector<Event*>::iterator e = Events.begin(); e != Events.end(); ++e) {
	  // 	   (*e)->print();
	  delete *e;
	}
	Events.clear();
      }
      else {
	//Read         
      }
      
      
          
      
    } // End on loop over Distances
  
  } // End on loop over Sources
  
  }// End on loop over Depths


//   //Calculate and Print Beta and Error Beta
  if (CalculateBeta){
      
    BetaCalculation btcalc;
    btcalc.calculateph1(led383int1,led400int1, led470int1, led525int1,led383intrms1, led400intrms1, led470intrms1, led525intrms1,
			led375int1, led425int1, led450int1, led495int1,led375intrms1, led425intrms1, led450intrms1, led495intrms1 );
    btcalc.calculateph2(led383int2, led400int2, led470int2, led525int2,led383intrms2, led400intrms2, led470intrms2, led525intrms2,
			led375int2, led425int2, led450int2, led495int2,led375intrms2, led425intrms2, led450intrms2, led495intrms2);

    btcalc.calculateallph(led383int1,led400int1, led470int1, led525int1,led383intrms1, led400intrms1, led470intrms1, led525intrms1,
			  led375int1, led425int1, led450int1, led495int1,led375intrms1, led425intrms1, led450intrms1, led495intrms1,
			  led383int2, led400int2, led470int2, led525int2,led383intrms2, led400intrms2, led470intrms2, led525intrms2,
			  led375int2, led425int2, led450int2, led495int2,led375intrms2, led425intrms2, led450intrms2, led495intrms2 );
    
    btcalc.calculateallphanddepth(led383int1,led400int1, led470int1, led525int1,led383intrms1, led400intrms1, led470intrms1, led525intrms1,
			  led375int1, led425int1, led450int1, led495int1,led375intrms1, led425intrms1, led450intrms1, led495intrms1,
			  led383int2, led400int2, led470int2, led525int2,led383intrms2, led400intrms2, led470intrms2, led525intrms2,
			  led375int2, led425int2, led450int2, led495int2,led375intrms2, led425intrms2, led450intrms2, led495intrms2 ); 
    
  }
  


}
