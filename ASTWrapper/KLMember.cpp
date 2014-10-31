// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLMember.h"

using namespace FabricServices::ASTWrapper;

KLMember::KLMember(JSONData data)
: KLCommented(data)
{
  m_name = getDictValue("memberDecls")->getArrayElement(0)->getDictValue("name")->getStringData();
  m_type = getStringDictValue("baseType");
  m_type += getDictValue("memberDecls")->getArrayElement(0)->getDictValue("arrayModifier")->getStringData();
}

KLMember::~KLMember()
{
}

const std::string & KLMember::getName() const
{
  return m_name;
}

const std::string & KLMember::getType() const
{
  return m_type;
}