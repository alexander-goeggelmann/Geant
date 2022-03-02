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
        virtual ~ECHo_PrimaryGeneratorAction() {
            delete fParticleGun;
            delete thickness;
            delete volume;
            }

        virtual void GeneratePrimaries(G4Event*);

        //const G4ParticleGun* GetParticleGun() const {return fParticleGun;}
        void SelectVolume(G4String);

     private:
        G4ThreeVector GetHalfLength(const G4String);

        G4ParticleGun *fParticleGun = new G4ParticleGun(1);
        ECHo_DetectorConstruction *fDetector;

        const G4bool contamination;
        const G4bool muon;
        const G4int nucA;
        const G4int nucZ;

        G4double Lx;
        G4double Ly;
        G4double Lz;

        G4double x0;
        G4double min_x0;
        G4double max_x0;
        G4double y0;
        G4double min_y0;
        G4double max_y0;
        G4double z0;
        G4double min_z0;
        G4double max_z0;

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

        G4double *thickness = new G4double[6]{0., 0., 0., 0., 0., 0.};
        G4double *volume = new G4double[6]{0., 0., 0., 0., 0., 0.};

        G4double volume01;
        G4double volume23;
        G4double volume45;

        G4double surface00;
        G4double surface01;
        G4double surface02;
        G4double surface03;
        G4double surface04;

        G4double inner_surface00 = 0.;
        G4double inner_surface01 = 0.;
        G4double inner_surface02 = 0.;
        G4double inner_surface03 = 0.;
        G4double inner_surface04 = 0.;

        G4double length_x;
        G4double length_y;
        G4double length_z;

        G4double shift_x0;
        G4double shift_x0_min;
        G4double shift_x0_max;
        G4double shift_y0;
        G4double shift_y0_min;
        G4double shift_y0_max;
        G4double shift_z0;
        G4double shift_z0_min;
        G4double shift_z0_max;

        G4double total_area;
        G4double total_area_outer;

        G4double total_volume;

        G4bool isShielding = false;
        G4bool isMMC = false;
        G4bool isPCB = false;

        G4double pcb_z = 0.;
        G4double pcb_dz = 0.;
        G4double pcb_totalA = 0.;
        G4double pcb_A0 = 0.;
        G4double pcb_A1 = 0.;

        G4double pcb_x0 = 0.;
        G4double pcb_y0 = 0.;
        G4double pcb_dy0 = 0.;
        G4double pcb_dx0 = 0.;
        G4double pcb_x1 = 0.;
        G4double pcb_y1 = 0.;
        G4double pcb_dy1 = 0.;
        G4double pcb_dx1 = 0.;
        G4double pcb_x2 = 0.;
        G4double pcb_y2 = 0.;
        G4double pcb_dy2 = 0.;
        G4double pcb_dx2 = 0.;

        G4double pcb_xl = 0.;
        G4double pcb_dxl = 0.;
};

#endif
