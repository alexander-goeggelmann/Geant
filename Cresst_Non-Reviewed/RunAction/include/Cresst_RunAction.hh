/// \file Cresst_RunAction.hh
/// \brief Definition of the Cresst_RunAction class

#ifndef Cresst_RunAction_h
#define Cresst_RunAction_h 1
#include "../../PrimaryGenerator/include/Cresst_PrimaryGeneratorAction.hh"
#include "../../ActionInitialization/include/Cresst_ActionInitialization.hh"

#include <G4UserRunAction.hh>
#include <G4Types.hh>

class G4Run;

class Cresst_RunAction : public G4UserRunAction
{
    public:
        Cresst_RunAction(const Cresst_ActionInitialization* init) : G4UserRunAction(),
            fInit(init)
        {
            ClearEventVector();
            ClearStepVector();
            ClearPosVector();
        }
        virtual ~Cresst_RunAction() {};

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);

        G4int GetNumOfEvents() {return num_of_events;}
        int8_t parse_process(G4String process)
            {return fInit->parse_process(process);}



        void SetStepVector(
            uint32_t event_number,
            uint64_t energy,
            uint16_t volume,
            int32_t pdg,
            uint32_t particle_id,
            int32_t parent_pdg,
            uint32_t parent_id,
            int8_t process,
            uint64_t depE,
            bool stop)
        {
            step_event_number.push_back((uint32_t) event_number);
            step_energy.push_back((uint64_t) energy);
            step_vol_number.push_back((uint16_t) volume);
            step_pdg.push_back((int32_t) pdg);
            step_particle_id.push_back((uint32_t) particle_id);
            step_parent_pdg.push_back((int32_t) parent_pdg);
            step_parent_id.push_back((uint32_t) parent_id);
            step_process.push_back((int8_t) process);
            step_depE.push_back((uint64_t) depE);
            step_stoped.push_back((uint8_t) stop);
        }


        void ClearStepVector()
        {
            step_event_number.clear();
            step_pdg.clear();
            step_particle_id.clear();
            step_parent_id.clear();
            step_parent_pdg.clear();
            step_energy.clear();
            step_vol_number.clear();
            step_process.clear();
            step_depE.clear();
            step_stoped.clear();
        }


        void SetEventVector(
            uint32_t event_number,
            uint64_t energy,
            uint8_t volume,
            uint64_t time,
            uint64_t t19,
            int32_t origin)
        {
            event_event_number.push_back((uint32_t) event_number);
            event_energy.push_back((uint64_t) energy);
            event_volume.push_back((uint8_t) volume);
            event_time.push_back((uint64_t) time);
            event_time19.push_back((uint64_t) t19);
            event_origin.push_back((int32_t) origin);
        }


        void ClearEventVector()
        {
            event_event_number.clear();
            event_energy.clear();
            event_time.clear();
            event_time19.clear();
            event_origin.clear();
            event_volume.clear();
        }


        void SetPosVector(int64_t x, int64_t y, int64_t z)
        {
            xpos.push_back(x);
            ypos.push_back(y);
            zpos.push_back(z);
        }

        void ClearPosVector()
        {
            xpos.clear();
            ypos.clear();
            zpos.clear();
        }


        G4int GetStepLength() {return step_event_number.size();}
        G4int GetEventLength() {return event_event_number.size();}
        G4int GetPosLength() {return xpos.size();}

        void SaveEvent();
        void SavePrims();
        void SavePos();
        time_t GetTimer() const {return fInit->GetTimer();}

    private:
        const Cresst_ActionInitialization* fInit;
        G4int num_of_events;

        std::vector<uint32_t> event_event_number;
        std::vector<uint64_t> event_energy;
        std::vector<uint64_t> event_time;
        std::vector<uint64_t> event_time19;
        std::vector<int32_t> event_origin;
        std::vector<uint8_t> event_volume;

        std::vector<uint32_t> step_event_number;
        std::vector<int32_t> step_pdg;
        std::vector<uint32_t> step_particle_id;
        std::vector<uint32_t> step_parent_id;
        std::vector<int32_t> step_parent_pdg;
        std::vector<uint64_t> step_energy;
        std::vector<uint16_t> step_vol_number;
        std::vector<int8_t> step_process;
        std::vector<uint64_t> step_depE;
        std::vector<uint8_t> step_stoped;


        std::vector<int64_t> xpos;
        std::vector<int64_t> ypos;
        std::vector<int64_t> zpos;
};

#endif

