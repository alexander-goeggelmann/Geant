/// \file Cresst_PrimaryGeneratorAction.hh
/// \brief Definition of the Cresst_PrimaryGeneratorAction class

#ifndef Cresst_PrimaryGeneratorAction_h
#define Cresst_PrimaryGeneratorAction_h 1

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4Types.hh>
#include "../../DetectorConstruction/include/Cresst_DetectorConstruction.hh"
#include <memory>

class G4Event;

class Cresst_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        Cresst_PrimaryGeneratorAction(G4int, G4int);
        virtual ~Cresst_PrimaryGeneratorAction() {delete fParticleGun;}

        virtual void GeneratePrimaries(G4Event*);

     private:
        G4ParticleGun *fParticleGun;

        G4ThreeVector position;
        G4ThreeVector halfLength;

        G4double x0;
        G4double y0;
        G4double z0;


        G4int nucA;
        G4int nucZ;

};

#endif
