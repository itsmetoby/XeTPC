#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <cmath>
#include <cstring>

#include <cstdlib>
#include <iostream>

#include "Garfield/AvalancheMC.hh"
#include "Garfield/AvalancheMicroscopic.hh"
#include "Garfield/ComponentAnsys123.hh"
#include "Garfield/MediumMagboltz.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"
#include "Garfield/ViewFEMesh.hh"
#include "Garfield/ViewField.hh"
#include "Garfield/ComponentElmer.hh"
#include "Garfield/ViewFEMesh.hh"



using namespace Garfield;

int main(int argc, char* argv[]) {
  TApplication app("app", &argc, argv);

  // Setup the gas.
  MediumMagboltz gas("xe",100);
  gas.SetTemperature(293.15);
  gas.SetPressure(760.);
  gas.Initialise(true);
  gas.LoadGasFile("/Users/tobychan/garfield/Gasfile_codes/xe_100_500Vcm.gas");

  // Import Elmer   
  ComponentElmer * elm = new ComponentElmer("/Users/tobychan/garfield/result_file_3/mesh.header",
    "/Users/tobychan/garfield/result_file_3/mesh.elements",
    "/Users/tobychan/garfield/result_file_3/mesh.nodes",
    "/Users/tobychan/garfield/result_file_3/dielectrics.dat",
    "/Users/tobychan/garfield/result_file_3/v2a_shield_500V.result",
    "cm"
  );
  elm->EnablePeriodicityX();
  elm->EnableMirrorPeriodicityY();
  elm->SetMedium(81,&gas);
  elm->SetWeightingField("/Users/tobychan/garfield/result_file_3/v2a_shield_weight.result", "readout");

  // Adding sensors so it knows where to calculate E field
  Sensor* sensor = new Sensor();
  sensor->AddComponent(elm);
  sensor->SetArea(-2, -2, -1, 2, 2, 1);

  
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  // Viewing E fields
  ViewField * vf = new ViewField();
  vf->SetSensor(sensor);
  vf->SetCanvas(c1);
  vf->SetArea(-2, -0.1, 2, 1);
  vf->SetNumberOfContours(20);
  vf->SetNumberOfSamples2d(50,50);
  vf->SetPlane(0,-1,0,0,0,0);
  // Viewing the TPC
  ViewFEMesh * vFE = new ViewFEMesh();
  vFE->SetCanvas(c1);
  vFE->SetComponent(elm);
  vFE->SetPlane(0,-0.1,0,0,0,0);
  vFE->SetFillMesh(true);
  vFE->SetColor(0,kBlue);
  vFE->SetColor(83,kMagenta); // shield
  vFE->SetColor(84,kGreen+3); // shield's pcb
  vFE->SetColor(85,kGreen+3);
  vFE->SetArea(-2, -2, -0.1, 2, 2, 1);
  
  vf->PlotContour("v");
  vFE->Plot(true);
  c1->Draw();
  c1->SaveAs("XeTPC_efield.pdf");
}
