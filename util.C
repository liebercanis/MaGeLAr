
void browse() 
{
 TBrowser* browser = new TBrowser();
 gSystem->Load("libTreeViewer");
 printf(" browse \n");
}

void dir() 
{
  gDirectory->ls("-m");
}


