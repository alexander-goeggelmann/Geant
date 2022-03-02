/// \file Screening_EventAction.hh
/// \brief Definition of the Screening_EventAction class

#ifndef Screening_EventAction_h
#define Screening_EventAction_h 1

#include "../../RunAction/include/Screening_RunAction.hh"
#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include <G4Types.hh>

class Screening_EventAction : public G4UserEventAction
{
    public:
        Screening_EventAction(Screening_RunAction *runAction) : G4UserEventAction(),
            fRunAction(runAction) {};
        virtual ~Screening_EventAction() {};

        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);

        static G4int parse_volume(G4String);
        int8_t parse_process(G4String process)
        {return fRunAction->parse_process(process);}

        G4String GetMessage() {return message;}
        void AddMessage(G4String mes) {message = mes;}

        void CreateParticle_Verbose(
            const G4double, const G4int, const G4int, const G4int,
            const G4int, const int8_t, const G4bool);
        void CreateParticle(const G4int, const G4int, const G4int);

        int32_t GetOrigin(const uint32_t);
        void SaveAncestors(uint32_t);
        void AddEnergy(
            const uint32_t, const uint64_t, const G4int, const G4bool, const G4bool);
        bool is_known(const uint32_t particle)
        {
            if (particle > step_save.size()) return true;
            else return step_save[particle - 1];
        }

        void AddEvent(
            const uint8_t, const uint64_t, const uint64_t,
            const uint64_t, const uint32_t);

        int pixel_exists(uint8_t pixel)
        {
            for (uint i = 0; i < event_Pixels.size(); i++)
            {
                if (event_Pixels[i] == pixel) return (int) i;
            }
            return -1;
        }

        G4bool in_Detector(const G4String name) {return name[0] == '0';}

        void ClearEventVector()
        {
            event_Energy.clear();
            event_LastTime.clear();
            event_FirstTime.clear();
            event_Origin.clear();
            event_Time19.clear();
            p_name = "";
            event_Pixels.clear();
        }


        void ClearStepVector()
        {
            event_pdg.clear();
            event_particle_id.clear();
            event_parent_id.clear();

            step_parent_pdg.clear();
            step_energy.clear();
            step_vol_number.clear();
            step_process.clear();

            step_depE.clear();
            step_save.clear();
            step_stop.clear();
        }

    private:
        Screening_RunAction *fRunAction;
        G4int num_of_events;
        G4int number;
        G4String message = "";
        const G4int number_output = 50;

        std::vector<uint8_t> event_Pixels;

        std::vector<std::vector<uint64_t>> event_Energy;
        std::vector<std::vector<uint64_t>> event_LastTime;
        std::vector<std::vector<uint64_t>> event_FirstTime;
        std::vector<std::vector<uint64_t>> event_Time19;
        std::vector<std::vector<int32_t>> event_Origin;

        std::vector<int32_t> event_pdg;
        std::vector<uint32_t> event_particle_id;
        std::vector<uint32_t> event_parent_id;

        G4String p_name;

        std::vector<int32_t> step_parent_pdg;
        std::vector<uint64_t> step_energy;
        std::vector<uint16_t> step_vol_number;
        std::vector<int8_t> step_process;

        std::vector<uint64_t> step_depE;
        std::vector<bool> step_save;
        std::vector<bool> step_stop;
};

#endif


