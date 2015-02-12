import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) ) 

process.options = cms.untracked.PSet(
	wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
		#'file:/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/signalTest_contains_HLT_objects.root'
		#'file:/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/Test_signal_contains_HLT_objects.root'
		'file:/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/signal_sample_with_HLT_objects.root'
		

		#DY->ee files
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_1.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_10.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_11.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_2.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_3.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_4.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_5.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_6.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_7.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_8.root',
		#'root://cms-xrd-global.cern.ch//store/user/skalafut/doubleElectronHLT/dyToEEWithHLT/outputFULL_DYtoEE_13TeV_M_50_25ns_40PU_RAW_to_HLTObjects_9.root',

    )
)

#process.demo = cms.EDAnalyzer('doubleEleTracklessAnalyzer',
#    #foutName = cms.untracked.string("testTreeFile.root")
#)

#this analyzer will make distributions of tracked and trackless leg cut variables
#before any tracked or trackless leg filters are applied
process.recoAnalyzerZero = cms.EDAnalyzer('recoAnalyzerZero',
		treeName = cms.string("recoTreeBeforeTriggerFilters"),
		trackedElectronCollection = cms.InputTag("hltEgammaCandidates","","TEST"),
		tracklessElectronCollection = cms.InputTag("hltEgammaCandidatesUnseeded","","TEST"),
		genTrackedElectronCollection = cms.InputTag("","",""),
		genTracklessElectronCollection = cms.InputTag("","","")
	
		)

#this analyzer will be used for Z->ee signal evts where dR matching btwn GEN and HLT objects should be required
#process.recoAnalyzerOne = cms.EDAnalyzer('recoAnalyzerOne',
#		trackedElectronCollection = cms.InputTag("hltEgammaCandidates","","TEST"),
#		tracklessElectronCollection = cms.InputTag("hltEgammaCandidatesUnseeded","","TEST"),
#		genTrackedElectronCollection = cms.InputTag("need something here","","and here"),
#		genTracklessElectronCollection = cms.InputTag("need something here","","and here")
#	
#		)



process.TFileService = cms.Service("TFileService",
	fileName = cms.string('experiment.root')
	#fileName = cms.string('/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/signal_ALLevts_very_loose_trackless_leg.root')
	#fileName = cms.string('/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/bkgnd_ALLevts_very_loose_trackless_leg.root')
	#fileName = cms.string('/afs/cern.ch/work/s/skalafut/public/doubleElectronHLT/unmatched_signal_ALLevts_very_loose_trackless_leg.root')
	
)


process.p = cms.Path(process.recoAnalyzerZero)
