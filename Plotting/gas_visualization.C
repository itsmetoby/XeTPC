#include <TApplication.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <cstdlib>
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/ViewMedium.hh"
#include <iostream>

using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);
  // Setup the gas.
  MediumMagboltz gas;
  gas.LoadGasFile("xe_500v.gas");
  gas.PrintGas();
  std::cout << "Now read the gas medium"<< std::endl;
  ViewMedium view(&gas);
  std::cout << "End of reading the gas medium"<< std::endl;
  TCanvas cV("cV", "", 600, 600);
  view.SetCanvas(&cV);
  view.PlotElectronVelocity('e'); 
  cV.SaveAs("electron_velocity.png");

  TCanvas cD("cD", "", 600, 600);
  view.SetCanvas(&cD);
  view.PlotElectronDiffusion();
  cD.SaveAs("electron_diffusion.png");

  TCanvas cT("cT", "", 600, 600);
  view.SetCanvas(&cT);
  view.PlotElectronTownsend();
  cT.SaveAs("electron_townsend.png");

  TCanvas cA("cA", "", 600, 600);
  view.SetCanvas(&cA);
  view.PlotElectronAttachment();
  cA.SaveAs("electron_attachment.png");

  TCanvas cI("cI", "", 600, 600);
  view.SetCanvas(&cI);
  view.PlotIonVelocity();
  cI.SaveAs("ion_velocity.png");
  TCanvas cD2("cD2", "", 600, 600);
  view.SetCanvas(&cD2);
  view.PlotIonDiffusion();
  cD2.SaveAs("ion_diffusion.png");


  app.Run();
  return 0;
}

