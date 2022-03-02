#ifndef ECHo_PhysicsList_h
#define ECHo_PhysicsList_h 1


#include <G4VModularPhysicsList.hh>
#include <G4VPhysicsConstructor.hh>
#include <G4RadioactiveDecay.hh>
#include <G4EmExtraPhysics.hh>
#include <G4UAtomicDeexcitation.hh>
#include <G4ProductionCuts.hh>
#include <memory>

/**
    \file ECHo_PhysicsList.hh
    Definition of the physics, which should be activated.
*/
class ECHo_PhysicsList: public G4VModularPhysicsList
{
    public:
        ECHo_PhysicsList() {};
        virtual ~ECHo_PhysicsList()
        {
            delete decayList;
            delete emList;
            delete raddecayList;
            delete hadeList;
            delete hadList;
            delete stopList;
            delete ioneList;
            delete ionList;

            delete RadioActivePhysics;
            delete ExtraPhysics;
            delete AtomPhysics;

            delete MMC_Cut;
            delete Wafer_Cut;
            delete Bath_Cut;
            delete Shielding_Cut;
            delete S500_Cut;
            delete S50_Cut;
            delete S5_Cut;
            delete InnerS_Cut;
            delete PCB_Cut;
            delete Plug_Cut;
            delete Veto_Cut;
        }
        virtual void ConstructParticle();
        virtual void ConstructProcess();
        virtual void SetCuts();

    private:

        G4VPhysicsConstructor* decayList;
        G4VPhysicsConstructor* emList;
        G4VPhysicsConstructor* raddecayList;
        G4VPhysicsConstructor* hadeList;
        G4VPhysicsConstructor* hadList;
        G4VPhysicsConstructor* stopList;
        G4VPhysicsConstructor* ioneList;
        G4VPhysicsConstructor* ionList;

        G4RadioactiveDecay* RadioActivePhysics;
        G4EmExtraPhysics* ExtraPhysics;
        G4UAtomicDeexcitation* AtomPhysics;

        G4ProductionCuts* MMC_Cut;
        G4ProductionCuts* Wafer_Cut;
        G4ProductionCuts* Bath_Cut;
        G4ProductionCuts* Shielding_Cut;
        G4ProductionCuts* S500_Cut;
        G4ProductionCuts* S50_Cut;
        G4ProductionCuts* S5_Cut;
        G4ProductionCuts* InnerS_Cut;
        G4ProductionCuts* PCB_Cut;
        G4ProductionCuts* Plug_Cut;
        G4ProductionCuts* Veto_Cut;


};

#endif
