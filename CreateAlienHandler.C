AliAnalysisGrid *CreateAlienHandler(Bool_t useParFiles) 
 {


        TString sdataset = "2015";  


	AliAnalysisAlien *plugin = new AliAnalysisAlien();
	plugin->SetUser("mhaque");



	plugin->AddIncludePath("-I. -I$ALICE_ROOT/include-g -I$ALICE_PHYSICS/include -g -I$ROOTSYS/include -g -I$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY -g");

	if(!useParFiles){
	  plugin->SetAdditionalLibs("libPWGflowBase.so libPWGflowTasks.so AliFlowAnalysisWithMixedHarmonicsForward.cxx AliFlowAnalysisWithMixedHarmonicsForward.h AliAnalysisTaskMixedHarmonicsForward.cxx AliAnalysisTaskMixedHarmonicsForward.h");
	}
        else{
	  plugin->SetAdditionalLibs("libPWGflowBase.so AliFlowAnalysisWithMixedHarmonicsForward.cxx AliFlowAnalysisWithMixedHarmonicsForward.h AliAnalysisTaskMixedHarmonicsForward.cxx AliAnalysisTaskMixedHarmonicsForward.h");
	}


	plugin->SetAnalysisSource("AliFlowAnalysisWithMixedHarmonicsForward.cxx AliAnalysisTaskMixedHarmonicsForward.cxx");

	plugin->SetOverwriteMode(kTRUE);       // Set overwrite mode.

	//Set the run mode (can be "full", "test", "offline", "submit" or "terminate")
	plugin->SetRunMode("test");        

	// Are you before the last stage?
	Bool_t pre_final_stage  = kTRUE;       // kTRUE; only kFALSE when downloading !!!!
	
      //plugin->SetAliPhysicsVersion("vAN-20170130-1");
        plugin->SetAliPhysicsVersion("vAN-20170724-1");   
	   

 if(sdataset=="2010"){
    plugin->SetGridDataDir("/alice/data/2010/LHC10h");
    plugin->SetDataPattern("*ESDs/pass2/AOD160/*AOD.root");
    plugin->SetRunPrefix("000");                   
    
    Int_t runArray[] = {139505};
  //Int_t runArray[] = {139510, 139507, 139505, 139503, 139465, 139438, 139437, 139360, 139329, 139328, 139314, 139310, 139309, 139173, 139107, 139105, 139038, 139037,139036, 139029, 139028, 138872, 138871, 138870, 138837, 138732, 138730, 138666, 138662, 138653, 138652, 138638, 138624, 138621, 138583, 138582, 138579, 138578, 138534, 138469, 138442, 138439, 138438, 138396, 138364, 138275, 138225, 138201, 138197, 138192, 138190, 137848, 137844, 137752, 137751, 137724, 137722, 137718, 137704, 137693, 137692, 137691, 137686, 137685, 137639, 137638, 137608, 137595, 137549, 137546, 137544, 137541, 137539, 137531, 137530, 137443, 137441, 137440, 137439, 137434, 137432, 137431, 137243, 137236, 137235, 137232, 137231, 137161, 137162}; // very bad run: 138469, 137638, 137639, Ilya.
 }


  if(sdataset=="2011"){
  // LHC11h
    plugin->SetGridDataDir("/alice/data/2011/LHC11h_2");
    plugin->SetDataPattern("*AOD145/*AOD.root");
    plugin->SetRunPrefix("000");   // real data // LHC11h, TPC good runs
    Int_t runArray[] = {167915};//, 
    //Int_t runArray[] = {168115, 168460, 169035, 169238, 169859, 170228, 167920, 168310, 168464, 169091, 169411, 169923, 170230, 167985, 168311, 168467, 169094, 169415, 170027, 170268, 167987, 168322, 168511, 169138, 169417, 170081, 170269, 167988, 168325, 168512, 169144, 169835, 170155, 170270, 168069, 168341, 168514, 169145, 169837, 170159, 170306, 168076, 168342, 168777, 169148, 169838, 170163, 170308, 168105, 168361, 168826, 169156, 169846, 170193, 170309, 168107, 168362, 168988, 169160, 169855, 170203, 168108, 168458, 168992, 169167, 169858, 170204};
  }



  if(sdataset=="2015"){
  // LHC15o - high IR
  plugin->SetGridDataDir("/alice/data/2015/LHC15o");
  plugin->SetDataPattern("*/pass1/AOD/*AOD.root");
  plugin->SetRunPrefix("000");  
  Int_t runArray[] = {246858};//
//Int_t runArray[] = {246858,246540}; // lowest event runs
//Int_t runArray[] = {246994, 246991, 246989, 246984, 246982, 246980, 246948, 246945, 246928, 246871, 246870, 246867, 246865, 246864, 246859, 246858, 246851, 246847, 246846, 246845, 246844, 246810, 246809, 246808, 246807, 246805, 246804, 246766, 246765, 246763, 246760, 246759, 246758, 246757, 246751, 246750, 246676, 246675, 246540, 246495, 246493, 246488, 246487, 246434, 246431, 246428, 246424, 246276, 246275, 246272, 246271, 246225, 246222, 246217, 246185, 246182, 246181, 246180, 246178, 246153, 246152, 246151, 246148, 246115, 246113, 246089, 246087, 246053, 246052, 246049, 246048, 246042, 246037, 246036, 246012, 246003, 246001, 245963, 245954, 245952, 245949, 245923, 245833, 245831, 245829, 245705, 245702, 245700, 245692, 245683};
  }



  for(Int_t i = 0; i < sizeof(runArray); i++) 
  {
    if(i==sizeof(runArray)/sizeof(runArray[1]))
    break;
    plugin->AddRunNumber(runArray[i]);           
   }

  //plugin->SetOutputToRunNo(kTRUE);
     plugin->SetOutputToRunNo(kFALSE);

  if(sdataset=="2015"){
     plugin->SetGridWorkingDir("zdc2015h_noRunout");
     plugin->SetAnalysisMacro("ZDCAnalysis2015h.C"); 
     plugin->SetExecutable("ZDCAnalysis2015h.sh");
     plugin->SetJDLName("ZDCAnalysis2015h.jdl");
   }
  else if(sdataset=="2011"){
     plugin->SetGridWorkingDir("CME_test11");
     plugin->SetAnalysisMacro("CME_2011h.C"); 
     plugin->SetExecutable("CME_2011h.sh");
     plugin->SetJDLName("CME_2011h.jdl");
   }
  else if(sdataset=="2010"){
     plugin->SetGridWorkingDir("CME_test10");
     plugin->SetAnalysisMacro("CME_2010h.C"); 
     plugin->SetExecutable("CME_2010h.sh");
     plugin->SetJDLName("CME_2010h.jdl");
   }


  if(useParFiles)
   {
     plugin->EnablePackage("PWGflowTasks.par");
   }

     plugin->SetGridOutputDir("output");   
     plugin->SetDefaultOutputs(kTRUE);
     plugin->SetSplitMaxInputFileNumber(8);
     plugin->SetNrunsPerMaster(4);
     plugin->SetTTL(14000);    // 3hr = 10800, 4hr= 14400, 6hr = 21600,
     plugin->SetKeepLogs(kTRUE);
     plugin->SetMergeViaJDL(pre_final_stage);
     plugin->SetMaxMergeStages(1);

     plugin->SetNtestFiles(1);

     return plugin;

 }//main ends


