/// \file Cresst_SteppingAction.hh
/// \brief Definition of the Cresst_SteppingAction class

#ifndef Cresst_SteppingAction_h
#define Cresst_SteppingAction_h 1

#include "../../EventAction/include/Cresst_EventAction.hh"
#include "../include/Cresst_Stepping_With_Prims.hh"
#include <G4UserSteppingAction.hh>
#include <G4Types.hh>
#include <memory>

class Cresst_SteppingAction : public G4UserSteppingAction
{
     public:
        Cresst_SteppingAction(Cresst_EventAction *eventAction)
            : G4UserSteppingAction()
        {
            fSteppingAction =
                new Cresst_Stepping_With_Prims(eventAction);
        }
        virtual ~Cresst_SteppingAction() {delete fSteppingAction;}

        virtual void UserSteppingAction(const G4Step* step)
            {fSteppingAction->UserSteppingAction(step);}

    private:
        G4UserSteppingAction* fSteppingAction;
};

#endif
