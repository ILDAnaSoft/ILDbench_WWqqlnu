#define test_cxx
#include "test.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void test::Loop()
{
//   In a ROOT session, you can do:
//      root> .L test.C
//      root> test t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
	std::cout<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
	//std::cout<<ientry<< " ientry"<<std::endl;
     // if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

	//std::cout<<"entry "<<jentry<<" ";
      // if (Cut(ientry) < 0) continue;
	//if(ntau0 <1) break;	
 	if((wwlike->at(0) ==1) && (ntau0>0) && (genMuon>0)){
				
		TLorentzVector wqq;
		for(int i=0; i<remPx0->size(); i++){
		
			TLorentzVector jet( remPx0->at(i), remPy0->at(i), remPz0->at(i), remE0->at(i) );
			if(jet.Pt() > 2){
				wqq += jet;
			}
	}
	
		wqqmass.Fill(wqq.M());
	//	TLorentzVector wqqf(qqPx0->at(0), qqPy0->at(0), qqPz0->at(0), qqE0->at(0));
		TLorentzVector wqqf;
		for(unsigned int i=0; i< qqPx0->size(); i++){
			TLorentzVector jet( qqPx0->at(i), qqPy0->at(i), qqPz0->at(i), qqE0->at(i) );
			wqqf += jet;
		}
		//std::cout<<wqqf.M()<<" ";
		wqqfmass.Fill(wqqf.M());

		fitprob.Fill(fitprob0);
		chi2.Fill(chi20);

		TLorentzVector lepf(lPx0->at(0), lPy0->at(0), lPz0->at(0), lE0->at(0));
		TLorentzVector nuf(nuPx0,nuPy0,nuPz0,nuE0);

		TLorentzVector wlf = lepf + nuf;

		lepfmass.Fill(wlf.M());

		TLorentzVector lep(candPx0,candPy0,candPz0,candE0);
		TLorentzVector nu;
		nu.SetXYZM( -(wqq+lep).Px(), -(wqq+lep).Py(), -(wqq+lep).Pz(), 0);

		TLorentzVector wl = lep+nu;
		lepmass.Fill(wl.M());

		nufE.Fill(nuf.E());
		nuE.Fill(nu.E());
	

		TLorentzVector g(gPx0,gPy0,gPz0,gE0);
		isrE.Fill(g.E());


		nufZ.Fill(nuf.Pz());
		nuZ.Fill(nu.Pz());
		
		TLorentzVector gennu(MCf_Px->at(2), MCf_Py->at(2), MCf_Pz->at(2), MCf_E->at(2));
		double dz = nu.Pz() - nuf.Pz();

	vDZ.Fill(dz);
		genNuE.Fill(gennu.E());
		genNuZ.Fill(gennu.Pz());
		probvz.Fill(  fitprob0, dz);
		

		//std::cout<<qqfitMass0<<" "<<lnufitMass0<<std::endl;

		//std::cout<<"meas "<<wqq.Px()<<" "<<wqq.Py()<<" "<<wqq.Pz()<<" "<<wqq.E()<<" "<<wqq.M()<<std::endl;
		//std::cout<<"fit  "<<wqqf.Px()<<" "<<wqqf.Py()<<" "<<wqqf.Pz()<<" "<<wqqf.E()<<" "<<wqqf.M()<<std::endl;
	
//	std::cout<<"event No: "<<jentry<<std::endl;	
	//print out all vecs
	std::cout<<"Wqq  "<<wqq.Px()<<" "<<wqq.Py()<<" "<<wqq.Pz()<<" "<<wqq.E()<<" "<<wqq.M()<<std::endl;
	std::cout<<"Wqqf "<<wqqf.Px()<<" "<<wqqf.Py()<<" "<<wqqf.Pz()<<" "<<wqqf.E()<<" "<<wqqf.M()<<std::endl;
	std::cout<<"lep  "<<lep.Px()<<" "<<lep.Py()<<" "<< lep.Pz()<<" "<<lep.E()<<" "<<lep.M()<<std::endl;
	std::cout<<"lepf "<<lepf.Px()<<" "<<lepf.Py()<<" "<< lepf.Pz()<<" "<<lepf.E()<<" "<<lepf.M()<<std::endl;
	std::cout<<"nu   "<<nu.Px()<<" "<<nu.Py()<<" "<<nu.Pz()<<" "<<nu.E()<<" "<<nu.M()<<std::endl;
	std::cout<<"nu   "<<nuf.Px()<<" "<<nuf.Py()<<" "<<nuf.Pz()<<" "<<nuf.E()<<" "<<nuf.M()<<std::endl;
	std::cout<<"Wl   "<<wl.Px()<<" "<<wl.Py()<<" "<<wl.Pz()<<" "<<wl.E()<<" "<<wl.M()<<std::endl;
	std::cout<<"Wlf  "<<wlf.Px()<<" "<<wlf.Py()<<" "<<wlf.Pz()<<" "<<wlf.E()<<" "<<wlf.M()<<std::endl;
	
	}//end checks//end checks??
	if(jentry == 100) break;
   	}

	TCanvas* c1 = new TCanvas();
	wqqfmass.Draw();
//	TCanvas* c1a = new TCanvas();
//	wqqmass.SetLineColor(kRed);
//	wqqmass.Draw("SAMES");
	TCanvas* c2 = new TCanvas();
	fitprob.Draw();
	TCanvas* c3 = new TCanvas();
	chi2.Draw();
	TCanvas* c4 = new TCanvas();
	lepfmass.Draw();
	//TCanvas* c5 = new TCanvas();
	lepmass.SetLineColor(kRed);
	lepmass.Draw("SAMES");

	TCanvas* c6 = new TCanvas();
	nufE.Draw();
	nuE.SetLineColor(kRed);
	nuE.Draw("SAMES");
	genNuE.SetLineColor(kBlue);
	genNuE.Draw("SAMES");

	TCanvas* c7 = new TCanvas();
	isrE.Draw();

	TCanvas* c8 = new TCanvas();
	nufZ.Draw();
	nuZ.SetLineColor(kRed);
	nuZ.Draw("SAMES");
	genNuZ.SetLineColor(kBlue);
	genNuZ.Draw("SAMES");

	TCanvas* c9 = new TCanvas();
	probvz.Draw("COLZ");
	
	TCanvas* c10 = new TCanvas();
	vDZ.Draw();


}
