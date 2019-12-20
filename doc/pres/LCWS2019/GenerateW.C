#include <boost/math/special_functions/ellint_1.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TFile.h>
using namespace boost::math;
using namespace std;

void GenerateW(){

  TRandom3 *rg = new TRandom3(4371);
  TFile *f = new TFile("outw.root","RECREATE");
  TH1D *hmass = new TH1D("hmass","hmass",80,40.0,120.0);
  TH1D *hmass2 = new TH1D("hmass2","hmass2",160,40.0,120.0);
  TH1D *hmass3 = new TH1D("hmass3","hmass3",320,40.0,120.0);

//  const int N = 5060623;
//  const int N = 5060623*1.09136;  //Extra factor so that we get around 5060623 in the [40,120] window.
   const int N = 9361721*1.09136;//what is this extra factor??
// Generate events from Breit-Wigner convolved with Gaussian.

  for(int i=0; i<N; i++){

     double g = rg->Gaus(0.0,1.0);
//     double m = rg->BreitWigner(80.0069,10.5818);
//     double mmeas = m + 0.00026*g;
     double m = rg->BreitWigner(79.7074,10.6972);
     double mmeas = m + 4.847e-7 * g;

     hmass->Fill(mmeas);
     hmass2->Fill(mmeas);
     hmass3->Fill(mmeas);

  }

  f->Write();
}
