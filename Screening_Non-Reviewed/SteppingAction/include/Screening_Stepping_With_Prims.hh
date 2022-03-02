/// \file Screening_SteppingAction.hh
/// \brief Definition of the Screening_SteppingAction class

#ifndef Screening_Stepping_With_Prims_h
#define Screening_Stepping_With_Prims_h 1

#include "../../EventAction/include/Screening_EventAction.hh"
#include <G4UserSteppingAction.hh>

class Screening_Stepping_With_Prims : public G4UserSteppingAction
{
     public:
        Screening_Stepping_With_Prims(Screening_EventAction *eventAction)
            : G4UserSteppingAction(),
            fEventAction(eventAction){};
        virtual ~Screening_Stepping_With_Prims() {};

        virtual void UserSteppingAction(const G4Step*);

    private:
        Screening_EventAction *fEventAction;
};

#endif
