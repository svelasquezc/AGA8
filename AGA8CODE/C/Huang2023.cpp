#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <thread>

#include "GERG2008.h"

// The compositions in the x() array use the following order and must be sent as mole fractions:
//     0 - Methane
//     1 - Nitrogen
//     2 - Carbon dioxide
//     3 - Ethane
//     4 - Propane
//     5 - Isobutane
//     6 - n-Butane
//     7 - Isopentane
//     8 - n-Pentane
//     9 - n-Hexane
//    10 - n-Heptane
//    11 - n-Octane
//    12 - n-Nonane
//    13 - n-Decane
//    14 - Hydrogen
//    15 - Oxygen
//    16 - Carbon monoxide
//    17 - Water
//    18 - Hydrogen sulfide
//    19 - Helium
//    20 - Argon


void densityCalculation(std::vector<double> composition, double temperature, const std::string& caseName){
    SetupGERG();
    double molarMass = 0 /* [g/mol] */;
    MolarMassGERG(composition, molarMass);

    std::stringstream iss;

    iss << "Density"<< "-" << caseName << "-" << "GERG"<< "-" << static_cast<int>(temperature) <<"K"<< ".csv";

    std::ofstream file(iss.str());

    file << "Pressure;Density"<<std::endl;


    int ierr = 0;
    std::string herr;

    double pressure = 101.325; /* [kPa] */
    double molarDensity = 0;

    while (pressure <= 20001){
        DensityGERG(0, temperature, pressure, composition, molarDensity, ierr, herr);
        if(ierr != 0) std::cerr << herr << std::endl;
        file << pressure/1000 /* [MPa] */ << ";" << molarDensity*molarMass /* [g/l] or [kg/m3] */ << std::endl;
        pressure+=1;
    }
    file.close();
}

int main(){
    std::vector<double> composition_50CH4_50H2 = {0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_95CH4_5H2 = {0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_50N2_50H2 = {0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_90CO2_10H2 = {0, 0, 0.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0, 0};
    const int NcGERG = 21; //Number of components (It is fixed)

    double temperature = 325, /* [K] */ pressure = 101.325 /* [kPa] */, molarDensity = 0 /* [mol/l] */, compressibilityFactor = 0 /*[-]*/;


    densityCalculation(composition_50CH4_50H2, 325, "50\%CH4+50\%H2");
    densityCalculation(composition_50CH4_50H2, 350, "50\%CH4+50\%H2");
    densityCalculation(composition_95CH4_5H2,  300, "95\%CH4+5\%H2");
    densityCalculation(composition_95CH4_5H2,  325, "95\%CH4+5\%H2");
    densityCalculation(composition_50N2_50H2,  325, "50\%N2+50\%H2");
    densityCalculation(composition_50N2_50H2,  350, "50\%N2+50\%H2");
    densityCalculation(composition_90CO2_10H2, 303, "90\%CO2+10\%H2");
    densityCalculation(composition_90CO2_10H2, 323, "90\%CO2+10\%H2");
}