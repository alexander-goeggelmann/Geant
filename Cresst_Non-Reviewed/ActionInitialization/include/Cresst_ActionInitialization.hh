/// \file Cresst_ActionInitialization.hh
/// \brief Definition of the Cresst_ActionInitialization class

#ifndef Cresst_ActionInitialization_h
#define Cresst_ActionInitialization_h 1

#include <G4VUserActionInitialization.hh>
// #include <G4UImessenger.hh>
#include "../../DetectorConstruction/include/Cresst_DetectorConstruction.hh"
#include "../../output.hh"
#include <time.h>
#include <memory>

static const G4String c_Bulk = "Bulk";
static const G4String c_Surface = "Surface";


class Cresst_ActionInitialization : public G4VUserActionInitialization
{
    public:
        Cresst_ActionInitialization(
            Cresst_DetectorConstruction*, G4int, G4int, G4String, G4int);
        virtual ~Cresst_ActionInitialization() {};

        virtual void BuildForMaster() const;
        virtual void Build() const;

        std::vector<std::string> GetProcesses() const {return fProcess;}
        G4String GetEventPath() const {return event_path;}
        G4String GetPrimPath() const {return prims_path;}
        G4String GetDatePath() const {return date_path;}
        G4String GetPosPath() const {return pos_path;}
        time_t GetTimer() const {return now;}

        void SetSeedX(G4int seed) {seedX = seed;}
        void SetSeedY(G4int seed) {seedY = seed;}
        void SetNuclide(G4String);


        int8_t parse_process(G4String process) const
        {
            if (process == "primary") return -1;
            for (uint i = 0; i < fProcess.size(); ++i)
            {
                if (fProcess[i] == ((std::string) process)) return (int8_t) i;
            }
            return -1;
        }

        void AddMessage(const G4String m) {message += m;}


    private:
        G4int GetAFromString(G4String);
        G4String GetElement(G4String);
        G4int GetZFromString(G4String);

        Cresst_DetectorConstruction *fDetector;

        //const G4String root_path = "../Simulations/";
        const G4String root_path = "/media/alexander/ECHoData/CresstSimulations/";
        G4String date_path;
        G4String event_path;
        G4String prims_path;
        G4String pos_path;

        time_t now;
        G4String message;

        G4int nucA;
        G4int nucZ;
        G4String nuclide;
        G4int seedX;
        G4int seedY;

        G4int d;

        const std::vector<G4String> e_names{
            "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg",
            "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr",
            "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br",
            "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd",
            "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La",
            "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er",
            "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au",
            "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
            "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md",
            "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn",
            "Nh", "Fl", "Mc", "Lv", "Ts", "Og"};

        const std::vector<std::string> e0_names{
            "H", "B", "C", "N", "O", "F", "P",
            "S", "K", "V", "Y", "I", "W", "U"};

        const std::vector<G4String> e1_names{
            "He", "Li", "Be", "Ne", "Na", "Mg", "Al", "Si", "Cl", "Ar", "Ca",
            "Sc", "Ti", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge",
            "As", "Se", "Br", "Kr", "Rb", "Sr", "Zr", "Nb", "Mo", "Tc", "Ru",
            "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "Xe", "Cs", "Ba",
            "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho",
            "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "Re", "Os", "Ir", "Pt", "Au",
            "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
            "Pa", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No",
            "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh",
            "Fl", "Mc", "Lv", "Ts", "Og"};

        const std::vector<std::string> fProcess =
            {"compt", "eIoni", "eBrem", "muIoni", "hIoni", "ionIoni",
             "Transportation", "photonNuclear", "electronNuclear",
             "positronNuclear", "muonNuclear", "GammaToMuPair",
             "AnnihiToMuPair", "ee2hadr", "SynRad", "RadioactiveDecay",
             "Decay", "phot", "conv", "Rayl", "msc", "ePairProd",
             "CoulombScat", "annihil", "muBrems", "muPairProd", "hBrems",
             "hPairProd", "nuclearStopping", "hadElastic", "neutronInelastic",
             "nCapture", "nFission", "protonInelastic", "pi+Inelastic",
             "pi-Inelastic", "kaon+Inelastic", "kaon-Inelastic",
             "kaon0LInelastic", "kaon0SInelastic", "lambdaInelastic",
             "anti-lambdaInelastic", "sigma-Inelastic", "anti_sigma-Inelastic",
             "sigma+Inelastic", "anti_sigma+Inelastic", "xi-Inelastic",
             "anti_xi-Inelastic", "xi0Inelastic", "anti_xi0Inelastic",
             "omega-Inelastic", "anti_omega-Inelastic", "anti_protonInelastic",
             "anti_neutronInelastic", "anti_deuteronInelastic",
             "anti_tritonInelastic", "anti_He3Inelastic",
             "anti_alphaInelastic", "hFritiofCaptureAtRest",
             "hBertiniCaptureAtRest", "muMinusCaptureAtRest", "ionElastic",
             "dInelastic", "tInelastic", "He3Inelastic", "alphaInelastic",
             "ionInelastic"};
};

#endif
