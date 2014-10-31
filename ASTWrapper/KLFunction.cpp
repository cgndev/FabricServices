// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLFunction.h"
#include "KLMethod.h"

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace FabricServices::ASTWrapper;

KLFunction::KLFunction(JSONData data)
: KLCommented(data)
{
  const char * returnType = getStringDictValue("returnType");
  if(returnType)
    m_returnType = returnType;

  m_name = getStringDictValue("name");

  JSONData params = getArrayDictValue("params");
  if(params)
  {
    for(unsigned int i=0;i<params->getArraySize();i++)
    {
      KLParameter * param = new KLParameter(params->getArrayElement(i));
      m_params.push_back(param);
    }
  }
}

KLFunction::~KLFunction()
{
  for(unsigned int i=0;i<m_params.size();i++)
  {
    if(m_params[i])
      delete(m_params[i]);
  }
}

void KLFunction::setExtension(const std::string & extension)
{
  KLCommented::setExtension(extension);
  for(unsigned int i=0;i<m_params.size();i++)
    m_params[i]->setExtension(extension);
}

void KLFunction::setKLFile(const std::string & klFile)
{
  KLCommented::setKLFile(klFile);
  for(unsigned int i=0;i<m_params.size();i++)
    m_params[i]->setKLFile(klFile);
}

const std::string & KLFunction::getName() const
{
  return m_name;
}

const std::string & KLFunction::getReturnType() const
{
  return m_returnType;
}

unsigned int KLFunction::getParameterCount() const
{
  return m_params.size();
}

const KLParameter * KLFunction::getParameter(unsigned int index) const
{
  return m_params[index];
}

bool KLFunction::isMethod() const
{
  return false;
}

std::string KLFunction::getPrefix() const
{
  return "";
}

std::string KLFunction::getSuffix() const
{
  return "";
}

const char * KLFunction::getKLType() const
{
  return "function";
}

std::string KLFunction::getKLCode(bool includeReturnType, bool includeKeyWord, bool includePrefix, bool includeName) const
{
  std::string code;

  if(includeKeyWord)
  {
    code += getKLType();
    code += " ";
  }

  if(m_returnType.length() > 0 && includeReturnType)
  {
    code += m_returnType;
    code += " ";
  }

  if(includePrefix)
    code += getPrefix();

  if(includeName)
    code += getName();

  bool skipSuffix = false;

  if(isMethod())
  {
    const KLMethod * method = (const KLMethod *)this;
    if("~"+method->getThisType() == getName())
      skipSuffix = true;
  }

  if(!skipSuffix)
    code += getSuffix();

  code += " (";

  if(m_params.size() > 0)
  {
    code += " ";

    for(unsigned int i=0;i<m_params.size();i++)
    {
      const KLParameter * p = m_params[i];
      if(i > 0)
        code += ", ";
      code += p->getUsage();
      code += " ";
      code += p->getTypeNoArray();
      code += " ";
      code += p->getName();
      code += p->getTypeArraySuffix();
    }

    code += " ";
  }

  code += ")";

  return code;
}

std::string KLFunction::getLabel() const
{
  return getKLCode(false, false, false, true);
}
