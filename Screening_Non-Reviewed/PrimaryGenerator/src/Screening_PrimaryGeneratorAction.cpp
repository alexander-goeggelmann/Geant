#include "../include/Screening_PrimaryGeneratorAction.hh"

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <Randomize.hh>

#include <G4IonTable.hh>

Screening_PrimaryGeneratorAction::Screening_PrimaryGeneratorAction(
    Screening_DetectorConstruction *det, G4int nucz, G4int nuca, G4bool con)
    : G4VUserPrimaryGeneratorAction(), fDetector(det), nucZ(nucz), nucA(nuca),
    cont(con){
    fParticleGun->SetParticleCharge(0.);
    //G4ParticleTable* ParticleTable = G4ParticleTable::GetParticleTable();
    //G4ParticleDefinition* Particle = ParticleTable->FindParticle("mu-");
    //fParticleGun->SetParticleDefinition(Particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(0.);

}

static inline G4double GetN(G4ThreeVector p, G4ThreeVector v, G4double r){

    G4double v2 = v.getX() * v.getX() + v.getY() * v.getY() + v.getZ() * v.getZ();
    G4double p2 = p.getX() * p.getX() + p.getY() * p.getY() + p.getZ() * p.getZ();
    G4double pv2 = v.getX() * p.getX() + v.getY() * p.getY() + v.getZ() * p.getZ();

    G4double b = pv2 / v2;
    G4double c = (p2 - r * r) / (2. * v2);

    return -b + std::sqrt(b * b - 2. * c);
}


static inline G4double Fcos2(G4double theta){
    // From 0 to pi /2
    // return (0.5 * (theta + sin(theta) * cos(theta))) / (CLHEP::pi / 4.);
    return (theta + sin(theta) * cos(theta)) / CLHEP::halfpi;
}


static inline G4double GetInverse(
    G4double x, G4double minVal, G4double maxVal, G4double (f)(G4double)){

    G4double high = maxVal;
    G4double low = minVal;
    G4double mid = (high + low) / 2.;
    const G4double gab = 1e-5;

    while ((high - low) > gab){
        if ((f)(mid) == x) return mid;
        if ((f)(mid) < x) low = mid;
        else high = mid;

        mid = (high + low) / 2.;
    }
    return mid;
}


static inline G4double GetEnergy(G4double x, std::vector<G4double> en_di){
    int first = 0;
    int last = en_di.size() - 1;
    int mid = (last + first) / 2;
    while ((last - first) > 1){
        if (en_di[mid] == x) return mid;
        if (en_di[mid] > x) last = mid;
        else first = mid;

        mid = (first + last) / 2;
    }
    return (G4double) mid;
}


void Screening_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    const bool muon = false;
    if (!muon){
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
        fParticleGun->SetParticleDefinition(ion);

        G4double rx = G4UniformRand();
        G4double ry = G4UniformRand();
        G4double rz = G4UniformRand();

        G4double dx = hx * (rx - 0.5);
        G4double dy = hy * (rx - 0.5);
        G4double dz = hz * (rx - 0.5);

        if (!cont){
            G4double area = totalA * G4UniformRand();
            if (area <= A_xy){
                dz = 0.5 * hz - depth;
                if (rz < 0.5) dz = -dz;
            }else if (area <= A_xz){
                dy = 0.5 * hy - depth;
                if (ry < 0.5) dy = -dy;
            }else{
                dx = 0.5 * hx - depth;
                if (rx < 0.5) dx = -dx;
            }
        }
        fParticleGun->SetParticlePosition(
            G4ThreeVector(x0 + dx, y0 + dy, z0 + dz));
    } else{
        G4double rx = G4UniformRand() - 0.5;
        G4double ry = G4UniformRand() - 0.5;
        G4double rz = G4UniformRand() - 0.5;

        G4double x = box_x0 + box_x * rx;
        G4double y = box_y0 + box_y * ry;
        G4double z = box_z0 + box_z * rz;

        G4double theta = GetInverse(G4UniformRand(), 0., CLHEP::halfpi, Fcos2);
        G4double phi = CLHEP::twopi * G4UniformRand();
        G4double vx = cos(phi) * sin(theta);
        G4double vy = sin(phi) * sin(theta);

        G4double vz = cos(theta);
        if (vz > 0) vz *= -1;

        G4double thisN = GetN(
            G4ThreeVector(x, y, z), G4ThreeVector(-vx, -vy, -vz), 0.5 * CLHEP::m);


        G4double entry = GetEnergy(G4UniformRand(), fDetector->GetEnDi());

        fParticleGun->SetParticleEnergy((entry  + 1.) / cos(theta));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx, vy, vz));
        x -= thisN * vx;
        y -= thisN * vy;
        z -= thisN * vz;
        fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));
    }

    fParticleGun->GeneratePrimaryVertex(anEvent);

}


