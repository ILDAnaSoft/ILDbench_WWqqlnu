
void gethists(std::vector<TH1D*>& hists, std::vector<std::string> taglist, std::string histname, TFile* f){
        for(int i=0; i<taglist.size(); i++){
                std::string hname = taglist.at(i)+histname;
                hists.at(i) = (TH1D*) f->Get(hname.c_str());
        }
}
void combineEff(std::string histname, std::string bgfile, std::string sigfile, std::string ofilename, std::string ofileopt, std::string selmode){
//merge everything

	
	std::string histnameN = histname + "NUM";
	std::string histnameD = histname + "DEN";

TFile* f1 = TFile::Open(bgfile.c_str());
TFile* f2 = TFile::Open(sigfile.c_str());

	std::vector<std::string> _2f{"BHAg", "ZHAD", "ZL", "WL"};  
        std::vector<std::string> _4f{"ZEEL","ZEES","ZNUL", "ZNUS","ZWML","WWHAD", "WWL", "ZZHAD", "ZZL", "ZZS","ZZWWH","ZZWWL"};
        std::vector<std::string> _6f{"EEWW","LLWW","TTB","VVWW","XXWW","XXZ","YYZ"};
        std::vector<std::string> _H{"EEH", "MUH", "TAUH", "QQH", "NNH"};

	std::vector<std::string> _Smu{"WWS1"};
        std::vector<std::string> _Sele{"WS1"};
        std::vector<std::string> _Stau{"WWS2"};
   ///     std::vector<std::string> _S2Full{"WS"};

	std::vector<TH1D*> _2fHist(_2f.size());
        std::vector<TH1D*> _4fHist(_4f.size());
        std::vector<TH1D*> _6fHist(_6f.size());
       std::vector<TH1D*> _HHist(_H.size());
	std::vector<TH1D*> _2fHistD(_2f.size());
        std::vector<TH1D*> _4fHistD(_4f.size());
        std::vector<TH1D*> _6fHistD(_6f.size());
       std::vector<TH1D*> _HHistD(_H.size());
//TODO add the others

//numerator
	std::vector<TH1D*> _SmuHist(_Smu.size());
	std::vector<TH1D*> _SeleHist(_Sele.size());
	std::vector<TH1D*> _StauHist(_Stau.size());

//denominator
	std::vector<TH1D*> _SmuHistD(_Smu.size());
	std::vector<TH1D*> _SeleHistD(_Sele.size());
	std::vector<TH1D*> _StauHistD(_Stau.size());


	gethists(_2fHist, _2f, histnameN, f1);
        gethists(_4fHist, _4f, histnameN, f1);
        gethists(_6fHist, _6f, histnameN, f1);
        gethists(_HHist, _H, histnameN, f1);
	gethists(_2fHistD, _2f, histnameD, f1);
        gethists(_4fHistD, _4f, histnameD, f1);
        gethists(_6fHistD, _6f, histnameD, f1);
        gethists(_HHistD, _H, histnameD, f1);

        gethists(_SmuHist, _Smu, histnameN, f2);
        gethists(_SeleHist, _Sele, histnameN, f2);
	gethists(_StauHist, _Stau, histnameN, f2);


	gethists(_SmuHistD, _Smu, histnameD, f2);
	gethists(_SeleHistD, _Sele, histnameD, f2);
	gethists(_StauHistD, _Stau, histnameD, f2);


	auto xaxis = _2fHist[0]->GetXaxis()->GetTitle();
        auto yaxis = _2fHist[0]->GetYaxis()->GetTitle();
        //add together appropriate histograms
        TH1D* _2ftot = _2fHist[0];
	TH1D* _2ftotD = _2fHistD[0];
        for(int i =1; i< _2fHist.size(); i++){
                _2ftot->Add(_2fHist[i]);
		_2ftotD->Add(_2fHistD[i]);
        }
       // _2ftot->SetFillColor(39);


        TH1D* _4ftot = _4fHist[0];
	TH1D* _4ftotD = _4fHistD[0];
        for(int i =1; i< _4fHist.size(); i++){

                _4ftot->Add(_4fHist[i]);
                _4ftotD->Add(_4fHistD[i]);
        }
        //_4ftot->SetFillColor(29);

        TH1D* _6ftot = _6fHist[0];
        TH1D* _6ftotD = (_6fHistD[0]);
        for(int i =1; i< _6fHist.size(); i++){

                _6ftot->Add(_6fHist[i]);
                _6ftotD->Add(_6fHistD[i]);
        }
        //_6ftot->SetFillColor(kBlue);

        TH1D* _Htot = _HHist[0];
       TH1D*  _HtotD =(_HHistD[0]);
        for(int i =1; i< _HHist.size(); i++){

                _Htot->Add(_HHist[i]);
                _Htot->Add(_HHistD[i]);
        }
        //_Htot->SetFillColor(kBlack);


	TH1D* _BGtot = _2ftot;
	_BGtot->Add(_4ftot);
	_BGtot->Add(_6ftot);
	_BGtot->Add(_Htot);
	TH1D* _BGtotD = _2ftotD;
	_BGtotD->Add(_4ftotD);
	_BGtotD->Add(_6ftotD);
	_BGtotD->Add(_HtotD);

	TH1D* _Stot = _SmuHist[0];
	_Stot->Add(_SeleHist[0]);
	_Stot->Add(_StauHist[0]);
	
	TH1D* _StotD = _SmuHistD[0];
	_StotD->Add(_SeleHistD[0]);
	_StotD->Add(_StauHistD[0]);



//make efficiency and save to histogram


	TH1D* Seff = (TH1D*) _Stot->Clone();
	Seff->Divide(_StotD);
        TH1D* BGeff= (TH1D*) _BGtot->Clone();
	BGeff->Divide(_BGtotD);
        Seff->SetLineColor(kRed);
	TFile* of = new TFile(("/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/"+ofilename).c_str(), ofileopt.c_str());

	of->WriteObject(Seff, ("signal"+histname).c_str());
	of->WriteObject(BGeff, ("bg"+histname).c_str());
	of->Write();
	of->Close();
	        //TCanvas* c = new TCanvas();
	//Seff->Draw();
	//BGeff->Draw("SAMES");

//get eff and purity bin by bin
	
	ofstream myfile ("/afs/desy.de/user/a/anguiano/dust/WWBenchmark/WWFiles/CutOptFiles/"+selmode+histname+"summary.out");
  

	double maxeffp = 0;
	int imax;
	int nbins =  _Stot->GetXaxis()->GetNbins();
	for(int i=1; i<=nbins; i++){
		double NS =  _Stot->GetBinContent(i);
		double NB = _BGtot->GetBinContent(i);
		double p = NS/(NS+NB);

		double effs = Seff->GetBinContent(i);
		double cutvalue = Seff->GetXaxis()->GetBinCenter(i);		
		double effb = BGeff->GetBinContent(i);		

		double effp = effs * p;
		if(effp > maxeffp){
			maxeffp = effp;
			imax = i;
		}
		myfile << histname <<" "<<cutvalue<<" "<< effs <<" "<<effb<< " "<<NS<<" "<<NB<<" "<<p<<" "<<effp<<" \n";

	}
	myfile<<"Best: "<<histname<<" "<<Seff->GetXaxis()->GetBinCenter(imax)<<" "<<maxeffp<<" \n";
 	
   	 myfile.close();
 	






}
