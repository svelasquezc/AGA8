#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <thread>

#include "GERG2008.h"

// The compositions in the x() array use the following order and must be sent as mole fractions:
//     0 - UNUSED The array is comprised of 22 elements empty at 0
//     1 - Methane
//     2 - Nitrogen
//     3 - Carbon dioxide
//     4 - Ethane
//     5 - Propane
//     6 - Isobutane
//     7 - n-Butane
//     8 - Isopentane
//     9 - n-Pentane
//    10 - n-Hexane
//    11 - n-Heptane
//    12 - n-Octane
//    13 - n-Nonane
//    14 - n-Decane
//    15 - Hydrogen
//    16 - Oxygen
//    17 - Carbon monoxide
//    18 - Water
//    19 - Hydrogen sulfide
//    20 - Helium
//    21 - Argon


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
    std::vector<double> composition_50CH4_50H2 = {0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_95CH4_5H2 = {0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.05, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_50N2_50H2 = {0, 0, 0.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0};
    std::vector<double> composition_90CO2_10H2 = {0, 0, 0, 0.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0, 0};
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