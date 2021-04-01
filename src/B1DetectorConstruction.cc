//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include <G4SubtractionSolid.hh>
#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"
#include "G4NistManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 15.0*m, env_sizeZ = 15.22*m;      // unit change
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");  // changing to AIR
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.5*env_sizeXY;
  G4double world_sizeZ  = 1.5*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        env_sizeXY, env_sizeXY, env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 

  // Shape 2
  //
  // /*edit start

   // define a material from elements and/or others materials (mixture of mixtures)

    G4double a, z, density;
    G4String name, symbol;
    G4int ncomponents;
    G4double  fractionmass;
    a = 10.81*g/mole;
    G4Element* elB = new G4Element(name="Boron",symbol="B" , z= 5., a);    //adding Boron
    a = 55.85*g/mole;
    G4Element* elFe = new G4Element(name="Fe",symbol="Fe" , z= 26., a);          //adding Fe


    G4NistManager* manager = G4NistManager::Instance();
    manager->SetVerbose(1);
    G4Material* mat = manager->FindOrBuildMaterial("G4_WATER");
density = 2.4*g/cm3;
G4Material* shape2_mat = new G4Material(name="Composite", density, ncomponents=3);
shape2_mat->AddMaterial(mat, fractionmass=70.0*perCent);
shape2_mat->AddElement(elB,  fractionmass=15.0*perCent);
shape2_mat->AddElement(elFe,  fractionmass=15.0*perCent);


  // edit end */
 // G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_CONCRETE");//G4_CONCRETE  G4_WATER
  G4ThreeVector pos2 = G4ThreeVector(0, 0, 0*m);


  G4double shape2_dxa = 10.0*m;
  G4double shape2_dya = 10.0*m;
  G4double shape2_dz  = 10.0*m;
  G4Box *outerBox = new G4Box("Outer Box",shape2_dxa,shape2_dya,shape2_dz);
G4Box *innerBox = new G4Box("Inner Box",(shape2_dxa-2.44*m),(shape2_dya-2.44*m),(shape2_dz-2.44*m));
G4SubtractionSolid *solidShape2 = new G4SubtractionSolid("Hollow Box",outerBox,innerBox);




  /// Box shape       
/*  G4double shape2_dxa = 6.4*m;// shape2_dxb = 12*cm;
  G4double shape2_dya = 6.4*m; //shape2_dyb = 16*cm;
  G4double shape2_dz  = 2.44*m;
  G4Box* solidShape2 =    
    new G4Box("Concret",                 //its name
              shape2_dxa,
              shape2_dya,
              shape2_dz); //its size
                */
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Concret");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Concret",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2; 

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
