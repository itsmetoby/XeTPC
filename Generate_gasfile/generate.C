#include "Garfield/FundamentalConstants.hh"
#include "Garfield/MediumMagboltz.hh"
#include <iostream>

using namespace Garfield;

int main(int argc, char* argv[]) {
  const double pressure = 1 * AtmosphericPressure;
  const double temperature = 293.15;
  std::cout << "the pressure is ====" << pressure << std::endl;
  // Setup the gas.
  MediumMagboltz gas("Xe", 100);
  gas.SetTemperature(temperature);
  gas.SetPressure(pressure);

  // Set the field range to be covered by the gas table.
  const size_t nE = 10;
  const double emin = 0.;
  const double emax = 300.;
  // Flag to request logarithmic spacing.
  constexpr bool useLog = false;
  gas.SetFieldGrid(emin, emax, nE, useLog);

  const int ncoll = 40;
  // Run Magboltz to generate the gas table.
  gas.GenerateGasTable(ncoll);
  // Save the table.
  gas.WriteGasFile("xe_500v.gas");
}
