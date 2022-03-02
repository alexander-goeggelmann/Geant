#ifndef Screening_DetectorConstruction_h
#define Screening_DetectorConstruction_h 1

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

class G4VPhysicalVolume;

class Screening_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        Screening_DetectorConstruction();
        virtual ~Screening_DetectorConstruction() {};

        std::vector<std::string> GetVolumes() {return fVolumes;}
        std::vector<G4double> GetEnDi() {return en_di;}
        void SetPath(G4String p) {path = p;}

        virtual G4VPhysicalVolume* Construct();


    private:
        std::vector<G4double> en_di;
        std::vector<std::string> fVolumes;
        G4String path;
        G4String message;
};

#endif
