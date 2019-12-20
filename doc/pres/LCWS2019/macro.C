void gethists(std::vector<TH1D*>& hists, std::vector<std::string> taglist, std::string histname, TFile* f){
        for(int i=0; i<taglist.size(); i++){
                std::string hname = taglist.at(i)+histname;
                hists.at(i) = (TH1D*) f->Get(hname.c_str());
        }
}


void macro(){
        TFile* f1s = TFile::Open("eventSelS.root");
        std::vector<std::string> _WWSignals{"WWS1", "WWS2","WS1", "WSBG", "WWS1BG","WWS2BG"};
        std::vector<TH1D*> massdiffs(_WWSignals.size());
       // std::vector<TH1D*> costdiffs(_WWSignals.size());
        gethists(massdiffs,_WWSignals , "mqqDiffCuts", f1s);    
//      gethists(costdiffs,_WWSignals, "qcostdiffHist", f1s);

        std::vector<TH1D*> massdiffOL(_WWSignals.size());
        gethists(massdiffOL, _WWSignals, "mqqDiffOL", f1s);

        TH1D* mdiff = massdiffs[0];
	mdiff->GetXaxis()->SetTitle("M_{qq}^{meas} - M_{qq}^{gen}");
        TH1D* cdiff = massdiffOL[0];
        for(int i=1;i<_WWSignals.size();i++){
                mdiff->Add(massdiffs[i]);
              cdiff->Add(massdiffOL[i]);
        }

	mdiff->SetStats(0);
	cdiff->SetStats(0);
	mdiff->SetLineColor(kGreen+2);
	cdiff->SetLineColor(kBlack);
        TCanvas* cmass = new TCanvas();
        mdiff->Draw("hist:e");

        cmass->Print("mqqdiffHist.pdf");

//	TCanvas* cmass2 = new TCanvas();
	cdiff->Draw("hist:e:same");
//	cmass2->Print("mqqdiffOLHist.pdf");

//	TLegend* legend = new TLegend(0.1,0.7,0.48,0.9);
//	auto* legend = new TLegend(0.2, 0.2, .8, .8);
	float ymax=800.0; float xlmin=0.7; float ylmin=0.7;//was 35 58
        const float dx=0.28;
        const float dy=0.26;
        TLegend* legend = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);  
 	legend->AddEntry(cdiff,"Before P.U. removal and selection cuts","l");	
	legend->AddEntry(mdiff,"After P.U. removal and selection cuts","l");
	legend->Draw();

std::vector<std::string> _WWSignals2{"WWS1","WWS2","WWS1BG","WWS2BG"};
	
	std::vector<TH1D*> masses(_WWSignals2.size());
	std::vector<TH1D*> massesud(_WWSignals2.size());
	std::vector<TH1D*> massescs(_WWSignals2.size());
	gethists(masses, _WWSignals2, "mqqCuts", f1s);
	gethists(massesud, _WWSignals2, "mqqUDCuts", f1s);
	gethists(massescs, _WWSignals2, "mqqCSCuts", f1s);

	TH1D* m1 = masses[0];
	TH1D* m2 = massesud[0];
	TH1D* m3 = massescs[0];
	for(unsigned int i=1; i<masses.size(); i++){
		m1->Add(masses[i]);
		m2->Add(massesud[i]);
		m3->Add(massescs[i]);
		
	}
	TCanvas* wmasses = new TCanvas();
	m1->Draw("hist:e");
	TCanvas* ud = new TCanvas();
	m2->SetLineColor(kRed);
	m2->Draw("hist:e");
	m3->SetLineColor(kBlue);
	m3->Draw("sames:hist:e");
	
}
