#ifndef Fireworks_Calo_MuonsProxyEveLegoBuilder_h
#define Fireworks_Calo_MuonsProxyEveLegoBuilder_h
// -*- C++ -*-
//
// Package:     Calo
// Class  :     MuonsProxyEveLegoBuilder
// 
/**\class MuonsProxyEveLegoBuilder MuonsProxyEveLegoBuilder.h Fireworks/Calo/interface/MuonsProxyEveLegoBuilder.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  
//         Created:  Sun Jan  6 23:42:33 EST 2008
// $Id: MuonsProxyEveLegoBuilder.h,v 1.2 2008/06/09 19:54:03 chrjones Exp $
//

// system include files

// user include files
#include "Fireworks/Core/interface/FW3DLegoDataProxyBuilder.h"

// forward declarations
class MuonsProxyEveLegoBuilder : public FW3DLegoDataProxyBuilder
{

   public:
      MuonsProxyEveLegoBuilder();
      virtual ~MuonsProxyEveLegoBuilder();

      // ---------- const member functions ---------------------
      REGISTER_PROXYBUILDER_METHODS();
   
      // ---------- static member functions --------------------
   private:
      virtual void build(const FWEventItem* iItem, 
			 TEveElementList** product);

      MuonsProxyEveLegoBuilder(const MuonsProxyEveLegoBuilder&); // stop default

      const MuonsProxyEveLegoBuilder& operator=(const MuonsProxyEveLegoBuilder&); // stop default

      // ---------- member data --------------------------------
};


#endif
