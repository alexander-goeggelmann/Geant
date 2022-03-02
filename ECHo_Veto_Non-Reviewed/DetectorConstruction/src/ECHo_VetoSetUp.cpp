#include "../include/ECHo_VetoSetUp.hh"
#include "../include/ECHo_DetectorConst.hh"
#include <G4SystemOfUnits.hh>
#include <G4Element.hh>
#include <G4Material.hh>
#include <G4VSolid.hh>
#include <G4Box.hh>
#include <G4Sphere.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4UserLimits.hh>
#include <G4Color.hh>
#include <G4VisAttributes.hh>
#include <G4Threading.hh>
#include <G4Region.hh>


G4VPhysicalVolume *ECHo_VetoSetUp::Construct()
{
    //std::cout << "Construct Detector for Thread ID " <<
    //             G4Threading::G4GetThreadId() << std::endl;
    ECHo_DetectorConst& detector_const = get_DetectorConst();
    detector_const.setVectors();

    G4Element *Ag = new G4Element("Silver", "Ag", z_Silver, moleweight_Silver);
    G4Element *Er = new G4Element("Erbium", "Er", z_Erbium, moleweight_Erbium);
    G4Element *O = new G4Element("Oxygen", "O", z_Oxygen, moleweight_Oxygen);
    G4Element *C = new G4Element("Carbon", "C", z_Carbon, moleweight_Carbon);
    G4Element *H = new G4Element("Hydrogen", "H", z_Hydrogen, moleweight_Hydrogen);

    G4Material *Gold = new G4Material(
        "Gold", z_Gold, moleweight_Gold, density_Gold);
    G4Material *Silver = new G4Material(
        "Silver", z_Silver, moleweight_Silver, density_Silver);
    G4Material *Copper = new G4Material(
        "Copper", z_Copper, moleweight_Copper, density_Copper);
    G4Material *Holmium = new G4Material(
        "Holmium", z_Holmium, moleweight_Holmium, density_Holmium);
    G4Material *Silicon = new G4Material(
        "Silicon", z_Silicon, moleweight_Silicon, density_Silicon);
    G4Material *Aluminium = new G4Material(
        "Aluminium", z_Aluminium, moleweight_Aluminium, density_Aluminium);
    G4Material *SilverErbium = new G4Material("Ag:Er", density_Silver, 2);
    SilverErbium->AddElement(Ag, fraction_Silver);
    SilverErbium->AddElement(Er, fraction_Erbium);
    G4Material *PCB = new G4Material("PCB", density_PCB, 3);
    PCB->AddElement(O, 3);
    PCB->AddElement(C, 18);
    PCB->AddElement(H, 12);

    G4Material *Vacuum = new G4Material(
        "Vacuum", z_Vacuum, moleweight_Vacuum, density_Vacuum, kStateGas,
        temperature_Vacuum, preasure_Vacuum);
    //G4Material *Iron = new G4Material(
    //    "Iron", z_Iron, moleweight_Iron, density_Iron);
    G4Material *Plastic = new G4Material(
        "Plastic", z_Plastic, moleweight_Plastic, density_Plastic);

    G4VSolid *SolidBox = new G4Box(
        name_Box, x_half_Box, y_half_Box, z_half_Box);

    G4VSolid *SolidMuonPanel_front_back = new G4Box(
        name_MuonPanel, x_half_Panel_front_back, y_half_Panel_front_back,
        z_half_Panel_front_back);
    G4VSolid *SolidMuonPanel_left_right = new G4Box(
        name_MuonPanel, x_half_Panel_left_right, y_half_Panel_left_right,
        z_half_Panel_left_right);
    G4VSolid *SolidMuonPanel_top = new G4Box(
        name_MuonPanel, x_half_Panel_top, y_half_Panel_top, z_half_Panel_top);
    G4VSolid *SolidMuonPanel_bottom = new G4Box(
        name_MuonPanel, x_half_Panel_bottom, y_half_Panel_bottom,
        z_half_Panel_bottom);
    //G4VSolid *SolidActiveV = new G4Box(
    //  "ActiveV", x_half_Active_V, y_half_Active_V, z_half_Active_V);

    G4VSolid *SolidVeto = new G4Box(
        name_SetUp, x_half_Veto, y_half_Veto, z_half_Veto);

    G4VisAttributes *silver = new G4VisAttributes();
    silver->SetColor(192./255., 192./255., 192./255.);
    silver->SetVisibility(true);
    silver->SetForceWireframe(true);

    G4VisAttributes *goldS = new G4VisAttributes();
    goldS->SetColor(255./255., 215./255., 0./255.);
    goldS->SetVisibility(true);
    goldS->SetForceSolid(true);

    G4VisAttributes *goldW = new G4VisAttributes();
    goldW->SetColor(255./255., 215./255., 0./255.);
    goldW->SetVisibility(true);
    goldW->SetForceWireframe(true);

    G4VisAttributes *holmium = new G4VisAttributes();
    holmium->SetColor(192./255., 192./255., 192./255.);
    holmium->SetVisibility(true);
    holmium->SetForceSolid(true);

    G4VisAttributes *erbium = new G4VisAttributes(G4Color::Grey());
    erbium->SetVisibility(true);
    erbium->SetForceSolid(true);

    G4VisAttributes *platine = new G4VisAttributes();
    platine->SetColor(255./255., 255./255., 255./255.);
    platine->SetVisibility(true);
    platine->SetForceSolid(true);

    G4VisAttributes *platine2 = new G4VisAttributes();
    platine2->SetColor(0./255., 102./255., 51./255.);
    platine2->SetVisibility(true);
    platine2->SetForceSolid(true);

    G4VisAttributes *platine3 = new G4VisAttributes();
    platine3->SetColor(0./255., 0./255., 0./255.);
    platine3->SetVisibility(true);
    platine3->SetForceSolid(true);

    G4VisAttributes *chip = new G4VisAttributes();
    chip->SetColor(153./255., 50./255., 204./255.);
    chip->SetVisibility(true);
    chip->SetForceSolid(true);

    G4VisAttributes *copper = new G4VisAttributes();
    copper->SetColor(229./255., 123./255., 25./255.);
    copper->SetVisibility(true);
    copper->SetForceSolid(true);

    G4VisAttributes *panels = new G4VisAttributes();
    panels->SetColor(0, 0, 0);
    panels->SetVisibility(true);
    panels->SetForceWireframe(true);

    G4VisAttributes *shielding = new G4VisAttributes();
    shielding->SetColor(192./255., 192./255., 192./255.);
    shielding->SetVisibility(true);
    shielding->SetForceWireframe(true);

    G4VisAttributes *invisible = new G4VisAttributes(G4Color::Black());
    invisible->SetVisibility(false);

    // Box
    G4Region *Box_Region = new G4Region(name_Box);
    G4LogicalVolume *LogicBox = new G4LogicalVolume(
        SolidBox, Vacuum, name_Box);
    LogicBox->SetVisAttributes(shielding);
    LogicBox->SetRegion(Box_Region);
    Box_Region->AddRootLogicalVolume(LogicBox);
    fVolumes.push_back(name_Box);

    // Veto
    G4Region *PanelFr_Region[4];
    G4Region *PanelBa_Region[4];
    G4Region *PanelLe_Region[4];
    G4Region *PanelRi_Region[4];
    G4Region *PanelTo_Region[4];
    G4Region *PanelBo_Region[4];
    G4LogicalVolume *PanelsFrontVolume[4];
    G4LogicalVolume *PanelsBackVolume[4];
    G4LogicalVolume *PanelsLeftVolume[4];
    G4LogicalVolume *PanelsRightVolume[4];
    G4LogicalVolume *PanelsTopVolume[4];
    G4LogicalVolume *PanelsBottomVolume[4];


    G4LogicalVolume *LogicVeto = new G4LogicalVolume(
        SolidVeto, Vacuum, name_SetUp);
    LogicVeto->SetVisAttributes(invisible);
    fVolumes.push_back(name_SetUp);

    // Test source
    //G4LogicalVolume *LogicSource = new G4LogicalVolume(
    //    SolidSource, Iron, name_Source);
    //LogicSource->SetVisAttributes(invisible);
    //fVolumes.push_back(name_Source);


    G4VPhysicalVolume *PhysVeto = new G4PVPlacement(
        0, G4ThreeVector(0.0, 0.0, 0.0), LogicVeto, name_SetUp,
        0, false, 0, true);

    for (int i = 0; i < 4; i++)
    {
        G4String position_name = "Front_";
        G4String panel_name = name_MuonPanel + "_0";

        PanelFr_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsFrontVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_front_back, Plastic,
            panel_name + std::to_string(i));
        PanelsFrontVolume[i]->SetVisAttributes(panels);
        PanelsFrontVolume[i]->SetRegion(PanelFr_Region[i]);
        PanelFr_Region[i]->AddRootLogicalVolume(PanelsFrontVolume[i]);
        //PanelsFrontVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        position_name = "Back_";
        panel_name = name_MuonPanel + "_1";

        PanelBa_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsBackVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_front_back, Plastic,
            panel_name + std::to_string(i));
        PanelsBackVolume[i]->SetVisAttributes(panels);
        PanelsBackVolume[i]->SetRegion(PanelBa_Region[i]);
        PanelBa_Region[i]->AddRootLogicalVolume(PanelsBackVolume[i]);
        //PanelsBackVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        position_name = "Left_";
        panel_name = name_MuonPanel + "_2";

        PanelLe_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsLeftVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_left_right, Plastic,
            panel_name + std::to_string(i));
        PanelsLeftVolume[i]->SetVisAttributes(panels);
        PanelsLeftVolume[i]->SetRegion(PanelLe_Region[i]);
        PanelLe_Region[i]->AddRootLogicalVolume(PanelsLeftVolume[i]);
        //PanelsLeftVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        position_name = "Right_";
        panel_name = name_MuonPanel + "_3";

        PanelRi_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsRightVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_left_right, Plastic,
            panel_name + std::to_string(i));
        PanelsRightVolume[i]->SetVisAttributes(panels);
        PanelsRightVolume[i]->SetRegion(PanelRi_Region[i]);
        PanelRi_Region[i]->AddRootLogicalVolume(PanelsRightVolume[i]);
        //PanelsRightVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        position_name = "Top_";
        panel_name = name_MuonPanel + "_4";

        PanelTo_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsTopVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_top, Plastic, panel_name + std::to_string(i));
        PanelsTopVolume[i]->SetVisAttributes(panels);
        PanelsTopVolume[i]->SetRegion(PanelTo_Region[i]);
        PanelTo_Region[i]->AddRootLogicalVolume(PanelsTopVolume[i]);
        //PanelsTopVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        position_name = "Bottom_";
        panel_name = name_MuonPanel + "_5";

        PanelBo_Region[i] = new G4Region(position_name + std::to_string(i));
        PanelsBottomVolume[i] = new G4LogicalVolume(
            SolidMuonPanel_bottom, Plastic, panel_name + std::to_string(i));
        PanelsBottomVolume[i]->SetVisAttributes(panels);
        PanelsBottomVolume[i]->SetRegion(PanelBo_Region[i]);
        PanelBo_Region[i]->AddRootLogicalVolume(PanelsBottomVolume[i]);
        //PanelsBottomVolume[i]->SetUserLimits(limit_Panel);
        fVolumes.push_back(panel_name + std::to_string(i));

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_FrPanelInSetUp[i],
            detector_const.vector_position_y_FrPanelInSetUp[i],
            detector_const.vector_position_z_FrPanelInSetUp[i]),
            PanelsFrontVolume[i], PanelsFrontVolume[i]->GetName(), LogicVeto,
            false, 0, true);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_BaPanelInSetUp[i],
            detector_const.vector_position_y_BaPanelInSetUp[i],
            detector_const.vector_position_z_BaPanelInSetUp[i]),
            PanelsBackVolume[i], PanelsBackVolume[i]->GetName(), LogicVeto,
            false, 0, true);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_LePanelInSetUp[i],
            detector_const.vector_position_y_LePanelInSetUp[i],
            detector_const.vector_position_z_LePanelInSetUp[i]),
            PanelsLeftVolume[i], PanelsLeftVolume[i]->GetName(), LogicVeto,
            false, 0, true);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_RiPanelInSetUp[i],
            detector_const.vector_position_y_RiPanelInSetUp[i],
            detector_const.vector_position_z_RiPanelInSetUp[i]),
            PanelsRightVolume[i], PanelsRightVolume[i]->GetName(), LogicVeto,
            false, 0, true);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_ToPanelInSetUp[i],
            detector_const.vector_position_y_ToPanelInSetUp[i],
            detector_const.vector_position_z_ToPanelInSetUp[i]),
            PanelsTopVolume[i], PanelsTopVolume[i]->GetName(), LogicVeto,
            false, 0, true);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_BoPanelInSetUp[i],
            detector_const.vector_position_y_BoPanelInSetUp[i],
            detector_const.vector_position_z_BoPanelInSetUp[i]),
            PanelsBottomVolume[i], PanelsBottomVolume[i]->GetName(), LogicVeto,
            false, 0, true);
    }

    new G4PVPlacement(
        0, position_BoxInVeto, LogicBox, name_Box,
        LogicVeto, false, 0, true);



    return PhysVeto;
}
