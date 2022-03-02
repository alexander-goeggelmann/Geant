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
const G4double x_half_Box = 20. * CLHEP::cm / 2.;
const G4double y_half_Box = 20. * CLHEP::cm / 2.;
const G4double z_half_Box = 20. * CLHEP::cm / 2.;


// Veto
const G4double y_half_Panel_front_back = 18.4 * CLHEP::cm / 2.;
const G4double x_half_Panel_front_back = 3. * CLHEP::cm / 2.;
const G4double z_half_Panel_front_back = 120. * CLHEP::cm / 2.;

const G4double x_half_Panel_left_right = y_half_Panel_front_back;
const G4double y_half_Panel_left_right = x_half_Panel_front_back;
const G4double z_half_Panel_left_right = z_half_Panel_front_back;

const G4double x_half_Panel_top = z_half_Panel_front_back;
const G4double y_half_Panel_top = y_half_Panel_front_back;
const G4double z_half_Panel_top = x_half_Panel_front_back;

const G4double x_half_Panel_bottom = y_half_Panel_front_back;
const G4double y_half_Panel_bottom = z_half_Panel_front_back;
const G4double z_half_Panel_bottom = x_half_Panel_front_back;

const G4double x_half_Active_V = 4. * y_half_Panel_front_back + 0.75 * CLHEP::cm;
const G4double y_half_Active_V = 4. * y_half_Panel_front_back + 0.75 * CLHEP::cm;
const G4double z_half_Active_V = z_half_Panel_front_back;

const G4double x_half_Veto = 10. * CLHEP::m / 2.;
const G4double y_half_Veto = x_half_Veto;
const G4double z_half_Veto = x_half_Veto;

// SetUp
const G4ThreeVector position_BoxInVeto = G4ThreeVector(
    0., 0., -z_half_Panel_front_back + 50. * CLHEP::cm);

const G4double delta_Panel = 0.5 * CLHEP::cm + y_half_Panel_front_back + 0.8 * CLHEP::cm;
const G4double position_xy_Panel = 4. * (y_half_Panel_front_back + 0.8 * CLHEP::cm) +
                                   (1. + 0.5 + 0.5) * CLHEP::cm +
                                   x_half_Panel_front_back;
const G4double position_z0_Panel = -z_half_Panel_front_back - 5. * CLHEP::cm -
                                   x_half_Panel_front_back - 0.1 * CLHEP::cm;
const G4double position_z1_Panel = -z_half_Panel_front_back - 5. * CLHEP::cm -
                                   3. * x_half_Panel_front_back - 0.2 * CLHEP::cm;
const G4double position_zz_Panel = 83. * CLHEP::cm - z_half_Panel_front_back;


const G4double min_range_Box = 1. * CLHEP::cm;
const G4double min_range_Panel = 2. * CLHEP::mm;

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
            G4bool vector_check = vector_position_x_FrPanelInSetUp.size() == 0;
            G4ThreeVector position_MMCIn1K;
            G4int small_count = 0;
            G4int big_count = 0;

            G4double sign = 0.;
            G4double mult = 0.;

            G4double pos_x = 0.;
            G4double pos_y = 0.;
            G4double pos_z = 0.;

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

};

inline ECHo_DetectorConst& get_DetectorConst()
{
    static ECHo_DetectorConst det_const;
    return det_const;
}

#endif
