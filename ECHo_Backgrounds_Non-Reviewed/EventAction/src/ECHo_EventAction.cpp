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
    ClearStepVector();
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
    //std::cout << "----Begin EnOfEvent----" << std::endl;
    for (uint j = 0; j < event_Pixels.size(); ++j)
    {
        for (uint i = 0; i < event_Energy[j].size(); ++i)
        {
            fRunAction->SetEventVector(
                number, event_Energy[j][i], event_Pixels[j],
                event_FirstTime[j][i], event_Time19[j][i],
                event_Origin[j][i]);
        }
    }

    for (uint i = 0; i < step_energy.size(); ++i)
    {
        if (step_save[i])
        {
            fRunAction->SetStepVector(
                number, step_energy[i], step_vol_number[i],
                event_pdg[i], event_particle_id[i],
                step_parent_pdg[i], event_parent_id[i], step_process[i],
                step_depE[i], step_stop[i]);
        }
    }
    /*
    for (uint i = 0; i < 35; ++i)
    {
        if (event_Energy_SubP[i] > 0)
        {
            fRunAction->SetSubPVector(
                number, event_Energy_SubP[i], event_SubP[i]);
        }
    }

    for (uint i = 0; i < 80; ++i)
    {
        if (event_Energy_SubSubP[i] > 0)
        {
            fRunAction->SetSubSubPVector(
                number, event_Energy_SubSubP[i], event_SubSubP[i]);
        }
    }*/
    /*
    for (uint i = 0; i < xpos.size(); ++i)
    {
        fRunAction->SetPosVector(xpos[i], ypos[i], zpos[i]);
    }
    */
    //std::cout << "End Event" << std::endl;
    if (fRunAction->GetStepLength() >= 10000) fRunAction->SavePrims();
    if (fRunAction->GetEventLength() >= 10000) fRunAction->SaveEvent();
    //if (fRunAction->GetSubPLength() >= 10000) fRunAction->SaveSubP();
    //if (fRunAction->GetSubSubPLength() >= 10000) fRunAction->SaveSubSubP();
    //std::cout << "End of event " << number << std::endl;
    // if (fRunAction->GetPosLength() >= 10000) fRunAction->SavePos();
}


void ECHo_EventAction::SaveAncestors(uint32_t particle)
{
    if (step_save[particle - 1]) return;
    step_save[particle - 1] = true;
    const uint32_t parent_ID = event_parent_id[particle - 1];
    if (parent_ID > 0) SaveAncestors(parent_ID);
}


void ECHo_EventAction::CreateParticle_Verbose(
    const G4double energy, const G4int volume, const G4int particle_PDG,
        const G4int particle_ID, const G4int parent_ID, const int8_t process,
        const G4bool stop)
{
    uint32_t last_id;
    if (event_particle_id.size() == 0) last_id = 0;
    else last_id = event_particle_id[event_particle_id.size() - 1];

    const uint32_t this_id = (uint32_t) particle_ID;
    const uint32_t parent_id = (uint32_t) parent_ID;
    //std::cout << parent_id << std::endl;
    //std::cout << this_id << std::endl;
    //std::cout << last_id << std::endl;

    if (this_id < last_id)
    {
        event_pdg[particle_ID - 1] = (int32_t) particle_PDG;
        event_particle_id[particle_ID - 1] = this_id;
        event_parent_id[particle_ID - 1] = parent_id;

        step_parent_pdg[particle_ID - 1] = event_pdg[parent_ID - 1];
        step_energy[particle_ID - 1] = (uint64_t) energy;
        step_vol_number[particle_ID - 1] = (uint16_t) volume;
        step_process[particle_ID - 1] = process;

        if (volume < 600)
        {
            step_save[particle_ID - 1] = true;
            step_stop[particle_ID - 1] = stop;
            if (not step_save[parent_ID - 1]) SaveAncestors(parent_id);
        }
        return;
    }

    for (uint32_t i = last_id; i < this_id - 1; ++i)
    {
        event_pdg.push_back(0);
        event_particle_id.push_back(0);
        event_parent_id.push_back(0);

        step_parent_pdg.push_back(0);
        step_energy.push_back(0);
        step_vol_number.push_back(0);
        step_process.push_back(0);

        step_depE.push_back(0);
        step_save.push_back(false);
        step_stop.push_back(0);
    }

    event_pdg.push_back((int32_t) particle_PDG);
    event_particle_id.push_back(this_id);
    event_parent_id.push_back(parent_id);

    if (parent_ID > 0) step_parent_pdg.push_back(event_pdg[parent_ID - 1]);
    else step_parent_pdg.push_back(0);
    step_energy.push_back((uint64_t) energy);
    step_vol_number.push_back((uint16_t) volume);
    step_process.push_back(process);

    step_depE.push_back(0);

    if (volume < 600)
    {
        step_save.push_back(true);
        step_stop.push_back(stop);
        if (parent_ID > 0)
        {
            if (not step_save[parent_ID - 1]) SaveAncestors(parent_id);
        }
    }
    else
    {
        step_save.push_back(false);
        step_stop.push_back(false);
    }
    return;
}


void ECHo_EventAction::CreateParticle(
    const G4int particle_PDG, const G4int particle_ID, const G4int parent_ID)
{
    uint32_t last_id;
    if (event_particle_id.size() == 0) last_id = 0;
    else last_id = event_particle_id[event_particle_id.size() - 1];

    const uint32_t this_id = (uint32_t) particle_ID;

    if (this_id < last_id)
    {
        event_pdg[particle_ID - 1] = (int32_t) particle_PDG;
        event_particle_id[particle_ID - 1] = this_id;
        event_parent_id[particle_ID - 1] = (uint32_t) parent_ID;
        return;
    }

    for (uint32_t i = last_id; i < this_id - 1; ++i)
    {
        event_pdg.push_back(0);
        event_particle_id.push_back(0);
        event_parent_id.push_back(0);
    }
    event_pdg.push_back((int32_t) particle_PDG);
    event_particle_id.push_back(this_id);
    event_parent_id.push_back((uint32_t) parent_ID);
    return;

}


int32_t ECHo_EventAction::GetOrigin(const uint32_t particle_ID)
{
    //std::cout << "Particle " << particle_ID << std::endl;
    const uint32_t parent_id = event_parent_id[particle_ID - 1];
    if (parent_id == 0) return 0;
    const int32_t parent_pdg = event_pdg[parent_id - 1];
    if ((parent_pdg != (int32_t) 11) and
        (parent_pdg != (int32_t) 22) and
        (parent_pdg != (int32_t) 100002004))
    {
        return parent_pdg;
    }
    else return GetOrigin(parent_id);
}

void ECHo_EventAction::AddEnergy(
        const uint32_t particle_ID, const uint64_t energy, const G4int volume,
        const G4bool stop, const G4bool last)
{
    step_depE[particle_ID - 1] += energy;
    if (stop) step_stop[particle_ID - 1] = true;
    //std::cout << particle_ID - 1 << std::endl;
    if (step_vol_number[particle_ID - 1] == (uint16_t) volume)
    {
        const int8_t proc = step_process[particle_ID - 1];
        if (stop and ((proc < 6) or (proc == 17))) step_save[particle_ID - 1] = false;

        //std::cout << event_parent_id[particle_ID - 1] << std::endl;
        if (last or (proc == -1)) return;
        uint32_t parent_ID = event_parent_id[particle_ID - 1];
        const int8_t proc_parent = step_process[parent_ID];
        G4bool n_last = (proc == proc_parent) and (proc == 15);

        AddEnergy(parent_ID, energy, volume, step_stop[parent_ID - 1], n_last);
    }
}


void ECHo_EventAction::AddEvent(
    const uint8_t pixel, const uint64_t time, const uint64_t t19,
        const uint64_t energy, const uint32_t id)
{
    uint pixel_pos = event_Pixels.size();
    uint i;

    for (i = 0; i < event_Pixels.size(); ++i)
    {
        if (event_Pixels[i] == pixel)
        {
            pixel_pos = i;
            break;
        }
    }
    // Create new entry for new pixel
    if (pixel_pos == event_Pixels.size())
    {
        //std::cout << "new pixel" << std::endl;
        event_Pixels.push_back(pixel);
        event_Time19.push_back(std::vector<uint64_t> {t19});
        event_Energy.push_back(std::vector<uint64_t> {energy});
        event_Origin.push_back(std::vector<int32_t> {GetOrigin(id)});
        event_LastTime.push_back(std::vector<uint64_t> {time});
        event_FirstTime.push_back(std::vector<uint64_t> {time});
        return;
    }
    else
    {
        // Size can not be equal to zero, because of upper if condition
        const uint size = event_Energy[pixel_pos].size();
        const uint64_t last19 = event_Time19[pixel_pos][size - 1];

        if (last19 < t19)
        {
            //std::cout << "new t19" << std::endl;
            event_Time19[pixel_pos].push_back(t19);
            event_Energy[pixel_pos].push_back(energy);
            event_Origin[pixel_pos].push_back(GetOrigin(id));
            event_LastTime[pixel_pos].push_back(time);
            event_FirstTime[pixel_pos].push_back(time);
            return;
        }
        else
        {
            uint first_hit = size;
            uint last_hit = size;
            for (i = 0; i < size; ++i)
            {
                if (event_Time19[pixel_pos][i] == t19)
                {
                    if (first_hit == size) first_hit = i;
                    last_hit = i;
                }
                else if (event_Time19[pixel_pos][i] > t19)
                {
                    if (first_hit == size)
                    {
                        //std::cout << "t19 insert" << std::endl;
                        event_Energy[pixel_pos].insert(
                            event_Energy[pixel_pos].begin() + i, energy);
                        event_Origin[pixel_pos].insert(
                            event_Origin[pixel_pos].begin() + i, GetOrigin(id));
                        event_Time19[pixel_pos].insert(
                            event_Time19[pixel_pos].begin() + i, t19);
                        event_LastTime[pixel_pos].insert(
                            event_LastTime[pixel_pos].begin() + i, time);
                        event_FirstTime[pixel_pos].insert(
                            event_FirstTime[pixel_pos].begin() + i, time);
                        return;
                    }
                    break;
                }
            }

            const uint64_t thr = 1e6;
            uint64_t low_bound;
            if (thr > time) low_bound = 0;
            else low_bound = time - thr;

            // last + thr < time <=> last < time - thr = low_bound
            if (event_LastTime[pixel_pos][last_hit] < low_bound)
            {
                if (last_hit == size - 1)
                {
                    //std::cout << "new time_window" << std::endl;
                    event_Time19[pixel_pos].push_back(t19);
                    event_Energy[pixel_pos].push_back(energy);
                    event_Origin[pixel_pos].push_back(GetOrigin(id));
                    event_LastTime[pixel_pos].push_back(time);
                    event_FirstTime[pixel_pos].push_back(time);
                    return;
                }
                else
                {
                    //std::cout << "time window insert" << std::endl;
                    last_hit += 1;
                    event_Energy[pixel_pos].insert(
                        event_Energy[pixel_pos].begin() + last_hit, energy);
                    event_Origin[pixel_pos].insert(
                        event_Origin[pixel_pos].begin() + last_hit, GetOrigin(id));
                    event_Time19[pixel_pos].insert(
                        event_Time19[pixel_pos].begin() + last_hit, t19);
                    event_LastTime[pixel_pos].insert(
                        event_LastTime[pixel_pos].begin() + last_hit, time);
                    event_FirstTime[pixel_pos].insert(
                        event_FirstTime[pixel_pos].begin() + last_hit, time);
                    return;
                }
            }
            else
            {
                const uint64_t up_bound = time + thr;
                for (i = first_hit; i <= last_hit; ++i)
                {
                    if ((event_FirstTime[pixel_pos][i] <= up_bound) and
                        (event_LastTime[pixel_pos][i] >= low_bound))
                    {
                        if (event_FirstTime[pixel_pos][i] > time)
                        {
                            event_FirstTime[pixel_pos][i] = time;
                            event_Origin[pixel_pos][i] = GetOrigin(id);
                        }
                        else if (event_LastTime[pixel_pos][i] < time)
                        {
                            event_LastTime[pixel_pos][i] = time;
                        }
                        event_Energy[pixel_pos][i] += energy;
                        return;
                    }
                    // first - thr > time <=> first > time + thr = up_bound
                    else if (event_FirstTime[pixel_pos][i] > up_bound)
                    {
                        //std::cout << "time between" << std::endl;
                        event_Energy[pixel_pos].insert(
                            event_Energy[pixel_pos].begin() + i, energy);
                        event_Origin[pixel_pos].insert(
                            event_Origin[pixel_pos].begin() + i, GetOrigin(id));
                        event_Time19[pixel_pos].insert(
                            event_Time19[pixel_pos].begin() + i, t19);
                        event_LastTime[pixel_pos].insert(
                            event_LastTime[pixel_pos].begin() + i, time);
                        event_FirstTime[pixel_pos].insert(
                            event_FirstTime[pixel_pos].begin() + i, time);
                        return;
                    }
                }
            }  // end of else of (event_LastTime[pixel_pos][last_hit] < low_bound)
        }  // end of else of (last19 < t19)
    }  // end of else of (pixel_pos < 0)
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


G4bool ECHo_EventAction::in_MMC(const G4String volume)
{
    const char num = volume[0];
    if (num == '0') return true;  // Absorber
    if (num == '1') return true;  // Silver
    if (num == '2') return true;  // Holmium
    return false;
}

//G4bool ECHo_EventAction::in_Veto(const G4String volume)
//{
//    const char num = volume[0];
//    if (num == 'p') return true;
//    return false;
//}

//G4bool ECHo_EventAction::in_SubP(const G4String volume)
//{
//    const char num = volume[0];
//    if (num == 'r') return true;
//    return false;
//}

//G4bool ECHo_EventAction::in_SubSubP(const G4String volume)
//{
//    const char num = volume[0];
//    if (num == 's') return true;
//    return false;
//}

//void ECHo_EventAction::AddSubP(const G4String volume, const uint64_t energy)
//{
//    event_Energy_SubP[get_pixel(volume)] += energy;
//}
//void ECHo_EventAction::AddSubSubP(const G4String volume, const uint64_t energy)
//{
//    event_Energy_SubSubP[get_number(volume)] += energy;
//}