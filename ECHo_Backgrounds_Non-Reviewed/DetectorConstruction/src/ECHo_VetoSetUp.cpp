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

    G4VSolid *SolidAbsorber = new G4Box(
        name_Absorber, x_half_Absorber, y_half_Absorber, z_half_Absorber);
    G4VSolid *SolidHolmium = new G4Box(
        name_Holmium, x_half_Holmium, y_half_Holmium, z_half_Holmium);
    G4VSolid *SolidSilver = new G4Box(
        name_Silver, x_half_Silver, y_half_Silver, z_half_Silver);
    G4VSolid *SolidSensor = new G4Box(
        name_Sensor, x_half_Sensor, y_half_Sensor, z_half_Sensor);
    G4VSolid *SolidMMC = new G4Box(
        name_MMC, x_half_MMC, y_half_MMC, z_half_MMC);

    G4VSolid *SolidWafer = new G4Box(
        name_Wafer, x_half_Wafer, y_half_Wafer, z_half_Wafer);
    G4VSolid *SolidsWafer = new G4Box(
        name_sWafer, x_half_sWafer, y_half_sWafer, z_half_sWafer);
    G4VSolid *SolidBath = new G4Box(
        name_Bath, x_half_Bath, y_half_Bath, z_half_Bath);
    G4VSolid *Solid1K = new G4Box(
        name_1K, x_half_1K, y_half_1K, z_half_1K);
    //G4VSolid *SolidSource = new G4Box(
    //    name_Source, x_half_Source, y_half_Source, z_half_Source);
    G4VSolid *SolidSmallBath = new G4Box(
        name_sBath, x_half_bath, y_half_bath, z_half_bath);
    G4VSolid *SolidSubP = new G4Box(
        name_SubP, x_half_SubP1, y_half_SubP1, z_half_SubP1);
    G4VSolid *SolidSubSubP = new G4Box(
        name_SubSubP, x_half_SubP0, y_half_SubP0, z_half_SubP0);

    G4VSolid *SolidCB0 = new G4Box(
        name_CB0, x_half_CB0, y_half_CB0, z_half_CB0);
    G4VSolid *SolidCB1 = new G4Box(
        name_CB1, x_half_CB1, y_half_CB1, z_half_CB1);
    G4VSolid *SolidCB2 = new G4Box(
        name_CB2, x_half_CB2, y_half_CB2, z_half_CB2);
    G4VSolid *SolidCB3 = new G4Box(
        name_CB3, x_half_CB3, y_half_CB3, z_half_CB3);
    G4VSolid *SolidCB4 = new G4Box(
        name_CB4, x_half_CB4, y_half_CB4, z_half_CB4);

    G4VSolid *SolidSQUID = new G4Box(
        name_SQUID, x_half_SQUID, y_half_SQUID, z_half_SQUID);

    G4VSolid *SolidPlug = new G4Box(
        name_Plug, x_half_Plug, y_half_Plug, z_half_Plug);

    G4VSolid *SolidCopperA = new G4Box(
        name_CopperA, x_half_Copper_B0, y_half_Copper_B0, z_half_Copper_B0);
    G4VSolid *SolidCopper500 = new G4Box(
        name_Copper500, x_half_Copper500, y_half_Copper500, z_half_Copper500);
    G4VSolid *SolidCopper50 = new G4Box(
        name_Copper50, x_half_Copper50, y_half_Copper50, z_half_Copper50);
    G4VSolid *SolidCopper5 = new G4Box(
        name_Copper5, x_half_Copper5, y_half_Copper5, z_half_Copper5);
    G4VSolid *SolidCopperB = new G4Box(
        name_CopperB, x_half_Copper_B1, y_half_Copper_B1, z_half_Copper_B1);

    G4VSolid *SolidShielding = new G4Box(
        name_Shielding, x_half_Shielding, y_half_Shielding, z_half_Shielding);
    G4VSolid *SolidS500 = new G4Box(
        name_S500, x_half_S500, y_half_S500, z_half_S500);
    G4VSolid *SolidS50 = new G4Box(
        name_S50, x_half_S50, y_half_S50, z_half_S50);
    G4VSolid *SolidS5 = new G4Box(
        name_S5, x_half_S5, y_half_S5, z_half_S5);
    G4VSolid *SolidInnerS = new G4Box(
        name_InnerS, x_half_InnerS, y_half_InnerS, z_half_InnerS);
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

    // MMC
    G4Region *MMC_Regions[number_of_pixels];
    G4LogicalVolume *MMCVolumes[number_of_pixels];
    G4LogicalVolume *AbsorberVolumes[number_of_pixels];
    G4LogicalVolume *SensorVolumes[number_of_pixels];
    G4LogicalVolume *HolmiumVolumes[number_of_pixels];
    G4LogicalVolume *SilverVolumes[number_of_pixels];

    // 1K-Chip
    G4Region *Wafer_Region = new G4Region(name_1K);
    G4LogicalVolume *Logic1K = new G4LogicalVolume(Solid1K, Vacuum, name_1K);
    Logic1K->SetVisAttributes(shielding);
    Logic1K->SetRegion(Wafer_Region);
    Wafer_Region->AddRootLogicalVolume(Logic1K);
    fVolumes.push_back(name_1K);

    G4LogicalVolume *LogicWafer = new G4LogicalVolume(
        SolidWafer, Silicon, name_Wafer);
    LogicWafer->SetVisAttributes(chip);
    LogicWafer->SetRegion(Wafer_Region);
    fVolumes.push_back(name_Wafer);
    G4LogicalVolume *LogicSubP[20];
    G4LogicalVolume *LogicSubSubP[80];

    G4Region *sWafer_Region = new G4Region(name_sWafer);
    G4LogicalVolume *LogicsWafer = new G4LogicalVolume(
        SolidsWafer, Silicon, name_sWafer);
    LogicsWafer->SetVisAttributes(chip);
    LogicsWafer->SetRegion(sWafer_Region);
    sWafer_Region->AddRootLogicalVolume(LogicsWafer);
    fVolumes.push_back(name_sWafer);

    G4Region *STL_Region = new G4Region("STL");
    G4LogicalVolume *LogicSQUID_TL = new G4LogicalVolume(
        SolidSQUID, Silicon, name_SQUID + "_0");
    LogicSQUID_TL->SetVisAttributes(platine2);
    LogicSQUID_TL->SetRegion(STL_Region);
    STL_Region->AddRootLogicalVolume(LogicSQUID_TL);
    fVolumes.push_back(name_SQUID + "_0");

    G4Region *STR_Region = new G4Region("STR");
    G4LogicalVolume *LogicSQUID_TR = new G4LogicalVolume(
        SolidSQUID, Silicon, name_SQUID + "_1");
    LogicSQUID_TR->SetVisAttributes(platine2);
    LogicSQUID_TR->SetRegion(STR_Region);
    STR_Region->AddRootLogicalVolume(LogicSQUID_TR);
    fVolumes.push_back(name_SQUID + "_1");

    G4Region *SBL_Region = new G4Region("SBL");
    G4LogicalVolume *LogicSQUID_BL = new G4LogicalVolume(
        SolidSQUID, Silicon, name_SQUID + "_2");
    LogicSQUID_BL->SetVisAttributes(platine2);
    LogicSQUID_BL->SetRegion(SBL_Region);
    SBL_Region->AddRootLogicalVolume(LogicSQUID_BL);
    fVolumes.push_back(name_SQUID + "_2");

    G4Region *SBR_Region = new G4Region("SBR");
    G4LogicalVolume *LogicSQUID_BR = new G4LogicalVolume(
        SolidSQUID, Silicon, name_SQUID + "_3");
    LogicSQUID_BR->SetVisAttributes(platine2);
    LogicSQUID_BR->SetRegion(SBR_Region);
    SBR_Region->AddRootLogicalVolume(LogicSQUID_BR);
    fVolumes.push_back(name_SQUID + "_3");

    G4Region *Bath_Region = new G4Region(name_Bath);
    G4Region *sBath_Regions[18];
    G4LogicalVolume *BathVolumes[18];
    G4LogicalVolume *LogicBath = new G4LogicalVolume(
        SolidBath, Gold, name_Bath);
    LogicBath->SetVisAttributes(goldS);
    LogicBath->SetRegion(Bath_Region);
    Bath_Region->AddRootLogicalVolume(LogicBath);
    fVolumes.push_back(name_Bath);

    // Box
    G4LogicalVolume *LogicBox = new G4LogicalVolume(
        SolidBox, Vacuum, name_Box);
    LogicBox->SetVisAttributes(invisible);
    fVolumes.push_back(name_Box);

    G4Region *Shielding_Region = new G4Region(name_Shielding);
    G4LogicalVolume *LogicShielding = new G4LogicalVolume(
        SolidShielding, Aluminium, name_Shielding);
    LogicShielding->SetVisAttributes(shielding);
    LogicShielding->SetRegion(Shielding_Region);
    Shielding_Region->AddRootLogicalVolume(LogicShielding);
    fVolumes.push_back(name_Shielding);

    G4Region *S500_Region = new G4Region(name_S500);
    G4LogicalVolume *LogicS500 = new G4LogicalVolume(
        SolidS500, Aluminium, name_S500);
    LogicS500->SetVisAttributes(shielding);
    LogicS500->SetRegion(S500_Region);
    S500_Region->AddRootLogicalVolume(LogicS500);
    fVolumes.push_back(name_S500);

    G4Region *S50_Region = new G4Region(name_S50);
    G4LogicalVolume *LogicS50 = new G4LogicalVolume(
        SolidS50, Aluminium, name_S50);
    LogicS50->SetVisAttributes(shielding);
    LogicS50->SetRegion(S50_Region);
    S50_Region->AddRootLogicalVolume(LogicS50);
    fVolumes.push_back(name_S50);

    G4Region *S5_Region = new G4Region(name_S5);
    G4LogicalVolume *LogicS5 = new G4LogicalVolume(
        SolidS5, Aluminium, name_S5);
    LogicS5->SetVisAttributes(shielding);
    LogicS5->SetRegion(S5_Region);
    S5_Region->AddRootLogicalVolume(LogicS5);
    fVolumes.push_back(name_S5);

    G4Region *InnerS_Region = new G4Region(name_InnerS);
    G4LogicalVolume *LogicInnerS = new G4LogicalVolume(
        SolidInnerS, Vacuum, name_InnerS);
    LogicInnerS->SetVisAttributes(shielding);
    LogicInnerS->SetRegion(InnerS_Region);
    InnerS_Region->AddRootLogicalVolume(LogicInnerS);
    fVolumes.push_back(name_InnerS);

    G4Region *CA_Region = new G4Region(name_CopperA);
    G4LogicalVolume *LogicCopperA = new G4LogicalVolume(
        SolidCopperA, Copper, name_CopperA);
    LogicCopperA->SetVisAttributes(copper);
    LogicCopperA->SetRegion(CA_Region);
    CA_Region->AddRootLogicalVolume(LogicCopperA);
    fVolumes.push_back(name_CopperA);

    G4Region *Copper500_Region = new G4Region(name_Copper500);
    G4LogicalVolume *LogicCopper500 = new G4LogicalVolume(
        SolidCopper500, Copper, name_Copper500);
    LogicCopper500->SetVisAttributes(copper);
    LogicCopper500->SetRegion(Copper500_Region);
    Copper500_Region->AddRootLogicalVolume(LogicCopper500);
    fVolumes.push_back(name_Copper500);

    G4Region *Copper50_Region = new G4Region(name_Copper50);
    G4LogicalVolume *LogicCopper50 = new G4LogicalVolume(
        SolidCopper50, Copper, name_Copper50);
    LogicCopper50->SetVisAttributes(copper);
    LogicCopper50->SetRegion(Copper50_Region);
    Copper50_Region->AddRootLogicalVolume(LogicCopper50);
    fVolumes.push_back(name_Copper50);

    G4Region *Copper5_Region = new G4Region(name_Copper5);
    G4LogicalVolume *LogicCopper5 = new G4LogicalVolume(
        SolidCopper5, Copper, name_Copper5);
    LogicCopper5->SetVisAttributes(copper);
    LogicCopper5->SetRegion(Copper5_Region);
    Copper5_Region->AddRootLogicalVolume(LogicCopper5);
    fVolumes.push_back(name_Copper5);

    G4Region *CB_Region = new G4Region(name_CopperB);
    G4LogicalVolume *LogicCopperB = new G4LogicalVolume(
        SolidCopperB, Copper, name_CopperB);
    LogicCopperB->SetVisAttributes(copper);
    LogicCopperB->SetRegion(CB_Region);
    CB_Region->AddRootLogicalVolume(LogicCopperB);
    fVolumes.push_back(name_CopperB);

    G4Region *CB0_Region = new G4Region(name_CB0);
    G4LogicalVolume *LogicCB0 = new G4LogicalVolume(
        SolidCB0, PCB, name_CB0);
    LogicCB0->SetVisAttributes(platine);
    LogicCB0->SetRegion(CB0_Region);
    CB0_Region->AddRootLogicalVolume(LogicCB0);
    fVolumes.push_back(name_CB0);

    G4Region *CB1_Region = new G4Region(name_CB1);
    G4LogicalVolume *LogicCB1 = new G4LogicalVolume(
        SolidCB1, PCB, name_CB1);
    LogicCB1->SetVisAttributes(platine);
    LogicCB1->SetRegion(CB1_Region);
    CB1_Region->AddRootLogicalVolume(LogicCB1);
    fVolumes.push_back(name_CB1);

    G4Region *CB2_Region = new G4Region(name_CB2);
    G4LogicalVolume *LogicCB2 = new G4LogicalVolume(
        SolidCB2, PCB, name_CB2);
    LogicCB2->SetVisAttributes(platine);
    LogicCB2->SetRegion(CB2_Region);
    CB2_Region->AddRootLogicalVolume(LogicCB2);
    fVolumes.push_back(name_CB2);

    G4Region *CB3_Region = new G4Region(name_CB3);
    G4LogicalVolume *LogicCB3 = new G4LogicalVolume(
        SolidCB3, PCB, name_CB3);
    LogicCB3->SetVisAttributes(platine);
    LogicCB3->SetRegion(CB3_Region);
    CB3_Region->AddRootLogicalVolume(LogicCB3);
    fVolumes.push_back(name_CB3);

    G4Region *CB4_Region = new G4Region(name_CB4);
    G4LogicalVolume *LogicCB4 = new G4LogicalVolume(
        SolidCB4, PCB, name_CB4);
    LogicCB4->SetVisAttributes(platine);
    LogicCB4->SetRegion(CB4_Region);
    CB4_Region->AddRootLogicalVolume(LogicCB4);
    fVolumes.push_back(name_CB4);

    G4Region *Plug_Regions[9];
    G4LogicalVolume *PlugVolumes[9];

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

    new G4PVPlacement(
        0, position_B1InBox, LogicCopperB, name_CopperB,
        LogicBox, false, 0, true);
    new G4PVPlacement(
        0, position_ShieldingInBox, LogicShielding, name_Shielding,
        LogicBox, false, 0, true);

    new G4PVPlacement(
        0, position_S500InShielding, LogicS500, name_S500,
        LogicShielding, false, 0, true);

    new G4PVPlacement(
        0, position_S50InS500, LogicS50, name_S50,
        LogicS500, false, 0, true);

    new G4PVPlacement(
        0, position_S5InS50, LogicS5, name_S5,
        LogicS50, false, 0, true);

    new G4PVPlacement(
        0, position_InnerSInS5, LogicInnerS, name_InnerS,
        LogicS5, false, 0, true);

    new G4PVPlacement(
        0, position_B0InInnerS, LogicCopperA, name_CopperA,
        LogicInnerS, false, 0, true);
    new G4PVPlacement(
        0, position_Copper500InCB0, LogicCopper500, name_Copper500,
        LogicCopperA, false, 0, true);
    new G4PVPlacement(
        0, position_Copper50InCopper500, LogicCopper50, name_Copper50,
        LogicCopper500, false, 0, true);
    new G4PVPlacement(
        0, position_Copper5InCopper50, LogicCopper5, name_Copper5,
        LogicCopper50, false, 0, true);

    new G4PVPlacement(
        0, position_1KInInnerS, Logic1K, name_1K,
        LogicInnerS, false, 0, true);
    new G4PVPlacement(
        0, position_BathIn1K, LogicBath, name_Bath,
        Logic1K, false, 0, true);
    new G4PVPlacement(
        0, position_WaferIn1K, LogicWafer, name_Wafer,
        Logic1K, false, 0, true);
    new G4PVPlacement(
        0, position_sWaferInWafer, LogicsWafer, name_sWafer,
        LogicWafer, false, 0, true);
    /*
    for (int i = 0; i < 20; ++i)
    {
        LogicSubP[i] = new G4LogicalVolume(
            SolidSubP, Silicon,  detector_const.vector_names_SubP[i]);
        LogicSubP[i]->SetVisAttributes(chip);
        LogicSubP[i]->SetRegion(Wafer_Region);
        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_SubPInWafer[i],
            detector_const.vector_position_y_SubPInWafer[i],
            detector_const.vector_position_z_SubPInWafer[i]),
            LogicSubP[i], detector_const.vector_names_SubP[i],
            LogicWafer, false, 0, true);

        fVolumes.push_back(detector_const.vector_names_SubP[i]);
    }

    for (int i = 0; i < 80; ++i)
    {
        LogicSubSubP[i] = new G4LogicalVolume(
            SolidSubSubP, Silicon,
            detector_const.vector_names_SubSubP[i]);
        LogicSubSubP[i]->SetVisAttributes(chip);
        LogicSubSubP[i]->SetRegion(Wafer_Region);

        new G4PVPlacement(0, G4ThreeVector(
            detector_const.vector_position_x_SubSubPInSubP[i],
            detector_const.vector_position_y_SubSubPInSubP[i],
            detector_const.vector_position_z_SubSubPInSubP[i]),
            LogicSubSubP[i],
            detector_const.vector_names_SubSubP[i],
            LogicSubP[(int) i / 4], false, 0, true);

        fVolumes.push_back(
            detector_const.vector_names_SubSubP[i]);
        std::cout << detector_const.vector_names_SubSubP[i] << std::endl;
    }
    */



    //new G4PVPlacement(
    //    0, position_SourceIn1K, LogicSource, name_Source,
    //    Logic1K, false, 0, true);

    G4ThreeVector position_MMCIn1K;

    for (int i = 0; i < number_of_pixels; i++)
    {
            MMC_Regions[i] = new G4Region(detector_const.vector_names_MMC[i]);
            AbsorberVolumes[i] = new G4LogicalVolume(SolidAbsorber, Gold,
                                                                detector_const.vector_names_Absorber[i]);
            AbsorberVolumes[i]->SetVisAttributes(goldW);
            AbsorberVolumes[i]->SetRegion(MMC_Regions[i]);
            //AbsorberVolumes[i]->SetUserLimits(limit_MMC);
            fVolumes.push_back(detector_const.vector_names_Absorber[i]);

            SensorVolumes[i] = new G4LogicalVolume(SolidSensor, SilverErbium,
                                                            detector_const.vector_names_Sensor[i]);
            SensorVolumes[i]->SetVisAttributes(erbium);
            SensorVolumes[i]->SetRegion(MMC_Regions[i]);
            //SensorVolumes[i]->SetUserLimits(limit_MMC);
            fVolumes.push_back(detector_const.vector_names_Sensor[i]);

            SilverVolumes[i] = new G4LogicalVolume(SolidSilver, Silver,
                                                                detector_const.vector_names_Silver[i]);
            SilverVolumes[i]->SetVisAttributes(silver);
            SilverVolumes[i]->SetRegion(MMC_Regions[i]);
            //SilverVolumes[i]->SetUserLimits(limit_MMC);
            fVolumes.push_back(detector_const.vector_names_Silver[i]);

            HolmiumVolumes[i] = new G4LogicalVolume(SolidHolmium, Holmium,
                                                                detector_const.vector_names_Holmium[i]);
            HolmiumVolumes[i]->SetVisAttributes(holmium);
            HolmiumVolumes[i]->SetRegion(MMC_Regions[i]);
            //HolmiumVolumes[i]->SetUserLimits(limit_MMC);
            fVolumes.push_back(detector_const.vector_names_Holmium[i]);

            MMCVolumes[i] = new G4LogicalVolume(SolidMMC, Vacuum,
                                                        detector_const.vector_names_MMC[i]);
            MMCVolumes[i]->SetRegion(MMC_Regions[i]);
            MMC_Regions[i]->AddRootLogicalVolume(MMCVolumes[i]);
            //MMCVolumes[i]->SetUserLimits(limit_MMC);
            fVolumes.push_back(detector_const.vector_names_MMC[i]);

            position_MMCIn1K =
                G4ThreeVector(detector_const.vector_position_x_MMCIn1K[i],
                                            detector_const.vector_position_y_MMCIn1K[i],
                                            detector_const.vector_position_z_MMCIn1K[i]);
            new G4PVPlacement(0, position_MMCIn1K, MMCVolumes[i],
                                        MMCVolumes[i]->GetName(), Logic1K, false, 0, true);
            new G4PVPlacement(0, position_AbsorberInMMC, AbsorberVolumes[i],
                                                AbsorberVolumes[i]->GetName(), MMCVolumes[i],
                                                false, 0, true);
            new G4PVPlacement(0, position_SilverInAbsorber, SilverVolumes[i],
                                                SilverVolumes[i]->GetName(), AbsorberVolumes[i],
                                                false, 0, true);
            new G4PVPlacement(0, position_HolmiumInSilver, HolmiumVolumes[i],
                                                HolmiumVolumes[i]->GetName(), SilverVolumes[i],
                                                false, 0, true);
            new G4PVPlacement(0, position_SensorInMMC, SensorVolumes[i],
                                                SensorVolumes[i]->GetName(), MMCVolumes[i],
                                                false, 0, true);
            /*
            LogicSubSubP[i] = new G4LogicalVolume(
                SolidSubSubP, Silicon,
                detector_const.vector_names_SubSubP[i]);
            LogicSubSubP[i]->SetVisAttributes(chip);
            LogicSubSubP[i]->SetRegion(Wafer_Region);

            new G4PVPlacement(0, G4ThreeVector(
                detector_const.vector_position_x_SubSubPInSubP[i],
                detector_const.vector_position_y_SubSubPInSubP[i],
                detector_const.vector_position_z_SubSubPInSubP[i]),
                LogicSubSubP[i],
                detector_const.vector_names_SubSubP[i],
                LogicWafer, false, 0, true);

            fVolumes.push_back(
                detector_const.vector_names_SubSubP[i]);
                */
    }

    for (int i = 0; i < 18; i++)
    {
        sBath_Regions[i] = new G4Region(detector_const.vector_names_Bath[i]);
        BathVolumes[i] = new G4LogicalVolume(SolidSmallBath, Gold,
                                                                                 detector_const.vector_names_Bath[i]);
        BathVolumes[i]->SetVisAttributes(goldS);
        BathVolumes[i]->SetRegion(sBath_Regions[i]);
        sBath_Regions[i]->AddRootLogicalVolume(BathVolumes[i]);
        //BathVolumes[i]->SetUserLimits(limit_Bath);
        fVolumes.push_back(detector_const.vector_names_Bath[i]);

        position_MMCIn1K =
            G4ThreeVector(detector_const.vector_position_x_BathIn1K[i],
                                        detector_const.vector_position_y_BathIn1K[i],
                                        detector_const.vector_position_z_BathIn1K[i]);
        new G4PVPlacement(0, position_MMCIn1K, BathVolumes[i],
                                            BathVolumes[i]->GetName(), Logic1K, false, 0, true);
    }

    for (int i = 0; i < 9; i++)
    {
        Plug_Regions[i] = new G4Region(detector_const.vector_names_Plug[i]);
        PlugVolumes[i] = new G4LogicalVolume(SolidPlug, Plastic,
                                                                                 detector_const.vector_names_Plug[i]);
        PlugVolumes[i]->SetVisAttributes(platine3);
        PlugVolumes[i]->SetRegion(Plug_Regions[i]);
        Plug_Regions[i]->AddRootLogicalVolume(PlugVolumes[i]);
        //PlugVolumes[i]->SetUserLimits(limit_Plug);
        fVolumes.push_back(detector_const.vector_names_Plug[i]);

        position_MMCIn1K =
            G4ThreeVector(detector_const.vector_position_x_PlugInBox[i],
                                        detector_const.vector_position_y_PlugInBox[i],
                                        detector_const.vector_position_z_PlugInBox[i]);
        new G4PVPlacement(0, position_MMCIn1K, PlugVolumes[i],
                                            PlugVolumes[i]->GetName(), LogicBox, false, 0, true);
    }

    new G4PVPlacement(0, position_CB0TopInInnerS, LogicCB0, name_CB0 + "_Top",
                                        LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_CB0BottomInInnerS, LogicCB0, name_CB0 + "_Bottom",
                                        LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_CB1InInnerS, LogicCB1, name_CB1,
                                        LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_CB2InInnerS, LogicCB2, name_CB2,
                                        LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_CB3InInnerS, LogicCB3, name_CB3,
                                        LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_CB4InBox, LogicCB4, name_CB4,
                                        LogicBox, false, 0, true);

    new G4PVPlacement(0, position_SQTopLInInnerS, LogicSQUID_TL,
                                        LogicSQUID_TL->GetName(), LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_SQTopRInInnerS, LogicSQUID_TR,
                                        LogicSQUID_TR->GetName(), LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_SQBottomLInInnerS, LogicSQUID_BL,
                                        LogicSQUID_BL->GetName(), LogicInnerS, false, 0, true);
    new G4PVPlacement(0, position_SQBottomRInInnerS, LogicSQUID_BR,
                                        LogicSQUID_BR->GetName(), LogicInnerS, false, 0, true);
    // std::cout << "Construct Detector -- Completed." << std::endl;

    return PhysVeto;
}
