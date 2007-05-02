
#ifndef MaterialEffects_h
#define MaterialEffects_h

/**
 * Steering class for the simulation of the Material Effects in each 
 * layer of the tracker material. For now, it has
 *
 *  - Photon conversion
 *  - Bremsstrahlung
 *  - Energy loss by ionization
 *  - Multiple scattering
 *
 * but no synchrotron radiation (well, this is not really a material 
 * effect, but might be dealt with here as well), no nuclear interactions, 
 * no delta-rays.
 *
 * The method interact() does all the above items in turn, and modifies 
 * the FSimEvent accordingly. For instance, a converting photon gets 
 * an end vertex here, and two new FSimTracks are created, one for the
 * electron and one for the positron, with the same parent vertex.
 *
 * \author: Stephan Wynhoff, Florian Beaudette, Patrick Janot
 * $Date: Last modification (after severe clean-up). 08-Jan-2004
 */

//Framework Headers
//#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Geometry Headers
#include "DataFormats/GeometryVector/interface/GlobalVector.h"

#include <iostream>

class FSimEvent;
class TrackerLayer;
class ParticlePropagator;
class PairProductionSimulator;
class MultipleScatteringSimulator;
class BremsstrahlungSimulator;
class EnergyLossSimulator;
class NuclearInteractionSimulator;
class RandomEngine;
class ParameterSet;

class MaterialEffects
{

 public:

  /// Constructor
  MaterialEffects(const edm::ParameterSet& matEff,
		  const RandomEngine* engine);

  /// Default destructor
  ~MaterialEffects();

  /// Steer the various interaction processes in the Tracker Material
  /// and update the FSimEvent
  void interact(FSimEvent& simEvent,
		const TrackerLayer& layer,
		ParticlePropagator& PP,
		unsigned i);

  /// The number of radiation lengths traversed
  double radLengths(const TrackerLayer& layer,
		    ParticlePropagator& myTrack ) const;

  /// The vector normal to the surface traversed
  GlobalVector normalVector(const TrackerLayer& layer,
			    ParticlePropagator& myTrack ) const;

  /// Save nuclear interaction information
  void save();

 private:

  PairProductionSimulator* PairProduction;
  BremsstrahlungSimulator* Bremsstrahlung;
  MultipleScatteringSimulator* MultipleScattering;
  EnergyLossSimulator* EnergyLoss;
  NuclearInteractionSimulator* NuclearInteraction;

  double pTmin;
  GlobalVector theNormalVector;

  // debugging
  double myEta;

  // The random engine
  const RandomEngine* random;

};

#endif
