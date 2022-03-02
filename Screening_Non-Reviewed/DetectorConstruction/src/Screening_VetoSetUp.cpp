#include "../include/Screening_VetoSetUp.hh"
#include "../include/Screening_DetectorConst.hh"
#include <G4SystemOfUnits.hh>
#include <G4Element.hh>
#include <G4Material.hh>
#include <G4VSolid.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4UserLimits.hh>
#include <G4Color.hh>
#include <G4VisAttributes.hh>
#include <G4Threading.hh>
#include <G4Region.hh>


G4VPhysicalVolume *Screening_VetoSetUp::Construct()
{
    G4Element *O = new G4Element("Oxygen", "O", z_Oxygen, moleweight_Oxygen);
    G4Element *C = new G4Element("Carbon", "C", z_Carbon, moleweight_Carbon);
    G4Element *H = new G4Element("Hydrogen", "H", z_Hydrogen, moleweight_Hydrogen);

    G4Element *Fe = new G4Element("Iron", "Fe", z_Iron, moleweight_Iron);
    G4Element *Mo = new G4Element("Molybdenum", "Mo", z_Molybdenum, moleweight_Molybdenum);
    G4Element *Ni = new G4Element("Nickel", "Ni", z_Nickel, moleweight_Nickel);

    G4Material *Copper = new G4Material(
        "Copper", z_Copper, moleweight_Copper, density_Copper);
    G4Material *Aluminium = new G4Material(
        "Aluminium", z_Aluminium, moleweight_Aluminium, density_Aluminium);
    G4Material *Germanium = new G4Material(
        "Germanium", z_Germanium, moleweight_Germanium, density_Germanium);

    G4Material *PCB = new G4Material("PCB", density_PCB, 3);
    PCB->AddElement(O, 3);
    PCB->AddElement(C, 18);
    PCB->AddElement(H, 12);

    G4Material *Cryoperm = new G4Material("Cryo", density_Cryo, 3);
    Cryoperm->AddElement(Fe, 3);
    Cryoperm->AddElement(Mo, 1);
    Cryoperm->AddElement(Ni, 16);

    G4Material *Plastic = new G4Material(
        "Plastic", z_Plastic, moleweight_Plastic, density_Plastic);

    G4Material *Vacuum = new G4Material(
        "Vacuum", z_Vacuum, moleweight_Vacuum, density_Vacuum, kStateGas,
        temperature_Vacuum, preasure_Vacuum);

    G4VSolid *SolidHole = new G4Tubs(
        name_Hole, 0., r_Hole, z_half_Hole, 0, CLHEP::twopi);

    G4VSolid *SolidDetectorB = new G4Tubs(
        name_DetectorB, 0., r_DetectorB, z_half_DetectorB, 0, CLHEP::twopi);

    G4VSolid *SolidDetector = new G4Tubs(
        name_Detector, 0., r_Detector, z_half_Detector, 0, CLHEP::twopi);

    G4VSolid *SolidDetectorLi = new G4Tubs(
        name_DetectorLi, 0., r_DetectorLi, z_half_DetectorLi, 0, CLHEP::twopi);

    G4VSolid *SolidHolder = new G4Tubs(
        name_Holder, 0., r_Holder, z_half_Holder, 0, CLHEP::twopi);

    G4VSolid *SolidInnerBox = new G4Box(
        name_InnerBox, x_half_InnerBox, y_half_InnerBox, z_half_InnerBox);

    G4VSolid *SolidEpoxy = new G4Box(
        name_Epoxy, x_half_Epoxy, y_half_Epoxy, z_half_Epoxy);

    G4VSolid *SolidWindow = new G4Box(
        name_Window, x_half_Window, y_half_Window, z_half_Window);

    G4VSolid *SolidBox = new G4Box(
        name_Box, x_half_Box, y_half_Box, z_half_Box);

    G4VSolid *SolidSample = new G4Box(
        name_Sample, x_half_Sample, y_half_Sample, z_half_Sample);

    G4VSolid *SolidVolume = new G4Box(
        name_Volume, x_half_Volume, y_half_Volume, z_half_Volume);

    G4VSolid *SolidWorld = new G4Box(
        name_World, x_half_World, y_half_World, z_half_World);

    G4VisAttributes *iron = new G4VisAttributes();
    iron->SetColor(192./255., 192./255., 192./255.);
    iron->SetVisibility(true);
    iron->SetForceWireframe(true);

    G4VisAttributes *sample = new G4VisAttributes();
    sample->SetColor(0., 0., 0.);
    sample->SetVisibility(true);
    sample->SetForceSolid(true);

    G4VisAttributes *epoxy = new G4VisAttributes();
    epoxy->SetColor(57./255., 140./255., 10./255.);
    epoxy->SetVisibility(true);
    epoxy->SetForceSolid(true);

    G4VisAttributes *layer = new G4VisAttributes();
    layer->SetColor(255./255., 255./255., 255./255.);
    layer->SetVisibility(true);
    layer->SetForceWireframe(true);

    G4VisAttributes *copper = new G4VisAttributes();
    copper->SetColor(229./255., 123./255., 25./255.);
    copper->SetVisibility(true);
    copper->SetForceSolid(true);

    G4VisAttributes *invisible = new G4VisAttributes(G4Color::Black());
    invisible->SetVisibility(false);

    G4Region *Box_Region = new G4Region(name_Box);

    G4LogicalVolume *LogicWorld = new G4LogicalVolume(
        SolidWorld, Vacuum, name_World);
    LogicWorld->SetVisAttributes(invisible);
    fVolumes.push_back(name_World);

    G4LogicalVolume *LogicVolume = new G4LogicalVolume(
        SolidVolume, Vacuum, name_Volume);
    LogicVolume->SetVisAttributes(invisible);
    LogicVolume->SetRegion(Box_Region);
    Box_Region->AddRootLogicalVolume(LogicVolume);
    fVolumes.push_back(name_Volume);

    // TODO Change material
    G4LogicalVolume *LogicSample = new G4LogicalVolume(
        SolidSample, Plastic, name_Sample);
    LogicSample->SetVisAttributes(sample);
    LogicSample->SetRegion(Box_Region);
    fVolumes.push_back(name_Sample);

    G4LogicalVolume *LogicBox = new G4LogicalVolume(
        SolidBox, Aluminium, name_Box);
    LogicBox->SetVisAttributes(iron);
    LogicBox->SetRegion(Box_Region);
    fVolumes.push_back(name_Box);

    G4LogicalVolume *LogicWindow = new G4LogicalVolume(
        SolidWindow, Vacuum, name_Window);
    LogicWindow->SetVisAttributes(invisible);
    LogicWindow->SetRegion(Box_Region);
    fVolumes.push_back(name_Window);

    G4LogicalVolume *LogicEpoxy = new G4LogicalVolume(
        SolidEpoxy, PCB, name_Epoxy);
    LogicEpoxy->SetVisAttributes(epoxy);
    LogicEpoxy->SetRegion(Box_Region);
    fVolumes.push_back(name_Epoxy);

    G4LogicalVolume *LogicInnerBox = new G4LogicalVolume(
        SolidInnerBox, Vacuum, name_InnerBox);
    LogicInnerBox->SetVisAttributes(invisible);
    LogicInnerBox->SetRegion(Box_Region);
    fVolumes.push_back(name_InnerBox);

    G4LogicalVolume *LogicHolder = new G4LogicalVolume(
        SolidHolder, Copper, name_Holder);
    LogicHolder->SetVisAttributes(copper);
    LogicHolder->SetRegion(Box_Region);
    fVolumes.push_back(name_Holder);

    G4LogicalVolume *LogicDetectorLi = new G4LogicalVolume(
        SolidDetectorLi, Germanium, name_DetectorLi);
    LogicDetectorLi->SetVisAttributes(layer);
    LogicDetectorLi->SetRegion(Box_Region);
    fVolumes.push_back(name_DetectorLi);

    G4LogicalVolume *LogicDetector = new G4LogicalVolume(
        SolidDetector, Germanium, name_Detector);
    LogicDetector->SetVisAttributes(iron);
    LogicDetector->SetRegion(Box_Region);
    fVolumes.push_back(name_Detector);

    G4LogicalVolume *LogicDetectorB = new G4LogicalVolume(
        SolidDetectorB, PCB, name_DetectorB);
    LogicDetectorB->SetVisAttributes(layer);
    LogicDetectorB->SetRegion(Box_Region);
    fVolumes.push_back(name_DetectorB);

    G4LogicalVolume *LogicHole = new G4LogicalVolume(
        SolidHole, PCB, name_Hole);
    LogicHole->SetVisAttributes(invisible);
    LogicHole->SetRegion(Box_Region);
    fVolumes.push_back(name_Hole);

    G4VPhysicalVolume *PhysWorld = new G4PVPlacement(
        0, G4ThreeVector(0.0, 0.0, 0.0), LogicWorld, name_World,
        0, false, 0, true);

    new G4PVPlacement(
        0, position_VolumeInWorld, LogicVolume, name_Volume,
        LogicWorld, false, 0, true);

    new G4PVPlacement(
        0, position_SampleInVolume, LogicSample, name_Sample,
        LogicVolume, false, 0, true);

    new G4PVPlacement(
        0, position_BoxInVolume, LogicBox, name_Box,
        LogicVolume, false, 0, true);

    new G4PVPlacement(
        0, position_WindowInBox, LogicWindow, name_Window,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_EpoxyInWindow, LogicEpoxy, name_Epoxy,
        LogicWindow, false, 0, true);

    new G4PVPlacement(
        0, position_InnerBoxInBox, LogicInnerBox, name_InnerBox,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_HolderInInnerBox, LogicHolder, name_Holder,
        LogicInnerBox, false, 0, true);

    new G4PVPlacement(
        0, position_DetectorLiInInnerBox, LogicDetectorLi, name_DetectorLi,
        LogicInnerBox, false, 0, true);

    new G4PVPlacement(
        0, position_DetectorInDetectorLi, LogicDetector, name_Detector,
        LogicDetectorLi, false, 0, true);

    new G4PVPlacement(
        0, position_DetectorBInDetector, LogicDetectorB, name_DetectorB,
        LogicDetector, false, 0, true);

    new G4PVPlacement(
        0, position_HoleInDetectorB, LogicHole, name_Hole,
        LogicDetectorB, false, 0, true);

    return PhysWorld;
}
