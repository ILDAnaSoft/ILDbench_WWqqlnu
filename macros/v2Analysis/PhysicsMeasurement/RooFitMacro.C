void RooFitMacro(){

using namespace RooFit;
 // gROOT->ProcessLine(".x ~/rootlogon.C");

  //TFile f("myZPeakCRAB.root");
  TFile *f = TFile::Open("eventSelS.root");

//TH1F*  Z_mass=(TH1F*)Zmass->Clone();
        TH1F* Z_mass = (TH1F*) f->Get("WWSmqqCuts");
 double hmin = Z_mass->GetXaxis()->GetXmin();
 double hmax = Z_mass->GetXaxis()->GetXmax();
 hmin = 40;
 hmax = 120; 

  // Declare observable x
  RooRealVar x("x","x",hmin,hmax) ;
  RooDataHist dh("dh","dh",x,Import(*Z_mass)) ;

  RooPlot* frame = x.frame(Title("W mass")) ;
  dh.plotOn(frame,MarkerColor(2),MarkerSize(0.9),MarkerStyle(21));  //this will show histogram data points on canvas 
  dh.statOn(frame);  //this will display hist stat on canvas

  RooRealVar mean("mean","mean",80.0, 60.0, 120.0);
  RooRealVar width("width","width",2.0, 0.0, 20.0);
  RooRealVar sigma("sigma","sigma",10.0, 0.0, 120.0);
//  RooGaussian gauss("gauss","gauss",x,mean,sigma);
//  RooBreitWigner gauss("gauss","gauss",x,mean,sigma);
  RooVoigtian gauss("gauss","gauss",x,mean,width,sigma);

  RooFitResult* filters = gauss.fitTo(dh,"qr");
  gauss.plotOn(frame,LineColor(4));//this will show fit overlay on canvas 
  gauss.paramOn(frame); //this will display the fit parameters on canvas
  //filters->Print("v");

  // Draw all frames on a canvas
  TCanvas* c = new TCanvas("WmassHisto","WmassHisto",800,400) ;
  c->cd() ; gPad->SetLeftMargin(0.15);
           
            frame->GetXaxis()->SetTitle("W mass (in GeV/c^{2})");  frame->GetXaxis()->SetTitleOffset(1.2);
	    float binsize = Z_mass->GetBinWidth(1); char Bsize[50]; 
            //sprintf(Bsize,"Events per %2.2f",binsize);
            // frame->GetYaxis()->SetTitle(Bsize);  
             //frame->GetYaxis()->SetTitleOffset(1.2);
            frame->Draw() ;
            c->Print("myWmaa.eps");  

}
