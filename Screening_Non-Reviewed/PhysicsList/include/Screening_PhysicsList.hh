#ifndef Screening_PhysicsList_h
#define Screening_PhysicsList_h 1


#include <G4VModularPhysicsList.hh>
#include <G4VPhysicsConstructor.hh>
#include <G4RadioactiveDecay.hh>
#include <G4EmExtraPhysics.hh>
#include <G4UAtomicDeexcitation.hh>
#include <G4ProductionCuts.hh>
#include <memory>

/**
    \file Screening_PhysicsList.hh
    Definition of the physics, which should be activated.
*/
class Screening_PhysicsList: public G4VModularPhysicsList
{
    public:
        Screening_PhysicsList() {};
        virtual ~Screening_PhysicsList()
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

            delete Box_Cut;
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

        G4ProductionCuts* Box_Cut;

};

#endif
