{
  printf("\n this is rootlogon for MaGeLAr \n");
  TString arch=gSystem->GetBuildArch();
  gROOT->LoadMacro("util.C");
  cout << " arch is " << arch << endl; 
  gSystem->AddIncludePath(" -I. -I./obj/ -I$MAGEDIR/io/obj");
  printf(" include path %s \n\n",gSystem->GetIncludePath());
  gSystem->AddDynamicPath("/usr/local/lib:$MAGEDIR/io/obj");
  printf(" dynamic path %s \n\n",gSystem->GetDynamicPath());
  
  int iload = gSystem->Load("/usr/local/lib/libCLHEP-Random-2.4.1.0.so");
  printf(" loaded libCLHEP-Random-2.4.1.0.so = %i zero is success! \n",iload);
  iload = gSystem->Load("/home/admin/MGDO/Root/libMGDOBase.so");
  printf(" loaded libMGDOBase.so = %i zero is success! \n",iload);
  iload = gSystem->Load("/home/admin/MGDO/Root/libMGDOTransforms.so");
  printf(" loaded libMGDOTransforms.so = %i zero is success! \n",iload);
  iload = gSystem->Load("/home/admin/MGDO/Root/libMGDORoot.so");
  printf(" loaded libMGDORoot.so = %i zero is success! \n",iload);
  iload = gSystem->Load("$MAGEDIR/lib/libLegendRoot.so");
  printf(" loaded $MAGEDIR/lib/libLegendRoot.so = %i zero is success \n",iload);
}

