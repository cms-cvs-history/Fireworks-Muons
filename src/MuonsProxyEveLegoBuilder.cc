// -*- C++ -*-
//
// Package:     Calo
// Class  :     MuonsProxyEveLegoBuilder
// 
// Implementation:
//     <Notes on implementation>
//
// Original Author:  
//         Created:  Sun Jan  6 23:57:00 EST 2008
// $Id: MuonsProxyEveLegoBuilder.cc,v 1.4 2008/06/09 19:54:03 chrjones Exp $
//

// system include files
#include "TEveElement.h"
#include "TColor.h"
#include "TGeoTube.h"
#include "TEveGeoShapeExtract.h"
#include "TEveTrans.h"
#include "TEveGeoNode.h"
#include "TROOT.h"
#include "TEveStraightLineSet.h"
#include "TEveCompound.h"

// user include files
#include "Fireworks/Muons/interface/MuonsProxyEveLegoBuilder.h"
#include "Fireworks/Core/interface/FWEventItem.h"
#include "Fireworks/Core/interface/BuilderUtils.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MuonsProxyEveLegoBuilder::MuonsProxyEveLegoBuilder()
{
}

// MuonsProxyEveLegoBuilder::MuonsProxyEveLegoBuilder(const MuonsProxyEveLegoBuilder& rhs)
// {
//    // do actual copying here;
// }

MuonsProxyEveLegoBuilder::~MuonsProxyEveLegoBuilder()
{
}

//
// assignment operators
//
// const MuonsProxyEveLegoBuilder& MuonsProxyEveLegoBuilder::operator=(const MuonsProxyEveLegoBuilder& rhs)
// {
//   //An exception safe implementation is
//   MuonsProxyEveLegoBuilder temp(rhs);
//   swap(rhs);
//
//   return *this;
// }


void
MuonsProxyEveLegoBuilder::build(const FWEventItem* iItem, TEveElementList** product)
{
   TEveElementList* tList = *product;

   if(0 == tList) {
      tList =  new TEveElementList(iItem->name().c_str(),"MuonsLego",true);
      *product = tList;
      tList->SetMainColor(iItem->defaultDisplayProperties().color());
   } else {
      tList->DestroyElements();
   }
   
   const reco::MuonCollection* muons=0;
   iItem->get(muons);
   if(0==muons) {
      std::cout <<"Failed to get Muonss"<<std::endl;
      return;
   }
   
   fw::NamedCounter counter("muon");

   for(reco::MuonCollection::const_iterator muon = muons->begin(); 
       muon != muons->end(); ++muon, ++counter) {

      TEveCompound* container = new TEveCompound( counter.str().c_str() );
      container->OpenCompound();
      //guarantees that CloseCompound will be called no matter what happens
      boost::shared_ptr<TEveCompound> sentry(container,boost::mem_fn(&TEveCompound::CloseCompound));
      	
      
      TEveStraightLineSet* marker = new TEveStraightLineSet("energy");
      marker->SetLineWidth(1);
      marker->SetLineColor(  iItem->defaultDisplayProperties().color() );
      fw::addStraightLineSegment( marker, &*muon );
      container->AddElement(marker);
      tList->AddElement(container);
      //container->CloseCompound();
   }
}

REGISTER_FW3DLEGODATAPROXYBUILDER(MuonsProxyEveLegoBuilder,reco::MuonCollection,"Muons");

