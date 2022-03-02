#include "../include/ECHo_Stepping_No_Prims.hh"
#include "../../EventAction/include/ECHo_EventAction.hh"

#include <G4Step.hh>
#include <G4Types.hh>

#include <boost/multiprecision/cpp_int.hpp>


void ECHo_Stepping_No_Prims::UserSteppingAction(const G4Step* step)
{
    if (step->GetTrack()->GetCurrentStepNumber() == 1)
    {
        fEventAction->CreateParticle(
            step->GetTrack()->GetDefinition()->GetPDGEncoding(),
            step->GetTrack()->GetTrackID(),
            step->GetTrack()->GetParentID());

        /*
        if (step->GetTrack()->GetTrackID() == 1)
        {
            fEventAction->AddPos(
                step->GetPreStepPoint()->GetPosition().getX() / CLHEP::um,
                step->GetPreStepPoint()->GetPosition().getY() / CLHEP::um,
                step->GetPreStepPoint()->GetPosition().getZ() / CLHEP::um);
        }
        */
    }

    const G4String volume = step->GetTrack()->GetVolume()->GetName();
    //std::cout << step->GetTrack()->GetDefinition()->GetParticleName() << std::endl;
    if (fEventAction->in_MMC(volume))
    {
        // Energy in meV, basis is MeV
        const uint64_t energy =
            (uint64_t) (step->GetTotalEnergyDeposit() * 1e9);

        if (energy != 0)
        {
            // Time in ps, basis is ns
            const G4double time = step->GetTrack()->GetGlobalTime() * 1e3;
            uint64_t t;
            uint64_t t_19 = 0;

            if (time <= 1e19) t = (uint64_t) time;
            else
            {
                boost::multiprecision::uint128_t tmp =
                    (boost::multiprecision::uint128_t) time;

                const boost::multiprecision::uint128_t t19 =
                    (boost::multiprecision::uint128_t) 1e19;
                const G4double t19_d = 1e19;
                const uint64_t t0 = (uint64_t) 1;

                const boost::multiprecision::uint128_t mult_long =
                    (boost::multiprecision::uint128_t) (time / t19_d);
                const uint64_t mult_short = (uint64_t) mult_long;

                tmp -= mult_long * t19;
                t_19 += mult_short * t0;
                t = (uint64_t) tmp;
            }

            const uint8_t pixel = fEventAction->get_pixel(volume);
            const uint32_t id = step->GetTrack()->GetTrackID();
            fEventAction->AddEvent(pixel, t, t_19, energy, id);
            //std::cout << volume << std::endl;
        }
    }
}
