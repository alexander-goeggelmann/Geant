#include "../include/Screening_DetectorConstruction.hh"
#include "../include/Screening_VetoSetUp.hh"
#include "../../EventAction/include/Screening_EventAction.hh"
#include "../../output.hh"
#include <G4Threading.hh>

#include <fstream>
#include <iostream>

G4double energy_dis(G4double xi){
    // From 1MeV - 9 TeV
    // https://arxiv.org/pdf/hep-ph/0604145.pdf
    const G4double c1 = 0.00253;
    const G4double c2 = 0.2455;
    const G4double c3 = 1.288;
    const G4double c4 = -0.2555;
    const G4double c5 = 0.0209;

    const G4double E = xi / CLHEP::GeV;
    const G4double logE = log10(E);
    G4double exponent = c2;
    exponent += c3 * logE;
    exponent += c4 * logE * logE;
    exponent += c5 * logE * logE * logE;
    // exponent *= -1.;

    return (c1 / std::pow(E, exponent));// / 8683022.;
}

G4double Fenergy_dis(u_int xi){
    const G4double step_length = 1. * CLHEP::MeV;
    const G4double x = (((G4double) xi) * step_length) + (1. * CLHEP::MeV);

    return energy_dis(x) * step_length / 8.80121;
}


Screening_DetectorConstruction::Screening_DetectorConstruction()
    : G4VUserDetectorConstruction(){
    const u_int prop_l = 5000000;
    if (en_di.empty()){
      en_di.push_back(0.);
      for (u_int i = 0; i < (prop_l - 1); i++){
        en_di.push_back(en_di[i] + Fenergy_dis(i));
      }
    }
}


G4VPhysicalVolume *Screening_DetectorConstruction::Construct()
{
    Screening_VetoSetUp *thisDetector = new Screening_VetoSetUp();
    G4VPhysicalVolume *PhysVeto = thisDetector->Construct();

    fVolumes = thisDetector->GetVolumes();
    std::ofstream myFile;
    myFile.open(path, std::ios::app);
    myFile << "Volume name" << "," << "Volume number" << std::endl;
    for (uint i = 0; i < fVolumes.size(); i++)
    {
        myFile << fVolumes[i] << ",";
        myFile << Screening_EventAction::parse_volume(fVolumes[i]) << std::endl;
    }
    myFile.close();
    message += blue_color;
    message += "Detector is constructed.\n";
    std::cout << message;

    return PhysVeto;
}
