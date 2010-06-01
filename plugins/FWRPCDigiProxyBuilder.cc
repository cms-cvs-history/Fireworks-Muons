// -*- C++ -*-
//
// Package:     Muon
// Class  :     FWRPCDigiProxyBuilder
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: mccauley
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: FWRPCDigiProxyBuilder.cc,v 1.1.2.2 2010/05/28 14:09:00 mccauley Exp $
//

#include "TEveStraightLineSet.h"
#include "TEveCompound.h"
#include "TEveGeoNode.h"

#include "Fireworks/Core/interface/FWProxyBuilderBase.h"
#include "Fireworks/Core/interface/FWEventItem.h"
#include "Fireworks/Core/interface/DetIdToMatrix.h"
#include "Fireworks/Core/interface/fwLog.h"

// This is not included in stand-alone tarball cms/DataFormats
//#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

class FWRPCDigiProxyBuilder : public FWProxyBuilderBase
{
public:
  FWRPCDigiProxyBuilder() {}
  virtual ~FWRPCDigiProxyBuilder() {}

  REGISTER_PROXYBUILDER_METHODS();

private:
  virtual void build(const FWEventItem* iItem, TEveElementList* product, const FWViewContext*);
  FWRPCDigiProxyBuilder(const FWRPCDigiProxyBuilder&);    
  const FWRPCDigiProxyBuilder& operator=(const FWRPCDigiProxyBuilder&);
};

void
FWRPCDigiProxyBuilder::build(const FWEventItem* iItem, TEveElementList* product, const FWViewContext*)
{
  /*
  const RPCDigiCollection* digis = 0;
 
  iItem->get(digis);

  if ( ! digis ) 
  {
    fwLog(fwlog::kWarning)<<"Failed to get RPCDigis"<<std::endl;
    return;
  }
  */
}

//REGISTER_FWPROXYBUILDER(FWRPCDigiProxyBuilder, RPCDigiCollection, "RPCDigi", FWViewType::kISpyBit);

