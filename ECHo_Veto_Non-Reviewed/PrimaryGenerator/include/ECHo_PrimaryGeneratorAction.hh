/// \file ECHo_PrimaryGeneratorAction.hh
/// \brief Definition of the ECHo_PrimaryGeneratorAction class

#ifndef ECHo_PrimaryGeneratorAction_h
#define ECHo_PrimaryGeneratorAction_h 1

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Types.hh>
#include "../../DetectorConstruction/include/ECHo_DetectorConstruction.hh"
#include <memory>

class G4Event;

class ECHo_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        ECHo_PrimaryGeneratorAction(
            ECHo_DetectorConstruction*, G4bool, G4bool, G4int, G4int, G4String);
        virtual ~ECHo_PrimaryGeneratorAction() {delete fParticleGun;}

        virtual void GeneratePrimaries(G4Event*);

        //const G4ParticleGun* GetParticleGun() const {return fParticleGun;}
        void SelectVolume(G4String);

     private:
        G4ThreeVector GetHalfLength(const G4String);

        G4ParticleGun *fParticleGun;
        ECHo_DetectorConstruction *fDetector;

        G4bool contamination;
        G4bool muon;

        G4ThreeVector position;
        G4ThreeVector halfLength;

        G4double x0;
        G4double y0;
        G4double z0;

        G4double max_x;
        G4double min_x;
        G4double max_y;
        G4double min_y;
        G4double max_z;
        G4double min_z;

        /*                   +z = top
                              ^
                              |   -y = back
                              |  /
                              | /
                              |/
            left = -x <-------/-------> +x = right
                             /|
                            / |
                           /  |
                 front = +y   |
                              v
                             -z = bottom
        */
        const G4double depth = 0.1 * CLHEP::nanometer;

        G4double thickness_left;
        G4double thickness_right;
        G4double thickness_front;
        G4double thickness_back;
        G4double thickness_top;
        G4double thickness_bottom;

        G4double surface_left;
        G4double surface_right;
        G4double surface_front;
        G4double surface_back;
        G4double surface_top;
        G4double surface_bottom;

        G4double surface_left_inner;
        G4double surface_right_inner;
        G4double surface_front_inner;
        G4double surface_back_inner;
        G4double surface_top_inner;
        G4double surface_bottom_inner;

        G4double total_area;
        G4double total_area_outer;
        G4double total_area_inner;

        G4double volume_left;
        G4double volume_right;
        G4double volume_front;
        G4double volume_back;
        G4double volume_top;
        G4double volume_bottom;

        G4double total_volume;

        G4int nucA;
        G4int nucZ;

        G4bool isShielding;
        G4bool isMMC;
};

#endif
