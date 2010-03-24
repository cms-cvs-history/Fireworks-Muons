// -*- C++ -*-
//
// Package:     Core
// Class  :     FWItemCSCSegmentAccessor
//
// Implementation:
//     An example of how to write a plugin based FWItemAccessorBase derived class.
//
// Original Author:  Giulio Eulisse
//         Created:  Thu Feb 18 15:19:44 EDT 2008
// $Id: FWItemMuonAccessors.cc,v 1.1 2010/03/01 09:46:33 eulisse Exp $
//

// system include files
#include <assert.h>
#include "Reflex/Object.h"
#include "TClass.h"

// user include files
#include "DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "Fireworks/Core/interface/FWItemRandomAccessor.h"

REGISTER_TEMPLATE_FWITEMACCESSOR(FWItemRandomAccessor<CSCRecHit2DCollection>,CSCRecHit2DCollection,"CSCRecHit2DCollectionAccessor");
REGISTER_TEMPLATE_FWITEMACCESSOR(FWItemRandomAccessor<CSCSegmentCollection>,CSCSegmentCollection,"CSCSegmentCollectionAccessor");
REGISTER_TEMPLATE_FWITEMACCESSOR(FWItemRandomAccessor<DTRecSegment2DCollection>,DTRecSegment2DCollection,"DTSegment2DCollectionAccessor");
REGISTER_TEMPLATE_FWITEMACCESSOR(FWItemRandomAccessor<DTRecSegment4DCollection>,DTRecSegment4DCollection,"DTSegment4DCollectionAccessor");