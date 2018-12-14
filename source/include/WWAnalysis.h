#include "marlin/Processor.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "IMPL/LCCollectionVec.h"
#include <marlin/Global.h>
#include "gear/BField.h"
#include "lcio.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <algorithm>
#include "TLorentzVector.h"
#include "TVector3.h"
#include "classifyTau.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "EVENT/LCParameters.h"

#include "eventVariables.h"
#include "jetVariables.h"
#include "PandoraPfoVariables.h"



//#define ncuts 7
//if we change nferm we need to recompile and also change _nfermion and _nleptons in xml
//#define nferm 4

using namespace lcio;

	/** WWAnalysis:<br>
 *
 * 
 * @author Justin Anguiano, University of Kansas
 * 
 */

 class WWAnalysis : public marlin::Processor {

 public:

 virtual marlin::Processor*  newProcessor() { return new WWAnalysis ; }

  WWAnalysis(const WWAnalysis&) = delete ;
  WWAnalysis& operator=(const WWAnalysis&) = delete ;

  WWAnalysis() ;

  /** Called at the beginning of the job before anything is read.
   *  Use to initialize the proscessor, e.g. book histograms.
   */
  virtual void init() ;
  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* run ) ;

  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent * evt ) ;


  /** Called after data processing for clean up.
   */
  virtual void end() ;

 //collection gathering
  bool FindMCParticles( LCEvent* evt );
  bool FindJets( LCEvent* evt ) ;
  bool FindPFOs( LCEvent* evt ) ;
  bool FindTracks( LCEvent* evt );
  bool FindJetsWithOverlay( LCEvent* evt );



  // lepton jet functions
  int identifyLeptonJet( std::vector<ReconstructedParticle*> jets);
  int identifyLeptonJet_bySeparation(std::vector<ReconstructedParticle*> jets);
  double getAngleOfjetandMCLepton(int jet_index);
  int getJetNearMCLepton(); //return index of jet closest to mclepton
  void  getMultiplicityOfTrueljet();
  void classifyTauDecay(MCParticle* mctau);
  MCParticle* getMClepton(MCParticle* parent);
  void AnalyzeDijet();

  int getLeptonJetCharge( ReconstructedParticle* ljet );

	//overlay analysis
	void AnalyzeOverlay(LCEvent* evt );
	void FindMCOverlay( MCParticle* p , std::vector<MCParticle*>& FSP);
	void AnalyzeOverlayAcceptance(std::vector<TLorentzVector*> _jetswithoverlay, std::vector<TLorentzVector*> _jetsremovedoverlay );
	void initOverlayEff();

  //jet analysis helpers
  void getJetMultiplicities();
  void exploreDaughterParticles(MCParticle* p, std::vector<MCParticle*>& FSP);
  bool allChildrenAreSimulation(MCParticle* p);
  void analyzeLeadingTracks();
  void EvaluateJetVariables( LCEvent* evt, std::vector<ReconstructedParticle*> jets, int& nJets, float& yMinus, float& yPlus); 
 void MCTagjets(std::vector<TLorentzVector*> mcp, std::vector<int> mcp_pdg, std::vector<TLorentzVector*> js, std::vector<int>& j_indices);

  //classify the type of lepton decay and retrieve the
  //mcparticles for qqlnu
//  MCParticle* classifyEvent(bool& isTau, bool& isMuon, int& trueq);
//  MCParticle* classifyEvent(bool& isTau, bool& isMuon, int& trueq, TLorentzVector* (&_MCf)[nferm], int (&_MCfpdg)[nferm]);
	MCParticle* classifyEvent(bool& isTau, bool& isMuon, int& trueq, std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCfpdg);
//  MCParticle* classifyEvent2fermion( TLorentzVector* (&_MCf)[nferm], int (&_MCfpdg)[nferm]);
	MCParticle* classifyEvent2fermion( std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCfpdg );
//  MCParticle* classifyEvent(bool& isTau, bool& isMuon, int& trueq, int (&_MCfpdg)[4]);

	//event selection variables
	void EvaluateEventSelectionVariables(int& _totaltracks,double& _total_Pt,double& _total_E, double& _total_M);

  //populate local datastructures (TLVS)
  void populateTLVs(int lindex);
  void populateCMTLVs();
	//for the extra overlay analysis jets
  void populateJetsWithOverlayTLVs(std::vector<ReconstructedParticle*> j);

  //helper function to get production angle of W-
  double getCosThetaW();

  //functions to populate histograms
  void FillHistos(int histNumber);
  void FillMuonHistos(int histNumber);
  void FillTauHistos(int histNumber);
  void fillEventSelectionHistos(double w);

  protected:

 eventVariables* ev1;
 jetVariables* jv1;
 PandoraPfoVariables* ppfov1;
//TTree
  TTree* _tree;
  int _nRun;
  int _nEvt;
//  float _xsec;
//  TString *_Process;

  //TLorentzVector* _MCf[nferm];
  //int _MCfpdg[nferm];
	std::vector<TLorentzVector*> _MCf;
	std::vector<int> _MCfpdg;

//event number
  int nEvt{};

//MC information
 //the true parent that contains qqlnu
  MCParticle* parent;
 //bools to characterize the true lepton decay for this event
  bool isTau;
  bool isMuon;
 //the true lepton charge
  int trueq=-3;

 //tau decay mode daniels code variables
  int tauDecayMode=-1;
  int taudaughters=-1;
  int tauChargedDaughters=-1;
  int tauNeutrals = -1;

//Lepton Jet variables
 //index of the identified lepton on jet vector
  int ljet_index;
 //the assigned charge for identifed lepton jet
  int lq;
 //the index of the jet which is closest to the true mc lepton
  int true_ljet_index;

//tallies for the number of each type of true lepton per event
  int ntau=0;
  int nmuon=0;
  int nelec=0;

 //the number of overlay events present in the event
	int OverlaynTotalEvents=-1;
	int OverlayPairBgOverlaynEvents=-1;
	//overlay rejected particle variables separated by flavour
	//these vectors need to be cleared for each event
	std::vector<double> uplike_rejects_costheta{};
	std::vector<double> downlike_rejects_costheta{};
	std::vector<double> lepton_rejects_costheta{};

	std::vector<double> uplike_rejects_pt{}; 
	std::vector<double> downlike_rejects_pt{};
	std::vector<double> lepton_rejects_pt{};
	
	std::vector<double> uplike_rejects_P{};
	std::vector<double> downlike_rejects_P{};
	std::vector<double> lepton_rejects_P{};

//the total number of unique cuts applied (for histogram indexing)

	int ncuts = 7;

  //how many times do we get the proper lepton charge?
  //for muons and for leptons separately
  int muonqmatch=0;
  int tauqmatch=0;
  
  //vector to hold the particles for the event
  std::vector<MCParticle*> _mcpartvec{};
  std::vector<ReconstructedParticle*> _jets{};
  std::vector<Track*> _trackvec{};
  std::vector<ReconstructedParticle*> _pfovec{};
  std::vector<ReconstructedParticle*> _jetswithoverlay{};
  
  //useful structures for calculation/ readability
  std::vector<TLorentzVector*> jets{};
  TLorentzVector* Wl; //l+nu
  TLorentzVector* Wqq; //q+q
  TLorentzVector* nu; //made from missing p with m=0
  std::vector<TLorentzVector*> CMJets{}; //q,q,l boosted into W rest frame
  TLorentzVector* CMnu;//nu boosted into W restframe

	//structure for jets with no overlay removal
  std::vector<TLorentzVector*> jetswithoverlay{};


  //jet matching and jet multiplicity variables
  int lpdg; // true pdg code for the lepton
  int lnparts; // number of particles in lepton jet
  int lntracks; // number of tracks in lepton jet
  int lnmcparts; //true n daughters of lepton
  int lnmctracks; //true n daughter tracks of lepton
  std::vector<int> jetNparts; //number of particles per any jet
  std::vector<int> jetNtracks; //number of tracks per any jet
  double leadingptljet; //pt of the leading track in the lepton jet
  double leadingd0ljet; //d0 of the leading track in the lepton jet
  double leadingd0relerrljet; //relative error of d0 of leading track in lepton jet

  int trueljetntracks; //number of tracks in the jet matched with true lepton 
  int jetleastntracks; //number of tracks in the jet with the least tracks
  int jetleastntracks_index;

	//montecarlo dijet (qq) variables
	double mcqqmass= -5;
	double mcqqE =-5;
	double mcqqcostheta =-5;
	double mcqqphi = -5;

  double leadingptqjet; //pt of the leading track in a quark jet
  double leadingd0qjet; //d0 of the leading track in a quark jet
  double leadingd0relerrqjet; //relative error of d0 of leading track in lepton jet

	//jet y variabls //log jet variables
  int _nJets;
  float _yMinus;
  float _yPlus;

  //opening angle between the lepton jet and mc lepton
  double psi_mcl_ljet;
  //opening angle between mc lepton and closest jet
  double true_psi_mcl_ljet;

  int qnparts;
  int qntracks;
  int qmcparts;
  int qmctracks;

	//event selection variables
	//EVENT SELECTION WEIGHT
	double weight{};//defined in xml
	int totaltracks{};
		//total 4 vector sum variables
	double total_Pt{};
	double total_E{};
	double total_M{};

	int   _printing{};

	//input background//number of fermions or leptons
	int _nfermions{};
	int _nleptons{};

  //input collections
  std::string _inputMcParticleCollectionName{};
  std::string _inputJetCollectionName{};
  std::string _inputJetWithOverlayCollectionName{};
  std::string _inputParticleCollectionName{};
  std::string _inputTrackCollectionName{};


  /* histograms split between muon/tau true events */
/*
	TFile* file;

	TH1D *WmassMuon[ncuts+1], *WmassTau[ncuts+1], *qqmassMuon[ncuts+1], *qqmassTau[ncuts+1];
	TH1D *WEMuon[ncuts+1], *WETau[ncuts+1], *EtotalMuon[ncuts+1], *EtotalTau[ncuts+1];
	TH1D *Wm_cosTheta[ncuts+1];

	TH1D *LjetMassMuon[ncuts+1], *LjetMassTau[ncuts+1];

	//tgc hists
	TH1D *costhetawMuon[ncuts+1] , *costhetawTau[ncuts+1];
	TH1D *thetaLMuon[ncuts+1], *thetaLTau[ncuts+1];
	TH1D *phiLMuon[ncuts+1], *phiLTau[ncuts+1];
	TH1D *thetaHMuon[ncuts+1], *thetaHTau[ncuts+1];
	TH1D *phiHMuon[ncuts+1], *phiHTau[ncuts+1];

    //jet information histograms
    TH1D  *leptonMCNPartsMuon[ncuts+1], *leptonMCNTracksMuon[ncuts+1], *leptonMCNPartsTau[ncuts+1], *leptonMCNTracksTau[ncuts+1];
	TH1D  *jetNpartsMuon[ncuts+1], *minjetNpartsMuon[ncuts+1], *jetNpartsTau[ncuts+1], *minjetNpartsTau[ncuts+1];
    TH1D  *jetNtracksMuon[ncuts+1], *minjetNtracksMuon[ncuts+1],  *jetNtracksTau[ncuts+1], *minjetNtracksTau[ncuts+1];

    //lepton jet info
	TH1D *ljetleadingd0Muon[ncuts+1], *ljetleadingd0Tau[ncuts+1], *ljetleadingptMuon[ncuts+1], *ljetleadingptTau[ncuts+1];
    TH1D *ljetd0relerrMuon[ncuts+1], *ljetd0relerrTau[ncuts+1]; 
    TH1D *qjetleadingd0Muon[ncuts+1], *qjetleadingd0Tau[ncuts+1], *qjetleadingptMuon[ncuts+1], *qjetleadingptTau[ncuts+1];
    TH1D *qjetd0relerrMuon[ncuts+1], *qjetd0relerrTau[ncuts+1];
	
	    TH1D *psiljetmclMuon[ncuts+1], *psiljetmclTau[ncuts+1];

	TH1D *htotalTracks[ncuts+1];

*/
	int ljetmatchmctau;
	int ljetmatchmcmuon;

     /* TESTING AREA !!! */
	TFile* file;

	std::vector<TH1D*> WmassMuon, WmassTau, qqmassMuon, qqmassTau;
	std::vector<TH1D*> WEMuon, WETau, EtotalMuon, EtotalTau;
	std::vector<TH1D*> Wm_cosTheta;

	std::vector<TH1D*> LjetMassMuon, LjetMassTau;

	//tgc hists
	std::vector<TH1D*> costhetawMuon , costhetawTau;
	std::vector<TH1D*> thetaLMuon, thetaLTau;
	std::vector<TH1D*> phiLMuon, phiLTau;
	std::vector<TH1D*> thetaHMuon, thetaHTau;
	std::vector<TH1D*> phiHMuon, phiHTau;

    //jet information histograms
    std::vector<TH1D*>  leptonMCNPartsMuon, leptonMCNTracksMuon, leptonMCNPartsTau, leptonMCNTracksTau;
	std::vector<TH1D*>  jetNpartsMuon, minjetNpartsMuon, jetNpartsTau, minjetNpartsTau;
    std::vector<TH1D*>  jetNtracksMuon, minjetNtracksMuon,  jetNtracksTau, minjetNtracksTau;

    //lepton jet info
	std::vector<TH1D*> ljetleadingd0Muon, ljetleadingd0Tau, ljetleadingptMuon, ljetleadingptTau;
    std::vector<TH1D*> ljetd0relerrMuon, ljetd0relerrTau; 
    std::vector<TH1D*> qjetleadingd0Muon, qjetleadingd0Tau, qjetleadingptMuon, qjetleadingptTau;
    std::vector<TH1D*> qjetd0relerrMuon, qjetd0relerrTau;
	
	std::vector<TH1D*> psiljetmclMuon, psiljetmclTau;

	std::vector<TH1D*> htotalTracks;


	/* END HISTO TEST */

	//these are populated directly from pandora pfos
	TH1D* htotaltracks;
	TH1D* htotalPt;
	TH1D* htotalE;
	TH1D* htotalM;
	TH1D* hym;
	TH1D* hyp;
 	/* end histograms */


	/* special set of histograms for dealing with overlay and forward acceptance */
	/* each hist in the array is a cut on costheta */
	/* the cuts are 0.99, 0.95, 0.91, 0.8, 0.6, 0.4, 0.2 */
	//total of 7 different cuts
	int overlaycuts = 8;
	std::vector<double> maxcosthetacuts{ 0.2, 0.4, 0.6, 0.8, 0.91, 0.95, 0.99,99};
	std::vector<TH1D*> maxcostheta_cut{};
	//no overlay removal in this plot
	std::vector<TH1D*> maxcostheta_cut_ovr{};

	//generator level
	std::vector<TH1D*> maxcostheta_cut_mc{};
	//mctag mqq - mc mqq
	std::vector<TH1D*> mctag_mc_dM_ovr{};
	std::vector<TH1D*> mctag_mc_dM{};
	
	
	

	/* end acceptance */

};
