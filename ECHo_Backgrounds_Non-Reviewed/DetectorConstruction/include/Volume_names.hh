
#ifndef Volume_Names_h
#define Volume_Names_h

#include "ECHo_DetectorConst.hh"

const std::string n_big_bath = "Big Bath";
const std::string n_small_bath = "Small Bath";
const std::string n_substrate = "Substrate";
const std::string n_small_substrate = "Substrate Layer";
const std::string n_source = "Test Source";
const std::string n_1k = "ECHo-1K Chip";

const std::string n_copper_a = "Copper Holder";
const std::string n_copper_500 = "Copper Holder 500 um";
const std::string n_copper_50 = "Copper Holder 50 um";
const std::string n_copper_5 = "Copper Holder 5 um";
const std::string n_copper_b = "Copper Holder T";

const std::string n_inners = "Inside Shielding";
const std::string n_shiedling = "Shielding";
const std::string n_shiedling_500 = "Shielding 500 um";
const std::string n_shielding_50 = "Shielding 50 um";
const std::string n_shielding_5 = "Shielding 5 um";

const std::string n_plug = "Plug";
const std::string n_cb = "PCB";
const std::string n_squid = "SQUID";
const std::string n_box = "Readout Channel";

const std::string n_muonpanel = "Muon Panel";
const std::string n_setup = "SetUp";


class VolumeNames
{
    public:
        void set_names()
        {
            bool vector_check = volume_names.size() == 0;
            if (vector_check)
            {
                const std::vector<std::string> prefix_letters = {
                    "A", "B", "C", "D", "E", "F", "G", "H",
                    "a", "b", "c", "d", "e", "f", "g", "h"};
                const std::vector<std::string> prefix_delimiter = {"", " ", "_"};
                const std::vector<std::string> prefix_layer = {"Layer", "layer"};

                const std::vector<std::string> n_silver = {
                    "Silver", "silver", "Ag", "ag"};
                for (uint i = 0; i < n_silver.size(); ++i)
                {
                    silver_names.push_back(n_silver[i]);
                }

                const std::vector<std::string> n_holmium = {
                    "Holmium", "holmium", "Ho", "ho"};
                for (uint i = 0; i < n_holmium.size(); ++i)
                {
                    holmium_names.push_back(n_holmium[i]);
                }

                for (uint pl = 0; pl < prefix_layer.size(); ++pl)
                {
                    for (uint pd = 0; pd < prefix_delimiter.size(); ++pd)
                    {
                        for (uint n = 0; n < n_silver.size(); ++n)
                        {
                            silver_names.push_back(
                                n_silver[n] + prefix_delimiter[pd] +
                                prefix_layer[pl]);
                        }

                        for (uint n = 0; n < n_holmium.size(); ++n)
                        {
                            holmium_names.push_back(
                                n_holmium[n] + prefix_delimiter[pd] +
                                prefix_layer[pl]);
                        }
                    }
                }

                std::string tmp_name;
                for (int num = 0; num < (number_of_pixels / 4); ++num)
                {
                    for (uint pl = 0; pl < prefix_letters.size(); ++pl)
                    {
                        if ((prefix_letters[pl] == "A") or
                            (prefix_letters[pl] == "a")) tmp_name = "_A";
                        else if ((prefix_letters[pl] == "B") or
                                (prefix_letters[pl] == "b")) tmp_name = "_B";
                        else if ((prefix_letters[pl] == "C") or
                                (prefix_letters[pl] == "c")) tmp_name = "_C";
                        else if ((prefix_letters[pl] == "D") or
                                (prefix_letters[pl] == "d")) tmp_name = "_D";
                        else if ((prefix_letters[pl] == "E") or
                                (prefix_letters[pl] == "e")) tmp_name = "_E";
                        else if ((prefix_letters[pl] == "F") or
                                (prefix_letters[pl] == "f")) tmp_name = "_F";
                        else if ((prefix_letters[pl] == "G") or
                                (prefix_letters[pl] == "g")) tmp_name = "_G";
                        else tmp_name = "_H";
                        tmp_name += std::to_string(num);

                        for (uint pd_0 = 0; pd_0 < prefix_delimiter.size(); ++pd_0)
                        {
                            for (uint pd_1 = 0; pd_1 < prefix_delimiter.size(); ++pd_1)
                            {
                                for (uint n = 0; n < absorber_names.size(); ++n)
                                {
                                    volume_names.push_back(
                                        absorber_names[n] +
                                        prefix_delimiter[pd_0] +
                                        prefix_letters[pl] +
                                        prefix_delimiter[pd_1] +
                                        std::to_string(num));
                                    volume_numbers.push_back(
                                        name_Absorber + tmp_name);
                                }
                                for (uint n = 0; n < silver_names.size(); ++n)
                                {
                                    volume_names.push_back(
                                        silver_names[n] +
                                        prefix_delimiter[pd_0] +
                                        prefix_letters[pl] +
                                        prefix_delimiter[pd_1] +
                                        std::to_string(num));
                                    volume_numbers.push_back(
                                        name_Silver + tmp_name);
                                }
                                for (uint n = 0; n < holmium_names.size(); ++n)
                                {
                                    volume_names.push_back(
                                        holmium_names[n] +
                                        prefix_delimiter[pd_0] +
                                        prefix_letters[pl] +
                                        prefix_delimiter[pd_1] +
                                        std::to_string(num));
                                    volume_numbers.push_back(
                                        name_Holmium + tmp_name);
                                }
                                for (uint n = 0; n < sensor_names.size(); ++n)
                                {
                                    volume_names.push_back(
                                        sensor_names[n] +
                                        prefix_delimiter[pd_0] +
                                        prefix_letters[pl] +
                                        prefix_delimiter[pd_1] +
                                        std::to_string(num));
                                    volume_numbers.push_back(
                                        name_Sensor + tmp_name);
                                }
                                for (uint n = 0; n < mmc_names.size(); ++n)
                                {
                                    volume_names.push_back(
                                        mmc_names[n] +
                                        prefix_delimiter[pd_0] +
                                        prefix_letters[pl] +
                                        prefix_delimiter[pd_1] +
                                        std::to_string(num));
                                    volume_numbers.push_back(
                                        name_MMC + tmp_name);
                                }
                            }
                        }
                    }
                }

                for (uint n = 0; n < big_bath_names.size(); ++n)
                {
                    volume_names.push_back(big_bath_names[n]);
                    volume_numbers.push_back(name_Bath);
                }

                for (uint n = 0; n < small_bath_names.size(); ++n)
                {
                    volume_names.push_back(small_bath_names[n]);
                    volume_numbers.push_back(name_sBath);
                }

                volume_names.push_back(n_big_bath);

                for (int i = 0; i < 18; ++i)
                {
                    volume_names.push_back(
                        n_small_bath + "_" + std::to_string(i));
                    volume_names.push_back(
                        n_small_bath + " " + std::to_string(i));
                }

                for (int i = 0; i < 9; ++i)
                {
                    volume_names.push_back(
                        n_plug + "_" + std::to_string(i));
                    volume_names.push_back(
                        n_small_bath + " " + std::to_string(i));
                }
            }
        }
        std::vector<std::string> volume_names;
        std::vector<std::string> volume_numbers;

        const std::vector<std::string> absorber_names = {
            "Absorber", "absorber", "Gold", "gold", "Au", "au"};
        std::vector<std::string> silver_names;
        std::vector<std::string> holmium_names;
        const std::vector<std::string> sensor_names = {
            "Sensor", "sensor", "Ag:Er", "AgEr"};
        const std::vector<std::string> mmc_names = {
            "MMC", "mmc", "Pixel", "pixel", "Calorimeter", "calorimeter"};

        const std::vector<std::string> big_bath_names;
        const std::vector<std::string> small_bath_names;
};

inline VolumeNames& get_volume_names()
{
    static VolumeNames vol_names;
    return vol_names;
}

#endif
