// -*- C++ -*-
//
// Package:     Muon
// Class  :     FWCSCStripDigis3DProxyBuilder
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: mccauley
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: FWCSCStripDigis3DProxyBuilder.cc,v 1.1.2.2 2010/03/02 15:08:37 mccauley Exp $
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
#include "Fireworks/Core/src/changeElementAndChildren.h"

#include "DataFormats/CSCDigi/interface/CSCStripDigiCollection.h"

class FWCSCStripDigis3DProxyBuilder : public FW3DDataProxyBuilder
{
public:
  FWCSCStripDigis3DProxyBuilder();
  virtual ~FWCSCStripDigis3DProxyBuilder();
  REGISTER_PROXYBUILDER_METHODS();

private:
  virtual void build(const FWEventItem* iItem, TEveElementList** product);
  FWCSCStripDigis3DProxyBuilder(const FWCSCStripDigis3DProxyBuilder&);
  const FWCSCStripDigis3DProxyBuilder& operator=(const FWCSCStripDigis3DProxyBuilder&);
};

FWCSCStripDigis3DProxyBuilder::FWCSCStripDigis3DProxyBuilder(){}
FWCSCStripDigis3DProxyBuilder::~FWCSCStripDigis3DProxyBuilder(){}

void
FWCSCStripDigis3DProxyBuilder::build(const FWEventItem* iItem, TEveElementList** product)
{
  TEveElementList* tList = *product;

  if ( 0 == tList ) 
  {
    tList =  new TEveElementList(iItem->name().c_str(),"cscStripDigis",true);
    *product = tList;
    tList->SetMainColor(iItem->defaultDisplayProperties().color());
    gEve->AddElement(tList);
   } 

  else 
  {
    tList->DestroyElements();
  }

  const CSCStripDigiCollection* digis = 0;
  iItem->get(digis);

  if ( 0 == digis ) 
  {
    return;
  }

  double width  = 0.01;
  double depth  = 0.01;
  double rotate = 0.0;
  int thresholdOffset = 9;

  unsigned int index = 0;       

  // Test iteration over digis
  for ( CSCStripDigiCollection::DigiRangeIterator dri = digis->begin(), driEnd = digis->end();
        dri != driEnd; ++dri, ++index )
  {    
    const CSCDetId& cscDetId = (*dri).first;
    const CSCStripDigiCollection::Range& range = (*dri).second;

    const TGeoHMatrix* matrix = iItem->getGeom()->getMatrix(cscDetId.rawId());
    
    /*
    if ( ! matrix )
    {
      std::cout<<"ERROR: Failed to get geometry of CSC chamber with detid: "
               << cscDetId.rawId() <<std::endl;
      continue;
    }
    */

    std::stringstream s;        
    s<< "strip "<<index;
     
    for(CSCStripDigiCollection::const_iterator dit = range.first;
        dit != range.second; ++dit)
    {
      CSCDetId id = cscDetId;
      std::vector<int> adcCounts = (*dit).getADCCounts();
      
      TEveCompound* compound = new TEveCompound("csc strip digi compound", "cscStripDigis");
      compound->OpenCompound();
      tList->AddElement(compound);

      int signalThreshold = (adcCounts[0] + adcCounts[1])/2 + thresholdOffset;  
            
      if ( std::find_if(adcCounts.begin(),adcCounts.end(),bind2nd(std::greater<int>(),signalThreshold)) != adcCounts.end() ) 
      {
        TEveStraightLineSet* stripDigiSet = new TEveStraightLineSet(s.str().c_str());
        stripDigiSet->SetLineWidth(3);
        stripDigiSet->SetMainColor(iItem->defaultDisplayProperties().color());
        stripDigiSet->SetRnrSelf(iItem->defaultDisplayProperties().isVisible());
        stripDigiSet->SetRnrChildren(iItem->defaultDisplayProperties().isVisible());
        compound->AddElement(stripDigiSet);

        int stripId = (*dit).getStrip();  
        int endcap  = id.endcap();
        int station = id.station();
        int ring    = id.ring();
        int chamber = id.chamber();

        /*
        std::cout<<"stripId, endcap, station, ring. chamber: "
                 << stripId <<" "<< endcap <<" "<< station <<" "
                 << ring <<" "<< chamber <<std::endl;
        */

        /*
          We need the x position of the strip to create 
          a local position: (xStrip(stripId), 0.0, 0.1)
          and then a conversion to global coordinates.
          We also need the length of the strip.
          
          The strip digi is rotated about the z axis by an angle:
        
          double angle = -atan2(pos.x(),pos.y()) - rotate;
      
          and a "box" is drawn with the width, length, and depth given above
        */
      } 
    }       
  }   
}

REGISTER_FW3DDATAPROXYBUILDER(FWCSCStripDigis3DProxyBuilder, CSCStripDigiCollection,"CSC-stripDigis");

