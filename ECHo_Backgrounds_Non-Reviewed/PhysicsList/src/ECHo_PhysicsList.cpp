#include "../include/ECHo_PhysicsList.hh"
#include "../../DetectorConstruction/include/ECHo_DetectorConst.hh"
#include "../../output.hh"

#include <G4Region.hh>
#include <G4RegionStore.hh>
#include <G4ProductionCuts.hh>

#include <G4Types.hh>
#include <G4EmLivermorePolarizedPhysics.hh>

#include <G4DecayPhysics.hh>

#include <G4LossTableManager.hh>

#include <G4SystemOfUnits.hh>

#include <G4NuclideTable.hh>
#include <G4DeexPrecoParameters.hh>
#include <G4NuclearLevelData.hh>
#include <G4RadioactiveDecay.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4UAtomicDeexcitation.hh>
#include <G4GenericIon.hh>

#include <G4HadronElasticPhysicsHP.hh>
#include <G4HadronPhysicsFTFP_BERT_HP.hh>
#include <G4IonElasticPhysics.hh>
#include <G4IonPhysics.hh>
#include <G4StoppingPhysics.hh>

#include <G4EmExtraPhysics.hh>

#include <G4LeptonConstructor.hh>
#include <G4MesonConstructor.hh>
#include <G4BosonConstructor.hh>
#include <G4BaryonConstructor.hh>
#include <G4IonConstructor.hh>
#include <G4ShortLivedConstructor.hh>

#include <G4ParticleHPManager.hh>
#include <G4Threading.hh>


void ECHo_PhysicsList::ConstructProcess()
{
    if (G4Threading::G4GetThreadId() > 0)
    {
        std::cout << blue_color;
        std::cout << "Generate Physics List for Thread ID " <<
                     G4Threading::G4GetThreadId() << std::endl;
    }
    else
    {
        std::cout << blue_color;
        std::cout << "Initialize Physics List" << std::endl;
    }
    AddTransportation();

    const G4int verbose = 0;
    decayList = new G4DecayPhysics(verbose);
    emList = new G4EmLivermorePolarizedPhysics(verbose);
    raddecayList = new G4RadioactiveDecayPhysics(verbose);
    hadeList = new G4HadronElasticPhysicsHP(verbose);
    hadList = new G4HadronPhysicsFTFP_BERT_HP(verbose);
    stopList = new G4StoppingPhysics(verbose);
    ioneList = new G4IonElasticPhysics(verbose);
    ionList = new G4IonPhysics(verbose);

    RadioActivePhysics = new G4RadioactiveDecay();
    ExtraPhysics = new G4EmExtraPhysics(verbose);
    AtomPhysics = new G4UAtomicDeexcitation();

    //////////////////////////////////////////////////////////////////
    //SetVerboseLevel(verbose);
    G4ParticleHPManager::GetInstance()->SetProduceFissionFragments(true);

    G4NuclideTable* nucdat = G4NuclideTable::GetInstance();
    G4DeexPrecoParameters* deex =
        G4NuclearLevelData::GetInstance()->GetParameters();
    G4EmParameters* param = G4EmParameters::Instance();


    G4PhysicsListHelper *pHelper = G4PhysicsListHelper::GetPhysicsListHelper();

    G4LossTableManager *man = G4LossTableManager::Instance();

    ExtraPhysics->ElectroNuclear(true);
    ExtraPhysics->MuonNuclear(true);
    ExtraPhysics->Synch(true);
    ExtraPhysics->SynchAll(true);
    ExtraPhysics->GammaNuclear(true);
    ExtraPhysics->LENDGammaNuclear(false);
    ExtraPhysics->GammaToMuMu(true);
    ExtraPhysics->PositronToHadrons(true);
    ExtraPhysics->PositronToMuMu(true);

    nucdat->SetThresholdOfHalfLife(1. * CLHEP::picosecond);
    nucdat->SetLevelTolerance(10.0 * CLHEP::eV);

    RadioActivePhysics->SetICM(true);
    RadioActivePhysics->SetARM(true);
    RadioActivePhysics->SetHLThreshold(1. * CLHEP::picosecond);
    pHelper->RegisterProcess(RadioActivePhysics, G4GenericIon::GenericIon());

    deex->SetCorrelatedGamma(true);
    deex->SetStoreAllLevels(true);
    deex->SetStoreICLevelData(true);
    deex->SetInternalConversionFlag(true);
    deex->SetMaxLifeTime(
        G4NuclideTable::GetInstance()->GetThresholdOfHalfLife() /std::log(2.));

    AtomPhysics->SetPIXE(true);
    AtomPhysics->SetAuger(true);
    AtomPhysics->SetFluo(true);
    AtomPhysics->SetAugerCascade(true);
    AtomPhysics->SetCutForAugerElectrons(1. * CLHEP::eV);
    AtomPhysics->SetCutForSecondaryPhotons(1. * CLHEP::eV);
    AtomPhysics->InitialiseAtomicDeexcitation();
    man->SetAtomDeexcitation(AtomPhysics);


    param->SetFluo(true);
    param->SetPixe(true);
    param->SetAuger(true);
    param->SetAugerCascade(true);
    param->SetBeardenFluoDir(true);
    param->SetDeexcitationIgnoreCut(true);
    param->SetMinEnergy(10. * CLHEP::eV);
    param->SetLowestElectronEnergy(1. * CLHEP::eV);

    ExtraPhysics->ConstructProcess();
    decayList->ConstructProcess();
    emList->ConstructProcess();
    raddecayList->ConstructProcess();
    hadeList->ConstructProcess();
    hadList->ConstructProcess();
    stopList->ConstructProcess();
    ioneList->ConstructProcess();
    ionList->ConstructProcess();
    //fStepPhysics->ConstructProcess();

    //////////////////////////////////////////////////////////////////
    if (G4Threading::G4GetThreadId() > 0)
    {
        std::cout << blue_color;
        std::cout << "Generate Physics List -- Completed." << std::endl;
    }
    else
    {
        std::cout << blue_color;
        std::cout << "Initialization Completed." << std::endl;
    }
}


// Generate the particles
void ECHo_PhysicsList::ConstructParticle()
{

    // Generate bosons
    G4BosonConstructor pBosonConstructor;
    pBosonConstructor.ConstructParticle();
    // Generate leptons
    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();
    // Generate mesons
    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();
    // Generate baryons
    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();
    // Generate ions
    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();
    // Generate short lived states (atomic and nuclear excitations)
    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();
}

void ECHo_PhysicsList::SetCuts()
{
    //SetCutsWithDefault();

    ECHo_DetectorConst& detector_const = get_DetectorConst();
    detector_const.setVectors();

    //fStepPhysics->ConstructProcess();

    G4Region *reg;
    MMC_Cut = new G4ProductionCuts();
    MMC_Cut->SetProductionCut(min_range_MMC);
    Wafer_Cut = new G4ProductionCuts();
    Wafer_Cut->SetProductionCut(min_range_1K);
    Bath_Cut = new G4ProductionCuts();
    Bath_Cut->SetProductionCut(min_range_Bath);
    Shielding_Cut = new G4ProductionCuts();
    Shielding_Cut->SetProductionCut(min_range_Shielding);
    S500_Cut = new G4ProductionCuts();
    S500_Cut->SetProductionCut(min_range_S500);
    S50_Cut = new G4ProductionCuts();
    S50_Cut->SetProductionCut(min_range_S50);
    S5_Cut = new G4ProductionCuts();
    S5_Cut->SetProductionCut(min_range_S5);
    InnerS_Cut = new G4ProductionCuts();
    InnerS_Cut->SetProductionCut(min_range_InnerS);
    PCB_Cut = new G4ProductionCuts();
    PCB_Cut->SetProductionCut(min_range_PCB);
    Plug_Cut = new G4ProductionCuts();
    Plug_Cut->SetProductionCut(min_range_Plug);
    Veto_Cut = new G4ProductionCuts();
    Veto_Cut->SetProductionCut(min_range_Panel);
    //G4UserLimits *limits;

    for (int i = 0; i < 4; i++)
    {
        reg = G4RegionStore::GetInstance()->GetRegion("Front_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
        reg = G4RegionStore::GetInstance()->GetRegion("Back_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
        reg = G4RegionStore::GetInstance()->GetRegion("Left_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
        reg = G4RegionStore::GetInstance()->GetRegion("Right_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
        reg = G4RegionStore::GetInstance()->GetRegion("Top_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
        reg = G4RegionStore::GetInstance()->GetRegion("Bottom_" + std::to_string(i));
        reg->SetProductionCuts(Veto_Cut);
    }
    reg = G4RegionStore::GetInstance()->GetRegion(name_Shielding);
    reg->SetProductionCuts(Shielding_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_S500);
    reg->SetProductionCuts(S500_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_S50);
    reg->SetProductionCuts(S50_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_S5);
    reg->SetProductionCuts(S5_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_InnerS);
    reg->SetProductionCuts(InnerS_Cut);

    reg = G4RegionStore::GetInstance()->GetRegion(name_CopperA);
    reg->SetProductionCuts(Shielding_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_Copper500);
    reg->SetProductionCuts(S500_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_Copper50);
    reg->SetProductionCuts(S50_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_Copper5);
    reg->SetProductionCuts(S5_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_CopperB);
    reg->SetProductionCuts(Shielding_Cut);

    reg = G4RegionStore::GetInstance()->GetRegion(name_CB0);
    reg->SetProductionCuts(PCB_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_CB1);
    reg->SetProductionCuts(PCB_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_CB2);
    reg->SetProductionCuts(PCB_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_CB3);
    reg->SetProductionCuts(PCB_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_CB4);
    reg->SetProductionCuts(Plug_Cut);

    reg = G4RegionStore::GetInstance()->GetRegion(name_1K);
    reg->SetProductionCuts(Wafer_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion(name_sWafer);
    reg->SetProductionCuts(S5_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion("STL");
    reg->SetProductionCuts(Wafer_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion("STR");
    reg->SetProductionCuts(Wafer_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion("SBL");
    reg->SetProductionCuts(Wafer_Cut);
    reg = G4RegionStore::GetInstance()->GetRegion("SBR");
    reg->SetProductionCuts(Wafer_Cut);

    reg = G4RegionStore::GetInstance()->GetRegion(name_Bath);
    reg->SetProductionCuts(Bath_Cut);
    for (int i = 0; i < 18; i++)
    {
        reg = G4RegionStore::GetInstance()->GetRegion(detector_const.vector_names_Bath[i]);
        reg->SetProductionCuts(Bath_Cut);
    }

    for (int i = 0; i < 9; i++)
    {
        reg = G4RegionStore::GetInstance()->GetRegion(detector_const.vector_names_Plug[i]);
        reg->SetProductionCuts(Plug_Cut);
    }

    for (int i = 0; i < number_of_pixels; i++)
    {
        reg = G4RegionStore::GetInstance()->GetRegion(detector_const.vector_names_MMC[i]);
        reg->SetProductionCuts(Plug_Cut);
    }

    std::cout << blue_color;
    std::cout << "Regions are definied." << std::endl;
    //fStepPhysics->ConstructProcess();

}

