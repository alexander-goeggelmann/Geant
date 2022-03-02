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

        void AddPanel(const G4String);

        static uint8_t get_pixel(const G4String);
        static G4int parse_volume(G4String);
        int8_t parse_process(G4String process)
        {return fRunAction->parse_process(process);}

        G4String GetMessage() {return message;}
        void AddMessage(G4String mes) {message = mes;}

        void ClearEventVector()
        {
            front0 = false;
            front1 = false;
            front2 = false;
            front3 = false;

            back0 = false;
            back1 = false;
            back2 = false;
            back3 = false;

            left0 = false;
            left1 = false;
            left2 = false;
            left3 = false;

            right0 = false;
            right1 = false;
            right2 = false;
            right3 = false;

            top0 = false;
            top1 = false;
            top2 = false;
            top3 = false;

            bottom0 = false;
            bottom1 = false;
            bottom2 = false;
            bottom3 = false;
        }

    private:
        ECHo_RunAction *fRunAction;
        G4int num_of_events;
        G4int number;
        G4String message = "";
        const G4int number_output = 50;

        bool front0;
        bool front1;
        bool front2;
        bool front3;
        bool back0;
        bool back1;
        bool back2;
        bool back3;
        bool left0;
        bool left1;
        bool left2;
        bool left3;
        bool right0;
        bool right1;
        bool right2;
        bool right3;
        bool top0;
        bool top1;
        bool top2;
        bool top3;
        bool bottom0;
        bool bottom1;
        bool bottom2;
        bool bottom3;
};

#endif


