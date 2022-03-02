/// \file Cresst_VetoSetUp.hh
/// \brief Definition of the Cresst_VetoSetUp class

#ifndef Cresst_Veto_h
#define Cresst_Veto_h 1
//#include "../include/Cresst_DetectorConst.hh"
#include <G4VUserDetectorConstruction.hh>
//#include <G4UserLimits.hh>
//#include <globals.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

class Cresst_VetoSetUp : public G4VUserDetectorConstruction
{
    public:
        Cresst_VetoSetUp(G4int _d) : G4VUserDetectorConstruction() {d = _d;}
        virtual ~Cresst_VetoSetUp() {};

        virtual G4VPhysicalVolume* Construct();
        std::vector<std::string> GetVolumes() {return fVolumes;}
    private:
        std::vector<std::string> fVolumes;
        G4int d;
};
#endif
