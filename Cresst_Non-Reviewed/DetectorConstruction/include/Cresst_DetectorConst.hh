/// \file Cresst_DetectorConst.hh
/// \brief Definition of the Cresst_DetectorConst class
#ifndef Cresst_DetectorConst_h
#define Cresst_DetectorConst_h 1

#include <G4SystemOfUnits.hh>
#include <G4Types.hh>
//#include <G4Element.hh>
//#include <G4Material.hh>
#include <G4ThreeVector.hh>

// Defintion of materials
const G4double moleweight_Calcium = 40. * CLHEP::g / CLHEP::mole;
const G4double density_Calcium = 1.55 * CLHEP::g / CLHEP::cm3;
const G4double z_Calcium = 20.;

const G4double moleweight_Tungsten = 183.8 * CLHEP::g / CLHEP::mole;
const G4double density_Tungsten = 19.25 * CLHEP::g / CLHEP::cm3;
const G4double z_Tungsten = 74.;

const G4double moleweight_Oxygen = 15.999 * CLHEP::g / CLHEP::mole;
const G4double density_Oxygen = 1.429e-3 * CLHEP::g / CLHEP::cm3;
const G4double z_Oxygen = 8.;

const G4double moleweight_Hydrogen = 1.008 * CLHEP::g / CLHEP::mole;
const G4double density_Hydrogen = 0.0899e-3 * CLHEP::g / CLHEP::cm3;
const G4double z_Hydrogen = 1.;

const G4double moleweight_Carbon = 12.011 * CLHEP::g / CLHEP::mole;
const G4double density_Carbon = 3.0 * CLHEP::g / CLHEP::cm3;
const G4double z_Carbon = 6.;

const G4double moleweight_Iron = 55.845 * CLHEP::g / CLHEP::mole;
const G4double density_Iron = 7.874 * CLHEP::g / CLHEP::cm3;
const G4double z_Iron = 26.;

const G4double moleweight_Copper = 63.546 * CLHEP::g / CLHEP::mole;
const G4double density_Copper = 8.92 * CLHEP::g / CLHEP::cm3;
const G4double z_Copper = 29.;

const G4double moleweight_Vacuum = 1.008 * CLHEP::g / CLHEP::mole;
const G4double density_Vacuum = 1.e-25 * CLHEP::g / CLHEP::cm3;
const G4double temperature_Vacuum = 1e-3 * CLHEP::kelvin;
const G4double preasure_Vacuum = 3e-18 * CLHEP::pascal;
const G4double z_Vacuum = 1.;

const G4double density_Glue = 1.85 * CLHEP::g / CLHEP::cm3;
const G4double density_Calciumtungstate = 6.06 * CLHEP::g / CLHEP::cm3;

// Detector
const G4double x_half_Detector = 1. * CLHEP::cm / 2.;
const G4double y_half_Detector = 1. * CLHEP::cm / 2.;
const G4double z_half_Detector = 1. * CLHEP::cm / 2.;
const G4double r_Detector = 2. * CLHEP::cm;

// Copper plate
const G4double y_half_Copper = 10. * CLHEP::cm / 2.;
const G4double x_half_Copper = 0.5 * CLHEP::cm / 2.;
const G4double z_half_Copper = 10. * CLHEP::cm / 2.;

// Source
const G4double x_half_Source = 0.2 * CLHEP::um / 2.;
const G4double y_half_Source = 1. * CLHEP::cm / 2.;
const G4double z_half_Source = 1. * CLHEP::cm / 2.;

// Screw
const G4double x_half_Screw = 1. * CLHEP::mm / 2.;
const G4double y_half_Screw = 1. * CLHEP::cm / 2.;
const G4double z_half_Screw = 1. * CLHEP::cm / 2.;

// Glue
const G4double x_half_Glue = 0.2 * CLHEP::um / 2.;
const G4double y_half_Glue = 1. * CLHEP::cm / 2.;
const G4double z_half_Glue = 1. * CLHEP::cm / 2.;

// Box
const G4double x_half_Box = 50. * CLHEP::cm / 2.;
const G4double y_half_Box = x_half_Box;
const G4double z_half_Box = x_half_Box;

// World
const G4double x_half_World = 1. * CLHEP::m / 2.;
const G4double y_half_World = x_half_World;
const G4double z_half_World = x_half_World;

const G4double distance_source_detector = 3. * CLHEP::cm;
const G4double distance_plate_detector = 1. * CLHEP::cm;

const G4ThreeVector position_BoxInWorld = G4ThreeVector(0., 0., 0.);
const G4ThreeVector position_DetectorInBox = G4ThreeVector(
    distance_source_detector / 2., 0., 0.);
const G4ThreeVector position_SourceInBox = G4ThreeVector(
    -distance_source_detector / 2., 0., 0.);
const G4ThreeVector position_ScrewInBox = G4ThreeVector(
    -distance_source_detector / 2. - (x_half_Source + x_half_Screw), 0., 0.);
const G4ThreeVector position_GlueInBox = G4ThreeVector(
    -distance_source_detector / 2. + (x_half_Source + x_half_Glue), 0., 0.);
const G4ThreeVector position_CopperInBox = G4ThreeVector(
    distance_source_detector / 2. - distance_plate_detector, 0., 0.);

const G4double min_range_Box = 100. * CLHEP::nm;

const G4String name_Detector = "0_Detector";
const G4String name_Source = "1_Source";
const G4String name_Plate = "2_Plate";
const G4String name_Box = "3_Box";
const G4String name_World = "4_World";
const G4String name_Screw = "5_Screw";
const G4String name_Glue = "6_Glue";

#endif
