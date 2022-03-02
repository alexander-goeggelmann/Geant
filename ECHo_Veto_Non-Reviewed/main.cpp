//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif
#include <G4UImanager.hh>

#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4Types.hh>

//#include <Randomize.hh>

#include "DetectorConstruction/include/ECHo_DetectorConstruction.hh"
#include "ActionInitialization/include/ECHo_ActionInitialization.hh"
#include "PhysicsList/include/ECHo_PhysicsList.hh"

#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>


static std::string get_parameter(std::string line)
{
    std::string result = "";
    bool find_e = false;

    for (int i = 0; i < line.size(); i++)
    {
        if (find_e and (line[i] != ' ')) result += line[i];
        if (line[i] == '=') find_e = true;
    }

    return result;
}


static G4bool get_bool(std::string line)
{
    G4bool b = false;
    if (boost::algorithm::contains(line, "true")) b = true;
    else if (boost::algorithm::contains(line, "True")) b = true;
    else if (boost::algorithm::contains(line, "t")) b = true;
    else if (boost::algorithm::contains(line, "T")) b = true;
    else if (boost::algorithm::contains(line, "1")) b = true;
    else if (boost::algorithm::contains(line, "false")) b = false;
    else if (boost::algorithm::contains(line, "False")) b = false;
    else if (boost::algorithm::contains(line, "f")) b = false;
    else if (boost::algorithm::contains(line, "F")) b = false;
    else if (boost::algorithm::contains(line, "0")) b = false;
    else
    {
        std::cout << "Can not interprete " + line;
        std::cout << " as a boolean. Value is set to False." << std::endl;
        std::cout << "Try one of 'True', 'true', 't', 'T', '1', 'False', ";
        std::cout << "'false', 'f', 'F' and '0'." << std::endl;
    }
    return b;
}


static int get_integer(std::string line)
{
    int out = 1;
    try
    {
        out = std::stoi(line);
    }
    catch (std::invalid_argument const &e)
    {
        std::cout << "Can not interprete " + line;
        std::cout << " as an integer. Value is set to 1." << std::endl;
        out = 1;
    }
    catch (std::out_of_range const &e)
    {
        std::cout << "Integer overflow: " + line + ".";
        std::cout << " Value is set to 1." << std::endl;
        out = 1;
    }

    return out;
}


int main(int argc,char** argv)
{
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    //#ifdef G4MULTITHREADED
    //G4MTRunManager* runManager = new G4MTRunManager;
    //#else
    G4RunManager* runManager = new G4RunManager;
    //#endif
    ECHo_DetectorConstruction *detector = new ECHo_DetectorConstruction();
    runManager->SetUserInitialization(detector);

    G4VModularPhysicsList *physicsList = new ECHo_PhysicsList();
    runManager->SetUserInitialization(physicsList);

    // G4String volume = "0_Absorber_A0";
    G4String volume = "h_Shielding";
    //G4String volume = "5_Wafer";
    G4String contamination = "Bulk";
    G4bool muon = false;
    G4int x_seed = 1;
    G4int y_seed = 1;
    //G4String nuclide = "K-40";
    //G4String nuclide = "U-238";
    G4String nuclide = "Th-232";
    G4bool save_prims = true;


    std::ifstream input("setup.init");
    if (input.is_open())
    {
        std::string line;
        std::string parameter;
        while (std::getline(input, line))
        {
            parameter = get_parameter(line);
            if (boost::algorithm::contains(line, "#")) continue;
            else if (boost::algorithm::contains(line, "volume")) volume = parameter;
            else if (boost::algorithm::contains(line, "contamination")) contamination = parameter;
            else if (boost::algorithm::contains(line, "nuclide")) nuclide = parameter;
            else if (boost::algorithm::contains(line, "x_seed")) x_seed = get_integer(parameter);
            else if (boost::algorithm::contains(line, "y_seed")) y_seed = get_integer(parameter);
            else if (boost::algorithm::contains(line, "save_prims")) save_prims = get_bool(parameter);
            else if (boost::algorithm::contains(line, "muon")) muon = get_bool(parameter);
            else if (line.size() > 0)
            {
                std::cout << "Can not interprete '" + line + "'." << std::endl;
                std::cout << "Hint: Use such syntax: x_seed = 10";
                std::cout << "Command is ignored." << std::endl;
            }

        }
        input.close();
    }


    if ((contamination != "Bulk") and (contamination != "Surface"))
    {
        contamination = "Bulk";
        std::cout << "Invalid value for contamination. Try one of 'Bulk' and ";
        std::cout << "'Surface'. Contamination is set to 'Bulk'." << std::endl;
    }

    volume = "o_Box";
    muon = true;
    save_prims = false;

    ECHo_ActionInitialization *act = new ECHo_ActionInitialization(
        detector, x_seed, y_seed, volume, contamination, nuclide, muon, save_prims);

    //act->AddMessage(standard_color);
    //act->AddMessage(standard_color);

    runManager->SetUserInitialization(act);

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui )
    {
        G4String command = "/control/foreach run_init.mac file ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
        delete ui;
    }
    else
    {
        UImanager->ApplyCommand(
            "/control/alias xSeed " + std::to_string(x_seed));
        UImanager->ApplyCommand(
            "/control/alias ySeed " + std::to_string(y_seed));
        UImanager->ApplyCommand(
            // "/control/foreach run_init.mac file viewer.mac");
            "/control/execute viewer.mac");
        ui->SessionStart();
    }

    delete visManager;
    delete runManager;
    delete act;
    delete detector;
    delete physicsList;
}

