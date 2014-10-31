// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLParameter__
#define __ASTWrapper_KLParameter__

#include "KLDecl.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLParameter : public KLDecl
    {
      friend class KLFunction;

    public:

      virtual ~KLParameter();

      virtual bool isInternal() const { return false; }

      const std::string & getUsage() const;
      const std::string & getName() const;
      const std::string & getType() const;
      std::string getTypeNoArray() const;
      std::string getTypeArraySuffix() const;

    protected:

      KLParameter(JSONData data);

    private:
      
      std::string m_usage;
      std::string m_name;
      std::string m_type;
    };

  };

};


#endif // __ASTWrapper_KLParameter__
