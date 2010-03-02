// -*- C++ -*-
//
// Package:     Muon
// Class  :     FWCSCWireDigis3DProxyBuilder
//
// Implementation:
//     <Notes on implementation>
//
// Original Author: mccauley
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: FWCSCWireDigis3DProxyBuilder.cc,v 1.2 2010/02/26 10:28:40 mccauley Exp $
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

#include "DataFormats/CSCDigi/interface/CSCWireDigiCollection.h"

class FWCSCWireDigis3DProxyBuilder : public FW3DDataProxyBuilder
{
public:
  FWCSCWireDigis3DProxyBuilder();
  virtual ~FWCSCWireDigis3DProxyBuilder();
  REGISTER_PROXYBUILDER_METHODS();

private:
  virtual void build(const FWEventItem* iItem,
                     TEveElementList** product);

  FWCSCWireDigis3DProxyBuilder(const FWCSCWireDigis3DProxyBuilder&);
  const FWCSCWireDigis3DProxyBuilder& operator=(const FWCSCWireDigis3DProxyBuilder&);
};

FWCSCWireDigis3DProxyBuilder::FWCSCWireDigis3DProxyBuilder(){}
FWCSCWireDigis3DProxyBuilder::~FWCSCWireDigis3DProxyBuilder(){}

void
FWCSCWireDigis3DProxyBuilder::build(const FWEventItem* iItem, TEveElementList** product)
{
  TEveElementList* tList = *product;

  if ( 0 == tList ) 
  {
    tList =  new TEveElementList(iItem->name().c_str(),"cscWireDigis",true);
    *product = tList;
    tList->SetMainColor(iItem->defaultDisplayProperties().color());
    gEve->AddElement(tList);
   } 

  else 
  {
    tList->DestroyElements();
  }

  const CSCWireDigiCollection* digis = 0;
  iItem->get(digis);

  if ( 0 == digis ) 
  {
    return;
  }

  double width  = 0.02;
  double depth  = 0.01;
  double rotate = M_PI*0.5;

  unsigned int index = 0;

  // Test iteration over digis
  for( CSCWireDigiCollection::DigiRangeIterator dri = digis->begin(), driEnd = digis->end(); dri != driEnd; ++dri, ++index )
  {  
    const CSCDetId& cscDetId = (*dri).first;
    const CSCWireDigiCollection::Range& range = (*dri).second;
 
    const TGeoHMatrix* matrix = iItem->getGeom()->getMatrix(cscDetId.rawId());
    
    if ( ! matrix )
    {
      std::cout<<"ERROR: Failed to get geometry of CSC chamber with detid: "
               << cscDetId.rawId() <<std::endl;
      continue;
    }
    
    std::stringstream s;
    s << "wire "<< index;

    for ( CSCWireDigiCollection::const_iterator dit = range.first;
          dit != range.second; ++dit )        
    { 
      TEveCompound* compound = new TEveCompound("csc wire digi compound", "cscWireDigis");
      compound->OpenCompound();
      tList->AddElement(compound);

      TEveStraightLineSet* wireDigiSet = new TEveStraightLineSet(s.str().c_str());
      wireDigiSet->SetLineWidth(3);
      wireDigiSet->SetMainColor(iItem->defaultDisplayProperties().color());
      wireDigiSet->SetRnrSelf(iItem->defaultDisplayProperties().isVisible());
      wireDigiSet->SetRnrChildren(iItem->defaultDisplayProperties().isVisible());
      compound->AddElement(wireDigiSet);

      CSCDetId id = cscDetId;
      int wireGroup = (*dit).getWireGroup();
      int endcap  = id.endcap();
      int station = id.station();
      int ring    = id.ring();
      int chamber = id.chamber();

      std::cout<<"wireGroup, endcap, station, ring. chamber: "
               << wireGroup <<" "<< endcap <<" "<< station <<" "
               << ring <<" "<< chamber <<std::endl;

      /*
        We need the local center of the wire group
        and then a conversion to global coordinates.
        In addition, we also need the length of the wire group
        
        The wire digi is rotated about the z axis by an angle:
        
        double angle = -atan2(pos.x(),pos.y()) - rotate;
      
        and a "box" is drawn with the width, length, and depth given above
      */
    }
  }
}

REGISTER_FW3DDATAPROXYBUILDER(FWCSCWireDigis3DProxyBuilder, CSCWireDigiCollection,"CSC-wireDigis");


