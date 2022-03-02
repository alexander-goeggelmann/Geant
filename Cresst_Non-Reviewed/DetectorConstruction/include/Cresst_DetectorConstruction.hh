#ifndef Cresst_DetectorConstruction_h
#define Cresst_DetectorConstruction_h 1

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

class G4VPhysicalVolume;

class Cresst_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        Cresst_DetectorConstruction(G4int);
        virtual ~Cresst_DetectorConstruction() {};

        std::vector<std::string> GetVolumes() {return fVolumes;}
        void SetPath(G4String p) {path = p;}

        virtual G4VPhysicalVolume* Construct();


    private:
        std::vector<std::string> fVolumes;
        G4String path;
        G4String message;
        G4int d;
};

#endif
