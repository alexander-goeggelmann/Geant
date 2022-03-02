#include "../include/Cresst_ActionInitialization.hh"
// #include "../../PrimaryGenerator/include/Cresst_PrimaryGeneratorAction.hh"
#include "../../RunAction/include/Cresst_RunAction.hh"
#include "../../EventAction/include/Cresst_EventAction.hh"
#include "../../SteppingAction/include/Cresst_SteppingAction.hh"
#include "../../output.hh"

#include <time.h>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <G4Threading.hh>

Cresst_ActionInitialization::Cresst_ActionInitialization(
    Cresst_DetectorConstruction *det, G4int seedX_, G4int seedY_,
    G4String nuclide_, G4int d_)
    : G4VUserActionInitialization()
{
    d = d_;
    message = "";
    fDetector = det;
    now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // strftime(buf, sizeof(buf), "%Y_%m_%d_%X", &tstruct);
    strftime(buf, sizeof(buf), "%Y_%m_%d-%H_%M", &tstruct);

    SetSeedX(seedX_);
    SetSeedY(seedY_);
    SetNuclide(nuclide_);
    //std::cout << nucA << " " << nucZ << " " << nuclide << std::endl;

    G4String con_name = c_Bulk;
    G4String name_add = "_" + con_name + "_Source";
    G4String p_name = nuclide;

    date_path = root_path + "Source_" + std::to_string(d);
    boost::filesystem::create_directory(date_path);
    date_path += "/" + p_name + "_" + con_name;
    boost::filesystem::create_directory(date_path);
    date_path = date_path + "/" + buf;
    G4String appendix;
    G4int app = 0;
    if (boost::filesystem::exists(date_path))
    {
        appendix = "_" + std::to_string(app);
        while (boost::filesystem::exists(date_path + appendix))
        {
            app++;
            appendix = "_" + std::to_string(app);
        }
        date_path += appendix;
    }
    boost::filesystem::create_directory(date_path);

    event_path = date_path + "/Event";
    prims_path = date_path + "/Prims";
    pos_path = date_path + "/Positions";

    boost::filesystem::create_directory(event_path);
    // boost::filesystem::create_directory(pos_path);
    std::ofstream myFile;
    myFile.open(date_path + "/PDG.csv", std::ios::app);
    myFile << "Particle name" << "," << "PDG" << std::endl;
    myFile << "e-" << "," << 11 << std::endl;
    myFile << "e+" << "," << -11 << std::endl;
    myFile << "nu_e" << "," << 12 << std::endl;
    myFile << "anti_nu_e" << "," << -12 << std::endl;
    myFile << "mu-" << "," << 13 << std::endl;
    myFile << "mu+" << "," << -13 << std::endl;
    myFile << "nu_mu" << "," << 14 << std::endl;
    myFile << "anti_nu_mu" << "," << -14 << std::endl;
    myFile << "tau-" << "," << 15 << std::endl;
    myFile << "tau+" << "," << -15 << std::endl;
    myFile << "nu_tau" << "," << 16 << std::endl;
    myFile << "anti_nu_tau" << "," << -16 << std::endl;
    myFile << "gamma" << "," << 22 << std::endl;
    myFile << "proton" << "," << 2212 << std::endl;
    myFile << "anti_proton" << "," << -2212 << std::endl;
    myFile << "neutron" << "," << 2112 << std::endl;
    myFile << "anti_neutron" << "," << -2112 << std::endl;
    myFile << "lambda" << "," << 3122 << std::endl;
    myFile << "anti_lambda" << "," << -3122 << std::endl;
    myFile << "pi-" << "," << -211 << std::endl;
    myFile << "pi+" << "," << 211 << std::endl;
    myFile << "pi0" << "," << 111 << std::endl;
    myFile << "kaon-" << "," << -321 << std::endl;
    myFile << "kaon+" << "," << 321 << std::endl;
    myFile << "kaon0" << "," << 311 << std::endl;
    myFile << "kaon0L" << "," << 130 << std::endl;
    myFile << "kaon0S" << "," << 310 << std::endl;
    myFile << "alpha" << "," << 1000020040 << std::endl;
    myFile << "anti_alpha" << "," << -1000020040 << std::endl;
    myFile << "deuteron" << "," << 1000010020 << std::endl;
    myFile << "anti_deuteron" << "," << -1000010020 << std::endl;
    myFile << "ion" << "," << -1 << std::endl;
    myFile.close();

    fDetector->SetPath(date_path + "/Volumes.csv");

    G4String path = date_path + "/" + p_name + name_add + ".csv";
    myFile.open(path, std::ios::app);
    myFile << "Thickness in um" <<
              "," << "Ion A" << "," <<
              "Ion Z" << "," << "Particle name" << "," << "Seed X" << "," <<
              "Seed Y" << std::endl;
    myFile << d << "," <<
              nucA << "," << nucZ << "," << p_name << "," <<
              seedX << "," << seedY << std::endl;
    myFile.close();

    boost::filesystem::create_directory(prims_path);

    myFile.open(date_path + "/Processes.csv", std::ios::app);
    myFile << "Process name" << "," << "Process number" << std::endl;
    for (uint i = 0; i < fProcess.size(); i++)
    {
        myFile << fProcess[i] << "," << i << std::endl;
    }
    myFile.close();
}


void Cresst_ActionInitialization::BuildForMaster() const
{
    SetUserAction(new Cresst_RunAction(this));
}


void Cresst_ActionInitialization::Build() const
{
    //std::cout << nucA << " " << nucZ << " " << nuclide << std::endl;
    SetUserAction(new Cresst_PrimaryGeneratorAction(nucA, nucZ));

    Cresst_RunAction *runAction = new Cresst_RunAction(this);
    SetUserAction(runAction);

    Cresst_EventAction *eventAction = new Cresst_EventAction(runAction);
    eventAction->AddMessage(message);
    SetUserAction(eventAction);

    SetUserAction(new Cresst_SteppingAction(eventAction));
}


G4int Cresst_ActionInitialization::GetAFromString(G4String name)
{
    for (int i = 295; i > 0; i--)
    {
        if (name.find(std::to_string(i)) != std::string::npos) return (G4int) i;
    }
    message += red_color;
    message += "Can not find mass number. H-3 will be used.\n";
    return 0;
}


G4String Cresst_ActionInitialization::GetElement(G4String name)
{
    for (uint i = 0; i < e1_names.size(); i++)
    {
        if (name.find(e1_names[i]) != std::string::npos) return e1_names[i];
    }
    for (uint i = 0; i < e0_names.size(); i++)
    {
        if (name.find(e0_names[i]) != std::string::npos) return e0_names[i];
    }
    message += red_color;
    message += "Can not find given element. H-3 will be used.\n";
    return "ABC";
}


G4int Cresst_ActionInitialization::GetZFromString(G4String name)
{
    G4String element = GetElement(name);
    if (element == "ABC") element = "H";
    for (uint i = 0; i < e_names.size(); i++)
    {
        if (e_names[i] == element) return i + 1;
    }
    return 0;
}


void Cresst_ActionInitialization::SetNuclide(G4String name)
{
    G4int A = GetAFromString(name);
    G4String element = GetElement(name);

    if (A == 0) element = "H";
    if (element == "ABC") A = 3;
    message += green_color;
    message += "Decay of " + name + " will be simulated.\n";

    nucA = A;
    //std::cout << nucA << std::endl;
    nucZ = GetZFromString(element);
    //std::cout << nucZ << std::endl;
    nuclide = name;
}
