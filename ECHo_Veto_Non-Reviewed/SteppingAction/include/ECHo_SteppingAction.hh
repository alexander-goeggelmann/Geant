/// \file ECH_SteppingAction.hh
/// \brief Definition of the ECH_SteppingAction class

#ifndef ECHo_SteppingAction_h
#define ECHo_SteppingAction_h 1

#include "../../EventAction/include/ECHo_EventAction.hh"
#include "../include/ECHo_Stepping_With_Prims.hh"
#include "../include/ECHo_Stepping_No_Prims.hh"
#include <G4UserSteppingAction.hh>
#include <G4Types.hh>
#include <memory>

class ECHo_SteppingAction : public G4UserSteppingAction
{
     public:
        ECHo_SteppingAction(ECHo_EventAction *eventAction, G4bool b)
            : G4UserSteppingAction()
        {
            if (b) fSteppingAction =
                new ECHo_Stepping_With_Prims(eventAction);
            else fSteppingAction =
                new ECHo_Stepping_No_Prims(eventAction);
        }
        virtual ~ECHo_SteppingAction() {delete fSteppingAction;}

        virtual void UserSteppingAction(const G4Step* step)
            {fSteppingAction->UserSteppingAction(step);}

    private:
        G4UserSteppingAction* fSteppingAction;
};

#endif
