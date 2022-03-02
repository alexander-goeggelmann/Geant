#include "../include/ECHo_PrimaryGeneratorAction.hh"
#include "../../DetectorConstruction/include/ECHo_DetectorConst.hh"
#include "../../DetectorConstruction/include/Volume_names.hh"

//#include <G4LogicalVolumeStore.hh>
//#include <G4LogicalVolume.hh>
//#include <G4Box.hh>
//#include <G4RunManager.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
//#include <G4UniformRand.hh>
#include <Randomize.hh>

#include <G4IonTable.hh>

ECHo_PrimaryGeneratorAction::ECHo_PrimaryGeneratorAction(
    ECHo_DetectorConstruction *det, G4bool muon_f, G4bool cont,
    G4int nuca, G4int nucz, G4String volume)
    : G4VUserPrimaryGeneratorAction()
{
    fDetector = det;

    SelectVolume(volume);

    x0 = position.getX();
    y0 = position.getY();
    z0 = position.getZ();

    fParticleGun = new G4ParticleGun(1);


    G4ParticleTable* ParticleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* Particle = ParticleTable->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(Particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(0.);

}


static G4double GetN(G4ThreeVector p, G4ThreeVector v, G4double r)
{
    G4double v2 = v.getX() * v.getX() +
                  v.getY() * v.getY() +
                  v.getZ() * v.getZ();
    G4double p2 = p.getX() * p.getX() +
                  p.getY() * p.getY() +
                  p.getZ() * p.getZ();
    G4double pv2 = v.getX() * p.getX() +
                   v.getY() * p.getY() +
                   v.getZ() * p.getZ();

    G4double b = pv2 / v2;
    G4double c = (p2 - r * r) / (2. * v2);

    return -b + std::sqrt(b * b - 2. * c);
}


static G4double Fcos2(G4double theta)
{   // From 0 to pi /2
    return (0.5 * (theta + sin(theta) * cos(theta))) /
           (CLHEP::pi / 4.);
}


static G4double GetInverse(
    G4double x, G4double minVal, G4double maxVal, G4double (f)(G4double))
{
    G4double high = maxVal;
    G4double low = minVal;
    G4double mid = (high + low) / 2.;
    G4double gab = 1e-5;

    while ((high - low) > gab)
    {
        if ((f)(mid) == x) return mid;
        if ((f)(mid) < x) low = mid;
        else high = mid;

        mid = (high + low) / 2.;
    }
    return mid;
}


static G4double GetEnergy(G4double x, std::vector<G4double> en_di)
{
    int first = 0;
    int last = en_di.size() - 1;
    int mid = (last + first) / 2;
    while ((last - first) > 1)
    {
        if (en_di[mid] == x) return mid;
        if (en_di[mid] > x) last = mid;
        else first = mid;

        mid = (first + last) / 2;
    }
    return (G4double) mid;
}


void ECHo_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4double dx = 2. * 10. * CLHEP::cm * (G4UniformRand() - 0.5);
    G4double dy = 2. * 10. * CLHEP::cm * (G4UniformRand() - 0.5);
    G4double dz = 2. * 10. * CLHEP::cm * (G4UniformRand() - 0.5);

    G4double theta = GetInverse(
        G4UniformRand(), 0., CLHEP::pi / 2., Fcos2);
    G4double phi = CLHEP::twopi * G4UniformRand();
    G4double vx = cos(phi) * sin(theta);
    G4double vy = sin(phi) * sin(theta);

    G4double vz = cos(theta);
    if (vz > 0) vz *= -1;

    G4double thisN = GetN(
        G4ThreeVector(x0 + dx, y0 + dy, z0 + dz),
        G4ThreeVector(-vx, -vy, -vz), 3 * CLHEP::m);


    G4double entry = GetEnergy(G4UniformRand(), fDetector->GetEnDi());
    G4double xi = entry  + 1.;
    G4double energy = xi / cos(theta);
    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx, vy, vz));
    fParticleGun->SetParticlePosition(G4ThreeVector(
        x0 + dx - thisN * vx, y0 + dy - thisN * vy, z0 + dz - thisN * vz));

    fParticleGun->GeneratePrimaryVertex(anEvent);

}


G4ThreeVector GetPositionSetUp(const G4String volume)
{
    ECHo_DetectorConst& detVec = get_DetectorConst();
    detVec.setVectors();

    const char num = volume[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'p':
            // const int digit = volume[volume.size() - 1] - '0';
            // const int row = volume[volume.size() - 2] - '0';
            if ((volume[volume.size() - 1] - '0' < 0) or
                (volume[volume.size() - 2] - '0' < 0) or
                (volume[volume.size() - 1] - '0' > 3) or
                    (volume[volume.size() - 2] - '0' > 5)) out = G4ThreeVector(0., 0., 0.);
            else
            {
                switch (volume[volume.size() - 2] - '0')
                {
                    case 0:
                        out = G4ThreeVector(
                            detVec.vector_position_x_FrPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_FrPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_FrPanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    case 1:
                        out = G4ThreeVector(
                            detVec.vector_position_x_BaPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_BaPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_BaPanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    case 2:
                        out = G4ThreeVector(
                            detVec.vector_position_x_LePanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_LePanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_LePanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    case 3:
                        out = G4ThreeVector(
                            detVec.vector_position_x_RiPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_RiPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_RiPanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    case 4:
                        out = G4ThreeVector(
                            detVec.vector_position_x_ToPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_ToPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_ToPanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    case 5:
                        out = G4ThreeVector(
                            detVec.vector_position_x_BoPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_y_BoPanelInSetUp[volume[volume.size() - 1] - '0'],
                            detVec.vector_position_z_BoPanelInSetUp[volume[volume.size() - 1] - '0']);
                        break;
                    default:
                        out = G4ThreeVector(0., 0., 0.);
                }
            }
            break;
        case 'q':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            out = position_BoxInVeto;
    }
    return out;
}


G4ThreeVector ECHo_PrimaryGeneratorAction::GetHalfLength(const G4String volume)
{
    const char num = volume[0];
    isMMC = false;
    G4ThreeVector out;
    switch (num)
    {
        case 'o':
            out = G4ThreeVector(x_half_Box, y_half_Box, z_half_Box);
            break;
        case 'p':
            //int row = volume[volume.size() - 2] - '0';
            switch (volume[volume.size() - 2] - '0')
            {
                case 0:
                    out = G4ThreeVector(
                        x_half_Panel_front_back, y_half_Panel_front_back,
                        z_half_Panel_front_back);
                    break;
                case 1:
                    out = G4ThreeVector(
                        x_half_Panel_front_back, y_half_Panel_front_back,
                        z_half_Panel_front_back);
                    break;
                case 2:
                    out = G4ThreeVector(
                        x_half_Panel_left_right, y_half_Panel_left_right,
                        z_half_Panel_left_right);
                    break;
                case 3:
                    out = G4ThreeVector(
                        x_half_Panel_left_right, y_half_Panel_left_right,
                        z_half_Panel_left_right);
                    break;
                case 4:
                    out = G4ThreeVector(
                        x_half_Panel_top, y_half_Panel_top, z_half_Panel_top);
                    break;
                case 5:
                    out = G4ThreeVector(
                        x_half_Panel_bottom, y_half_Panel_bottom,
                        z_half_Panel_bottom);
                    break;
                default:
                    out = G4ThreeVector(0., 0., 0.);
            }
            break;
        case 'q':
            out = G4ThreeVector(
                x_half_Active_V, y_half_Active_V, z_half_Active_V);
            break;
        default:
            out = G4ThreeVector(0., 0., 0.);
    }
    return out;
}


void ECHo_PrimaryGeneratorAction::SelectVolume(G4String volume)
{
    halfLength = GetHalfLength(volume);
    //startV = volume;
    position = GetPositionSetUp(volume);
}
