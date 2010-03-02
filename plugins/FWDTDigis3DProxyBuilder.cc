// -*- C++ -*-
//
// Package:     Muon
// Class  :     FWDTDigis3DProxyBuilder
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: mccauley
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: FWDTDigis3DProxyBuilder.cc,v 1.1.2.1 2010/03/02 13:12:41 mccauley Exp $
//

#include "TEveManager.h"
#include "TGeoTube.h"
#include "TEveGeoNode.h"
#include "TEveElement.h"
#include "TEveCompound.h"
#include "TEvePointSet.h"

#include "Fireworks/Core/interface/FW3DDataProxyBuilder.h"
#include "Fireworks/Core/interface/FWEventItem.h"
#include "Fireworks/Core/interface/BuilderUtils.h"
#include "Fireworks/Core/interface/FW3DView.h"
#include "Fireworks/Core/interface/FWEveScalableStraightLineSet.h"
#include "Fireworks/Core/interface/FWEveValueScaler.h"
#include "Fireworks/Core/interface/DetIdToMatrix.h"

#include "DataFormats/DTDigi/interface/DTDigiCollection.h"

class FWDTDigis3DProxyBuilder : public FW3DDataProxyBuilder
{
public:
  FWDTDigis3DProxyBuilder();
  virtual ~FWDTDigis3DProxyBuilder();
  REGISTER_PROXYBUILDER_METHODS();

private:
  virtual void build(const FWEventItem* iItem,
                     TEveElementList** product);

  FWDTDigis3DProxyBuilder(const FWDTDigis3DProxyBuilder&);
  const FWDTDigis3DProxyBuilder& operator=(const FWDTDigis3DProxyBuilder&);
};

FWDTDigis3DProxyBuilder::FWDTDigis3DProxyBuilder(){}
FWDTDigis3DProxyBuilder::~FWDTDigis3DProxyBuilder(){}

void
FWDTDigis3DProxyBuilder::build(const FWEventItem* iItem, TEveElementList** product)
{
  TEveElementList* tList = *product;

  if ( 0 == tList ) 
  {
    tList =  new TEveElementList(iItem->name().c_str(),"dtDigis",true);
    *product = tList;
    tList->SetMainColor(iItem->defaultDisplayProperties().color());
    gEve->AddElement(tList);
   } 

  else 
  {
    tList->DestroyElements();
  }

  const DTDigiCollection* digis = 0;
  iItem->get(digis);

  if ( 0 == digis ) 
  {
    return;
  }

  unsigned int index = 0;

  // Test iteration over digis
  for( DTDigiCollection::DigiRangeIterator dri = digis->begin(), driEnd = digis->end(); dri != driEnd; ++dri, ++index )
  {  
    const DTLayerId& dtLayerId = (*dri).first;
    const DTDigiCollection::Range& range = (*dri).second;

    std::cout<<"DTLayerId: "<< dtLayerId <<std::endl;
   
    std::stringstream s;
    s << "dt "<< index;

    for ( DTDigiCollection::const_iterator dit = range.first;
          dit != range.second; ++dit )        
    { 
      TEveCompound* compound = new TEveCompound("dt digi compound", "dtDigis");
      compound->OpenCompound();
      tList->AddElement(compound);

      TEveStraightLineSet* digiSet = new TEveStraightLineSet(s.str().c_str());
      digiSet->SetLineWidth(3);
      digiSet->SetMainColor(iItem->defaultDisplayProperties().color());
      digiSet->SetRnrSelf(iItem->defaultDisplayProperties().isVisible());
      digiSet->SetRnrChildren(iItem->defaultDisplayProperties().isVisible());
      compound->AddElement(digiSet);
    
      int wireNumber = (*dit).wire();
      int countsTDC = (*dit).countsTDC();

      std::cout<<"DT wire number, countsTDC: "
               << wireNumber <<" "<< countsTDC <<std::endl;

      // These are probably best left for the table view
      int layerId = dtLayerId.layer();
      int superLayerId = dtLayerId.superlayerId().superLayer();
      int sectorId = dtLayerId.superlayerId().chamberId().sector();
      int stationId = dtLayerId.superlayerId().chamberId().station();
      int wheelId = dtLayerId.superlayerId().chamberId().wheel();

      /*
        We need the x position of the wire in the DT frame to create a point 
        (xPos, 0.0, 0.0) that nust be transformed to global coordinates.
        We also need the length, width, and height of the DT from the DTLayer.
        Then, rotate the tube about the proper axis by the correct angle.
      */

    } // end of iteration over digis in range
  } // end of iteration over digi range
  
}

REGISTER_FW3DDATAPROXYBUILDER(FWDTDigis3DProxyBuilder, DTDigiCollection,"DT-Digis");


