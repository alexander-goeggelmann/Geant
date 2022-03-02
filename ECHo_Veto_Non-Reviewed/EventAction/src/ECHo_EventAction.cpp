#include "../include/ECHo_EventAction.hh"
#include "../../RunAction/include/ECHo_RunAction.hh"
#include "../../output.hh"

#include <G4Event.hh>
#include <G4RunManager.hh>
#include <G4Threading.hh>
#include <iostream>
#include <fstream>
#include <G4String.hh>
#include <algorithm>
#include <time.h>
#include <boost/filesystem.hpp>
#include <G4ProcessTable.hh>


void ECHo_EventAction::BeginOfEventAction(const G4Event* run)
{

    num_of_events = fRunAction->GetNumOfEvents();
    number = run->GetEventID();
    ClearEventVector();
    // ClearPosVector();

    if ((num_of_events >= number_output) and ((number % (num_of_events / number_output)) == 0))
    {
        const double diff = difftime(time(0), fRunAction->GetTimer());
        const int counter = number / (num_of_events / number_output);
        const double time_left = (
            (G4double) number_output * diff / ((double) counter)) - diff;
        const int minutes = time_left / 60;
        const int seconds = time_left - 60 * minutes;
        G4String tempS = " minutes and ";
        G4String tempM = "Time left: ";
        const int percent = 100. * ((double) number) / ((double) num_of_events);
        if (seconds < 10) {tempS += " ";}
        if (minutes < 10) {tempM += " ";}

        std::cout << clear_display;
        std::cout << GetMessage();
        std::cout << standard_color;
        std::cout << "----------------------------------\n";
        std::cout << tempM << minutes << tempS << seconds;
        std::cout << " seconds. Processing: ";
        std::cout << percent;
        std::cout << " %." << std::endl;
    }
    //std::cout << "Start of Event " << number << std::endl;
}


void ECHo_EventAction::EndOfEventAction(const G4Event*)
{
    fRunAction->SetEventVector(
        number, front0, front1, front2, front3,
        back0, back1, back2, back3,
        left0, left1, left2, left3,
        right0, right1, right2, right3,
        top0, top1, top2, top3,
        bottom0, bottom1, bottom2, bottom3);

    if (fRunAction->GetEventLength() >= 10000) fRunAction->SaveEvent();
    //if (fRunAction->GetSubPLength() >= 10000) fRunAction->SaveSubP();
    //if (fRunAction->GetSubSubPLength() >= 10000) fRunAction->SaveSubSubP();
    //std::cout << "End of event " << number << std::endl;
    // if (fRunAction->GetPosLength() >= 10000) fRunAction->SavePos();
}

void ECHo_EventAction::AddPanel(const G4String volume)
{
    uint8_t index = volume[volume.size() - 1] - '0';
    switch (volume[volume.size() - 2])
    {
        case '0':
            switch (index)
            {
                case 0:
                    front0 = true;
                    break;
                case 1:
                    front1 = true;
                    break;
                case 2:
                    front2 = true;
                    break;
                default:
                    front3 = true;
            }
            break;
        case '1':
            switch (index)
            {
                case 0:
                    back0 = true;
                    break;
                case 1:
                    back1 = true;
                    break;
                case 2:
                    back2 = true;
                    break;
                default:
                    back3 = true;
            }
            break;
        case '2':
            switch (index)
            {
                case 0:
                    left0 = true;
                    break;
                case 1:
                    left1 = true;
                    break;
                case 2:
                    left2 = true;
                    break;
                default:
                    left3 = true;
            }
            break;
        case '3':
            switch (index)
            {
                case 0:
                    right0 = true;
                    break;
                case 1:
                    right1 = true;
                    break;
                case 2:
                    right2 = true;
                    break;
                default:
                    right3 = true;
            }
            break;
        case '4':
            switch (index)
            {
                case 0:
                    top0 = true;
                    break;
                case 1:
                    top1 = true;
                    break;
                case 2:
                    top2 = true;
                    break;
                default:
                    top3 = true;
            }
            break;
        default:
            switch (index)
            {
                case 0:
                    bottom0 = true;
                    break;
                case 1:
                    bottom1 = true;
                    break;
                case 2:
                    bottom2 = true;
                    break;
                default:
                    bottom3 = true;
            }
            break;
    }
}

// -----------------------------
// Begin Helper for parse_volume
// -----------------------------

static inline uint8_t get_number(const G4String volume)
{
    return volume[volume.size() - 1] - '0';
}

uint8_t ECHo_EventAction::get_pixel(const G4String volume)
{
    const uint8_t num = (volume[volume.size() - 2] - 'A') * 10;
    return num + get_number(volume);
}


static inline uint8_t get_number_in_name(const G4String volume)
{
    uint8_t num = get_number(volume);
    if ((volume[volume.size() - 2] == '_') or
            (volume[volume.size() - 2] == '0')) return num;
    else
    {
        uint8_t num1 = (volume[volume.size() - 2] - '0') * 10;
        return num + num1;
    }
}


static inline uint8_t get_number_pcb(const G4String volume)
{
    if (volume[volume.size() - 2] == '_') return get_number(volume) + 1;
    else if (volume[volume.size() - 1] == 'p') return 0;
    else return 1;
}

// -----------------------------
// End Helper for parse_volume
// -----------------------------

G4int ECHo_EventAction::parse_volume(const G4String volume)
{
    const char num = volume[0];
    switch (num)
    {
        case '0': // Absorber
            return 100 + get_pixel(volume);
        case '1': // Silver
            return 200 + get_pixel(volume);
        case '2': // Holmium
            return 300 + get_pixel(volume);
        case '3': // Sensor
            return 400 + get_pixel(volume);
        case '4': // MMC
            return 500 + get_pixel(volume);
        case '5': // Substrat
            return 600;
        case '6': // Small Substrat
            return 601;
        case '7': // Big Thermalizationbath
            return 700;
        case '8': // Small Thermalizationbath
            return 701 + get_number_in_name(volume);
        case '9': // Test Source
            return 800;
        case 'a': // ECHo-1K chip
            return 900;
        case 'b': // Long part of copper holder
            return 1000;
        case 'c': // 500 um part of copper holder
            return 1001;
        case 'd': // 50 um part of copper holder
            return 1002;
        case 'e': // 5 um part of copper holder
            return 1003;
        case 'f': // Orthogonal part of copper holder
            return 1010;
        case 'g': // Volume inside of shielding
            return 1100;
        case 'h': // Shielding
            return 1110;
        case 'i': // 500 um part of shielding
            return 1111;
        case 'j': // 50 um part of shielding
            return 1112;
        case 'k': // 5 um part of shiedling
            return 1113;
        case 'l': // Plugs
            return 1200 + get_number(volume);
        case 'm': // Printed circuit board
            return 1300 + get_number_pcb(volume);
        case 'n': // DC-SQUID chips
            return 1400 + get_number(volume);
        case 'o': // One ECHo-1K-Chip plus setup
            return 1500;
        case 'p': // Muon panels
            return 1600 + get_number_in_name(volume);
        case 'q': // The whole setup
            return 1700;
        case 'r': // Substrate Pixels
            return 1800 + get_pixel(volume);
        case 's': // Substrate Sub-Pixels
            return 1900 + get_pixel(volume);
        default: // Not defined volume
            return 1999;
    }
}


