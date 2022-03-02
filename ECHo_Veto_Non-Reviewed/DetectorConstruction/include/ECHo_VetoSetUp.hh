/// \file ECHo_VetoSetUp.hh
/// \brief Definition of the ECHo_VetoSetUp class

#ifndef ECHo_Veto_h
#define ECHo_Veto_h 1
//#include "../include/ECHo_DetectorConst.hh"
#include <G4VUserDetectorConstruction.hh>
//#include <G4UserLimits.hh>
//#include <globals.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

class ECHo_VetoSetUp : public G4VUserDetectorConstruction
{
    public:
        ECHo_VetoSetUp() : G4VUserDetectorConstruction() {};
        virtual ~ECHo_VetoSetUp() {};

        virtual G4VPhysicalVolume* Construct();
        std::vector<std::string> GetVolumes() {return fVolumes;}
    private:
        std::vector<std::string> fVolumes;
};
#endif
