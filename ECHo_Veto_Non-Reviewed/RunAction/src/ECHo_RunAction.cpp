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
    if (event_number.size() > 0) SaveEvent();

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

        G4String path = fInit->GetDatePath() + "/";
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
    G4String path = fInit->GetEventPath() + "/";
    path += std::to_string(G4Threading::G4GetThreadId());

    myFile.open(path + "_event.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &event_number[0],
                 event_number.size() * sizeof(uint32_t));
    myFile.close();

    myFile.open(path + "_front0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &front0[0],
                 front0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_front1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &front1[0],
                 front1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_front2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &front2[0],
                 front2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_front3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &front3[0],
                 front3.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_back0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &back0[0],
                 back0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_back1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &back1[0],
                 back1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_back2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &back2[0],
                 back2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_back3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &back3[0],
                 back3.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_left0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &left0[0],
                 left0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_left1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &left1[0],
                 left1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_left2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &left2[0],
                 left2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_left3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &left3[0],
                 left3.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_right0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &right0[0],
                 right0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_right1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &right1[0],
                 right1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_right2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &right2[0],
                 right2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_right3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &right3[0],
                 right3.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_top0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &top0[0],
                 top0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_top1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &top1[0],
                 top1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_top2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &top2[0],
                 top2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_top3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &top3[0],
                 top3.size() * sizeof(uint8_t));
    myFile.close();

    myFile.open(path + "_bottom0.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &bottom0[0],
                 bottom0.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_bottom1.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &bottom1[0],
                 bottom1.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_bottom2.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &bottom2[0],
                 bottom2.size() * sizeof(uint8_t));
    myFile.close();
    myFile.open(path + "_bottom3.binary", std::ios::app | std::ios::binary);
    myFile.write((char*) &bottom3[0],
                 bottom3.size() * sizeof(uint8_t));
    myFile.close();
    ClearEventVector();
}
