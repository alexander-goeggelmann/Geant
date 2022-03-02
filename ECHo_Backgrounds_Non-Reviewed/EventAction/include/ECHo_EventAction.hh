/// \file ECHo_EventAction.hh
/// \brief Definition of the ECHo_EventAction class

#ifndef ECHo_EventAction_h
#define ECHo_EventAction_h 1

#include "../../RunAction/include/ECHo_RunAction.hh"
#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include <G4Types.hh>

class ECHo_EventAction : public G4UserEventAction
{
    public:
        ECHo_EventAction(ECHo_RunAction *runAction) : G4UserEventAction(),
            fRunAction(runAction) {};
        virtual ~ECHo_EventAction() {};

        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);

        void CreateParticle_Verbose(
            const G4double, const G4int, const G4int, const G4int,
            const G4int, const int8_t, const G4bool);
        void CreateParticle(const G4int, const G4int, const G4int);

        //void AddPos(const G4double x, const G4double y, const G4double z)
        //{
        //    xpos.push_back((int64_t) x);
        //    ypos.push_back((int64_t) y);
        //    zpos.push_back((int64_t) z);
        //}

        int32_t GetOrigin(const uint32_t);
        void SaveAncestors(uint32_t);
        void AddEnergy(
            const uint32_t, const uint64_t, const G4int, const G4bool, const G4bool);
        bool is_known(const uint32_t particle)
        {
            if (particle > step_save.size()) return true;
            else return step_save[particle - 1];
        };

        void AddEvent(
            const uint8_t, const uint64_t, const uint64_t,
            const uint64_t, const uint32_t);

        int pixel_exists(uint8_t pixel)
        {
            for (uint i = 0; i < event_Pixels.size(); i++)
            {
                if (event_Pixels[i] == pixel) return (int) i;
            };
            return -1;
        };

        G4bool in_MMC(const G4String);
        //G4bool in_Veto(const G4String);
        //G4bool in_SubP(const G4String);
        //G4bool in_SubSubP(const G4String);
        static uint8_t get_pixel(const G4String);

        static G4int parse_volume(G4String);
        
        int8_t parse_process(G4String process)
        {return fRunAction->parse_process(process);};

        //void AddSubP(const G4String, const uint64_t);
        //void AddSubSubP(const G4String, const uint64_t);

        G4String GetMessage() {return message;};
        void AddMessage(G4String mes) {message = mes;};
        //void SetVeto(const G4String name)
        //{
        //    if (p_name == "") p_name = name;
        //    else if (p_name != name) event_Veto = true;
        //}
        //bool GetVeto() {return event_Veto;}

        void ClearEventVector()
        {
            event_Energy.clear();
            event_LastTime.clear();
            event_FirstTime.clear();
            event_Origin.clear();
            event_Time19.clear();
            event_Pixels.clear();
            //event_Veto = false;
            p_name = "";
            //event_Energy_SubP.clear();
            //event_Energy_SubSubP.clear();
            //for (uint i = 0; i < 46; ++i) event_Energy_SubP.push_back(0);
            //for (uint i = 0; i < 91; ++i) event_Energy_SubSubP.push_back(0);
        };


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
        };


        //void ClearPosVector()
        //{
        //    xpos.clear();
        //    ypos.clear();
        //    zpos.clear();
        //}

    private:
        ECHo_RunAction *fRunAction;
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

        const std::vector<uint8_t> event_SubP = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                                 10, 11, 12, 13, 14, 15, 16,
                                                 17, 18, 19, 20, 21, 22, 23,
                                                 24, 25, 26, 27, 28, 29, 30,
                                                 31, 32, 33, 34, 35, 36, 37,
                                                 38, 39, 40, 41, 42, 43, 44,
                                                 45, 46, 47};
        const std::vector<uint8_t> event_SubSubP = {0, 1, 2, 3, 4, 5, 6, 7, 8,
                                              9, 10, 11, 12, 13, 14, 15, 16, 17,
                                              18, 19, 20, 21, 22, 23, 24, 25,
                                              26, 27, 28, 29, 30, 31, 32, 33,
                                              34, 35, 36, 37, 38, 39, 40, 41,
                                              42, 43, 44, 45, 46, 47, 48, 49,
                                              50, 51, 52, 53, 54, 55, 56, 57,
                                              58, 59, 60, 61, 62, 63, 64, 65,
                                              66, 67, 68, 69, 70, 71, 72, 73,
                                              74, 75, 76, 77, 78, 79};
        //std::vector<uint64_t> event_Energy_SubP;
        //std::vector<uint64_t> event_Energy_SubSubP;

        //bool event_Veto;
        G4String p_name;

        std::vector<int32_t> step_parent_pdg;
        std::vector<uint64_t> step_energy;
        std::vector<uint16_t> step_vol_number;
        std::vector<int8_t> step_process;

        std::vector<uint64_t> step_depE;
        std::vector<bool> step_save;
        std::vector<bool> step_stop;

        //std::vector<int64_t> xpos;
        //std::vector<int64_t> ypos;
        //std::vector<int64_t> zpos;
};

#endif


