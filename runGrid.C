#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"

void runGrid() {
	Bool_t useParFiles = kFALSE;
	// load libraries
	gSystem->Load("libCore.so");
	gSystem->Load("libTree.so");
	gSystem->Load("libGeom");
	gSystem->Load("libVMC");
	gSystem->Load("libXMLIO");
	gSystem->Load("libPhysics");
	gSystem->Load("libSTEERBase");
	gSystem->Load("libESD");
	gSystem->Load("libAOD");
	gSystem->Load("libANALYSIS");
	gSystem->Load("libANALYSISalice");
	gSystem->Load("libANALYSISaliceBase");
	gSystem->Load("libCORRFW");
	gSystem->Load("libOADB");
	gSystem->Load("libPWGflowBase.so");
	if(!useParFiles)
        gSystem->Load("libPWGflowTasks.so");
	//rihan:how par file system works?
	if(useParFiles) AliAnalysisAlien::SetupPar("PWGflowTasks");
	gSystem->Load("libqpythia");
	gSystem->Load("libEGPythia6");
	gSystem->Load("libAliPythia6");
	gSystem->Load("libAliPythia8");
	gSystem->Load("libTHerwig");
	gSystem->Load("libHERWIG");




	gROOT->ProcessLine(".include $ALICE_ROOT/include");
	gROOT->ProcessLine(".include $ALICE_PHYSICS/include");
	gROOT->ProcessLine(".include $ROOTSYS/include");
	gROOT->LoadMacro("CreateAlienHandler.C"); 	                   


	AliAnalysisAlien *alienHandler = CreateAlienHandler(useParFiles);  // rihan:This is the first object created.
	if (!alienHandler) return;

	AliAnalysisManager *mgr    = new AliAnalysisManager("testRihan");  // Create the analysis manager
	mgr->SetGridHandler(alienHandler);                                 // Connect plug-in to the analysis manager

	AliAODInputHandler *inputH = new AliAODInputHandler(); 	           // Create an input handler: 
	mgr->SetInputEventHandler(inputH);

	// AliMCEventHandler* handler = new AliMCEventHandler();           // for MC Data
	// handler->SetReadTR(false);
	// mgr->SetMCtruthEventHandler(handler);

	TGrid::Connect("alien://");

 
	gROOT->LoadMacro("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"); // Needed for LHC2015o
	AliMultSelectionTask *task = AddTaskMultSelection(kFALSE);            // kFALSE == User mode, kTRUE == Calibration mode
        task->SetSelectedTriggerClass(AliVEvent::kINT7);                      
        mgr->AddTask(task);

        //gROOT->LoadMacro("$ALICE_PHYSICS/PWGCF/FLOW/macros/AddTaskFlowCentrality.C");  
	//gROOT->LoadMacro("$ALICE_PHYSICS/PWGCF/FLOW/macros/AddTaskVZERO.C");  
        //AddTaskVZERO(); put the argument

       //gROOT->LoadMacro("AddTaskFlowCentrality.C");  
       //AddTaskFlowCentrality(0,10,"AnalysisResults");
       //AddTaskFlowCentrality(10,20,"AnalysisResults");

         gROOT->LoadMacro("$ALICE_PHYSICS/PWGCF/FLOW/macros/AddTaskZDCEP.C");
         AddTaskZDCEP("alien:///alice/cern.ch/user/j/jmargutt/15oHI_ZDCcalibVar_CenVtxCen_VtxRbR_Ecom_EcomVtx_Cen_VtxFit7_EZDCVtx3D.root");

         //gROOT->LoadMacro("AddTaskCMEAnalysisZDC.C");  
         //AddTaskCMEAnalysisZDC(
         //kTRUE,2015,kTRUE,kTRUE,AliFlowEventCuts::kVZERO,"Qa",0.0,kFALSE,1,-1,-1, 0,-1,kFALSE,kFALSE,kTRUE,kFALSE,kFALSE
         //);



	 gROOT->LoadMacro("AliFlowAnalysisWithMixedHarmonicsForward.cxx++g");
 	 gROOT->LoadMacro("AliAnalysisTaskMixedHarmonicsForward.cxx++g");
         //gROOT->LoadMacro("$ALICE_PHYSICS/PWGCF/FLOW/macros/parity/AddTaskCMEAnalysis.C");

         gROOT->LoadMacro("AddTaskCMEAnalysisForward.C");  
         AddTaskCMEAnalysisForward(
         kTRUE,2015,kTRUE,kTRUE,AliFlowEventCuts::kVZERO,"Qa",0.0,kFALSE,1,-1,-1, 0,-1,kFALSE,kFALSE,kTRUE,kFALSE,kFALSE
			    );


	if (!mgr->InitAnalysis()) 
        {
	  printf("Impossible to initialize the manager!\n");
	  return;
	}

      //mgr->SetUseProgressBar(1, 25);  
      //mgr->SetDebugLevel(2);
	mgr->PrintStatus();     
           
	mgr->StartAnalysis("grid");          	// Start analysis in grid.
	
}


