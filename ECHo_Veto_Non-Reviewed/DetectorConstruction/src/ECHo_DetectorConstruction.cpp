#include "../include/ECHo_DetectorConstruction.hh"
#include "../include/ECHo_VetoSetUp.hh"
#include "../../EventAction/include/ECHo_EventAction.hh"
#include "../../output.hh"
#include <G4Threading.hh>

#include <fstream>
#include <iostream>

G4double energy_dis(G4double xi)
{
    // From 1MeV - 9 TeV
    // https://arxiv.org/pdf/hep-ph/0604145.pdf
    G4double c1 = 0.00253;
    G4double c2 = 0.2455;
    G4double c3 = 1.288;
    G4double c4 = -0.2555;
    G4double c5 = 0.0209;

    G4double E = xi / CLHEP::GeV;
    G4double exponent = c2;
    exponent += c3 * log10(E);
    exponent += c4 * log10(E) * log10(E);
    exponent += c5 * log10(E) * log10(E) * log10(E);
    // exponent *= -1.;

    return (c1 / std::pow(E, exponent));// / 8683022.;
}

G4double Fenergy_dis(u_int xi)
{
    G4double step_length = 1. * CLHEP::MeV;
    G4double x = (((G4double) xi) * step_length) + (1. * CLHEP::MeV);

    return energy_dis(x) * step_length / 8.80121;
}


ECHo_DetectorConstruction::ECHo_DetectorConstruction()
    : G4VUserDetectorConstruction()
{
    u_int prop_l = 5000000;
    //G4String path = "../Simulations/Prop.csv";
    //std::ofstream myFile;
    //myFile.open(path, std::ios::app);
    if (en_di.empty())
    {
      en_di.push_back(0.);
      //myFile << en_di[0] << std::endl;
      for (u_int i = 0; i < (prop_l - 1); i++)
      {
        en_di.push_back(en_di[i] + Fenergy_dis(i));
        //myFile << en_di[i + 1] << std::endl;
      }
      message = "";
      //std::cout << en_di[0] << std::endl;
      //std::cout << en_di[en_di.size() - 1] << std::endl;
      //myFile.close();
    }
}


G4VPhysicalVolume *ECHo_DetectorConstruction::Construct()
{
    ECHo_VetoSetUp *thisDetector = new ECHo_VetoSetUp();
    G4VPhysicalVolume *PhysVeto = thisDetector->Construct();

    fVolumes = thisDetector->GetVolumes();
    std::ofstream myFile;
    myFile.open(path, std::ios::app);
    myFile << "Volume name" << "," << "Volume number" << std::endl;
    for (uint i = 0; i < fVolumes.size(); i++)
    {
        myFile << fVolumes[i] << ",";
        myFile << ECHo_EventAction::parse_volume(fVolumes[i]) << std::endl;
    }
    myFile.close();
    message += blue_color;
    message += "Detector is constructed.\n";
    std::cout << message;

    return PhysVeto;
}
