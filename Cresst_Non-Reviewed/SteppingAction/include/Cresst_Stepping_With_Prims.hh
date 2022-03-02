/// \file Cresst_SteppingAction.hh
/// \brief Definition of the Cresst_SteppingAction class

#ifndef Cresst_Stepping_With_Prims_h
#define Cresst_Stepping_With_Prims_h 1

#include "../../EventAction/include/Cresst_EventAction.hh"
#include <G4UserSteppingAction.hh>

class Cresst_Stepping_With_Prims : public G4UserSteppingAction
{
     public:
        Cresst_Stepping_With_Prims(Cresst_EventAction *eventAction)
            : G4UserSteppingAction(),
            fEventAction(eventAction){};
        virtual ~Cresst_Stepping_With_Prims() {};

        virtual void UserSteppingAction(const G4Step*);

    private:
        Cresst_EventAction *fEventAction;
};

#endif
