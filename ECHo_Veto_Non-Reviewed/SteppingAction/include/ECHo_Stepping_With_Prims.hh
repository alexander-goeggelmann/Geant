/// \file ECH_SteppingAction.hh
/// \brief Definition of the ECH_SteppingAction class

#ifndef ECHo_Stepping_With_Prims_h
#define ECHo_Stepping_With_Prims_h 1

#include "../../EventAction/include/ECHo_EventAction.hh"
#include <G4UserSteppingAction.hh>

class ECHo_Stepping_With_Prims : public G4UserSteppingAction
{
     public:
        ECHo_Stepping_With_Prims(ECHo_EventAction *eventAction)
            : G4UserSteppingAction(),
            fEventAction(eventAction){};
        virtual ~ECHo_Stepping_With_Prims() {};

        virtual void UserSteppingAction(const G4Step*);

    private:
        ECHo_EventAction *fEventAction;
};

#endif
