// -*- C++ -*-
//
// Package:     Muon
// Class  :     FWCSCRPCDigiProxyBuilder
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: mccauley
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: FWCSCRPCDigiProxyBuilder.cc,v 1.1.2.6 2010/06/07 15:50:15 mccauley Exp $
//

#include "TEveStraightLineSet.h"
#include "TEveCompound.h"
#include "TEveGeoNode.h"

#include "Fireworks/Core/interface/FWProxyBuilderBase.h"
#include "Fireworks/Core/interface/FWEventItem.h"
#include "Fireworks/Core/interface/DetIdToMatrix.h"
#include "Fireworks/Core/interface/fwLog.h"

#include "DataFormats/CSCDigi/interface/CSCRPCDigiCollection.h"

class FWCSCRPCDigiProxyBuilder : public FWProxyBuilderBase
{
public:
  FWCSCRPCDigiProxyBuilder() {}
  virtual ~FWCSCRPCDigiProxyBuilder() {}

  REGISTER_PROXYBUILDER_METHODS();

private:
  virtual void build(const FWEventItem* iItem, TEveElementList* product, const FWViewContext*);
  FWCSCRPCDigiProxyBuilder(const FWCSCRPCDigiProxyBuilder&);    
  const FWCSCRPCDigiProxyBuilder& operator=(const FWCSCRPCDigiProxyBuilder&);
};

void
FWCSCRPCDigiProxyBuilder::build(const FWEventItem* iItem, TEveElementList* product, const FWViewContext*)
{
  const CSCRPCDigiCollection* digis = 0;
 
  iItem->get(digis);

  if ( ! digis ) 
  {
    fwLog(fwlog::kWarning)<<"Failed to get CSCRPCDigis"<<std::endl;
    return;
  }

  else 
    std::cout<<"Got CSCRPC digis!"<<std::endl;

  int i = 0;

  for ( CSCRPCDigiCollection::DigiRangeIterator dri = digis->begin(), driEnd = digis->end();
        dri != driEnd; ++dri )
  {
    std::cout<<"CSCRPC DigiRange: "<< ++i <<std::endl;

    const CSCDetId& cscDetId = (*dri).first;

    const TGeoHMatrix* matrix = iItem->getGeom()->getMatrix(cscDetId);
  
    if ( ! matrix ) 
    {
      std::cout << "ERROR: failed get geometry of CSC volume with detid: "
                << cscDetId << std::endl;
      return;
    }     

    const CSCRPCDigiCollection::Range& range = (*dri).second;

    std::cout<< cscDetId <<std::endl;

    int j = 0;

    for ( CSCRPCDigiCollection::const_iterator dit = range.first;
          dit != range.second; ++dit )
    {
      std::cout<<"CSCRPCDigi: "<< ++j <<std::endl;

      TEveCompound* compound = new TEveCompound("cscrpc digi compound", "cscrpcDigis");
      compound->OpenCompound();
      product->AddElement(compound);

      

    }

  }
  
}

REGISTER_FWPROXYBUILDER(FWCSCRPCDigiProxyBuilder, CSCRPCDigiCollection, "CSCRPCDigi", FWViewType::kISpyBit);

