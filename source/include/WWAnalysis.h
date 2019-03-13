#include "marlin/Processor.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCRelation.h"
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
#include "TROOT.h"
#include <string> 

#include "eventVariables.h"
#include "jetVariables.h"
#include "PandoraPfoVariables.h"
#include "anaVariables.h"
#include "overlayVariables.h"
#include "HistoManager.h"
#include "tauFinderVariables.h"
#include "mcVariables.h"


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
 // bool FindJets( LCEvent* evt ) ;
  bool FindPFOs( LCEvent* evt ) ;
  bool FindPFOCollection( LCEvent* evt, std::string PfoCollectionName, std::vector<ReconstructedParticle*>& localVec );
  bool FindTracks( LCEvent* evt );
  bool FindRecoToMCRelation( LCEvent* evt );
 // bool FindJetsWithOverlay( LCEvent* evt );
  bool FindJetCollection( LCEvent* evt, std::string JetCollectionName, std::vector<ReconstructedParticle*>& localVec );

	void processSignalVariableSet(LCEvent* evt, std::vector<LCRelation*> pfo2mc, eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar, overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets);
	void printSignalVariableSet( eventVariables*& evtVar, jetVariables*& jetVar, PandoraPfoVariables*& ppfoVar, anaVariables*& anaVar, overlayVariables*& oVar );

   void processOverlayVariables(overlayVariables*& oVar, std::vector<ReconstructedParticle*> jets, std::vector<MCParticle*> mcpartvec , std::vector<LCRelation*> pfo2mc);

   void processVariables(LCEvent* evt, eventVariables*& evtVar, jetVariables*& jetVar, anaVariables*& anaVar, std::vector<ReconstructedParticle*> jets );

   void processBackground(LCEvent* evt, eventVariables*& evtVar, jetVariables*& jetVar, anaVariables*& anaVar, std::vector<ReconstructedParticle*> jets);


	


  //jet analysis helpers
 
 	//TODO reimplement in other class
	MCParticle* classifyEvent2fermion( std::vector<TLorentzVector*>& _MCf, std::vector<int>& _MCfpdg );



	//for the extra overlay analysis jets
  void populateJetsWithOverlayTLVs(std::vector<ReconstructedParticle*> j);

  //helper function to get production angle of W-
  double getCosThetaW();

  

  protected:

 //variable helper classes
 eventVariables* ev_eekt{};
 jetVariables* jv_eekt{};
 anaVariables* ana_eekt{};
 overlayVariables* ov_eekt{};
 
	eventVariables* ev_pure{};
	jetVariables*	jv_pure{};
	anaVariables*  ana_pure{};

	eventVariables* ev_kt15{};
 jetVariables* jv_kt15{};
 anaVariables* ana_kt15{};
 overlayVariables* ov_kt15{};

	eventVariables* ev_kt08{};
 jetVariables* jv_kt08{};
 anaVariables* ana_kt08{};
 overlayVariables* ov_kt08{};

	//testing classes for tau finder
	tauFinderVariables* tfv{};
	eventVariables* ev_tfv{};

//overlay removed from eekt variables set
// eventVariables* ev_eekt_no_overlay{};
// jetVariables* jv_eekt_no_overlay{};
// anaVariables* ana_eekt_no_overlay{};

 PandoraPfoVariables* ppfov{};
 PandoraPfoVariables* ppfoPure{};
 //overlayVariables* ppfo_ovr{};
 HistoManager* h1{};
//TTree
  TFile* file{};
  TTree* _tree{};//general tree

  TTree* _puretree{};
  TTree* _eekttree{};
  TTree* _kt15tree{};
  TTree* _kt08tree{};

  //taufinder tree
  TTree* _tautree{};



 std::vector<TTree*> _trees{};

//Tau optimization////
 void initTauFinderOptimization();
 void SetTauOptimizationVariables();
 void initEmptyTau(tauFinderVariables*& t);
 void initTauWithNoMCLepton(tauFinderVariables*& t);
 std::vector<tauFinderVariables*> _tf{};
 std::vector<mcVariables*> _mcv{};


  int _nRun{};
  int _nEvt{};

std::string _outpath;







//the total number of unique cuts applied (for histogram indexing)

	int ncuts = 7;

  
  //vector to hold the particles for the event
  std::vector<MCParticle*> _mcpartvec{};

  std::vector<Track*> _trackvec{};
  std::vector<ReconstructedParticle*> _pfovec{};
  std::vector<ReconstructedParticle*> _purePFOs{};
  std::vector<LCRelation*> _reco2mcvec{};
 
 std::vector<ReconstructedParticle*> _eektJets{};
  std::vector<ReconstructedParticle*> _kt08Jets{};

  std::vector<ReconstructedParticle*> _kt15Jets{};
  std::vector<ReconstructedParticle*> _pureJets{};


  std::vector<ReconstructedParticle*> _tauJets{};

 
 
 
	//jet y variabls //log jet variables
  int _nJets{};
  int _nJetCollections = 5;


	//EVENT SELECTION WEIGHT
	double weight{};//defined in xml


	int   _printing{};

	//running mode
	int _runSignalMode{};

//input background//number of fermions or leptons
	int _nfermions{};
	int _nleptons{};

  //input collections
  std::string _inputMcParticleCollectionName{};
  std::string _inputJetCollectionName{};
  std::string _inputJetWithOverlayCollectionName{};
  std::string _inputParticleCollectionName{};
  std::string _inputTrackCollectionName{};
  std::string _inputRecoRelationCollectionName{};

  std::vector<std::string> _inputJetCollectionsNames{};
  std::vector<std::vector<ReconstructedParticle*> > _particleCollections{};

 // std::< std::vector<std::string> > jetCollectionNames{};

  std::string _JetCollName_eekt = "eektJets";
  std::string _JetCollName_kt15 = "kt15Jets";
  std::string _JetCollName_kt08 = "kt08Jets";
  std::string _JetCollName_pure = "pureJets";
  std::string _PfoCollName_pure = "purgedPFOs";
  //taufinding
	std::string _JetCollName_tau = "tauJets";



};
