#include "../include/ECHo_Stepping_With_Prims.hh"
#include "../../EventAction/include/ECHo_EventAction.hh"

#include <G4Step.hh>
#include <G4VProcess.hh>
#include <G4Types.hh>

#include <boost/multiprecision/cpp_int.hpp>

void ECHo_Stepping_With_Prims::UserSteppingAction(const G4Step *step)
{

    const G4String volume = step->GetTrack()->GetVolume()->GetName();
    const G4bool isStopped = step->GetTrack()->GetTrackStatus() != fAlive;
    //std::cout << volume << std::endl;
    //std::cout << "Start Step" << std::endl;
    //std::cout << "Particle " <<
    //        step->GetTrack()->GetDefinition()->GetParticleName();
    //std::cout << " in  " << volume << std::endl;


    if (step->GetTrack()->GetCurrentStepNumber() == 1)
    {
        //std::cout << "Start generation" << std::endl;
        G4String process_name = "primary";
        if (step->GetTrack()->GetCreatorProcess() != 0)
        {
            process_name =
                step->GetTrack()->GetCreatorProcess()->GetProcessName();
        }

        //else
        //{
        //    fEventAction->AddPos(
        //        step->GetPreStepPoint()->GetPosition().getX() / CLHEP::um,
        //        step->GetPreStepPoint()->GetPosition().getY() / CLHEP::um,
        //        step->GetPreStepPoint()->GetPosition().getZ() / CLHEP::um);
        //}

        // Energy in meV, basis is MeV
        //std::cout << volume << std::endl;
        //std::cout << step->GetTrack()->GetDefinition()->GetParticleName() << std::endl;
        fEventAction->CreateParticle_Verbose(
            step->GetPreStepPoint()->GetKineticEnergy() * 1e9,
            fEventAction->parse_volume(volume),
            step->GetTrack()->GetDefinition()->GetPDGEncoding(),
            step->GetTrack()->GetTrackID(),
            step->GetTrack()->GetParentID(),
            fEventAction->parse_process(process_name),
            isStopped);
        //std::cout << "Generated" << std::endl;
    }

    if (fEventAction->in_MMC(volume))
    {
        //std::cout << "in MMC" << std::endl;
        // Energy in meV, basis is MeV
        const uint64_t energy =
            (uint64_t) (step->GetTotalEnergyDeposit() * 1e9);

        if (energy != 0)
        {
            //std::cout << "nonzero energy" << std::endl;
            //std::cout << step->GetTrack()->GetDefinition()->GetParticleName() << std::endl;
            const uint32_t particleID =
                    (uint32_t) step->GetTrack()->GetTrackID();
            const uint8_t pixel = fEventAction->get_pixel(volume);
            const uint32_t id = step->GetTrack()->GetTrackID();

            if (not fEventAction->is_known(particleID))
                    fEventAction->SaveAncestors(particleID);
            //std::cout << "anything working" << std::endl;
            fEventAction->AddEnergy(
                particleID, energy, fEventAction->parse_volume(volume),
                isStopped, false);
            //std::cout << "still working" << std::endl;

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


            fEventAction->AddEvent(pixel, t, t_19, energy, id);
            //std::cout << "End" << std::endl;
        }
    } //else if (fEventAction->in_Veto(volume) and !fEventAction->GetVeto())
    //{
        //std::cout << "Veto" << std::endl;
    //    if (step->GetTotalEnergyDeposit() > 0) fEventAction->SetVeto(volume);
    //} //else if (fEventAction->in_SubSubP(volume))
    //{
    //    //std::cout << volume << std::endl;
    //    const uint64_t energy =
    //        (uint64_t) (step->GetTotalEnergyDeposit() * 1e9);

    //    if (energy > 0) fEventAction->AddSubP(volume, energy);
    //}


    //std::cout << "End step" << std::endl;
    //if (step->GetPostStepPoint()->GetTouchableHandle()->GetVolume())
    //{std::cout << step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << std::endl;
    //std::cout << step->GetPostStepPoint()->GetPhysicalVolume()->GetName() << std::endl;
    //}
}
