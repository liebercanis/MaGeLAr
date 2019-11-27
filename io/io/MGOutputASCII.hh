//---------------------------------------------------------------------------//
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//                                                                           //
//                                                                           //
//                         MaGe Simulation                                   //
//                                                                           //
//      This code implementation is the intellectual property of the         //
//      MAJORANA and Gerda Collaborations. It is based on Geant4, an         //
//      intellectual property of the RD44 GEANT4 collaboration.              //
//                                                                           //
//                        *********************                              //
//                                                                           //
//    Neither the authors of this software system, nor their employing       //
//    institutes, nor the agencies providing financial support for this      //
//    work  make  any representation or  warranty, express or implied,       //
//    regarding this software system or assume any liability for its use.    //
//    By copying, distributing or modifying the Program (or any work based   //
//    on on the Program) you indicate your acceptance of this statement,     //
//    and all its terms.                                                     //
//                                                                           //
//bb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nubb0nu//
//---------------------------------------------------------------------------//
/**                                                            
 * $Id: MGOutputASCII.hh,v 1.1 2006-01-24 02:56:48 jasondet Exp $
 *      
 * CLASS DECLARATION:  MGOutputASCII.hh
 *
 * DESCRIPTION: 
 * Abstract base class for ASCII output file. 
 * 
 * AUTHOR: J. Detwiler
 * CONTACT: 
 * FIRST SUBMISSION: 
 * 
 * REVISION:
 *
 */

#ifndef _MGOUTPUTASCII_HH
#define _MGOUTPUTASCII_HH 

#include <fstream>

#include "io/MGVOutputManager.hh"

class MGOutputASCII : public MGVOutputManager
{
  public:
    MGOutputASCII();
    virtual ~MGOutputASCII() {}

    void OpenFile();
    void CloseFile();

    virtual void DefineSchema() {} // not used

  protected:
    std::ofstream fFile;
};

#endif
