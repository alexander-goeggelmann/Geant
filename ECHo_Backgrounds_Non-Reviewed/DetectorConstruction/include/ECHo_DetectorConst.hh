/// \file ECHo_DetectorConst.hh
/// \brief Definition of the ECHo_DetectorConst class
#ifndef ECHo_DetectorConst_h
#define ECHo_DetectorConst_h 1

#include <G4SystemOfUnits.hh>
#include <G4Types.hh>
//#include <G4Element.hh>
//#include <G4Material.hh>
#include <G4ThreeVector.hh>

const int number_of_pixels = 72;

const G4String alphabet[] = {"_A", "_B", "_C", "_D", "_E", "_F", "_G", "_H",
                             "_I", "_J", "_K", "_L", "_M", "_N", "_O", "_P",
                             "_Q", "_R", "_S", "_T", "_U", "_V", "_W", "_X",
                             "_Y", "_Z"};

// Defintion of materials
const G4double moleweight_Gold = 197. * CLHEP::g / CLHEP::mole;
const G4double density_Gold = 19.32 * CLHEP::g / CLHEP::cm3;
const G4double z_Gold = 79.;

const G4double moleweight_Erbium = 167.32 * CLHEP::g / CLHEP::mole;
const G4double density_Erbium = 9.05 * CLHEP::g / CLHEP::cm3;
const G4double z_Erbium = 68.;

const G4double moleweight_Silver = 108. * CLHEP::g / CLHEP::mole;
const G4double density_Silver = 10.49 * CLHEP::g / CLHEP::cm3;
const G4double z_Silver = 47.;

const G4double moleweight_Holmium = 163. * CLHEP::g / CLHEP::mole;
const G4double density_Holmium = 8.78 * CLHEP::g / CLHEP::cm3;
const G4double z_Holmium = 67.;

const G4double moleweight_Silicon = 28.085 * CLHEP::g / CLHEP::mole;
const G4double density_Silicon = 2.336 * CLHEP::g / CLHEP::cm3;
const G4double z_Silicon = 14.;

const G4double moleweight_Iron = 55.845 * CLHEP::g / CLHEP::mole;
const G4double density_Iron = 7.874 * CLHEP::g / CLHEP::cm3;
const G4double z_Iron = 26.;

const G4double moleweight_Plastic = 12. * CLHEP::g / CLHEP::mole;
const G4double density_Plastic = 1. * CLHEP::g / CLHEP::cm3;
const G4double z_Plastic = 6.;

const G4double density_PCB = 1.85 * CLHEP::g / CLHEP::cm3;
const G4double moleweight_Oxygen = 15.999 * CLHEP::g / CLHEP::mole;
const G4double density_Oxygen = 1.429e-3 * CLHEP::g / CLHEP::cm3;
const G4double z_Oxygen = 8.;
const G4double moleweight_Hydrogen = 1.008 * CLHEP::g / CLHEP::mole;
const G4double density_Hydrogen = 0.0899e-3 * CLHEP::g / CLHEP::cm3;
const G4double z_Hydrogen = 1.;
const G4double moleweight_Carbon = 12.011 * CLHEP::g / CLHEP::mole;
const G4double density_Carbon = 3.0 * CLHEP::g / CLHEP::cm3;
const G4double z_Carbon = 6.;

const G4double moleweight_Copper = 63.546 * CLHEP::g / CLHEP::mole;
const G4double density_Copper = 8.92 * CLHEP::g / CLHEP::cm3;
const G4double z_Copper = 29.;

const G4double moleweight_Aluminium = 26.981 * CLHEP::g / CLHEP::mole;
const G4double density_Aluminium = 2.7 * CLHEP::g / CLHEP::cm3;
const G4double z_Aluminium = 13.;

const G4double moleweight_Vacuum = 1.008 * CLHEP::g / CLHEP::mole;
const G4double density_Vacuum = 1.e-25 * CLHEP::g / CLHEP::cm3;
const G4double temperature_Vacuum = 1e-3 * CLHEP::kelvin;
const G4double preasure_Vacuum = 3e-18 * CLHEP::pascal;
const G4double z_Vacuum = 1.;

const G4double fraction_Erbium = 200e-6;
const G4double fraction_Silver = 1. - fraction_Erbium;

// MMC
const G4double x_half_Absorber = 180. * CLHEP::um / 2.;
const G4double y_half_Absorber = 180. * CLHEP::um / 2.;
const G4double z_half_Absorber = 10. * CLHEP::um / 2.;

const G4double x_half_Silver = x_half_Absorber;
const G4double y_half_Silver = y_half_Absorber;
const G4double z_half_Silver = 200. * CLHEP::nm / 2.;

const G4double x_half_Holmium = 160. * CLHEP::um / 2.;
const G4double y_half_Holmium = 160. * CLHEP::um / 2.;
const G4double z_half_Holmium = 10. * CLHEP::nm / 2.;

const G4double x_half_Sensor = x_half_Absorber;
const G4double y_half_Sensor = y_half_Absorber;
const G4double z_half_Sensor = 1.35 * CLHEP::um / 2.;

const G4double x_half_MMC = x_half_Absorber;
const G4double y_half_MMC = y_half_Absorber;
const G4double z_half_MMC = z_half_Absorber + z_half_Sensor;

// 1K-Board
const G4double x_half_Wafer = 9.98 * CLHEP::mm / 2.;
const G4double y_half_Wafer = 4.84 * CLHEP::mm / 2.;
const G4double z_half_Wafer = 0.35 * CLHEP::mm / 2.;

const G4double x_half_SubP0 = x_half_Absorber + 40. * CLHEP::um;
const G4double y_half_SubP0 = y_half_Absorber + 40. * CLHEP::um;
const G4double z_half_SubP0 = z_half_Wafer - 24. * CLHEP::um;

const G4double x_half_SubP1 = 2. * x_half_Absorber + (40. + 59.) * CLHEP::um;
const G4double y_half_SubP1 = 2. * y_half_Absorber + (60. + 59.) * CLHEP::um;
const G4double z_half_SubP1 = z_half_Wafer - 24. * CLHEP::um;

const G4double x_half_Bath = 1.9 * CLHEP::mm / 2.;
const G4double y_half_Bath = 2.1 * CLHEP::mm / 2.;
const G4double z_half_Bath = 1.0 * CLHEP::um / 2.;

const G4double x_half_bath = 0.46 * CLHEP::mm / 2.;
const G4double y_half_bath = 1.2 * CLHEP::mm / 2.;
const G4double z_half_bath = z_half_Bath;

const G4double x_half_1K = x_half_Wafer + 1. * CLHEP::um;
const G4double y_half_1K = y_half_Wafer + 1. * CLHEP::um;
const G4double z_half_1K = 1.55 * CLHEP::mm / 2.; //z_half_Wafer + z_half_MMC;

const G4double position_x_MMCIn1K =
    60. * CLHEP::um + x_half_MMC;
const G4double position_y_MMCIn1K =
    60. * CLHEP::um + y_half_MMC;
const G4double position_z_MMCIn1K =
    -z_half_1K + 2. * z_half_Wafer + z_half_MMC;
const G4double small_delta_x_MMC = 2. * x_half_MMC + 80. * CLHEP::um;
const G4double big_delta_x_MMC = 2. * x_half_MMC + 120. * CLHEP::um;
const G4double delta_y_MMC = 2. * y_half_MMC + 120. * CLHEP::um;

const G4double x_half_sWafer = position_x_MMCIn1K +
                               4. * small_delta_x_MMC +
                               4. * big_delta_x_MMC +
                               x_half_MMC + 50. * CLHEP::um;
const G4double y_half_sWafer = position_y_MMCIn1K + delta_y_MMC +
                               y_half_MMC + 50. * CLHEP::um;
const G4double z_half_sWafer = 49.5 * CLHEP::um / 2.;

// Test-Source
const G4double x_half_Source = 500 * CLHEP::nm / 2.;
const G4double y_half_Source = x_half_Source;
const G4double z_half_Source = x_half_Source;

// SQUID
const G4double x_half_SQUID = 6. * CLHEP::mm / 2.;
const G4double y_half_SQUID = 2.5 * CLHEP::mm / 2.;
const G4double z_half_SQUID = 0.35 * CLHEP::mm / 2.;

// Veto
const G4double y_half_Panel_front_back = 20. * CLHEP::cm / 2.;
const G4double x_half_Panel_front_back = 3. * CLHEP::cm / 2.;
const G4double z_half_Panel_front_back = 130. * CLHEP::cm / 2.;

const G4double x_half_Panel_left_right = y_half_Panel_front_back;
const G4double y_half_Panel_left_right = x_half_Panel_front_back;
const G4double z_half_Panel_left_right = z_half_Panel_front_back;

const G4double x_half_Panel_top = z_half_Panel_front_back;
const G4double y_half_Panel_top = y_half_Panel_front_back;
const G4double z_half_Panel_top = x_half_Panel_front_back;

const G4double x_half_Panel_bottom = y_half_Panel_front_back;
const G4double y_half_Panel_bottom = z_half_Panel_front_back;
const G4double z_half_Panel_bottom = x_half_Panel_front_back;

const G4double x_half_Active_V = 4. * y_half_Panel_front_back;
const G4double y_half_Active_V = 4. * y_half_Panel_front_back;
const G4double z_half_Active_V = z_half_Panel_front_back;

const G4double x_half_Veto = 10. * CLHEP::m / 2.;
const G4double y_half_Veto = x_half_Veto;
const G4double z_half_Veto = x_half_Veto;

// Copper T Board
const G4double x_half_Copper_B0 = 15.7 * CLHEP::cm / 2.;
const G4double y_half_Copper_B0 = 2.64 * CLHEP::cm / 2.;
const G4double z_half_Copper_B0 = 0.7 * CLHEP::cm / 2.;

const G4double x_half_Copper5 = x_half_1K + 5. * CLHEP::um;
const G4double y_half_Copper5 = y_half_1K + 5. * CLHEP::um;
const G4double z_half_Copper5 = 5. * CLHEP::um;

const G4double x_half_Copper50 = x_half_1K + 50. * CLHEP::um;
const G4double y_half_Copper50 = y_half_1K + 50. * CLHEP::um;
const G4double z_half_Copper50 = 50. * CLHEP::um;

const G4double x_half_Copper500 = x_half_1K + 500. * CLHEP::um;
const G4double y_half_Copper500 = y_half_1K + 500. * CLHEP::um;
const G4double z_half_Copper500 = 500. * CLHEP::um;

const G4double x_half_Copper_B1 = 2.64 * CLHEP::cm / 2.;
const G4double y_half_Copper_B1 = 12.5 * CLHEP::cm / 2.;
const G4double z_half_Copper_B1 = z_half_Copper_B0;

const G4double x_half_Plug = 0.5 * CLHEP::cm / 2.;
const G4double y_half_Plug = 1.5 * CLHEP::cm / 2.;
const G4double z_half_Plug = 1. * CLHEP::cm / 2.;

// PCB
const G4double x_half_CB0 = 2. * x_half_Wafer;
const G4double y_half_CB0 = y_half_Copper_B0 / 3.;
const G4double z_half_CB0 = 1.55 * CLHEP::mm / 2.;

const G4double x_half_CB1 = x_half_CB0 / 2. - x_half_SQUID - 0.1 * CLHEP::mm;
const G4double y_half_CB1 = y_half_Wafer;
const G4double z_half_CB1 = z_half_CB0;

const G4double x_half_CB2 = x_half_CB0 - x_half_CB1;
const G4double y_half_CB2 = y_half_Copper_B0;
const G4double z_half_CB2 = z_half_CB0;

const G4double x_half_CB3 = x_half_Copper_B0 - x_half_CB0 - x_half_CB2;
const G4double y_half_CB3 = y_half_Copper_B0;
const G4double z_half_CB3 = z_half_CB0;

const G4double x_half_CB4 = x_half_Copper_B1;
const G4double y_half_CB4 = y_half_Copper_B1;
const G4double z_half_CB4 = z_half_CB0;

/*
                                         |---------|
                                         |         |
                                         |         |
|----------|--------------|------||------|         |
|          |  CB0_Top     |              |         |
|          |--------------|              |         |
|          |              |              |         |
|          |      |-------|              |         |
|   CB2    |      |  CB1  |    CB3       |   CB4   |
|          |      |-------|              |         |
|          |              |              |         |
|          |--------------|              |         |
|          |  CB0_Bottom  |              |         |
|----------|--------------|------||------|         |
                                         |         |
                                         |         |
                                         |---------|
*/

// Shielding
const G4double thickness_Shielding = 5.555 * CLHEP::mm;
const G4double thickness_Shielding_top = 3. * CLHEP::mm;
const G4double thickness_Shielding_left = 10.3 * CLHEP::mm;

const G4double thickness_5 = 5. * CLHEP::um;
const G4double thickness_50 = thickness_5 + 50. * CLHEP::um;
const G4double thickness_500 = thickness_50 + 500. * CLHEP::um;

const G4double x_half_Shielding = x_half_Copper_B0 + (thickness_Shielding_left / 2.);
const G4double y_half_Shielding = y_half_Copper_B0 + thickness_Shielding_left;
const G4double z_half_Shielding =
    z_half_Copper_B0 + z_half_1K + thickness_Shielding_top + 0.45 * CLHEP::mm;

// const G4double thickness_S500 = thickness_Shielding - 5. * CLHEP::mm;
const G4double thickness_S500 = 555. * CLHEP::um;
const G4double x_half_S500 = x_half_Copper_B0 + (thickness_S500 / 2.);
const G4double y_half_S500 = y_half_Copper_B0 + thickness_S500;
const G4double z_half_S500 = z_half_Copper_B0 + z_half_1K + thickness_S500 + 0.45 * CLHEP::mm;

// const G4double thickness_S50 = thickness_S500 - 500. * CLHEP::um;
const G4double thickness_S50 = 55. * CLHEP::um;
const G4double x_half_S50 = x_half_Copper_B0 + (thickness_S50 / 2.);
const G4double y_half_S50 = y_half_Copper_B0 + thickness_S50;
const G4double z_half_S50 = z_half_Copper_B0 + z_half_1K + thickness_S50 + 0.45 * CLHEP::mm;

// const G4double thickness_S5 = thickness_S50 - 50. * CLHEP::um;
const G4double thickness_S5 = 5. * CLHEP::um;
const G4double x_half_S5 = x_half_Copper_B0 + (thickness_S5 / 2.);
const G4double y_half_S5 = y_half_Copper_B0 + thickness_S5;
const G4double z_half_S5 = z_half_Copper_B0 + z_half_1K + thickness_S5 + 0.45 * CLHEP::mm;

const G4double x_half_InnerS = x_half_Copper_B0;
const G4double y_half_InnerS = y_half_Copper_B0;
const G4double z_half_InnerS = z_half_Copper_B0 + z_half_1K + 0.45 * CLHEP::mm;

const G4double x_half_Box = x_half_Copper_B0 + x_half_Copper_B1 + thickness_Shielding_left / 2.;
const G4double y_half_Box = y_half_Copper_B1;
const G4double z_half_Box = 5. * CLHEP::cm; //z_half_Shielding;

//const G4ThreeVector origin = G4ThreeVector(0.0, 0.0, 0.0);

// MMC
const G4ThreeVector position_AbsorberInMMC = G4ThreeVector(
    0.0, 0.0, z_half_Sensor);
const G4ThreeVector position_SilverInAbsorber = G4ThreeVector(0.0, 0.0, 0.0);
const G4ThreeVector position_HolmiumInSilver = G4ThreeVector(0.0, 0.0, 0.0);
const G4ThreeVector position_SensorInMMC = G4ThreeVector(
    0.0, 0.0, -z_half_Absorber);


// 1K-Chip
const G4ThreeVector position_sWaferInWafer = G4ThreeVector(
    0., 0., z_half_Wafer - z_half_sWafer);
const G4ThreeVector position_WaferIn1K = G4ThreeVector(
    0.0, 0.0, -z_half_1K + z_half_Wafer);
const G4ThreeVector position_SourceIn1K = G4ThreeVector(
    0., 0., z_half_1K - 500 * CLHEP::nm);

const G4ThreeVector position_BathIn1K = G4ThreeVector(
    -3.69 * CLHEP::mm, 0.0, -z_half_1K + 2. * z_half_Wafer + z_half_Bath);
const G4double position_y0_BathIn1K = 1.16 * CLHEP::mm;
const G4double delta_x_Bath = 2. * x_half_bath + 80. * CLHEP::um;


// Inner Shielding
const G4ThreeVector position_B0InInnerS = G4ThreeVector(
    0., 0., -z_half_InnerS + z_half_Copper_B0);

const G4double deltachip = x_half_CB0 + 2. * x_half_CB2;
const G4ThreeVector position_1KInInnerS = G4ThreeVector(
    -x_half_InnerS + deltachip, 0.0,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_1K);

const G4double deltasquid = x_half_SQUID + 0.1 * CLHEP::mm;
const G4double ysquid = 3.95 * CLHEP::mm;
const G4ThreeVector position_SQTopLInInnerS = G4ThreeVector(
    -x_half_InnerS + deltachip - deltasquid, ysquid,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_SQUID);
const G4ThreeVector position_SQTopRInInnerS = G4ThreeVector(
    -x_half_InnerS + deltachip + deltasquid, ysquid,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_SQUID);
const G4ThreeVector position_SQBottomLInInnerS = G4ThreeVector(
    -x_half_InnerS + deltachip - deltasquid, -ysquid,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_SQUID);
const G4ThreeVector position_SQBottomRInInnerS = G4ThreeVector(
    -x_half_InnerS + deltachip + deltasquid, -ysquid,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_SQUID);

const G4ThreeVector position_CB0TopInInnerS = G4ThreeVector(
    -x_half_InnerS + 2. * x_half_CB2 + x_half_CB0, y_half_Copper_B0 - y_half_CB0,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_CB0);
const G4ThreeVector position_CB0BottomInInnerS = G4ThreeVector(
    -x_half_InnerS + 2. * x_half_CB2 + x_half_CB0, -y_half_Copper_B0 + y_half_CB0,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_CB0);
const G4ThreeVector position_CB1InInnerS = G4ThreeVector(
    -x_half_InnerS + 2. * x_half_CB2 + 2. * x_half_CB0 - x_half_CB1, 0.,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_CB0);
const G4ThreeVector position_CB2InInnerS = G4ThreeVector(
    -x_half_InnerS + x_half_CB2, 0.,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_CB0);
const G4ThreeVector position_CB3InInnerS = G4ThreeVector(
    -x_half_InnerS + 2. * x_half_CB2 + 2. * x_half_CB0 + x_half_CB3, 0.,
    -z_half_InnerS + 2. * z_half_Copper_B0 + z_half_CB0);

const G4ThreeVector position_Copper500InCB0 = G4ThreeVector(
    -x_half_Copper_B0 + deltachip, 0., z_half_Copper_B0 - z_half_Copper500);
const G4ThreeVector position_Copper50InCopper500 = G4ThreeVector(
    0., 0., z_half_Copper500 - z_half_Copper50);
const G4ThreeVector position_Copper5InCopper50 = G4ThreeVector(
    0., 0., z_half_Copper50 - z_half_Copper5);


// Shielding
const G4ThreeVector position_S500InShielding = G4ThreeVector(
    (thickness_Shielding_left - thickness_500) / 2., 0., 0.);
const G4ThreeVector position_S50InS500 = G4ThreeVector(
    (thickness_500 - thickness_50) / 2., 0., 0.);
const G4ThreeVector position_S5InS50 = G4ThreeVector(
    (thickness_50 - thickness_5) / 2., 0., 0.);
const G4ThreeVector position_InnerSInS5 = G4ThreeVector(
    thickness_S5 / 2., 0., 0.);


// Box
const G4double delta_x_plug = x_half_Copper_B1 / 2.;
const G4double delta_y_plug = 2. * y_half_Plug + 0.1 * CLHEP::cm;
const G4double x0_plug = -x_half_Box + 2. * x_half_Copper_B0 + x_half_Copper_B1 +
                         thickness_Shielding_left;
const G4double z_PlugInBox = -z_half_Box + 2. * z_half_Copper_B0 +
                             z_half_Plug; // + thickness_Shielding;

// Copper T-Board
//const G4ThreeVector position_B0InBox = G4ThreeVector(
//    -x_half_Box + x_half_Copper_B0 + thickness_Shielding , 0.0,
//    -z_half_Box + z_half_Copper_B0 + thickness_Shielding);
const G4ThreeVector position_B1InBox = G4ThreeVector(
    -x_half_Box + 2. * x_half_Copper_B0 + thickness_Shielding_left + x_half_Copper_B1,
    0.0, -z_half_Box + z_half_Copper_B0 + thickness_Shielding_top);

const G4ThreeVector position_ShieldingInBox = G4ThreeVector(
    -x_half_Box + x_half_Shielding, 0.0,
    -z_half_Box + z_half_Shielding);

const G4ThreeVector position_CB4InBox = G4ThreeVector(
    -x_half_Box + 2. * x_half_Copper_B0 + thickness_Shielding_left + x_half_CB4, 0.,
    -z_half_Box + 2. * z_half_Copper_B0 + z_half_CB0 + thickness_Shielding_top);


// SetUp
const G4ThreeVector position_BoxInVeto = G4ThreeVector(
    0., 0., -z_half_Panel_front_back + 30. * CLHEP::cm);

const G4double delta_Panel = 0.5 * CLHEP::cm + y_half_Panel_front_back;
const G4double position_xy_Panel = 4. * y_half_Panel_front_back +
                                   (1. + 0.5 + 0.5) * CLHEP::cm +
                                   x_half_Panel_front_back;
const G4double position_z0_Panel = -z_half_Panel_front_back -
                                   x_half_Panel_front_back - 0.1 * CLHEP::cm;
const G4double position_z1_Panel = -z_half_Panel_front_back -
                                   3. * x_half_Panel_front_back - 0.2 * CLHEP::cm;
const G4double position_zz_Panel = 83. * CLHEP::cm - z_half_Panel_front_back;


const G4double min_range_Shielding = 1. * CLHEP::mm;
const G4double min_range_S500 = 20. * CLHEP::um;
const G4double min_range_S50 = 2. * CLHEP::um;
const G4double min_range_S5 = 100. * CLHEP::nm;
const G4double min_range_InnerS = 1. * CLHEP::um;

const G4double min_range_1K = 1. * CLHEP::um;
const G4double min_range_MMC = 100. * CLHEP::nm;
const G4double min_range_Bath = min_range_MMC;

const G4double min_range_PCB = 10. * CLHEP::um;
const G4double min_range_Plug = 1. * CLHEP::mm;
const G4double min_range_Panel = 2. * CLHEP::mm;

//const G4double min_E_kin_Setup = 100. * CLHEP::eV;
//const G4double max_step_Setup = 1. * CLHEP::mm;
//const G4double min_range_Setup = 10. * CLHEP::um;
const G4String name_Absorber = "0_Absorber";
const G4String name_Silver = "1_Silver";
const G4String name_Holmium = "2_Holmium";
const G4String name_Sensor = "3_Sensor";
const G4String name_MMC = "4_MMC";

const G4String name_Wafer = "5_Wafer";
const G4String name_sWafer = "6_sWafer";
const G4String name_Bath = "7_Bath";
const G4String name_sBath = "8_sBath";

const G4String name_Source = "9_Source";
const G4String name_1K = "a_1K";

const G4String name_CopperA = "b_Copper_A";
const G4String name_Copper500 = "c_Copper500";
const G4String name_Copper50 = "d_Copper50";
const G4String name_Copper5 = "e_Copper5";
const G4String name_CopperB = "f_Copper_B";

const G4String name_InnerS = "g_InnerShielding";
const G4String name_Shielding = "h_Shielding";
const G4String name_S500 = "i_Shielding500";
const G4String name_S50 = "j_Shielding50";
const G4String name_S5 = "k_Shielding5";

const G4String name_Plug = "l_Plug";

const G4String name_CB0 = "m_CB_0";
const G4String name_CB1 = "m_CB_1";
const G4String name_CB2 = "m_CB_2";
const G4String name_CB3 = "m_CB_3";
const G4String name_CB4 = "m_CB_4";

const G4String name_SQUID = "n_SQUID";

const G4String name_Box = "o_Box";
const G4String name_MuonPanel = "p_MuonPanel";
const G4String name_SetUp = "q_SetUp";

const G4String name_SubP = "r_SubP";
const G4String name_SubSubP = "s_SubSubP";

class ECHo_DetectorConst
{
    public:
        void setVectors()
        {
            G4bool vector_check = vector_position_x_MMCIn1K.size() == 0;
            G4ThreeVector position_MMCIn1K;
            G4int small_count = 0;
            G4int big_count = 0;

            G4double sign = 0.;
            G4double mult = 0.;

            G4double pos_x = 0.;
            G4double pos_y = 0.;
            G4double pos_z = position_z_MMCIn1K;

            //  ---------------------------------------------------------------------
            // |        ---   ---   ---   ---   -----   ---   ---   ---   ---        |
            // |        | |   | |   | |   | |   |   |   | |   | |   | |   | |        |
            // |        ---   ---   ---   ---   -----   ---   ---   ---   ---        |
            // |      (D8 D7 D6 D5 D4 D3 D2 D1 D0) (C0 C1 C2 C3 C4 C5 C6 C7 C8)      |
            // |  --- (B8 B7 B6 B5 B4 B3 B2 B1 B0) (A0 A1 A2 A3 A4 A5 A6 A7 A8)      |
            // | |   | ---------------------------------------------------------     |
            // |  --- (F8 F7 F6 F5 F4 F3 F2 F1 F0) (E0 E1 E2 E3 E4 E5 E6 E7 E8)      |
            // |      (H8 H7 H6 H5 H4 H3 H2 H1 H0) (G0 G1 G2 G3 G4 G5 G6 G7 G8)      |
            // |        ---   ---   ---   ---   -----   ---   ---   ---   ---        |
            // |        | |   | |   | |   | |   |   |   | |   | |   | |   | |        |
            // |        ---   ---   ---   ---   -----   ---   ---   ---   ---        |
            //  ---------------------------------------------------------------------
            if (vector_check)
            {
                for (int i = 0; i < (number_of_pixels / 4); i++)
                {
                    small_count = (i + 1) / 2;
                    big_count = i / 2;

                    // Row A
                    pos_x = position_x_MMCIn1K +
                            small_count * small_delta_x_MMC +
                            big_count * big_delta_x_MMC;
                    pos_y = position_y_MMCIn1K;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_A" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_A" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_A" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_A" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_A" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_A" + std::to_string(i));

                    // Row B
                    pos_x = -pos_x;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_B" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_B" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_B" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_B" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_B" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_B" + std::to_string(i));

                    // Row C
                    pos_x = -pos_x;
                    pos_y += delta_y_MMC;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_C" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_C" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_C" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_C" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_C" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_C" + std::to_string(i));

                    // Row D
                    pos_x = -pos_x;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_D" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_D" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_D" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_D" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_D" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_D" + std::to_string(i));

                    // Row G
                    pos_x = -pos_x;
                    pos_y = -pos_y;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_G" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_G" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_G" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_G" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_G" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_G" + std::to_string(i));

                    // Row H
                    pos_x = -pos_x;
                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_H" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_H" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_H" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_H" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_H" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_H" + std::to_string(i));

                    // Row E
                    pos_x = -pos_x;
                    pos_y += delta_y_MMC;
                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_E" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_E" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_E" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_E" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_E" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_E" + std::to_string(i));

                    // Row F
                    pos_x = -pos_x;
                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_MMCIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_SubSubPInSubP.push_back(
                        -z_half_Wafer + z_half_SubP1);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_F" + std::to_string(i));

                    vector_names_Sensor.push_back(
                        name_Sensor + "_F" + std::to_string(i));
                    vector_names_Holmium.push_back(
                        name_Holmium + "_F" + std::to_string(i));
                    vector_names_Silver.push_back(
                        name_Silver + "_F" + std::to_string(i));
                    vector_names_Absorber.push_back(
                        name_Absorber + "_F" + std::to_string(i));
                    vector_names_MMC.push_back(
                        name_MMC + "_F" + std::to_string(i));
                }
                /*
                for (int i = 0; i < 5; ++i)
                {
                    pos_x = 40. * CLHEP::um + position_x_MMCIn1K + \
                            x_half_Absorber + \
                            i * (4. * x_half_Absorber + 200. * CLHEP::um);
                    pos_y = position_y_MMCIn1K + y_half_Absorber + 60. * CLHEP::um;

                    vector_position_x_SubPInWafer.push_back(
                        (double) pos_x);
                    vector_position_y_SubPInWafer.push_back(
                        (double) pos_y);
                    vector_position_z_SubPInWafer.push_back(
                        (double) -z_half_Wafer + z_half_SubP0);
                    vector_names_SubP.push_back(
                        name_SubP + "_A" + std::to_string(i));

                    pos_x *= -1.;

                    vector_position_x_SubPInWafer.push_back(
                        (double) pos_x);
                    vector_position_y_SubPInWafer.push_back(
                        (double) pos_y);
                    vector_position_z_SubPInWafer.push_back(
                        (double) -z_half_Wafer + z_half_SubP0);
                    vector_names_SubP.push_back(
                        name_SubP + "_B" + std::to_string(i));

                    pos_x *= -1.;
                    pos_y *= -1.;

                    vector_position_x_SubPInWafer.push_back(
                        (double) pos_x);
                    vector_position_y_SubPInWafer.push_back(
                        (double) pos_y);
                    vector_position_z_SubPInWafer.push_back(
                        (double) -z_half_Wafer + z_half_SubP0);
                    vector_names_SubP.push_back(
                        name_SubP + "_C" + std::to_string(i));

                    pos_x *= -1.;

                    vector_position_x_SubPInWafer.push_back(
                        (double) pos_x);
                    vector_position_y_SubPInWafer.push_back(
                        (double) pos_y);
                    vector_position_z_SubPInWafer.push_back(
                        (double) -z_half_Wafer + z_half_SubP0);
                    vector_names_SubP.push_back(
                        name_SubP + "_D" + std::to_string(i));


                }

                for (int i = 0; i < 20; ++i)
                {
                    pos_x = x_half_Absorber + 40. * CLHEP::um;
                    pos_y = y_half_Absorber + 60. * CLHEP::um;

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) pos_x);
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) pos_y);
                    vector_position_z_SubSubPInSubP.push_back(1. * CLHEP::um);
                    vector_names_SubSubP.push_back(
                        name_SubSubP +  "_" + std::to_string(4 * i));


                    pos_x *= -1.;

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) pos_x);
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) pos_y);
                    vector_position_z_SubSubPInSubP.push_back(1. * CLHEP::um);
                    vector_names_SubSubP.push_back(
                        name_SubSubP + "_" + std::to_string(4 * i + 1));

                    pos_x *= -1.;
                    pos_y *= -1.;

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) pos_x);
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) pos_y);
                    vector_position_z_SubSubPInSubP.push_back(1. * CLHEP::um);
                    vector_names_SubSubP.push_back(
                        name_SubSubP + "_" + std::to_string(4 * i + 2));

                    pos_x *= -1.;

                    vector_position_x_SubSubPInSubP.push_back(
                        (double) pos_x);
                    vector_position_y_SubSubPInSubP.push_back(
                        (double) pos_y);
                    vector_position_z_SubSubPInSubP.push_back(1. * CLHEP::um);
                    vector_names_SubSubP.push_back(
                        name_SubSubP + "_" + std::to_string(4 * i + 3));
                }
                */
                //  -----------------------------------
                // |         15 11 7 3 0 2 6 10 14     |
                // | |--|    .....................     |
                // | |--|    .....................     |
                // |         17 13 9 5 1 4 8 12 16     |
                //  -----------------------------------
                pos_z = position_BathIn1K.getZ();
                for (int i = 0; i < 5; i++)
                {
                    pos_x = i * delta_x_Bath;
                    pos_y = position_y0_BathIn1K;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_BathIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_BathIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_BathIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    if (i != 0)
                    {
                        pos_x = -pos_x;
                        position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                        vector_position_x_BathIn1K.push_back(
                            (double) position_MMCIn1K.getX());
                        vector_position_y_BathIn1K.push_back(
                            (double) position_MMCIn1K.getY());
                        vector_position_z_BathIn1K.push_back(
                            (double) position_MMCIn1K.getZ());
                    }

                    pos_x = -pos_x;
                    pos_y = -pos_y;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_BathIn1K.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_BathIn1K.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_BathIn1K.push_back(
                        (double) position_MMCIn1K.getZ());

                    if (i != 0)
                    {
                        pos_x = -pos_x;
                        position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                        vector_position_x_BathIn1K.push_back(
                            (double) position_MMCIn1K.getX());
                        vector_position_y_BathIn1K.push_back(
                            (double) position_MMCIn1K.getY());
                        vector_position_z_BathIn1K.push_back(
                            (double) position_MMCIn1K.getZ());
                    }

                }

                for (int i = 0; i < 18; i++)
                {
                    vector_names_Bath.push_back(
                        name_sBath + "_" + std::to_string(i));
                }

                //                              ______
                //                             | 8  5 |
                //          -------------------| 4  1 |
                //         |                        0 |
                //          -------------------| 3  2 |
                //                             | 7  6 |
                //                              ------
                pos_z = z_PlugInBox;
                for (int i = 0; i < 3; i++)
                {
                    pos_x = x0_plug + delta_x_plug;
                    pos_y = i * delta_y_plug;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                    vector_position_x_PlugInBox.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_PlugInBox.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_PlugInBox.push_back(
                        (double) position_MMCIn1K.getZ());

                    if (i != 0)
                    {
                        pos_y = -pos_y;

                        position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                        vector_position_x_PlugInBox.push_back(
                            (double) position_MMCIn1K.getX());
                        vector_position_y_PlugInBox.push_back(
                            (double) position_MMCIn1K.getY());
                        vector_position_z_PlugInBox.push_back(
                            (double) position_MMCIn1K.getZ());

                        pos_x -= 2. * delta_x_plug;

                        position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                        vector_position_x_PlugInBox.push_back(
                            (double) position_MMCIn1K.getX());
                        vector_position_y_PlugInBox.push_back(
                            (double) position_MMCIn1K.getY());
                        vector_position_z_PlugInBox.push_back(
                            (double) position_MMCIn1K.getZ());

                        pos_y = -pos_y;

                        position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);

                        vector_position_x_PlugInBox.push_back(
                            (double) position_MMCIn1K.getX());
                        vector_position_y_PlugInBox.push_back(
                            (double) position_MMCIn1K.getY());
                        vector_position_z_PlugInBox.push_back(
                            (double) position_MMCIn1K.getZ());
                    }
                }

                for (int i = 0; i < 9; i++)
                {
                    vector_names_Plug.push_back(
                        name_Plug + "_" + std::to_string(i));
                }

                //                                                      Right_1
                //                                                        |
                //                Back_3                                  v
                //                  |  _______    _______    _______    _______
                //                  v/|       |  |       |  |       |  |      /|
                //             Back_2 |       |  |       |  |       |  |     / |
                //               | /  |       |  |       |  |       |  |    /  |
                //               v/|  |       |  |       |  |       |  |   /|  |
                //          Back_0 |  |       |  |       |  |       |  |  / |  |
                //            | /  |  |Right_3|  |Right_2|  |Right_0|  | /  |  |
                //            v/|  |  |       |  |       |  |       |  |/|  |  |
                //       Back_1 |  |  |       |  |       |  |       |  / |  | <-- Front_3
                //         | /  |  |  |       |  |       |  |       | /  |  |  |
                //         v/|  |  |  |       |  |       |  |        /|  |  |  |
                //         / |  |  |  |       |  |       |  |       / |  | <-- Front_2
                //        _______    _______    _______    _______ |  |  |  |  |
                //       |       |  |       |  |       |  |       ||  |  |  |  |
                //       |       |  |       |  |       |  |       ||  | <-- Front_0
                //       |       |  |       |  |       |  |       ||  |  |  |  |
                //       |       |  |       |  |       |  |       ||  |  |  |  /--------
                //       |       |  |       |  |       |  |       || <-- Front_1       /|
                //       |       |  |       |  |       |  |       ||  |  |  |/        <-- Top_3
                //       |Left_3 |  |Left_2 |  |Left_0 |  |Left_1 ||  |  |  /--------/ /
                //       |       |  |       |  |       |  |       ||  |  | /        /|/
                //       |       |  |       |  |       |  |       ||  |  |/        <-- Top_2
                //       |       |  |       |  |       |  |       ||  |  /--------/ /
                //       |       |  |       |  |       |  |       ||  | /        /|/
                //       |       |  |       |  |       |  |       ||  |/        <-- Top_0
                //       |       |  |       |  |       |  |       ||  /--------/ /
                //       |       |  |       |  |       |  |       || /        /|/
                //       |       |  |       |  |       |  |       ||/        <-- Top_1
                //        -------    -------    -------    -------  --------- /
                //       |                                                  |/
                //        --------------------------------------------------
                //      /       /  /       /  /       /  /       / /
                //     /       /  /       /  /       /  /       / /
                //    /       /  /       /  /       /  /       / /
                //   /       /  /       /  /       /  /       / /
                //   -------    -------    -------    -------- /
                //  |       |  |       |  |       |  |       |/
                //   -------    -------    -------    --------
                //     ^          ^          ^          ^
                //     |          |          |          |
                //  Bottom_3   Bottom_2   Bottom_0   Bottom_1
                for (int i = 0; i < 4; i++)
                {
                    sign = 1.;
                    mult = 0.;
                    if (i > 1) sign = -1.;
                    if ((i == 1) or (i == 3)) mult = 1.;

                    // Front
                    pos_x = position_xy_Panel;
                    pos_y = sign * delta_Panel +
                            2. * sign * mult * y_half_Panel_front_back +
                            sign * mult * CLHEP::cm;
                    pos_z = 0.;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_FrPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_FrPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_FrPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());

                    // Back
                    pos_x = -position_xy_Panel;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_BaPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_BaPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_BaPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());

                    // Left
                    pos_x = pos_y;
                    pos_y = position_xy_Panel;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_LePanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_LePanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_LePanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());

                    // Right
                    pos_y = -position_xy_Panel;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_RiPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_RiPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_RiPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());

                    // Top
                    pos_y = pos_x;
                    pos_x = position_zz_Panel;
                    pos_z = position_z0_Panel;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_ToPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_ToPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_ToPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());

                    // Bottom
                    pos_x = pos_y;
                    pos_y = position_zz_Panel;
                    pos_z = position_z1_Panel;

                    position_MMCIn1K = G4ThreeVector(pos_x, pos_y, pos_z);
                    vector_position_x_BoPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getX());
                    vector_position_y_BoPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getY());
                    vector_position_z_BoPanelInSetUp.push_back(
                        (double) position_MMCIn1K.getZ());
                }
            }
        }

        std::vector<double> vector_position_x_MMCIn1K;
        std::vector<double> vector_position_y_MMCIn1K;
        std::vector<double> vector_position_z_MMCIn1K;

        std::vector<double> vector_position_x_BathIn1K;
        std::vector<double> vector_position_y_BathIn1K;
        std::vector<double> vector_position_z_BathIn1K;

        std::vector<double> vector_position_x_PlugInBox;
        std::vector<double> vector_position_y_PlugInBox;
        std::vector<double> vector_position_z_PlugInBox;

        std::vector<double> vector_position_x_FrPanelInSetUp;
        std::vector<double> vector_position_y_FrPanelInSetUp;
        std::vector<double> vector_position_z_FrPanelInSetUp;

        std::vector<double> vector_position_x_BaPanelInSetUp;
        std::vector<double> vector_position_y_BaPanelInSetUp;
        std::vector<double> vector_position_z_BaPanelInSetUp;

        std::vector<double> vector_position_x_LePanelInSetUp;
        std::vector<double> vector_position_y_LePanelInSetUp;
        std::vector<double> vector_position_z_LePanelInSetUp;

        std::vector<double> vector_position_x_RiPanelInSetUp;
        std::vector<double> vector_position_y_RiPanelInSetUp;
        std::vector<double> vector_position_z_RiPanelInSetUp;

        std::vector<double> vector_position_x_ToPanelInSetUp;
        std::vector<double> vector_position_y_ToPanelInSetUp;
        std::vector<double> vector_position_z_ToPanelInSetUp;

        std::vector<double> vector_position_x_BoPanelInSetUp;
        std::vector<double> vector_position_y_BoPanelInSetUp;
        std::vector<double> vector_position_z_BoPanelInSetUp;


        std::vector<double> vector_position_x_SubPInWafer;
        std::vector<double> vector_position_y_SubPInWafer;
        std::vector<double> vector_position_z_SubPInWafer;

        std::vector<double> vector_position_x_SubSubPInSubP;
        std::vector<double> vector_position_y_SubSubPInSubP;
        std::vector<double> vector_position_z_SubSubPInSubP;

        std::vector<std::string> vector_names_Absorber;
        std::vector<std::string> vector_names_Holmium;
        std::vector<std::string> vector_names_Silver;
        std::vector<std::string> vector_names_Sensor;
        std::vector<std::string> vector_names_MMC;
        std::vector<std::string> vector_names_Bath;
        std::vector<std::string> vector_names_Plug;
        std::vector<std::string> vector_names_SubP;
        std::vector<std::string> vector_names_SubSubP;
};

inline ECHo_DetectorConst& get_DetectorConst()
{
    static ECHo_DetectorConst det_const;
    return det_const;
}

#endif
