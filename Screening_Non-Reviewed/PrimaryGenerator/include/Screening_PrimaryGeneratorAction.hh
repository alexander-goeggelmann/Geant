/// \file Screening_PrimaryGeneratorAction.hh
/// \brief Definition of the Screening_PrimaryGeneratorAction class

#ifndef Screening_PrimaryGeneratorAction_h
#define Screening_PrimaryGeneratorAction_h 1

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Types.hh>
#include "../../DetectorConstruction/include/Screening_DetectorConstruction.hh"
#include "../../DetectorConstruction/include/Screening_DetectorConst.hh"
#include <memory>

class G4Event;

class Screening_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        Screening_PrimaryGeneratorAction(
            Screening_DetectorConstruction*, G4int, G4int, G4bool);
        virtual ~Screening_PrimaryGeneratorAction() {delete fParticleGun;}

        virtual void GeneratePrimaries(G4Event*);

     private:
        G4ParticleGun *fParticleGun = new G4ParticleGun(1);
        Screening_DetectorConstruction *fDetector;
        const G4int nucZ;
        const G4int nucA;
        const G4bool cont;

        const G4double depth = 5. * CLHEP::nm;

        const G4double hx = 2. * x_half_Sample;
        const G4double hy = 2. * y_half_Sample;
        const G4double hz = 2. * z_half_Sample;

        const G4double box_x = 2. * x_half_Box;
        const G4double box_y = 2. * y_half_Box;
        const G4double box_z = 2. * z_half_Box;

        const G4double box_x0 = position_BoxInVolume.getX();
        const G4double box_y0 = position_BoxInVolume.getY();
        const G4double box_z0 = position_BoxInVolume.getZ();

        const G4double x0 = position_SampleInVolume.getX();
        const G4double y0 = position_SampleInVolume.getY();
        const G4double z0 = position_SampleInVolume.getZ();

        const G4double A_xy = hx * hy;
        const G4double A_xz = A_xy + hx * hz;
        const G4double totalA = hx * (hy + hz) + hy * hz;




};

#endif
