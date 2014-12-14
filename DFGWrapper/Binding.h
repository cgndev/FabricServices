// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Binding__
#define __DFGWrapper_Binding__

#include <FabricCore.h>

#include "GraphExecutable.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Binding
    {
      friend class Host;

    public:

      Binding(FabricCore::DFGBinding binding);
      Binding(const Binding & other);
      virtual ~Binding();

      bool isValid() const;
      FabricCore::DFGBinding getWrappedCoreBinding() const;

      FabricCore::RTVal getArgValue(char const *name);
      void setArgValue(char const *name, FabricCore::RTVal value);

      GraphExecutable getGraph();

      void execute();

    private:
      FabricCore::DFGBinding m_binding;      
    };

  };

};


#endif // __DFGWrapper_Binding__