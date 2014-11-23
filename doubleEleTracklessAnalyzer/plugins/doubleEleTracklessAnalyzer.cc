// -*- C++ -*-
//
// Package:    doubleElectronTracklessTrigger/doubleEleTracklessAnalyzer
// Class:      doubleEleTracklessAnalyzer
// 
/**\class doubleEleTracklessAnalyzer doubleEleTracklessAnalyzer.cc doubleElectronTracklessTrigger/doubleEleTracklessAnalyzer/plugins/doubleEleTracklessAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sean Kalafut
//         Created:  Thu, 06 Nov 2014 23:16:33 GMT
//
//


// system include files
#include <memory>
#include <map>
#include <utility>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>



// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateIsolation.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"


#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ClusterShape.h"
#include "DataFormats/EgammaReco/interface/ClusterShapeFwd.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
//#include "DataFormats/HLTReco/interface/TriggerEvent.h" // trigger::TriggerEvent
#include "DataFormats/HLTReco/interface/TriggerObject.h" 
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h" 
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h" 
#include "DataFormats/HLTReco/interface/TriggerRefsCollections.h" 
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h" 



#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFraction.h"
#include "DataFormats/ParticleFlowReco/interface/PFLayer.h"

#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/CaloRecHit/interface/CaloRecHit.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TAttFill.h"
#include "TAttMarker.h"
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TROOT.h>
#include "TTree.h"


//
// class declaration
//

class doubleEleTracklessAnalyzer : public edm::EDAnalyzer {
   public:
      explicit doubleEleTracklessAnalyzer(const edm::ParameterSet&);
      ~doubleEleTracklessAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      
      TTree *tree;

	  void incrementNumTriggeredEvents(){
		  numTriggeredEvents = numTriggeredEvents + 1.0;
	  }
	  double getNumTriggeredEvents(){
		  return numTriggeredEvents;
	  }

	  void incrementEfficiencyDenominator(){
		  efficiencyDenominator = efficiencyDenominator + 1.0;
	  }
	  double getEfficiencyDenominator(){
		  return efficiencyDenominator;
	  }

	  void addRECEta(double eta){
		  RECEta.push_back(eta);
	  }
	  double getRECEta(unsigned int t){
		  if(RECEta.size() > t) return RECEta[t];
		  return 0;
	  }

	  void addRECPt(double pt){
		  RECPt.push_back(pt);
	  }
	  double getRECPt(unsigned int t){
		  if(RECPt.size() > t) return RECPt[t];
		  return 0;
	  }


	  void addRECHcalIso(double hcalIso){
		  RECHcalIso.push_back(hcalIso);
	  }
	  double getRECHcalIso(unsigned int t){
		  if(RECHcalIso.size() > t) return RECHcalIso[t];
		  return 0;
	  }


	  void addRECEcalIso(double ecalIso){
		  RECEcalIso.push_back(ecalIso);
	  }
	  double getRECEcalIso(unsigned int t){
		  if(RECEcalIso.size() > t) return RECEcalIso[t];
		  return 0;
	  }


	  void addRECHoverE(double HoE){
		  RECHoverE.push_back(HoE);
	  }
	  double getRECHoverE(unsigned int t){
		  if(RECHoverE.size() > t) return RECHoverE[t];
		  return 0;
	  }


	  void addRECEcalClusterShape(double clstShape){
		  RECEcalClusterShape.push_back(clstShape);
	  }
	  double getRECEcalClusterShape(unsigned int t){
		  if(RECEcalClusterShape.size() > t) return RECEcalClusterShape[t];
		  return 0;
	  }


	  void addRECEcalClusterShape_SigmaIEtaIEta(double sigmaIEta){
		  RECEcalClusterShape_SigmaIEtaIEta.push_back(sigmaIEta);
	  }
	  double getRECEcalClusterShape_SigmaIEtaIEta(unsigned int t){
		  if(RECEcalClusterShape_SigmaIEtaIEta.size() > t) return RECEcalClusterShape_SigmaIEtaIEta[t];
		  return 0;
	  }

	  unsigned int getRECEtaSize(){
		  return RECEta.size();
	  }




   private:
	  double numTriggeredEvents=0;
	  double efficiencyDenominator=0;	//total number of events where there is one GEN electron with pT > 15 GeV in the trackless region, and one tracked electron
	  
	  std::vector<double> RECEta;
	  std::vector<double> RECPt;
	  std::vector<double> RECEcalIso;
	  std::vector<double> RECHcalIso;
	  std::vector<double> RECHoverE;
	  std::vector<double> RECEcalClusterShape;
	  std::vector<double> RECEcalClusterShape_SigmaIEtaIEta;

	  std::string foutName;
      TFile *tree_file;
      void InitNewTree(void);
	

   public:
      bool booked(const std::string histName) const { return hists_.find(histName.c_str())!=hists_.end(); };
      bool bookedTwo(const std::string histName) const { return histsTwo_.find(histName.c_str())!=histsTwo_.end(); };
      bool bookedThree(const std::string histName) const { return histsThree_.find(histName.c_str())!=histsThree_.end(); };

      /// fill histogram if it had been booked before
      void fill(const std::string histName, double value) const { if(booked(histName.c_str())) hists_.find(histName.c_str())->second->Fill(value); };
      void fillTwo(const std::string histName, double valX, double valY) const{  if(bookedTwo(histName.c_str())) histsTwo_.find(histName.c_str())->second->Fill(valX, valY); };
      void fillThree(const std::string histName, double valX, double valY, double valZ) const{  if(bookedThree(histName.c_str())) histsThree_.find(histName.c_str())->second->Fill(valX, valY, valZ); };


      //this takes three 2D histograms, divides two of them, and places the contents of the two divided histogram into the histo (histNameReturned) that called Divide
      void divideTwo(const std::string histNameNumerator, const std::string histNameDenominator, const std::string histNameReturned) const{
	      if(bookedTwo(histNameNumerator.c_str()) && bookedTwo(histNameDenominator.c_str()) && bookedTwo(histNameReturned.c_str()) ){
		      //if all three 2D histos have been declared, then call divide on histNameReturned and pass histNameNumerator, histNameDenominator into Divide as arguments
		      histsTwo_.find(histNameReturned.c_str())->second->Divide( histsTwo_.find(histNameNumerator.c_str())->second, histsTwo_.find(histNameDenominator.c_str())->second );

	      }

      }

      //this gets the number of X axis bins from a 1D, 2D, or 3D histo
      int getXBins(const std::string histName) const {
	      if(bookedTwo(histName.c_str()) ){
		      int binsX = histsTwo_.find(histName.c_str() )->second->GetNbinsX();
		      return binsX;
	      }

	      if(booked(histName.c_str()) ){
		      int binsX = hists_.find(histName.c_str() )->second->GetNbinsX();
		      return binsX;
	      }

	      if(bookedThree(histName.c_str()) ){
		      int binsX = histsThree_.find(histName.c_str() )->second->GetNbinsX();
		      return binsX;
	      }


	      int failsafe = 0;
	      return failsafe;
      }//end getXBins(histName) 

      //this gets the number of Y axis bins from a 2D or 3D histo
      int getYBins(const std::string histName) const {
	      if(bookedTwo(histName.c_str()) ){
		      int binsY = histsTwo_.find(histName.c_str() )->second->GetNbinsY();
		      return binsY;
	      }

	      if(bookedThree(histName.c_str()) ){
		      int binsY = histsThree_.find(histName.c_str() )->second->GetNbinsY();
		      return binsY;
	      }


	      int failsafe = 0;
	      return failsafe;
      }//end getYBins(histName)

      //this returns the contents of bin (x,y) in a 2D histo
      double get2DBinContents(const std::string histName, int xBin, int yBin) const {
	      if(bookedTwo(histName.c_str()) ){
		      double binContents = histsTwo_.find(histName.c_str() )->second->GetBinContent(xBin, yBin);
		      return binContents;
	      }

	      double failsafe = 0.;
	      return failsafe;

      }//end get2DBinContents()

      //this returns the contents of bin xBin in a 1D histo
      double get1DBinContents(const std::string histName, int xBin) const {
	      if(booked(histName.c_str()) ){
		      double binContents = hists_.find(histName.c_str() )->second->GetBinContent(xBin);
		      return binContents;
	      }

	      double failsafe = 0.;
	      return failsafe;

      }//end get1DBinContents()

      //this returns the upper value (right most) corresponding to the right edge of a bin in a 1D histo
      double get1DUpperBinEdge(const std::string histName, int xBin) const {
	      if(booked(histName.c_str()) ){
		      double lowerBinEdge = hists_.find(histName.c_str() )->second->GetBinLowEdge(xBin);
		      double binWidth = hists_.find(histName.c_str() )->second->GetBinWidth(xBin);
		      double upperBinEdge = lowerBinEdge + binWidth;
		      return upperBinEdge;
	      }

	      double failsafe = 0.;
	      return failsafe;

      }//end get1DUpperBinEdge()

      //this sets the contents of bin xBin in a 1D histo
      void set1DBinContents(const std::string histName, int xBin, double content) const {
	      if(booked(histName.c_str()) ){
		      hists_.find(histName.c_str() )->second->SetBinContent(xBin, content);
	      }

      }//end set1DBinContents()


      void set2DBinContents(const std::string histName, int xBin, int yBin, double content) const {
	      if(bookedTwo(histName.c_str()) ){
		      histsTwo_.find(histName.c_str() )->second->SetBinContent(xBin, yBin, content);
	      }

      }//end set2DBinContents()

      double get3DBinContents(const std::string histName, int xBin, int yBin, int zBin) const {
	      if(bookedThree(histName.c_str()) ){
		      double binContents = histsThree_.find(histName.c_str() )->second->GetBinContent(xBin, yBin, zBin);
		      return binContents;
	      }

	      double failsafe = 0.;
	      return failsafe;

      }//end get3DBinContents()

      void set3DBinContents(const std::string histName, int xBin, int yBin, int zBin, double content) const {
	      if(bookedThree(histName.c_str()) ){
		      histsThree_.find(histName.c_str() )->second->SetBinContent(xBin, yBin, zBin, content);
	      }

      }//end set3DBinContents()


void makeAndSaveSingleHisto(TString title, TString filePostfix, TString canvName, TString legEntry, const std::string histName, bool doLogYAxis){
	TString longPathName = "/eos/uscms/store/user/skalafut/HGCal/1D_";

	TH1D * histogram = hists_.find(histName.c_str())->second;
	TString saveFileType = ".gif";
	TString canvasName = canvName;

	TCanvas * c111=new TCanvas(canvasName,canvasName,800,800);
	c111->cd();
	if(doLogYAxis==true){
		c111->SetLogy(1);
		histogram->SetMinimum(1);
	}
	if(doLogYAxis==false){
		histogram->SetMinimum(0);
	}


	histogram->SetLineColor(1);
	histogram->SetLineWidth(1);
	histogram->SetTitle(title);

	TLegend * leg111 = new TLegend(.8,.27,1,.4);
	leg111->AddEntry(histogram,legEntry);

	histogram->Draw("hist");
	leg111->Draw();

	c111->SaveAs(longPathName+filePostfix+saveFileType, "recreate");

}//end makeAndSaveSingleHisto(...)

void makeAndSaveSingle2DHisto(TString title, TString filePostfix, TString canvName, TString legEntry, const std::string histName, bool doLogYAxis){
	TString longPathName = "/eos/uscms/store/user/skalafut/HGCal/2D_";

	TH2D * histogram = histsTwo_.find(histName.c_str())->second;
	TString saveFileType = ".gif";
	TString canvasName = canvName;

	TCanvas * c111=new TCanvas(canvasName,canvasName,800,800);
	c111->cd();
	if(doLogYAxis==true){
		c111->SetLogy(1);
		histogram->SetMinimum(1);
	}
	if(doLogYAxis==false){
		histogram->SetMinimum(0);
	}


	histogram->SetLineColor(1);
	histogram->SetLineWidth(1);
	histogram->SetTitle(title);

	TLegend * leg111 = new TLegend(.8,.27,1,.4);
	leg111->AddEntry(histogram,legEntry);

	histogram->Draw("hist");
	leg111->Draw();

	c111->SaveAs(longPathName+filePostfix+saveFileType, "recreate");

}//end makeAndSaveSingle2DHisto(...)



void makeAndSaveSingle3DHisto(TString title, TString filePostfix, TString canvName, TString legEntry, const std::string histName, bool doLogZAxis){
	TString longPathName = "/eos/uscms/store/user/skalafut/HGCal/3D_";

	TH3D * histogram = histsThree_.find(histName.c_str())->second;
	TString saveFileType = ".gif";
	TString canvasName = canvName;

	TCanvas * c111=new TCanvas(canvasName,canvasName,800,800);
	c111->cd();
	if(doLogZAxis==true){
		c111->SetLogz(1);
		histogram->SetMinimum(1);
	}
	if(doLogZAxis==false){
		histogram->SetMinimum(0);
	}


	histogram->SetLineColor(1);
	histogram->SetLineWidth(1);
	histogram->SetTitle(title);
	histogram->GetXaxis()->SetTitleOffset(1.6);
	histogram->GetYaxis()->SetTitleOffset(1.75);
	histogram->GetZaxis()->SetTitleOffset(1.5);


	TLegend * leg111 = new TLegend(.8,.27,1,.4);
	leg111->AddEntry(histogram,legEntry);

	histogram->Draw("hist");
	leg111->Draw();

	c111->SaveAs(longPathName+filePostfix+saveFileType, "recreate");

}//end makeAndSaveSingle3DHisto(...)

//calculates delta R between two specified (eta, phi) points, and returns the value of delta R
double deltaR(const double ETA, const double PHI, const double eta, const double phi){
	double deltaEta = ETA-eta;
	double deltaPhi = PHI-phi;
	double dR = TMath::Sqrt( TMath::Power(deltaEta,2) + TMath::Power(deltaPhi,2) );
	return dR;

}


void GetMatchedTriggerObjects(
		const edm::Event& iEvent,
		const std::vector<std::string>& trig_names, const double eta, const double phi, const double dRForMatch)
{
	/*
	 * Find all trigger objects that match a vector of trigger names and
	 * are within some minimum dR of a specified eta and phi.
	 */
	// If our vector is empty or the first item is blank
	if (trig_names.size() == 0 || trig_names[0].size() == 0) {
		return;
	}
	bool incrementedTriggeredEvents = false;

	// Load Trigger Event with references to objects 
	edm::InputTag hltTrigInfoTag("hltTriggerSummaryRAW","","TEST");
	edm::Handle<trigger::TriggerEventWithRefs> trig_event;

	iEvent.getByLabel(hltTrigInfoTag, trig_event);
	if (!trig_event.isValid() ){
		std::cout << "No valid hltTriggerSummaryRAW." << std::endl;
		return;
	}

	typedef edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>,float,unsigned int> > ecalCandToValMap;

/*

	//collections for tracked electron candidates
	
	edm::InputTag hltEleGsfTrackIsoTag("hltEgammaEleGsfTrackIso","","TEST");
	edm::Handle<ecalCandToValMap> trackedEleGsfTrackIsoHandle;
	iEvent.getByLabel(hltEleGsfTrackIsoTag, trackedEleGsfTrackIsoHandle);

	edm::InputTag hltGsfTrackVarsDetaTag("hltEgammaGsfTrackVars","Deta","TEST");
	edm::Handle<ecalCandToValMap> trackedGsfTrackVarsDetaHandle;
	iEvent.getByLabel(hltGsfTrackVarsDetaTag, trackedGsfTrackVarsDetaHandle);

	edm::InputTag hltGsfTrackVarsDphiTag("hltEgammaGsfTrackVars","Dphi","TEST");
	edm::Handle<ecalCandToValMap> trackedGsfTrackVarsDphiHandle;
	iEvent.getByLabel(hltGsfTrackVarsDphiTag, trackedGsfTrackVarsDphiHandle);

	edm::InputTag hltGsfTrackVarsMissingHitsTag("hltEgammaGsfTrackVars","MissingHits","TEST");
	edm::Handle<ecalCandToValMap> trackedGsfTrackVarsMissingHitsHandle;
	iEvent.getByLabel(hltGsfTrackVarsMissingHitsTag, trackedGsfTrackVarsMissingHitsHandle);

	edm::InputTag hltGsfTrackVarsOneOESeedMinusOneOPTag("hltEgammaGsfTrackVars","OneOESeedMinusOneOP","TEST");
	edm::Handle<ecalCandToValMap> trackedGsfTrackVarsOneOESeedMinusOneOPHandle;
	iEvent.getByLabel(hltGsfTrackVarsOneOESeedMinusOneOPTag, trackedGsfTrackVarsOneOESeedMinusOneOPHandle);

	edm::InputTag hltGsfTrackVarsOneOESuperMinusOneOPTag("hltEgammaGsfTrackVars","OneOESuperMinusOneOP","TEST");
	edm::Handle<ecalCandToValMap> trackedGsfTrackVarsOneOESuperMinusOneOPHandle;
	iEvent.getByLabel(hltGsfTrackVarsOneOESuperMinusOneOPTag, trackedGsfTrackVarsOneOESuperMinusOneOPHandle);


	edm::InputTag hltTrackedEcalClusterShapeTag("hltEgammaClusterShape","","TEST");
	edm::Handle<ecalCandToValMap> trackedEcalClusterShapeHandle;
	iEvent.getByLabel(hltTrackedEcalClusterShapeTag, trackedEcalClusterShapeHandle);

	edm::InputTag hltTrackedEcalClusterShapeSigmaIEtaIEtaTag("hltEgammaClusterShape","sigmaIEtaIEta5x5","TEST");
	edm::Handle<ecalCandToValMap> trackedEcalClusterShapeSigmaIEtaIEtaHandle;
	iEvent.getByLabel(hltTrackedEcalClusterShapeSigmaIEtaIEtaTag, trackedEcalClusterShapeSigmaIEtaIEtaHandle);

	edm::InputTag hltTrackedEcalIsoTag("hltEgammaEcalPFClusterIso","","TEST");
	edm::Handle<ecalCandToValMap> trackedEcalIsoHandle;
	iEvent.getByLabel(hltTrackedEcalIsoTag, trackedEcalIsoHandle);

	edm::InputTag hltTrackedHoverETag("hltEgammaHoverE","","TEST");
	edm::Handle<ecalCandToValMap> trackedHoverEHandle;
	iEvent.getByLabel(hltTrackedHoverETag, trackedHoverEHandle);

	edm::InputTag hltTrackedHcalIsoTag("hltEgammaHcalPFClusterIso","","TEST");
	edm::Handle<ecalCandToValMap> trackedHcalIsoHandle;
	iEvent.getByLabel(hltTrackedHcalIsoTag, trackedHcalIsoHandle);
*/


	//collections for untracked electron candidates
	edm::InputTag hltNoTrackEcalClusterShapeTag("hltEgammaClusterShapeUnseeded","","TEST");
	edm::Handle<ecalCandToValMap> untrackedEcalClusterShapeHandle;
	iEvent.getByLabel(hltNoTrackEcalClusterShapeTag, untrackedEcalClusterShapeHandle);

	edm::InputTag hltNoTrackEcalClusterShapeSigmaIEtaIEtaTag("hltEgammaClusterShapeUnseeded","sigmaIEtaIEta5x5","TEST");
	edm::Handle<ecalCandToValMap> untrackedEcalClusterShapeSigmaIEtaIEtaHandle;
	iEvent.getByLabel(hltNoTrackEcalClusterShapeSigmaIEtaIEtaTag, untrackedEcalClusterShapeSigmaIEtaIEtaHandle);

	edm::InputTag hltNoTrackEcalIsoTag("hltEgammaEcalPFClusterIsoUnseeded","","TEST");
	edm::Handle<ecalCandToValMap> untrackedEcalIsoHandle;
	iEvent.getByLabel(hltNoTrackEcalIsoTag, untrackedEcalIsoHandle);

	edm::InputTag hltNoTrackHoverETag("hltEgammaHoverEUnseeded","","TEST");
	edm::Handle<ecalCandToValMap> untrackedHoverEHandle;
	iEvent.getByLabel(hltNoTrackHoverETag, untrackedHoverEHandle);

	edm::InputTag hltNoTrackHcalIsoTag("hltEgammaHcalPFClusterIsoUnseeded","","TEST");
	edm::Handle<ecalCandToValMap> untrackedHcalIsoHandle;
	iEvent.getByLabel(hltNoTrackHcalIsoTag, untrackedHcalIsoHandle);

	std::vector<edm::Handle<ecalCandToValMap> > untrackedHandles;
	untrackedHandles.push_back(untrackedEcalClusterShapeHandle);
	untrackedHandles.push_back(untrackedEcalClusterShapeSigmaIEtaIEtaHandle);
	untrackedHandles.push_back(untrackedEcalIsoHandle);
	untrackedHandles.push_back(untrackedHoverEHandle);
	untrackedHandles.push_back(untrackedHcalIsoHandle);


	for (auto& trig_name : trig_names) {
		//loop over the different filter modules that appear in the HLT path.  The names of these modules are specified in the input vector<std::string> called trig_names.
		//std::cout<<"looking at trigger module named "<< trig_name <<std::endl; 
		edm::InputTag filter_tag(trig_name, "", "TEST");

		trigger::size_type filter_index = trig_event->filterIndex(filter_tag);
		
		if(filter_index < trig_event->size()) { //Check that at least one object in the event passed the filter corresponding to filter_index 
			//std::cout<<"at least one object in the event passed filter number "<< filter_index << std::endl;
			//std::cout<<"the name of this filter module is "<< trig_name << std::endl;

			for(int i=0; i<=100; i++){
				//loop over all possible photon ids (integer values)
				//each object that passes a filter is assigned an id # 
				//most ids are either 81 or 92, even if there are more than 2 objects which pass the filter

				//trigger::VRphoton is a typedef to a vector of edm::Refs which points to reco::RecoEcalCandidate objects
				trigger::VRphoton tracklessEleRefs;

				//this fills the vector of RecoEcalCandidate references named tracklessEleRefs with pointers to real RecoEcalCandidate objects
				trig_event->getObjects(filter_index, i, tracklessEleRefs);
				//std::cout<<"when photonId equals "<< i <<" there are "<< tracklessEleRefs.size() <<" different references to RecoEcalCandidate objects"<<std::endl; 

				//now loop over all objects which passed  
				for(unsigned int j=0; j<tracklessEleRefs.size() ; j++){

					std::vector<float> untrackedEleParams;
					std::vector<std::string> untrackedEleParamNames;
					untrackedEleParamNames.push_back("pt");
					untrackedEleParamNames.push_back("eta");
					untrackedEleParamNames.push_back("ecal cluster shape");
					untrackedEleParamNames.push_back("ecal cluster shape sigma IEta IEta");	//this is slightly different from "ecal cluster shape"
					untrackedEleParamNames.push_back("ecal iso");
					untrackedEleParamNames.push_back("H/E");
					untrackedEleParamNames.push_back("hcal iso");

					//for the trackless electron candidate: ecal iso cut <--> filter_index = 5, H/E cut <--> filter_index = 6, 
					//hcal iso cut <--> filter_index = 7

					untrackedEleParams.push_back( tracklessEleRefs[j]->energy()/( TMath::CosH(tracklessEleRefs[j]->eta() ) ) );
					untrackedEleParams.push_back( tracklessEleRefs[j]->eta() );
					std::vector<ecalCandToValMap> valMaps;
					for(unsigned int q=0; q<untrackedHandles.size() ;q++){
						if(untrackedHandles[q].isValid() ){
							valMaps.push_back( *(untrackedHandles[q].product() ) );	//gets a map from the handle, puts map in the last element of a vector
							untrackedEleParams.push_back( ( valMaps[valMaps.size()-1].find(tracklessEleRefs[j]) )->val ); //gets value of variable (ecal iso, H/E, etc) from map, and stores it in a vector

						}

					}//end loop over edm::Handle objects to collections tied to untracked electron candidates
					
					//eta and pT cut on trackless candidate, and dilepton mass cut on tracked+untracked electon candidates will be added later
					//std::cout<<" "<<std::endl;
					//std::cout<<"found a trackless electron candidate with "<<std::endl;
					for(unsigned int w=0; w<untrackedEleParamNames.size() ;w++){
						//std::cout<< untrackedEleParamNames[w] <<" equal to "<< untrackedEleParams[w] <<std::endl;
					}
					//std::cout<<" "<<std::endl;

					if(filter_index == 7){
						//filter_index = 7 corresponds to HCAL iso
						if( std::fabs(tracklessEleRefs[j]->eta()) >= 2.5 && std::fabs(tracklessEleRefs[j]->eta()) < 3.0 ){
							if(deltaR(eta, phi, tracklessEleRefs[j]->eta(), tracklessEleRefs[j]->phi() )  <= dRForMatch){
								//if the REC is matched to a gen electron in the trackless EE region
								//then write the calo iso, H/E, and cluster shape info associated with the REC into vectors
								addRECPt(untrackedEleParams[0]);
								addRECEta(untrackedEleParams[1]);
								addRECEcalClusterShape(untrackedEleParams[2]);
								addRECEcalClusterShape_SigmaIEtaIEta(untrackedEleParams[3]);
								addRECEcalIso(untrackedEleParams[4]);
								addRECHoverE(untrackedEleParams[5]);
								addRECHcalIso(untrackedEleParams[6]);
								if(!incrementedTriggeredEvents){
								   	incrementNumTriggeredEvents();
									incrementedTriggeredEvents = true;	//guarantees numTriggeredEvents only gets incremented by at most once per iEvent object
									std::cout<<"numTriggeredEvents equals "<< getNumTriggeredEvents() <<std::endl;
								}

							}//end deltaR matching filter

						}//end requirement that REC be in trackless EE

					}//end filter_index == 7


/*
					reco::SuperClusterRef toSC = tracklessEleRefs[j]->superCluster();
					std::cout<<"SC associated with RecoEcalCandidate has raw energy equal to "<< toSC->rawEnergy() <<std::endl;
					std::cout<<"SC also has eta width "<< toSC->etaWidth() <<std::endl;
					std::cout<<"SC also has phi width "<< toSC->phiWidth() <<std::endl;
					std::cout<<"SC contains "<< toSC->clustersSize() <<" basic clusters" <<std::endl;
					std::cout<<" "<<std::endl;
*/


				}//end loop over all elements in tracklessEleRefs vector

			}//end loop over photon id values

		}//end if(filter_index...)

	}//end loop over trigger module names

}//end GetMatchedTriggerObjects() 

unsigned int addToPtSortedVector(std::vector<double>& genElePts,double& genPT){
 	//add the double value named genPT to the vector genElePts such that the first element in genElePts is the smallest element in the vector, and
 	//the last element in genElePts is the largest element in the vector
	//return the element # where genPT is placed
	unsigned int vectorSize = genElePts.size();

	if(genElePts.size() < 1){
	   //if genElePts is empty when it is passed to this function
	   genElePts.push_back(genPT);
	   return 0;
 	}

	//if vectorSize >= 1, then loop over all elements of the genElePts vector, insert genPT such that genElePts remains pT sorted, and
	//return the index where genPT was added.  This index will be used by the vectors which store gen electron eta and phi.
	unsigned int i=0;
	for(std::vector<double>::iterator iT = genElePts.begin(); iT != genElePts.end() ; iT++){
		if(genPT< *iT){
			genElePts.insert(iT, genPT);
			return i;
		}

		//if genPT is > any element currently in genElePts
		if(i == (vectorSize -1) ){
			genElePts.push_back(genPT);
			return (i+1);
		}

		i++;	//if genPT is not less than the current element pointed to by the iterator iT, then increase i by one and keep looking for the appropriate place to insert genPT

	}//end for loop

	return 0;

}	

double totalNumEvents;	//total number of events which are analyzed, no requirement on either GEN electron


private:
virtual void beginJob() override;
virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
virtual void endJob() override;

std::map<std::string,TH1D*> hists_;
std::map<std::string,TH2D*> histsTwo_;
std::map<std::string,TH3D*> histsThree_;


//virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
//virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
//virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
//virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
doubleEleTracklessAnalyzer::doubleEleTracklessAnalyzer(const edm::ParameterSet& iConfig)
/*  vtxCollectionTAG(iConfig.getParameter<edm::InputTag>("vertexCollection")),
  BeamSpotTAG(iConfig.getParameter<edm::InputTag>("BeamSpotCollection")),
  electronsTAG(iConfig.getParameter<edm::InputTag>("electronCollection")),
  recHitCollectionEBTAG(iConfig.getParameter<edm::InputTag>("recHitCollectionEB")),
  recHitCollectionEETAG(iConfig.getParameter<edm::InputTag>("recHitCollectionEE")),
  EESuperClustersTAG(iConfig.getParameter<edm::InputTag>("EESuperClusterCollection")),
  rhoTAG(iConfig.getParameter<edm::InputTag>("rhoFastJet")),
  triggerResultsTAG(iConfig.getParameter<edm::InputTag>("triggerResultsCollection")),*/
  //foutName(iConfig.getParameter<std::string>("foutName"))

{
   //now do what ever initialization is needed
   edm::Service<TFileService> fs;

   hists_["GenEta_leadingEle"]=fs->make<TH1D>("GenEta_leadingEle","#eta of leading generator electron; electron #eta;",300,-3.0,3.0);
   hists_["GenEta_subLeadingEle"]=fs->make<TH1D>("GenEta_subLeadingEle","#eta of sub-leading generator electron; electron #eta;",300,-3.0,3.0);

   hists_["GenPt_leadingEle"]=fs->make<TH1D>("GenPt_leadingEle","P_{T} of leading generator electron; electron p_{T} (GeV);",300,0.0,100.0);
   hists_["GenPt_subLeadingEle"]=fs->make<TH1D>("GenPt_subLeadingEle","P_{T} of sub-leading generator electron; electron p_{T} (GeV);",300,0.0,100.0);

   hists_["GenPt_untrackedEle"]=fs->make<TH1D>("GenPt_untrackedEle","P_{T} of untracked generator electron in events with one tracked electron and one untracked electron ; untracked electron p_{T} (GeV);",300,0.0,100.0);


   hists_["EventFraction"]=fs->make<TH1D>("EventFraction","Fraction of events with zero, one, and two untracked GEN electrons in EE; ; event fraction",3,0.0,3.0);

   hists_["HLTRecoEff"]=fs->make<TH1D>("HLTRecoEff","Efficiency of trackless leg of HLT path; ; efficiency",1,0.0,1.0);



   //THIS declaration is here for reference

   //histsThree_["PFClusterSum_HCALovrECAL_gen_eta_energy"]=fs->make<TH3D>("PFClusterSum_HCALovrECAL_gen_eta_energy","Reco E_HCAL/E_ECAL for Pi+ vs gen Pi+ energy and eta", 100, 0., 210., 15, 1.55, 3.0, 30, 0., 15.);


}


doubleEleTracklessAnalyzer::~doubleEleTracklessAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
doubleEleTracklessAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;

	totalNumEvents += 1.0;
	//bool incrementedEffDenom = false;

	/**/
	std::vector<std::string> tracklessModNames;
	//tracklessModNames.push_back("hltL1sL1ZeroBias");
	//tracklessModNames.push_back("hltEGL1SingleEG20ORL1SingleEG22Filter");	//this module is called in the Ele27 sequence (this sequence looks for a tracked electron candidate)
	//tracklessModNames.push_back("hltL1sL1SingleEG20ORL1SingleEG22");	//this appears in the path for the double electron trigger, before the Ele27 and Ele15 sequences

	/*tracklessModNames.push_back("hltEgammaCandidatesWrapperUnseeded");
	tracklessModNames.push_back("hltEG15WPYYtracklessEtFilterUnseeded");
	tracklessModNames.push_back("hltEle15WPYYtracklessEcalIsoFilter");
	tracklessModNames.push_back("hltEle15WPYYtracklessHEFilter");
	*/
	tracklessModNames.push_back("hltEle15WPYYtracklessHcalIsoFilter");
	double maxDRForMatch = 0.20;

	//GetMatchedTriggerObjects(iEvent, tracklessModNames, somEta, somePhi, dRForMatch);
	/**/

	//tree->Fill();

	InputTag genParticleTag("genParticles","","SIM");
	Handle<std::vector<reco::GenParticle> > genPart;
	iEvent.getByLabel(genParticleTag, genPart);

	//std::cout<<"declared and initialized handle object to reco::GenParticle collection"<<std::endl;

	double gPt=0;
	double gEta=0;
	double gPhi=0;

	//the last two elements in these vectors represent the leading (last element) and subleading (2nd to last element) GEN electrons
	std::vector<double> genElectronPTs;
	std::vector<double> genElectronEtas;
	std::vector<double> genElectronPhis;

	for(int i=0; i<100 ;i++){
		//there should be no events with 100 gen level electrons and positrons
		genElectronEtas.push_back(0.0);
		genElectronPhis.push_back(0.0);
	}


	for(std::vector<reco::GenParticle>::const_iterator genIt=genPart->begin(); genIt != genPart->end(); genIt++){

		bool isZDecay = false;

		if( genIt->numberOfMothers() > 0 && std::fabs(genIt->pdgId()) == 11 ){
			for (unsigned int a=0; !isZDecay && a< (genIt->numberOfMothers()) ; a++) {
				if ( std::fabs((genIt->mother(a))->pdgId()) == 23 ) {
					isZDecay = true;
				}
			}//end loop over all mothers of the GenParticle electron or positron

		}

		if(isZDecay){
			gEta = genIt->eta();
			gPhi = genIt->phi();
			gPt = genIt->pt();
			unsigned int index = addToPtSortedVector(genElectronPTs,gPt);
			genElectronEtas[index] = gEta;
			genElectronPhis[index] = gPhi;
			//if(std::fabs(gEta) >= 2.5 && std::fabs(gEta) < 3.0 && gPt > 15.0) std::cout<<"found a trackless EE lepton"<<std::endl;
			//if(std::fabs(gEta) < 2.5 && gPt > 27.0) std::cout<<"found a tracked lepton"<<std::endl;


		}//end filter which saves kinematic info for GEN electrons and positrons which came from a Z decay 

	}//end loop over GenParticle

	bool haveTracklessEleCand = false;
	for(std::vector<reco::GenParticle>::const_iterator genIt=genPart->begin(); genIt != genPart->end(); genIt++){
		if( std::fabs(genIt->pdgId()) == 11 ){
			if(genIt->pt() > 15.0 && std::fabs(genIt->eta()) >= 2.5 && std::fabs(genIt->eta()) < 3.0 ){
				haveTracklessEleCand = true;
				break;
			}
		}

	}//end loop over GenParticle, looking for trackless electron at GEN lvl

	/**/
	for(std::vector<reco::GenParticle>::const_iterator genIt=genPart->begin(); genIt != genPart->end(); genIt++){
		if( std::fabs(genIt->pdgId()) == 11 ){
			if(genIt->pt() > 27.0 && std::fabs(genIt->eta()) < 2.5 && haveTracklessEleCand){
				incrementEfficiencyDenominator();
				break;
			}
		}

	}//end loop over GenParticle, looking for tracked electron at GEN lvl

	/**/


	//DON'T USE the size of the genElectronEtas or genElectronPhis vectors
	unsigned int length = genElectronPTs.size();
	bool oneUntrackedElectron = false;
	bool twoUntrackedElectrons = false;


	//count event if there is an untracked electron with pT > 15.0 GeV
	//determine the number of untracked EE electrons in the event
	if(length >= 2){
		//std::cout<<"leading electron has eta of "<< genElectronEtas[length-1] << std::endl;
		//std::cout<<"sub-leading electron has eta of "<< genElectronEtas[length-2] << std::endl;

		if( std::fabs(genElectronEtas[length-1]) >= 2.5 && std::fabs(genElectronEtas[length-1]) < 3.0 && std::fabs(genElectronEtas[length-2]) >= 2.5 && std::fabs(genElectronEtas[length-2]) < 3.0){
			twoUntrackedElectrons = true;

		}


		if(!twoUntrackedElectrons && ( (std::fabs(genElectronEtas[length-1]) >= 2.5 && std::fabs(genElectronEtas[length-1]) < 3.0) || (std::fabs(genElectronEtas[length-2]) >= 2.5 && std::fabs(genElectronEtas[length-2]) < 3.0) ) ){
			oneUntrackedElectron = true;
			if( std::fabs(genElectronEtas[length-1]) >= 2.5 && std::fabs(genElectronEtas[length-1]) < 3.0 ){
				fill("GenPt_untrackedEle", genElectronPTs[length-1]);
				GetMatchedTriggerObjects(iEvent, tracklessModNames, genElectronEtas[length-1], genElectronPhis[length-1], maxDRForMatch);
			}

			if( std::fabs(genElectronEtas[length-2]) >= 2.5 && std::fabs(genElectronEtas[length-2]) < 3.0 ){
			   	fill("GenPt_untrackedEle", genElectronPTs[length-2]);
				GetMatchedTriggerObjects(iEvent, tracklessModNames, genElectronEtas[length-2], genElectronPhis[length-2], maxDRForMatch);
			}

		}


	}


	for(std::vector<reco::GenParticle>::const_iterator genIt=genPart->begin(); genIt != genPart->end(); genIt++){
		if(length < 2) break;
		if(genIt->pt() == genElectronPTs[length-2]){
			fill("GenEta_subLeadingEle",genIt->eta() );
			fill("GenPt_subLeadingEle",genIt->pt() );
		}

		if(genIt->pt() == genElectronPTs[length-1]){
			fill("GenEta_leadingEle",genIt->eta() );
			fill("GenPt_leadingEle",genIt->pt() );
		}

	}//end loop over GenParticle

	//first bin on the plot is bin # 1!!

	for(int i=1; i<=getXBins("EventFraction"); i++){
		if( getXBins("EventFraction") < 3) break;	//shouldn't need this, but just in case
		if(i==1 && !oneUntrackedElectron && !twoUntrackedElectrons ){
			set1DBinContents("EventFraction",i, get1DBinContents("EventFraction",i) + 1.0);
			break;
		}
		
		if(i==2 && oneUntrackedElectron){
			set1DBinContents("EventFraction",i, get1DBinContents("EventFraction",i) + 1.0);
			break;
		}
		
		if(i==3 && twoUntrackedElectrons){
			set1DBinContents("EventFraction",i, get1DBinContents("EventFraction",i) + 1.0);
			break;
		}

	}



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
doubleEleTracklessAnalyzer::beginJob()
{
/*
  tree_file = new TFile(foutName.c_str(), "recreate");
  if(tree_file->IsZombie()){
    throw cms::Exception("OutputError") <<  "Output tree not created (Zombie): " << foutName;
    return;
  }
  tree_file->cd();
  
  //now do what ever initialization is needed
  tree = new TTree("selected","selected");
  tree->SetDirectory(tree_file);

  //InitNewTree();
*/

}

// ------------ method called once each job just after ending the event loop  ------------
void 
doubleEleTracklessAnalyzer::endJob() 
{
	//loop over bins of "EventFraction", divide each bin content by totalNumEvents, then reset the bin content to the old content divided by totalNumEvents

	for(int i=1; i<=getXBins("EventFraction"); i++){
		if( getXBins("EventFraction") < 3) break;	//shouldn't need this, but just in case
	
		std::cout<<"bin # "<< i <<" content equals "<< get1DBinContents("EventFraction",i) <<std::endl;
		set1DBinContents("EventFraction",i, (get1DBinContents("EventFraction",i)/totalNumEvents) );
		std::cout<<"bin # "<< i <<" content equals "<< get1DBinContents("EventFraction",i) <<std::endl;
	
	}

   std::cout<< "the trackless leg triggered "<< getNumTriggeredEvents() << " events out of "<< getEfficiencyDenominator() << " total events" <<std::endl;
   set1DBinContents("HLTRecoEff",1, getNumTriggeredEvents()/getEfficiencyDenominator());
   std::cout<<"RECEta size equals "<< getRECEtaSize() << std::endl;



	/*
  //save the tree into the file
  tree_file->cd();
  tree->Write();
  tree_file->Close();
*/

}

// ------------ method called when starting to processes a run  ------------
/*
void 
doubleEleTracklessAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
doubleEleTracklessAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
doubleEleTracklessAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
doubleEleTracklessAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
doubleEleTracklessAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

/*
void doubleEleTracklessAnalyzer::InitNewTree(void){

  std::cout << "[STATUS] InitNewTree" << std::endl;
  if(tree==NULL) return;
  tree->Branch("runNumber",     &runNumber,     "runNumber/I");
  tree->Branch("eventNumber",   &eventNumber, "eventNumber/l");
  tree->Branch("lumiBlock",     &lumiBlock,     "lumiBlock/I");
  tree->Branch("runTime",       &runTime,         "runTime/i");
  
  tree->Branch("mcGenWeight",   &mcGenWeight, "mcGenWeight/F");

  tree->Branch("nPU", nPU, "nPU[1]/I");
  tree->Branch("rho", &rho, "rho/F");
  tree->Branch("nPV", &nPV, "nPV/I");


  tree->Branch("chargeEle",   chargeEle,    "chargeEle[2]/I");	//[nEle]
  tree->Branch("etaSCEle",      etaSCEle,       "etaSCEle[2]/F");	//[nSCEle]
  tree->Branch("phiSCEle",      phiSCEle,       "phiSCEle[2]/F");	//[nSCEle]

  tree->Branch("PtEle",       PtEle,        "PtEle[2]/F");

  tree->Branch("seedXSCEle",           seedXSCEle,      "seedXSCEle[2]/F");
  tree->Branch("seedYSCEle",           seedYSCEle,      "seedYSCEle[2]/F");
  tree->Branch("seedEnergySCEle", seedEnergySCEle, "seedEnergySCEle[2]/F");

  tree->Branch("gainEle", gainEle, "gainEle[2]/b");

  tree->Branch("energyMCEle", energyMCEle, "energyMCEle[2]/F");
  tree->Branch("energySCEle", energySCEle, "energySCEle[2]/F");
  tree->Branch("rawEnergySCEle", rawEnergySCEle, "rawEnergySCEle[2]/F");
  tree->Branch("esEnergySCEle", esEnergySCEle, "esEnergySCEle[2]/F");


  tree->Branch("R9Ele", R9Ele, "R9Ele[2]/F");

  tree->Branch("e5x5SCEle", e5x5SCEle, "e5x5SCEle[2]/F");

  tree->Branch("invMass",    &invMass,      "invMass/F");   // invariant mass ele+SC
  tree->Branch("invMass_SC", &invMass_SC,   "invMass_SC/F"); // invariant mass SC+SC


  tree->Branch("invMass_MC", &invMass_MC, "invMass_MC/F");

  tree->Branch("etaMCEle",      etaMCEle,       "etaMCEle[2]/F");	//[nEle]
  tree->Branch("phiMCEle",      phiMCEle,       "phiMCEle[2]/F");	//[nEle]

  tree->Branch("nHitsSCEle", nHitsSCEle, "nHitsSCEle[2]/I");

  tree->Branch("sigmaIEtaIEtaSCEle", sigmaIEtaIEtaSCEle, "sigmaIEtaIEtaSCEle[2]/F");
  tree->Branch("sigmaIEtaIEtaSCEle", sigmaIEtaIEtaSCEle, "sigmaIEtaIEtaSCEle[2]/F");

  return;
}

//negative index means the corresponding electron does not exist
void doubleEleTracklessAnalyzer::TreeSetSingleElectronVar(const pat::Electron& electron1, int index){

  if(index<0){
    PtEle[-index] 	  = 0;  
    chargeEle[-index] = 0;
    etaEle[-index]    = 0; 
    phiEle[-index]    = 0;
    return;
  }   

  PtEle[index]     = electron1.et();  
  chargeEle[index] = electron1.charge();
  etaEle[index]    = electron1.eta(); 
  phiEle[index]    = electron1.phi();
}

void doubleEleTracklessAnalyzer::TreeSetSingleElectronVar(const reco::SuperCluster& electron1, int index){

  if(index<0){
    PtEle[-index] 	  = 0;
    chargeEle[-index] = 0;
    etaEle[-index]    = 0;
    phiEle[-index]    = 0;
    return;
  }

//checks

  PtEle[index]     = electron1.energy()/cosh(electron1.eta());
  chargeEle[index] = -100; // dont know the charge for SC
  etaEle[index]    = electron1.eta(); // eta = etaSC
  phiEle[index]    = electron1.phi();
}

void doubleEleTracklessAnalyzer::TreeSetDiElectronVar(const pat::Electron& electron1, const reco::SuperCluster& electron2){
  
  TreeSetSingleElectronVar(electron1, 0);
  TreeSetSingleElectronVar(electron2, 1);

  double t1=TMath::Exp(-etaEle[0]);
  double t2=TMath::Exp(-etaEle[1]);
  double t1q = t1*t1;
  double t2q = t2*t2;

  double angle=1- ( (1-t1q)*(1-t2q)+4*t1*t2*cos(phiEle[0]-phiEle[1]))/( (1+t1q)*(1+t2q) );


  invMass = sqrt(2*electron1.energy()*electron2.energy() *angle);
  invMass_e5x5   = sqrt(2*electron1.e5x5()*(clustertools->e5x5(*electron2.seed())) * angle);

}
*/


//define this as a plug-in
DEFINE_FWK_MODULE(doubleEleTracklessAnalyzer);
