void wfit(string histname="hmass",float sigmafixed=3.5){
  //
  // Use Voigtian for PDF (ie. BW convolved with Gaussian)
  //
  // In this case the mass, width, and resolution are all free
  // 
  gSystem->Load("libRooFit"); 
  using namespace RooFit;

  cout << "histname = " << histname << " fixing sigma to " << sigmafixed << endl;

  RooRealVar mass("mass","mass",40.0,120.0,"mass");             

  // Define the fitting function
  RooRealVar mean("mean","Mean",80.0,78.0,82.0);              // Mean of the Breit-Wigner       ToyMC value = 80.385 GeV
  RooRealVar width("width","BW width",10.0,1.0,20.0);           // Width of the Breit-Wigner      ToyMC value =  2.085 GeV
  RooRealVar sigma("sigma","Sigma of Gaussian",1.0,0.00001,10.0);   // RMS of the Mass Resolution     Varies from 0 to 10.0 GeV in steps of 0.25 GeV (hists 800 - 840) 
  RooVoigtian model("voigt","voigt(mass,mean,width,sigma)",mass,mean,width,sigma);
   
  width = 2.085;
//  width.setConstant(kTRUE);
  sigma = sigmafixed;
//  sigma.setConstant(kTRUE);

  // Access the histogram and tree stored in the root file
  TFile hfile("outw.root");
  // hfile.ls();
  TH1F *h1 = (TH1F*) gDirectory->Get(histname.c_str());    // This is the histogram with 1.5 GeV mass resolution.

  // Put data into a suitable RooDataHist
  RooDataHist *db = new RooDataHist("db","db",RooArgSet(mass),h1); // Data from histogram

  hfile.Close();

  // Do chi-squared fit using Minuit
  RooChi2Var chi2("chi2","chi2",model,*db);
  RooMinuit m(chi2);
  m.migrad();
  //m.hesse();
  m.minos();

  cout << mean.getError() << " " << mean.getError()/sqrt(10.0) << endl;
  cout << width.getError() << " " << width.getError()/sqrt(10.0) << endl;
  cout << sigma.getError() << " " << sigma.getError()/sqrt(10.0) << endl;

  cout << "End of fit with resolution of " << sigmafixed << endl;

  // Plot data and results
  RooPlot* massframe=mass.frame(Title("W mass"));
  db->plotOn(massframe);
  model.plotOn(massframe,LineColor(kBlue));
  model.paramOn(massframe,Parameters(RooArgSet(mean,width,sigma)),Layout(0.90,0.48,0.90));
 massframe->GetXaxis()->SetTitle("W mass (in GeV/c^{2})");  massframe->GetXaxis()->SetTitleOffset(1.2);
  massframe->Draw();


/* TCanvas* c = new TCanvas("WmassHisto","WmassHisto",800,400) ;
  c->cd() ; gPad->SetLeftMargin(0.15);

            frame->GetXaxis()->SetTitle("W mass (in GeV/c^{2})");  frame->GetXaxis()->SetTitleOffset(1.2);
            float binsize = Z_mass->GetBinWidth(1); char Bsize[50];
            //sprintf(Bsize,"Events per %2.2f",binsize);
            // frame->GetYaxis()->SetTitle(Bsize);  
             //frame->GetYaxis()->SetTitleOffset(1.2);
            frame->Draw() ;
            c->Print("myWmaa.eps");*/

  // Check goodness of fit ...
}
