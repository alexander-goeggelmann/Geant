/// \file Screening_DetectorConst.hh
/// \brief Definition of the Screening_DetectorConst class
#ifndef Screening_DetectorConst_h
#define Screening_DetectorConst_h 1

#include <G4SystemOfUnits.hh>
#include <G4Types.hh>
//#include <G4Element.hh>
//#include <G4Material.hh>
#include <G4ThreeVector.hh>

// Defintion of materials
const G4double moleweight_Germanium = 72.6 * CLHEP::g / CLHEP::mole;
const G4double density_Germanium = 5.323 * CLHEP::g / CLHEP::cm3;
const G4double z_Germanium = 32.;

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

const G4double density_Cryo = 8.85 * CLHEP::g / CLHEP::cm3;
const G4double moleweight_Nickel = 58.6934 * CLHEP::g / CLHEP::mole;
const G4double density_Nickel = 8.908 * CLHEP::g / CLHEP::cm3;
const G4double z_Nickel = 28.;
const G4double moleweight_Molybdenum = 95.95 * CLHEP::g / CLHEP::mole;
const G4double density_Molybdenum = 10.28 * CLHEP::g / CLHEP::cm3;
const G4double z_Molybdenum = 42.;
const G4double moleweight_Iron = 55.845 * CLHEP::g / CLHEP::mole;
const G4double density_Iron = 7.874 * CLHEP::g / CLHEP::cm3;
const G4double z_Iron = 26.;

const G4double moleweight_Plastic = 12. * CLHEP::g / CLHEP::mole;
const G4double density_Plastic = 1. * CLHEP::g / CLHEP::cm3;
const G4double z_Plastic = 6.;

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

// Li-layer Detector
const G4double z_half_DetectorLi = 7. * CLHEP::cm / 2.;
const G4double d_DetectorLi = 6.7 * CLHEP::cm;
const G4double r_DetectorLi = d_DetectorLi / 2.;

// Aktive Detector
const G4double z_half_Detector = z_half_DetectorLi - 0.3 * CLHEP::um / 2.;
const G4double d_Detector = d_DetectorLi - 1.3 * CLHEP::mm;
const G4double r_Detector = d_Detector / 2.;

// Hole
const G4double z_half_Hole = 5.45 * CLHEP::cm / 2.;
const G4double d_Hole = 1.15 * CLHEP::cm;
const G4double r_Hole = d_Hole / 2.;

// B-layer Detector
const G4double z_half_DetectorB = z_half_Hole;
const G4double d_DetectorB = d_Hole + 0.4 * CLHEP::um / 2.;
const G4double r_DetectorB = d_DetectorB / 2.;

// Holder
const G4double z_half_Holder = z_half_DetectorLi;
const G4double d_Holder = 0.5 * d_DetectorLi;
const G4double r_Holder = d_Holder / 2.;

// Inner Box
const G4double d_InnerBox = 7.5 * CLHEP::mm;
const G4double x_half_InnerBox = d_InnerBox + d_DetectorLi / 2.;
const G4double y_half_InnerBox = x_half_InnerBox;
const G4double z_half_InnerBox = d_InnerBox + z_half_DetectorLi + z_half_Holder;

// Al Box
const G4double d_Box = 1.5 * CLHEP::mm;
const G4double x_half_Box = d_Box + x_half_InnerBox;
const G4double y_half_Box = d_Box + y_half_InnerBox;
const G4double z_half_Box = d_Box + z_half_InnerBox;

const G4double x_half_Window = x_half_Box - d_InnerBox / 2.;
const G4double y_half_Window = y_half_Box - d_InnerBox / 2.;
const G4double z_half_Window = d_Box / 2.;

const G4double x_half_Epoxy = x_half_Window;
const G4double y_half_Epoxy = y_half_Window;
const G4double z_half_Epoxy = 0.45 * CLHEP::mm / 2.;

// Copper sample
const G4double x_half_Copper = 3. * CLHEP::cm / 2.;
const G4double y_half_Copper = 4.5 * CLHEP::cm / 2.;
const G4double z_half_Copper = 3. * CLHEP::mm / 2.;

// PCB sample
const G4double x_half_PCB = 4.6 * CLHEP::cm / 2.;
const G4double y_half_PCB = 15.6 * CLHEP::cm / 2.;
const G4double z_half_PCB = 0.7 * CLHEP::mm / 2.;

// Al sample
const G4double x_half_Al = 11.5 * CLHEP::cm / 2.;
const G4double y_half_Al = 14. * CLHEP::cm / 2.;
const G4double z_half_Al = 1. * CLHEP::mm / 2.;

// Connector sample
const G4double x_half_Plug = 4.5 * CLHEP::cm / 2.;
const G4double y_half_Plug = 5.5 * CLHEP::cm / 2.;
const G4double z_half_Plug = 3. * CLHEP::mm / 2.;

// Volume
const G4double x_half_Volume = 20. * CLHEP::cm / 2.;
const G4double y_half_Volume = x_half_Volume;
const G4double z_half_Volume = x_half_Volume;

// World
const G4double x_half_World = 250. * CLHEP::cm / 2.;
const G4double y_half_World = x_half_World;
const G4double z_half_World = x_half_World;

const G4double d_sample_detector = 0.1 * CLHEP::cm;

// TODO Change this:
const G4double x_half_Sample = x_half_Plug;
const G4double y_half_Sample = y_half_Plug;
const G4double z_half_Sample = z_half_Plug;

const G4ThreeVector position_VolumeInWorld = G4ThreeVector(0., 0., 0.);
const G4ThreeVector position_SampleInVolume = G4ThreeVector(
    0., 0., -z_half_Volume + 2. * z_half_Box + d_sample_detector + z_half_Sample);
const G4ThreeVector position_BoxInVolume = G4ThreeVector(
    0., 0., -z_half_Volume + z_half_Box);
const G4ThreeVector position_WindowInBox = G4ThreeVector(
    0., 0., z_half_Box - z_half_Window);
const G4ThreeVector position_EpoxyInWindow = G4ThreeVector(
    0., 0., -z_half_Window + z_half_Epoxy);
const G4ThreeVector position_InnerBoxInBox = G4ThreeVector(0., 0., 0.);
const G4ThreeVector position_DetectorLiInInnerBox = G4ThreeVector(
    0., 0., z_half_InnerBox - z_half_DetectorLi - d_InnerBox);
const G4ThreeVector position_HolderInInnerBox = G4ThreeVector(
    0., 0., z_half_InnerBox - 2. * z_half_DetectorLi - d_InnerBox - z_half_Holder);
const G4ThreeVector position_DetectorInDetectorLi = G4ThreeVector(
    0., 0., -z_half_DetectorLi + z_half_Detector);
const G4ThreeVector position_DetectorBInDetector = G4ThreeVector(
    0., 0., -z_half_Detector + z_half_DetectorB);
const G4ThreeVector position_HoleInDetectorB = G4ThreeVector(
    0., 0., -z_half_DetectorB + z_half_Hole);


const G4double min_range_Box = 300. * CLHEP::nm;

const G4String name_Detector = "0_Detector";
const G4String name_DetectorLi = "1_DetectorLi";
const G4String name_DetectorB = "2_DetectorB";
const G4String name_Hole = "3_Hole";
const G4String name_Holder = "4_Holder";
const G4String name_InnerBox = "5_InnerBox";
const G4String name_Box = "6_Box";
const G4String name_Window = "7_Window";
const G4String name_Epoxy = "8_Epoxy";
const G4String name_Sample = "9_Sample";
const G4String name_Volume = "a_Volume";
const G4String name_World = "b_World";

#endif
