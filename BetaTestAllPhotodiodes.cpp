void BetaCalculation::calculateallphanddepth (std::map<int, std::map<int, double> >& led383int1, std::map<int, std::map<int, double> >& led400int1, std::map<int, std::map<int, double> >& led470int1, std::map<int, std::map<int, double> >& led525int1, std::map<int, std::map<int, double> >& led383intrms1, std::map<int, std::map<int, double> >& led400intrms1, std::map<int, std::map<int, double> >& led470intrms1, std::map<int, std::map<int, double> >& led525intrms1,std::map<int, std::map<int, double> >& led375int1, std::map<int, std::map<int, double> >& led425int1, std::map<int, std::map<int, double> >& led450int1, std::map<int, std::map<int, double> >& led495int1, std::map<int, std::map<int, double> >& led375intrms1, std::map<int, std::map<int, double> >& led425intrms1, std::map<int, std::map<int, double> >& led450intrms1, std::map<int, std::map<int, double> >& led495intrms1,std::map<int, std::map<int, double> >& led383int2, std::map<int, std::map<int, double> >& led400int2, std::map<int, std::map<int, double> >& led470int2, std::map<int, std::map<int, double> >& led525int2 , std::map<int, std::map<int, double> >& led383intrms2, std::map<int, std::map<int, double> >& led400intrms2, std::map<int, std::map<int, double> >& led470intrms2, std::map<int, std::map<int, double> >& led525intrms2,std::map<int, std::map<int, double> >& led375int2, std::map<int, std::map<int, double> >& led425int2, std::map<int, std::map<int, double> >& led450int2, std::map<int, std::map<int, double> >& led495int2, std::map<int, std::map<int, double> >& led375intrms2, std::map<int, std::map<int, double> >& led425intrms2, std::map<int, std::map<int, double> >& led450intrms2, std::map<int, std::map<int, double> >& led495intrms2){



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
  DepthsToBeProccessed.push_back(20001500);
  DepthsToBeProccessed.push_back(15001000);
  DepthsToBeProccessed.push_back(1000500);




  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph1; 
  std::map<int,std::map<double,double> > fitlength400ph1; 
  std::map<int,std::map<double,double> > fitlength470ph1; 
  std::map<int,std::map<double,double> > fitlength525ph1; 
  std::map<int,std::map<double,double> > fitlength375ph1; 
  std::map<int,std::map<double,double> > fitlength425ph1;
  std::map<int,std::map<double,double> > fitlength450ph1; 
  std::map<int,std::map<double,double> > fitlength495ph1;

  std::map<int,std::vector<TransmissionLength> > trlengph1;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph1[(*dep)] = fitbetamethodph1(led383int1[(*dep)],led383intrms1[(*dep)]);
    fitlength400ph1[(*dep)] = fitbetamethodph1(led400int1[(*dep)],led400intrms1[(*dep)]);
    fitlength470ph1[(*dep)] = fitbetamethodph1(led470int1[(*dep)],led470intrms1[(*dep)]);
    fitlength525ph1[(*dep)] = fitbetamethodph1(led525int1[(*dep)],led525intrms1[(*dep)]);
    fitlength375ph1[(*dep)] = fitbetamethodph1(led375int1[(*dep)],led375intrms1[(*dep)]);
    fitlength425ph1[(*dep)] = fitbetamethodph1(led425int1[(*dep)],led425intrms1[(*dep)]);
    fitlength450ph1[(*dep)] = fitbetamethodph1(led450int1[(*dep)],led450intrms1[(*dep)]);
    fitlength495ph1[(*dep)] = fitbetamethodph1(led495int1[(*dep)],led495intrms1[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph1[(*dep)].begin();it!=fitlength383ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph1[(*dep)].begin();it!=fitlength400ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph1[(*dep)].begin();it!=fitlength470ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph1[(*dep)].begin();it!=fitlength525ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph1[(*dep)].begin();it!=fitlength375ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph1[(*dep)].begin();it!=fitlength425ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph1[(*dep)].begin();it!=fitlength450ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph1[(*dep)].begin();it!=fitlength495ph1[(*dep)].end();++it){
   trlengph1[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths


  // Create a file

  std::map<int,std::map<double,double> > fitlength383ph2; 
  std::map<int,std::map<double,double> > fitlength400ph2; 
  std::map<int,std::map<double,double> > fitlength470ph2; 
  std::map<int,std::map<double,double> > fitlength525ph2; 
  std::map<int,std::map<double,double> > fitlength375ph2; 
  std::map<int,std::map<double,double> > fitlength425ph2;
  std::map<int,std::map<double,double> > fitlength450ph2; 
  std::map<int,std::map<double,double> > fitlength495ph2;

  std::map<int,std::vector<TransmissionLength> > trlengph2;

    // Loop over Depths
  for (std::vector<int>::iterator dep=DepthsToBeProccessed.begin(); dep!=DepthsToBeProccessed.end(); ++dep) {

    fitlength383ph2[(*dep)] = fitbetamethodph2(led383int2[(*dep)],led383intrms2[(*dep)]);
    fitlength400ph2[(*dep)] = fitbetamethodph2(led400int2[(*dep)],led400intrms2[(*dep)]);
    fitlength470ph2[(*dep)] = fitbetamethodph2(led470int2[(*dep)],led470intrms2[(*dep)]);
    fitlength525ph2[(*dep)] = fitbetamethodph2(led525int2[(*dep)],led525intrms2[(*dep)]);
    fitlength375ph2[(*dep)] = fitbetamethodph2(led375int2[(*dep)],led375intrms2[(*dep)]);
    fitlength425ph2[(*dep)] = fitbetamethodph2(led425int2[(*dep)],led425intrms2[(*dep)]);
    fitlength450ph2[(*dep)] = fitbetamethodph2(led450int2[(*dep)],led450intrms2[(*dep)]);
    fitlength495ph2[(*dep)] = fitbetamethodph2(led495int2[(*dep)],led495intrms2[(*dep)]);


  for (std::map<double,double>::iterator it =fitlength383ph2[(*dep)].begin();it!=fitlength383ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 383. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength400ph2[(*dep)].begin();it!=fitlength400ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 400. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength470ph2[(*dep)].begin();it!=fitlength470ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 470. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength525ph2[(*dep)].begin();it!=fitlength525ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 525. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength375ph2[(*dep)].begin();it!=fitlength375ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 375. , (*it).first,(*it).second ) );
//    std::cout<< (*it).first << " " <<(*it).second <<std::endl;
  }
  for (std::map<double,double>::iterator it =fitlength425ph2[(*dep)].begin();it!=fitlength425ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 425. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength450ph2[(*dep)].begin();it!=fitlength450ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 450. , (*it).first,(*it).second ) );
  }
  for (std::map<double,double>::iterator it =fitlength495ph2[(*dep)].begin();it!=fitlength495ph2[(*dep)].end();++it){
   trlengph2[(*dep)].push_back( TransmissionLength( 495. , (*it).first,(*it).second ) );
  }

  } // End on loop over Depths

 ///////////////////////////////Transmission Length Sinartisi WaveLength 2500,3400,4100m////////////////////////////////////////////// 
  TCanvas *c3 = new TCanvas("c3");
   
  TGraphErrors *translength4100 = fitbetamethodgrapherrorph1( trleng[4100] );
  translength4100->SetMarkerStyle(20);//circle full 
  translength4100->SetMarkerSize(0.9); 
  translength4100->SetMarkerColor(2);//red  
  translength4100->SetLineColor(2);
  translength4100->Draw("AP");
  c3->Update();

  TGraphErrors *translength3400 = fitbetamethodgrapherrorph1( trleng[3400] );
  translength3400->SetMarkerStyle(29);//star full 
  translength3400->SetMarkerSize(0.9); 
  translength3400->SetMarkerColor(4);//blue  
  translength3400->SetLineColor(4);
  translength3400->Draw("PS");
  c3->Update();

  TGraphErrors *translength2500 = fitbetamethodgrapherrorph1( trleng[2500] );
  translength2500->SetMarkerStyle(22);// triangle full 
  translength2500->SetMarkerSize(0.9); 
  translength2500->SetMarkerColor(8);//green  
  translength2500->SetLineColor(8);
  translength2500->Draw("PS");
  c3->Update();

  TLegend *leg = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg->AddEntry(translength4100,"4100 m","LP");  
  leg->AddEntry(translength3400,"3400 m","LP");  
  leg->AddEntry(translength2500,"2500 m","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" Depth ");
                                            // use "f" for a box
  leg->Draw("PS");
  c3->Update();

  translength4100 -> SetTitle( "  	PRELIMINARY. April 2008 NOT FOR DISTRIBUTION. ");

  translength4100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength4100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength4100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength4100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3->Update();

  /////////////Transmission Length Sinartisi WaveLength 500-1000,1000-1500,1500-2000m////////////////////////////////////////////// 
  TCanvas *c3= new TCanvas("c3");
   
  TGraphErrors *translength15002000 = fitbetamethodgrapherrorph1( trleng[15002000] );
  translength15002000->SetMarkerStyle(20);//circle full 
  translength15002000->SetMarkerSize(0.9); 
  translength15002000->SetMarkerColor(2);//red  
  translength15002000->SetLineColor(2);
  translength15002000->Draw("SP");
  c3->Update();

  TGraphErrors *translength10001500 = fitbetamethodgrapherrorph1( trleng[10001500] );
  translength10001500->SetMarkerStyle(29);//star full 
  translength10001500->SetMarkerSize(0.9); 
  translength10001500->SetMarkerColor(4);//blue  
  translength10001500->SetLineColor(4);
  translength10001500->Draw("PS");
  c3->Update();

  TGraphErrors *translength5001000 = fitbetamethodgrapherrorph1( trleng[5001000] );
  translength5001000->SetMarkerStyle(22);// triangle full 
  translength5001000->SetMarkerSize(0.9); 
  translength5001000->SetMarkerColor(8);//green  
  translength5001000->SetLineColor(8);
  translength5001000->Draw("PS");
  c3->Update();

  TLegend *leg_500_2000 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg->AddEntry(translength15002000,"1500-2000 m","LP");  
  leg->AddEntry(translength10001500,"1000-1500 m","LP");  
  leg->AddEntry(translength5001000,"500-1000 m","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" Depth ");
                                            // use "f" for a box
  leg->Draw("PS");
  c3->Update();

  translength15002000 -> SetTitle( "  	PRELIMINARY. April 2008 NOT FOR DISTRIBUTION. ");

  translength15002000 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength15002000 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength15002000 ->GetYaxis()->SetRangeUser(15.,50.);
  translength15002000 ->GetXaxis()->SetRangeUser(360.,560.);
  c3_500_2000->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-2500,2500-3400,3400-4100m////////////////////////////////////////////// 
  TCanvas *c3 = new TCanvas("c3_2000_4100");
   
  TGraphErrors *translength34004100 = fitbetamethodgrapherrorph1( trleng[34004100] );
  translength34004100->SetMarkerStyle(20);//circle full 
  translength34004100->SetMarkerSize(0.9); 
  translength34004100->SetMarkerColor(2);//red  
  translength34004100->SetLineColor(2);
  translength34004100->Draw("SP");
  c3->Update();

  TGraphErrors *translength25003400 = fitbetamethodgrapherrorph1( trleng[25003400] );
  translength25003400->SetMarkerStyle(29);//star full 
  translength25003400->SetMarkerSize(0.9); 
  translength25003400->SetMarkerColor(4);//blue  
  translength25003400->SetLineColor(4);
  translength25003400->Draw("PS");
  c3->Update();

  TGraphErrors *translength20002500 = fitbetamethodgrapherrorph1( trleng[20002500] );
  translength20002500->SetMarkerStyle(22);// triangle full 
  translength20002500->SetMarkerSize(0.9); 
  translength20002500->SetMarkerColor(8);//green  
  translength20002500->SetLineColor(8);
  translength20002500->Draw("PS");
  c3->Update();

  TLegend *leg_2000_4100 = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg->AddEntry(translength34004100,"3400-4100 m","LP");  
  le->AddEntry(translength25003400,"2500-3400 m","LP");  
  leg->AddEntry(translength20002500,"2000-2500 m","LP");  
  leg->SetFillColor(18);
  leg->SetHeader(" Depth ");
                                            // use "f" for a box
  leg->Draw("PS");
  c3->Update();

  translength34004100 -> SetTitle( "  	PRELIMINARY. April 2008 NOT FOR DISTRIBUTION. ");

  translength34004100 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength34004100 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength34004100 ->GetYaxis()->SetRangeUser(15.,50.);
  translength34004100 ->GetXaxis()->SetRangeUser(360.,560.);
  c3->Update();

  /////////////Transmission Length Sinartisi WaveLength 4100-3400,3400-2500,2500-2000m////////////////////////////////////////////// 

  TCanvas *c3  = new TCanvas("c3 ");
   
   TGraphErrors *translength41003400 = fitbetamethodgrapherrorph1( trleng[41003400] );
  translength41003400->SetMarkerStyle(20);//circle full 
  translength41003400->SetMarkerSize(0.9); 
  translength41003400->SetMarkerColor(2);//red  
  translength41003400->SetLineColor(2);
  translength41003400->Draw("SP");
  c3 ->Update();

  TGraphErrors *translength34002500 = fitbetamethodgrapherrorph1( trleng[34002500] );
  translength34002500->SetMarkerStyle(29);//star full 
  translength34002500->SetMarkerSize(0.9); 
  translength34002500->SetMarkerColor(4);//blue  
  translength34002500->SetLineColor(4);
  translength34002500->Draw("PS");
  c3 ->Update();

  TGraphErrors *translength25002000 = fitbetamethodgrapherrorph1( trleng[25002000] );
  translength25002000->SetMarkerStyle(22);// triangle full 
  translength25002000->SetMarkerSize(0.9); 
  translength25002000->SetMarkerColor(8);//green  
  translength25002000->SetLineColor(8);
  translength25002000->Draw("PS");
  c3 ->Update();

  TLegend *leg  = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg ->AddEntry(translength41003400,"4100-3400 m","LP");  
  leg ->AddEntry(translength34002500,"3400-2500 m","LP");  
  leg ->AddEntry(translength25002000,"2500-2000 m","LP");  
  leg ->SetFillColor(18);
  leg ->SetHeader(" Depth ");
                                            // use "f" for a box
  leg ->Draw("PS");
  c3 ->Update();

  translength41003400 -> SetTitle( "  	PRELIMINARY. April 2008 NOT FOR DISTRIBUTION. ");

  translength41003400 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength41003400 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength41003400 ->GetYaxis()->SetRangeUser(15.,50.);
  translength41003400 ->GetXaxis()->SetRangeUser(360.,560.);
  c3 ->Update();

  /////////////Transmission Length Sinartisi WaveLength 2000-500m////////////////////////////////////////////// 

  TCanvas *c3  = new TCanvas("c3 ");
   
  TGraphErrors *translength20001500 = fitbetamethodgrapherrorph1( trleng[20001500] );
  translength20001500->SetMarkerStyle(20);//circle full 
  translength20001500->SetMarkerSize(0.9); 
  translength20001500->SetMarkerColor(2);//red  
  translength20001500->SetLineColor(2);
  translength20001500->Draw("SP");
  c3 ->Update();

  TGraphErrors *translength15001000 = fitbetamethodgrapherrorph1( trleng[15001000] );
  translength15001000->SetMarkerStyle(29);//star full 
  translength15001000->SetMarkerSize(0.9); 
  translength15001000->SetMarkerColor(4);//blue  
  translength15001000->SetLineColor(4);
  translength15001000->Draw("PS");
  c3 ->Update();

  TGraphErrors *translength1000500 = fitbetamethodgrapherrorph1( trleng[1000500] );
  translength1000500->SetMarkerStyle(22);// triangle full 
  translength1000500->SetMarkerSize(0.9); 
  translength1000500->SetMarkerColor(8);//green  
  translength1000500->SetLineColor(8);
  translength1000500->Draw("PS");
  c3 ->Update();

  TLegend *leg  = new TLegend(0.8,0.6,0.89,0.89);  //coordinates are fractions
                                         //of pad dimensions
  leg ->AddEntry(translength20001500,"2000-1500 m","LP");  
  leg ->AddEntry(translength15001000,"1500-1000 m","LP");  
  leg ->AddEntry(translength1000500,"1000-500 m","LP");  
  leg ->SetFillColor(18);
  leg ->SetHeader(" Depth ");
                                            // use "f" for a box
  leg ->Draw("PS");
  c3 ->Update();

  translength20001500 -> SetTitle( "  	PRELIMINARY. April 2008 NOT FOR DISTRIBUTION. ");

  translength20001500 ->GetHistogram()->SetXTitle("Wavelength (nm) ");
  translength20001500 ->GetHistogram()->SetYTitle(" Transmission Length (m)");
  translength20001500 ->GetYaxis()->SetRangeUser(15.,50.);
  translength20001500 ->GetXaxis()->SetRangeUser(360.,560.);
  c3 ->Update();



  TFile f("HistTrvsWLforAllDepth.root","recreate");
  c3->Write();
  f.Close();
  delete c3;
  delete translength4100;
  delete translength3400;
  delete translength2500;
  delete translength41003400;
  delete translength34002500;
  delete translength25002000;
  delete translength20001500;
  delete translength15001000;
  delete translength1000500;
  delete leg;
  

}














