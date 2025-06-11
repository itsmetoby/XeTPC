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
  ViewMedium view(&gas);

  TCanvas cV("cV", "", 600, 600);
  view.SetCanvas(&cV);
  view.PlotElectronVelocity('e'); 
  app.Run(true);

  //TCanvas cD("cD", "", 600, 600);
  //view.SetCanvas(&cD);
  //view.PlotElectronDiffusion();
  //app.Run(true);
//
  //TCanvas cT("cT", "", 600, 600);
  //view.SetCanvas(&cT);
  //view.PlotElectronTownsend();
  //app.Run(true);
//
  //TCanvas cA("cA", "", 600, 600);
  //view.SetCanvas(&cA);
  //view.PlotElectronAttachment();
  //app.Run(true);
//
  //TCanvas cI("cI", "", 600, 600);
  //view.SetCanvas(&cI);
  //view.PlotIonVelocity();
  //app.Run(true);
}

