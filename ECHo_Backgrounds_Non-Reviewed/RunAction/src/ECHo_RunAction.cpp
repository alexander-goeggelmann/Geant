#include "../include/ECHo_RunAction.hh"
#include "../../ActionInitialization/include/ECHo_ActionInitialization.hh"
#include "../../output.hh"

#include <G4RunManager.hh>
#include <G4Run.hh>
#include <G4AccumulableManager.hh>
#include <G4Types.hh>
#include <G4Threading.hh>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>


void ECHo_RunAction::BeginOfRunAction(const G4Run* run)
{
    // inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    // reset accumulables to their initial values
    G4AccumulableManager* AccumulableManager = G4AccumulableManager::Instance();
    AccumulableManager->Reset();
    num_of_events = run->GetNumberOfEventToBeProcessed();
    //runID = run->GetRunID();
    std::cout << clear_display;
    std::cout << set_background;
}


void ECHo_RunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    //std::cout << event_energy.size() << std::endl;
    if (event_energy.size() > 0) SaveEvent();
    if (step_energy.size() > 0) SavePrims();
    //if (subp_energy.size() > 0) SaveSubP();
    //if (subsubp_energy.size() > 0) SaveSubSubP();
    // if (xpos.size() > 0) SavePos();

    G4AccumulableManager* AccumulableManager = G4AccumulableManager::Instance();
    AccumulableManager->Merge();

    if (IsMaster())
    {
        //std::cout << clear_display;
        std::cout << standard_color;
        std::cout << "-----------End of Run--------------" << std::endl;

        double diff = difftime(time(0), fInit->GetTimer());
        int minutes = diff / 60;
        int seconds = diff - 60 * minutes;

        G4String path = fInit->GetDatePath() + fInit->GetDelimiter();
        path += std::to_string(nofEvents) + "_Events.txt";
        std::ofstream myFile;
        myFile.open(path, std::ios::app);
        myFile << "Simulation duration: " << minutes << " minutes and ";
        myFile << seconds << " seconds." << std::endl;

        myFile.close();
        std::cout << "Simulation duration: " << minutes << " minutes and ";
        std::cout << seconds << " seconds." << std::endl;
        std::cout << "\033[0m\n";
    }
}


void ECHo_RunAction::SaveEvent()
{
    std::ofstream myFile;
    G4String path = fInit->GetEventPath() + fInit->GetDelimiter();
    path += std::to_string(G4Threading::G4GetThreadId());

    myFile.open(path + "_event.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_event_number[0],
                 event_event_number.size() * sizeof(uint32_t));
    myFile.close();

    myFile.open(path + "_energy.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_energy[0],
                 event_energy.size() * sizeof(uint64_t));
    myFile.close();

    myFile.open(path + "_volume.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_volume[0],
                 event_volume.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_first_time.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_time[0],
                 event_time.size() * sizeof(uint64_t));
    myFile.close();

    myFile.open(path + "_t19.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_time19[0],
                 event_time19.size() * sizeof(uint64_t));
    myFile.close();

    myFile.open(path + "_origin.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_origin[0],
                 event_origin.size() * sizeof(int32_t));
    myFile.close();

    //myFile.open(path + "_veto.binary", std::ios::app | std::ios::binary);
    //myFile.write((char*) &event_veto[0],
    //             event_veto.size() * sizeof(uint8_t));
    //myFile.close();
    ClearEventVector();
}


void ECHo_RunAction::SavePrims()
{
    std::ofstream myFile;
    G4String path = fInit->GetPrimPath() + fInit->GetDelimiter();
    path += std::to_string(G4Threading::G4GetThreadId());

    myFile.open(path + "_event.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_event_number[0],
                step_event_number.size() * sizeof(uint32_t));
    myFile.close();

    myFile.open(path + "_energy.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_energy[0],
                 step_energy.size() * sizeof(uint64_t));
    myFile.close();

    myFile.open(path + "_volume.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_vol_number[0],
                 step_vol_number.size() * sizeof(uint16_t));
    myFile.close();

    myFile.open(path + "_depE.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_depE[0],
                 step_depE.size() * sizeof(uint64_t));
    myFile.close();

    myFile.open(path + "_particle.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_pdg[0],
                 step_pdg.size() * sizeof(int32_t));
    myFile.close();

    myFile.open(path + "_particle_id.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_particle_id[0],
                 step_particle_id.size() * sizeof(uint32_t));
    myFile.close();

    myFile.open(path + "_parent.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_parent_pdg[0],
                 step_parent_pdg.size() * sizeof(int32_t));
    myFile.close();

    myFile.open(path + "_parent_id.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_parent_id[0],
                 step_parent_id.size() * sizeof(uint32_t));
    myFile.close();

    myFile.open(path + "_process.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_process[0],
                 step_process.size() * sizeof(int8_t));
    myFile.close();

    myFile.open(path + "_stop.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &step_stoped[0],
                 step_stoped.size() * sizeof(uint8_t));
    myFile.close();
    ClearStepVector();
}

//void ECHo_RunAction::SavePos()
//{
//    std::ofstream myFile;
//    G4String path = fInit->GetPosPath() + "/";
//    path += std::to_string(G4Threading::G4GetThreadId());

//    myFile.open(path + "_xpos.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &xpos[0], xpos.size() * sizeof(int64_t));
//    myFile.close();

//    myFile.open(path + "_ypos.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &ypos[0], ypos.size() * sizeof(int64_t));
//    myFile.close();

//    myFile.open(path + "_zpos.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &zpos[0], zpos.size() * sizeof(int64_t));
//    myFile.close();

//    ClearPosVector();
//}

//void ECHo_RunAction::SaveSubP()
//{
//    std::ofstream myFile;
//    G4String path = fInit->GetSubPPath() + "/";
//    path += std::to_string(G4Threading::G4GetThreadId());

//    myFile.open(path + "_energy.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subp_energy[0],
//                 subp_energy.size() * sizeof(uint64_t));
//    myFile.close();

//    myFile.open(path + "_event.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subp_event_number[0],
//                 subp_event_number.size() * sizeof(uint32_t));
//    myFile.close();

//    myFile.open(path + "_volume.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subp_volume[0], subp_volume.size() * sizeof(uint8_t));
//    myFile.close();

//    ClearSubPVector();
//}

//void ECHo_RunAction::SaveSubSubP()
//{
//    std::ofstream myFile;
//    G4String path = fInit->GetSubSubPPath() + "/";
//    path += std::to_string(G4Threading::G4GetThreadId());

//    myFile.open(path + "_energy.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subsubp_energy[0],
//                 subsubp_energy.size() * sizeof(uint64_t));
//    myFile.close();

//    myFile.open(path + "_event.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subsubp_event_number[0],
//                 subsubp_event_number.size() * sizeof(uint32_t));
//    myFile.close();

//    myFile.open(path + "_volume.binary", std::ios::app | std::ios::binary);
//    myFile.write((char*) &subsubp_volume[0],
//                 subsubp_volume.size() * sizeof(uint8_t));
//    myFile.close();

//    ClearSubSubPVector();
//}