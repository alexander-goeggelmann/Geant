/// \file Screening_VetoSetUp.hh
/// \brief Definition of the Screening_VetoSetUp class

#ifndef Screening_Veto_h
#define Screening_Veto_h 1
//#include "../include/Screening_DetectorConst.hh"
#include <G4VUserDetectorConstruction.hh>
//#include <G4UserLimits.hh>
//#include <globals.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

class Screening_VetoSetUp : public G4VUserDetectorConstruction
{
    public:
        Screening_VetoSetUp() : G4VUserDetectorConstruction() {}
        virtual ~Screening_VetoSetUp() {};

        virtual G4VPhysicalVolume* Construct();
        std::vector<std::string> GetVolumes() {return fVolumes;}
    private:
        std::vector<std::string> fVolumes;
        G4int d;
};
#endif
