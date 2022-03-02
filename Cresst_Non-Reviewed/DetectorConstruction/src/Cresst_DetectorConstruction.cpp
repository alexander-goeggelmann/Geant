#include "../include/Cresst_DetectorConstruction.hh"
#include "../include/Cresst_VetoSetUp.hh"
#include "../../EventAction/include/Cresst_EventAction.hh"
#include "../../output.hh"
#include <G4Threading.hh>

#include <fstream>
#include <iostream>


Cresst_DetectorConstruction::Cresst_DetectorConstruction(G4int _d)
    : G4VUserDetectorConstruction()
{d = _d;}


G4VPhysicalVolume *Cresst_DetectorConstruction::Construct()
{
    Cresst_VetoSetUp *thisDetector = new Cresst_VetoSetUp(d);
    G4VPhysicalVolume *PhysVeto = thisDetector->Construct();

    fVolumes = thisDetector->GetVolumes();
    std::ofstream myFile;
    myFile.open(path, std::ios::app);
    myFile << "Volume name" << "," << "Volume number" << std::endl;
    for (uint i = 0; i < fVolumes.size(); i++)
    {
        myFile << fVolumes[i] << ",";
        myFile << Cresst_EventAction::parse_volume(fVolumes[i]) << std::endl;
    }
    myFile.close();
    message += blue_color;
    message += "Detector is constructed.\n";
    std::cout << message;

    return PhysVeto;
}
