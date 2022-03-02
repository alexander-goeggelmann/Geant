/// \file Screening_SteppingAction.hh
/// \brief Definition of the Screening_SteppingAction class

#ifndef Screening_SteppingAction_h
#define Screening_SteppingAction_h 1

#include "../../EventAction/include/Screening_EventAction.hh"
#include "../include/Screening_Stepping_With_Prims.hh"
#include <G4UserSteppingAction.hh>
#include <G4Types.hh>
#include <memory>

class Screening_SteppingAction : public G4UserSteppingAction
{
     public:
        Screening_SteppingAction(Screening_EventAction *eventAction)
            : G4UserSteppingAction()
        {
            fSteppingAction =
                new Screening_Stepping_With_Prims(eventAction);
        }
        virtual ~Screening_SteppingAction() {delete fSteppingAction;}

        virtual void UserSteppingAction(const G4Step* step)
            {fSteppingAction->UserSteppingAction(step);}

    private:
        G4UserSteppingAction* fSteppingAction;
};

#endif
