#include "../include/Cresst_VetoSetUp.hh"
#include "../include/Cresst_DetectorConst.hh"
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


G4VPhysicalVolume *Cresst_VetoSetUp::Construct()
{
    G4Element *Ca = new G4Element("Calcium", "Ca", z_Calcium, moleweight_Calcium);
    G4Element *W = new G4Element("Tungsten", "W", z_Tungsten, moleweight_Tungsten);
    G4Element *O = new G4Element("Oxygen", "O", z_Oxygen, moleweight_Oxygen);
    G4Element *C = new G4Element("Carbon", "C", z_Carbon, moleweight_Carbon);
    G4Element *H = new G4Element("Hydrogen", "H", z_Hydrogen, moleweight_Hydrogen);

    G4Material *Copper = new G4Material(
        "Copper", z_Copper, moleweight_Copper, density_Copper);
    G4Material *Iron = new G4Material(
        "Iron", z_Iron, moleweight_Iron, density_Iron);
    G4Material *Calciumtungstate = new G4Material(
        "CaWO4", density_Calciumtungstate, 3);
    Calciumtungstate->AddElement(Ca, 0.33 / 2);
    Calciumtungstate->AddElement(W, 0.33 / 2);
    Calciumtungstate->AddElement(O, 0.67);

    G4Material *Glue = new G4Material("Glue", density_Glue, 3);
    Glue->AddElement(O, 3);
    Glue->AddElement(C, 18);
    Glue->AddElement(H, 12);

    G4Material *Vacuum = new G4Material(
        "Vacuum", z_Vacuum, moleweight_Vacuum, density_Vacuum, kStateGas,
        temperature_Vacuum, preasure_Vacuum);

    G4VSolid *SolidDetector = new G4Tubs(
        name_Detector, 0., r_Detector, z_half_Detector, 0, CLHEP::twopi);

    G4VSolid *SolidPlate;
    if (d > 0) SolidPlate = new G4Box(
        name_Plate, ((G4double) d) * CLHEP::um / 2., y_half_Copper, z_half_Copper);

    G4VSolid *SolidSource = new G4Box(
        name_Source, x_half_Source, y_half_Source, z_half_Source);
    G4VSolid *SolidScrew = new G4Box(
        name_Screw, x_half_Screw, y_half_Screw, z_half_Screw);
    G4VSolid *SolidGlue = new G4Box(
        name_Glue, x_half_Glue, y_half_Glue, z_half_Glue);

    G4VSolid *SolidBox = new G4Box(
        name_Box, x_half_Box, y_half_Box, z_half_Box);

    G4VSolid *SolidWorld = new G4Box(
        name_World, x_half_World, y_half_World, z_half_World);

    G4VisAttributes *iron = new G4VisAttributes();
    iron->SetColor(192./255., 192./255., 192./255.);
    iron->SetVisibility(true);
    iron->SetForceSolid(true);

    G4VisAttributes *source = new G4VisAttributes();
    source->SetColor(0., 0., 0.);
    source->SetVisibility(true);
    source->SetForceSolid(true);

    G4VisAttributes *detector = new G4VisAttributes();
    detector->SetColor(255./255., 255./255., 255./255.);
    detector->SetVisibility(true);
    detector->SetForceSolid(true);

    G4VisAttributes *glue = new G4VisAttributes();
    glue->SetColor(255./255., 255./255., 255./255.);
    glue->SetVisibility(true);
    glue->SetForceWireframe(true);

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

    G4LogicalVolume *LogicBox = new G4LogicalVolume(
        SolidBox, Vacuum, name_Box);
    LogicBox->SetVisAttributes(invisible);
    LogicBox->SetRegion(Box_Region);
    Box_Region->AddRootLogicalVolume(LogicBox);
    fVolumes.push_back(name_Box);

    G4LogicalVolume *LogicDetector = new G4LogicalVolume(
        SolidDetector, Calciumtungstate, name_Detector);
    LogicDetector->SetVisAttributes(detector);
    LogicDetector->SetRegion(Box_Region);
    fVolumes.push_back(name_Detector);

    G4LogicalVolume *LogicSource = new G4LogicalVolume(
        SolidSource, Iron, name_Source);
    LogicSource->SetVisAttributes(source);
    LogicSource->SetRegion(Box_Region);
    fVolumes.push_back(name_Source);

    G4LogicalVolume *LogicScrew = new G4LogicalVolume(
        SolidScrew, Iron, name_Screw);
    LogicScrew->SetVisAttributes(iron);
    LogicScrew->SetRegion(Box_Region);
    fVolumes.push_back(name_Screw);

    G4LogicalVolume *LogicGlue = new G4LogicalVolume(
        SolidGlue, Glue, name_Glue);
    LogicGlue->SetVisAttributes(glue);
    LogicGlue->SetRegion(Box_Region);
    fVolumes.push_back(name_Glue);

    G4LogicalVolume *LogicPlate;
    if (d > 0)
    {
        LogicPlate = new G4LogicalVolume(SolidPlate, Copper, name_Plate);
        LogicPlate->SetVisAttributes(copper);
        LogicPlate->SetRegion(Box_Region);
        fVolumes.push_back(name_Plate);
    }

    G4VPhysicalVolume *PhysWorld = new G4PVPlacement(
        0, G4ThreeVector(0.0, 0.0, 0.0), LogicWorld, name_World,
        0, false, 0, true);

    new G4PVPlacement(
        0, position_BoxInWorld, LogicBox, name_Box,
        LogicWorld, false, 0, true);

    new G4PVPlacement(
        0, position_DetectorInBox, LogicDetector, name_Detector,
        LogicBox, false, 0, true);

    if (d > 0) new G4PVPlacement(
        0, position_CopperInBox, LogicPlate, name_Plate,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_SourceInBox, LogicSource, name_Source,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_ScrewInBox, LogicScrew, name_Screw,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_GlueInBox, LogicGlue, name_Glue,
        LogicBox, false, 0, true);

    return PhysWorld;
}
