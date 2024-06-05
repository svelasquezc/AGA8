#include <sstream>
#include <iostream>

#include "GERG2008.h"

int main(){
    SetupGERG();
    double _x[] = {0.77824, 0.02, 0.06, 0.08, 0.03, 0.0015, 0.003, 0.0005,
        0.00165, 0.00215, 0.00088, 0.00024, 0.00015, 0.00009, 0.004, 0.005,
        0.002, 0.0001, 0.0025, 0.007, 0.001};
    const int NcGERG = 21;
    std::vector<double> x(_x, _x+NcGERG), xGrs(4,0);
    x.insert(x.begin(), 0.0);
    double mm = 0;
    MolarMassGERG(x, mm);

    int ierr = 0;
    std::string herr;
    double T = 400, P = 50000, D = 6.36570, Z = 0;
    double dPdD, d2PdD2, d2PdTD, dPdT, U, H, S, Cv, Cp, W, G, JT, Kappa, A;
    DensityGERG(0, T, P, x, D, ierr, herr);
    PropertiesGERG(T, D, x, P, Z, dPdD, d2PdD2, d2PdTD, dPdT, U, H, S,
        Cv, Cp, W, G, JT, Kappa, A);
}