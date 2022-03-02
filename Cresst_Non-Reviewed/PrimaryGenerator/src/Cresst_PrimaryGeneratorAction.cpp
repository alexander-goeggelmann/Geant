#include "../include/Cresst_PrimaryGeneratorAction.hh"
#include "../../DetectorConstruction/include/Cresst_DetectorConst.hh"

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <Randomize.hh>

#include <G4IonTable.hh>

Cresst_PrimaryGeneratorAction::Cresst_PrimaryGeneratorAction(
    G4int nucz, G4int nuca)
    : G4VUserPrimaryGeneratorAction()
{
    halfLength = G4ThreeVector(x_half_Source, y_half_Source, z_half_Source);
    position = position_SourceInBox;

    x0 = position.getX();
    y0 = position.getY();
    z0 = position.getZ();

    fParticleGun = new G4ParticleGun(1);
    nucA = nuca;
    nucZ = nucz;

    //std::cout << nucA << " " << nucZ << std::endl;
    //G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
    //fParticleGun->SetParticleDefinition(ion);
    //fParticleGun->SetParticleCharge(0.);
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    //fParticleGun->SetParticleEnergy(0.);

}


void Cresst_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(0.);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(0.);

    G4double dx = 2. * halfLength.getX() * (G4UniformRand() - 0.5);
    G4double dy = 2. * halfLength.getY() * (G4UniformRand() - 0.5);
    G4double dz = 2. * halfLength.getZ() * (G4UniformRand() - 0.5);

    fParticleGun->SetParticlePosition(
            G4ThreeVector(x0 + dx, y0 + dy, z0 + dz));

    fParticleGun->GeneratePrimaryVertex(anEvent);

}


