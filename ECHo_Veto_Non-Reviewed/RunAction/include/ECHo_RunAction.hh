/// \file ECHo_RunAction.hh
/// \brief Definition of the ECHo_RunAction class

#ifndef ECHo_RunAction_h
#define ECHo_RunAction_h 1
#include "../../PrimaryGenerator/include/ECHo_PrimaryGeneratorAction.hh"
#include "../../ActionInitialization/include/ECHo_ActionInitialization.hh"

#include <G4UserRunAction.hh>
#include <G4Types.hh>

class G4Run;

class ECHo_RunAction : public G4UserRunAction
{
    public:
        ECHo_RunAction(const ECHo_ActionInitialization* init) : G4UserRunAction(),
            fInit(init)
        {
            ClearEventVector();
        }
        virtual ~ECHo_RunAction() {};

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);

        G4int GetNumOfEvents() {return num_of_events;}
        int8_t parse_process(G4String process)
            {return fInit->parse_process(process);}



        void SetEventVector(
            uint32_t event_num,
            bool front_0, bool front_1, bool front_2, bool front_3,
            bool back_0, bool back_1, bool back_2, bool back_3,
            bool left_0, bool left_1, bool left_2, bool left_3,
            bool right_0, bool right_1, bool right_2, bool right_3,
            bool top_0, bool top_1, bool top_2, bool top_3,
            bool bottom_0, bool bottom_1, bool bottom_2, bool bottom_3)
        {
            event_number.push_back((uint32_t) event_num);
            front0.push_back((uint8_t) front_0);
            front1.push_back((uint8_t) front_1);
            front2.push_back((uint8_t) front_2);
            front3.push_back((uint8_t) front_3);
            back0.push_back((uint8_t) back_0);
            back1.push_back((uint8_t) back_1);
            back2.push_back((uint8_t) back_2);
            back3.push_back((uint8_t) back_3);
            left0.push_back((uint8_t) left_0);
            left1.push_back((uint8_t) left_1);
            left2.push_back((uint8_t) left_2);
            left3.push_back((uint8_t) left_3);
            right0.push_back((uint8_t) right_0);
            right1.push_back((uint8_t) right_1);
            right2.push_back((uint8_t) right_2);
            right3.push_back((uint8_t) right_3);
            top0.push_back((uint8_t) top_0);
            top1.push_back((uint8_t) top_1);
            top2.push_back((uint8_t) top_2);
            top3.push_back((uint8_t) top_3);
            bottom0.push_back((uint8_t) bottom_0);
            bottom1.push_back((uint8_t) bottom_1);
            bottom2.push_back((uint8_t) bottom_2);
            bottom3.push_back((uint8_t) bottom_3);
        }


        void ClearEventVector()
        {
            event_number.clear();
            front0.clear();
            front1.clear();
            front2.clear();
            front3.clear();
            back0.clear();
            back1.clear();
            back2.clear();
            back3.clear();
            left0.clear();
            left1.clear();
            left2.clear();
            left3.clear();
            right0.clear();
            right1.clear();
            right2.clear();
            right3.clear();
            top0.clear();
            top1.clear();
            top2.clear();
            top3.clear();
            bottom0.clear();
            bottom1.clear();
            bottom2.clear();
            bottom3.clear();

        }


        G4int GetEventLength() {return event_number.size();}

        void SaveEvent();
        time_t GetTimer() const {return fInit->GetTimer();}

    private:
        const ECHo_ActionInitialization* fInit;
        G4int num_of_events;

        std::vector<uint32_t> event_number;

        std::vector<uint8_t> front0;
        std::vector<uint8_t> front1;
        std::vector<uint8_t> front2;
        std::vector<uint8_t> front3;

        std::vector<uint8_t> back0;
        std::vector<uint8_t> back1;
        std::vector<uint8_t> back2;
        std::vector<uint8_t> back3;

        std::vector<uint8_t> left0;
        std::vector<uint8_t> left1;
        std::vector<uint8_t> left2;
        std::vector<uint8_t> left3;

        std::vector<uint8_t> right0;
        std::vector<uint8_t> right1;
        std::vector<uint8_t> right2;
        std::vector<uint8_t> right3;

        std::vector<uint8_t> top0;
        std::vector<uint8_t> top1;
        std::vector<uint8_t> top2;
        std::vector<uint8_t> top3;

        std::vector<uint8_t> bottom0;
        std::vector<uint8_t> bottom1;
        std::vector<uint8_t> bottom2;
        std::vector<uint8_t> bottom3;
};

#endif

