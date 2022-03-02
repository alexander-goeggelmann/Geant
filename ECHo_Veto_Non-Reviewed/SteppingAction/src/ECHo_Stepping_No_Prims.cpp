#include "../include/ECHo_Stepping_No_Prims.hh"
#include "../../EventAction/include/ECHo_EventAction.hh"

#include <G4Step.hh>
#include <G4Types.hh>

#include <boost/multiprecision/cpp_int.hpp>


void ECHo_Stepping_No_Prims::UserSteppingAction(const G4Step* step)
{
    if (step->GetTrack()->GetTrackID() == 1)
    {
        if (step->IsFirstStepInVolume())
        {
            const G4String volume = step->GetTrack()->GetVolume()->GetName();
            if (volume[0] == 'p') fEventAction->AddPanel(volume);
        }
    }
}
