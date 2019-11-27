#ifndef _LGND_JSONREADER_HH
#define _LGND_JSONREADER_HH
//--------------------------
#include <fstream>
#include <vector>
#include "globals.hh"
//--------------------------
class LGND_JSONReader
{
public:
  LGND_JSONReader();
  LGND_JSONReader(const G4String &inputFile);
  ~LGND_JSONReader();

  std::vector<G4double> ReadDetectorRis(const G4String &serialNum);
  std::vector<G4double> ReadDetectorRos(const G4String &serialNum);
  std::vector<G4double> ReadDetectorZs(const G4String &serialNum);
  std::vector<G4String> ReadCryostats(const G4String &serialNum);
  std::vector<G4String> ReadCrystalAssemblyList(const G4String &serialNum);
  std::vector<G4String> ReadAssemblyStringList (const G4String &serialNum);
  std::vector<G4String> ReadCrystalAssembly(const G4String &serialNum);
  std::vector<G4String> ReadCustom(const G4String &serialNum, const G4String &type, const G4String &param);

  G4bool isFileOpen() {return fInputFile.is_open();}

  void SetDelimiters(G4String delimiters) {fDelimiters = delimiters;}
  std::vector<G4String> Tokenize(G4String separators, G4String input);

private:

  G4bool SearchFromCurrentPos(G4String parameter); //return whether a parameter is found. Remember that the ifstream keeps on flowin'.
  //std::vector<G4String> SearchParameter(G4String parameter); //return a vector of parameters and value.

  std::ifstream fInputFile;
  std::vector<G4String> fCurrentLine;
  G4String fDelimiters;
};

#endif
