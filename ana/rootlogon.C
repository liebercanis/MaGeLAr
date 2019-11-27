{
  printf("\n this is rootlogon for bacon \n");
  TString arch=gSystem->GetBuildArch();
  gROOT->LoadMacro("util.C");
  cout << " arch is " << arch << endl; 
  gSystem->AddIncludePath(" -I. -I./obj/");
  printf(" include path %s \n\n",gSystem->GetIncludePath());
  gSystem->AddDynamicPath("/usr/local/lib");
  printf(" dynamic path %s \n\n",gSystem->GetDynamicPath());
  
  int iload = gSystem->Load("/usr/local/lib/libCLHEP-Random-2.4.1.0.so");
  printf(" loaded libCLHEP-Random-2.4.1.0.so = %i zero is success! \n",iload);
  iload = gSystem->Load("/home/admin/MGDO/Root/libMGDORoot.so");
  printf(" loaded libMGDORoot.so = %i zero is success! \n",iload);
}

