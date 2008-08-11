/*
    Copyright (C) 2007 Development Team of Peragro Tempus

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "nwwriter.h"

#include "network.h"

#include <algorithm>
#include <iostream>

/// \todo: It would be better to use a template rather than hardcode everything.

nwWriter::nwWriter(nwNetwork* nw) : nw(nw)
{
}

std::string nwWriter::toConst(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), toupper);
  return str;
}

std::string nwWriter::toVariable(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), tolower);
  //str.insert(0, "m_");
  return str;
}

std::string nwWriter::toFunction(std::string str)
{
  str[0] = (char) tolower(str[0]);
  return str;
}

void nwWriter::writeLicenceHeader(std::ofstream& out)
{
  out << 
    "/*\n"
    "    Copyright (C) 2005 Development Team of Peragro Tempus\n\n"

    "    This program is free software; you can redistribute it and/or modify\n"
    "    it under the terms of the GNU General Public License as published by\n"
    "    the Free Software Foundation; either version 2 of the License, or\n"
    "    (at your option) any later version.\n\n"

    "    This program is distributed in the hope that it will be useful,\n"
    "    but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "    GNU General Public License for more details.\n\n"

    "    You should have received a copy of the GNU General Public License\n"
    "    along with this program; if not, write to the Free Software\n"
    "    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n"
    "*/\n\n";

  out <<
    "//  !! This file was automatically generated by a network code generator   !!\n"
    "//  !! Do not change this file since all changes will be overwritten later !!\n"
    "//  !! Instead please change the source files here: peragro/data/generate  !!\n\n";
}

void nwWriter::writeNetwork(std::ofstream& out)
{
  writeLicenceHeader(out);

  out << "#ifndef NWTYPES_H\n";
  out << "#define NWTYPES_H\n";

  out << "\n"
         "#define MSG_NET_VERSION " << nw->netId << "\n"
         "\n";
  
  size_t i = 0;
  for (i = 0; i < nw->peers.size(); i++)
  {
    out << "#define MSG_" << toConst(nw->peers[i]->name).c_str() 
        << "_PEER_VERSION " << nw->peers[i]->netId << "\n";
  }

  out << "\n"
         "#define MSG_HANDLER_COUNT " << nw->types.size() << "\n"
         "\n"
         "namespace MESSAGES\n"
         "{\n"
         "  enum HANDLERS\n"
         "  {\n";

  for (i = 0; i < nw->types.size()-1; i++)
  {
    out <<  "    " << toConst(nw->types[i]->name).c_str() << 
            "=" << nw->types[i]->id << ",\n";
  }
  out << "    " << toConst(nw->types[i]->name).c_str() << 
         "=" << nw->types[i]->id << "\n";

  out << "  };\n"
         "}\n"
         "\n";

  out << "#endif // NWTYPES_H\n";
}

void nwWriter::writeParamDefinition(std::ofstream& out, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "  ptString " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "  const char* " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "  bool " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "  unsigned char " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "  unsigned short " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "  unsigned int " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "  float " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "  unsigned char " << toVariable(param->name).c_str() << "[3];\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "  float " << toVariable(param->name).c_str() << "[3];\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    out <<  "  class List" << param->name.c_str() << "\n"
        <<  "  {\n"
        <<  "  public:\n";

    for ( size_t i=0; i < param->params.size(); i++ )
    {
      writeParamListDefinition(out, param->params[i]);
    }

    out <<  "  };\n\n";
    out <<  "  unsigned char " << toVariable(param->name).c_str() << "count;\n";
    out <<  "  List" << param->name.c_str() << "* " << toVariable(param->name).c_str() << ";\n\n";
  }
}

void nwWriter::writeParamSerialisation(std::ofstream& out, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "  serial.setString(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "  serial.setString(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << "?1:0);\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "  serial.setInt16(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "  serial.setInt32(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "  serial.setFloat(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << "[0]);\n";
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << "[1]);\n";
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << "[2]);\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "  serial.setFloat(" << toVariable(param->name).c_str() << "[0]);\n";
    out <<  "  serial.setFloat(" << toVariable(param->name).c_str() << "[1]);\n";
    out <<  "  serial.setFloat(" << toVariable(param->name).c_str() << "[2]);\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    out <<  "  serial.setInt8(" << toVariable(param->name).c_str() << "count);\n"
        <<  "  for ( size_t i = 0; i < " << toVariable(param->name).c_str() << "count ; i++ )\n"
        <<  "  {\n";

    for ( size_t i=0; i < param->params.size(); i++ )
    {
      writeParamListSerialisation(out, param->name, param->params[i]);
    }

    out <<  "  };\n\n";
  }
}

void nwWriter::writeParamDeserialisation(std::ofstream& out, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = serial.getString();\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "  serial.getString(" << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = serial.getInt8() != 0;\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = (unsigned char) serial.getInt8();\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = (unsigned short) serial.getInt16();\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = (unsigned int) serial.getInt32();\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "  " << toVariable(param->name).c_str() << " = serial.getFloat();\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "  " << toVariable(param->name).c_str() << "[0] = (unsigned char) serial.getInt8();\n";
    out <<  "  " << toVariable(param->name).c_str() << "[1] = (unsigned char) serial.getInt8();\n";
    out <<  "  " << toVariable(param->name).c_str() << "[2] = (unsigned char) serial.getInt8();\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "  " << toVariable(param->name).c_str() << "[0] = serial.getFloat();\n";
    out <<  "  " << toVariable(param->name).c_str() << "[1] = serial.getFloat();\n";
    out <<  "  " << toVariable(param->name).c_str() << "[2] = serial.getFloat();\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    out <<  "  " << toVariable(param->name).c_str() << "count = (unsigned char) serial.getInt8();\n"
        <<  "  set" << param->name.c_str() << "Count(" << toVariable(param->name).c_str() << "count);\n"
        <<  "  for ( size_t i = 0; i < " << toVariable(param->name).c_str() << "count ; i++ )\n"
        <<  "  {\n";

    for ( size_t i=0; i < param->params.size(); i++ )
    {
      writeParamListDeserialisation(out, param->name, param->params[i]);
    }

    out <<  "  };\n\n";
  }
}

void nwWriter::writeParamGetterSetter(std::ofstream& out, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "  ptString get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(ptString x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "  const char* get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(const char* x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "  bool get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(bool x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "  unsigned char get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(unsigned char x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "  unsigned short get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(unsigned short x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "  unsigned int get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(unsigned int x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "  float get" << param->name.c_str() << "() const { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(float x) { " 
        << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "  unsigned char* get" << param->name.c_str() << "() { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(unsigned char r, unsigned char g, unsigned char b)\n"
        <<  "  {\n" 
        <<  "    " << toVariable(param->name).c_str() << "[0] = r;\n"
        <<  "    " << toVariable(param->name).c_str() << "[1] = g;\n"
        <<  "    " << toVariable(param->name).c_str() << "[2] = b;\n"
        <<  "  }\n"
        <<  "  void set" << param->name.c_str() << "(const unsigned char* x)\n"
        <<  "  {\n" 
        <<  "    set" << param->name.c_str() << "(x[0], x[1], x[2]);\n"
        <<  "  }\n\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "  float* get" << param->name.c_str() << "() { return " 
        << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(float x, float y, float z)\n"
        <<  "  {\n" 
        <<  "    " << toVariable(param->name).c_str() << "[0] = x;\n"
        <<  "    " << toVariable(param->name).c_str() << "[1] = y;\n"
        <<  "    " << toVariable(param->name).c_str() << "[2] = z;\n"
        <<  "  }\n"
        <<  "  void set" << param->name.c_str() << "(const float* x)\n"
        <<  "  {\n" 
        <<  "    set" << param->name.c_str() << "(x[0], x[1], x[2]);\n"
        <<  "  }\n\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    out <<  "  unsigned char get" << param->name.c_str() << "Count() const { return " 
        <<  toVariable(param->name).c_str() << "count; }\n"
        <<  "  void set" << param->name.c_str() << "Count(unsigned char ic)\n"
        <<  "  {\n"
        <<  "    " << toVariable(param->name).c_str() << "count = ic;\n"
        <<  "    delete [] " << toVariable(param->name).c_str() << ";\n"
        <<  "    " << toVariable(param->name).c_str() << " = new List" << param->name.c_str() 
        <<  "[ic];\n"
        <<  "  }\n\n";
      
    out <<  "  // --- begin List" << param->name.c_str() << " Getter and Setter ---\n\n";

    for ( size_t i=0; i < param->params.size(); i++ )
    {
      writeParamListGetterSetter(out, param->name.c_str(), param->params[i]);
    }
    out <<  "  // --- end List" << param->name.c_str() << " Getter and Setter ---\n\n";
  }
}

void nwWriter::writeParamListDefinition(std::ofstream& out, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "    ptString " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "    const char* " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "    bool " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "    unsigned char " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "    unsigned short " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "    unsigned int " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "    float " << toVariable(param->name).c_str() << ";\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "    unsigned char " << toVariable(param->name).c_str() << "[3];\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "    float " << toVariable(param->name).c_str() << "[3];\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    std::cerr << "Error! Nested Lists are not yet supported!";
  }
}

void nwWriter::writeParamListSerialisation(std::ofstream& out, std::string listname, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "    serial.setString(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "    serial.setString(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "    serial.setInt8(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "?1:0);\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "    serial.setInt8(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "    serial.setInt16(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "    serial.setInt32(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "    serial.setFloat(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "    serial.setInt8(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0]);\n";
    out <<  "    serial.setInt8(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1]);\n";
    out <<  "    serial.setInt8(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2]);\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "    serial.setFloat(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0]);\n";
    out <<  "    serial.setFloat(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1]);\n";
    out <<  "    serial.setFloat(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2]);\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    // Not yet supported
  }
}

void nwWriter::writeParamListDeserialisation(std::ofstream& out, std::string listname, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = serial.getString();\n";
  }
  if (param->type == nwParamType::TEXT)
  {
    out <<  "    serial.getString(" << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << ");\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = serial.getInt8() != 0;\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = (unsigned char) serial.getInt8();\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = (unsigned short) serial.getInt16();\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = (unsigned int) serial.getInt32();\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = serial.getFloat();\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0] = (unsigned char) serial.getInt8();\n";
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1] = (unsigned char) serial.getInt8();\n";
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2] = (unsigned char) serial.getInt8();\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0] = serial.getFloat();\n";
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1] = serial.getFloat();\n";
    out <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2] = serial.getFloat();\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    // Not yet supported
  }
}

void nwWriter::writeParamListGetterSetter(std::ofstream& out, std::string listname, nwParams* param)
{
  if (param->type == nwParamType::STRING)
  {
    out <<  "  ptString get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, ptString x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::TEXT)
  {
    out <<  "  const char* get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]."<< toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, const char* x) { " 
        << toVariable(listname).c_str() << "[i]."<< toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::BOOL)
  {
    out <<  "  bool get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, bool x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT8)
  {
    out <<  "  unsigned char get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, unsigned char x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT16)
  {
    out <<  "  unsigned short get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, unsigned short x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::UINT32)
  {
    out <<  "  unsigned int get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, unsigned int x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::FLOAT)
  {
    out <<  "  float get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, float x) { " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << " = x; }\n\n";
  }
  else if (param->type == nwParamType::COLOUR24)
  {
    out <<  "  unsigned char* get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, unsigned char r, unsigned char g, unsigned char b)\n"
        <<  "  {\n" 
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0] = r;\n"
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1] = g;\n"
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2] = b;\n"
        <<  "  }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, const unsigned char* x)\n"
        <<  "  {\n" 
        <<  "    set" << param->name.c_str() << "(i, x[0], x[1], x[2]);\n"
        <<  "  }\n\n";
  }
  else if (param->type == nwParamType::VECTOR3F)
  {
    out <<  "  float* get" << param->name.c_str() << "(size_t i) { return " 
        << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "; }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, float x, float y, float z)\n"
        <<  "  {\n" 
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[0] = x;\n"
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[1] = y;\n"
        <<  "    " << toVariable(listname).c_str() << "[i]." << toVariable(param->name).c_str() << "[2] = z;\n"
        <<  "  }\n"
        <<  "  void set" << param->name.c_str() << "(size_t i, float* x)\n"
        <<  "  {\n" 
        <<  "    set" << param->name.c_str() << "(i, x[0], x[1], x[2]);\n"
        <<  "  }\n\n";
  }
  else if (param->type == nwParamType::LIST)
  {
    // Not yet supported
  }
}

void nwWriter::writeTypeHead(std::ofstream& out, nwType* type)
{
  writeLicenceHeader(out);

  out << "#ifndef " << toConst(type->name).c_str() << "MESSAGES_H\n";
  out << "#define " << toConst(type->name).c_str() << "MESSAGES_H\n\n";

  out << "#include \"netmessage.h\"\n\n";

  out << "namespace " << toConst(type->name).c_str() << "\n"
         "{\n"
         "  enum MESSAGES\n"
         "  {\n";

  size_t i = 0;
  for (i = 0; i < type->msgs.size()-1; i++)
  {
    out <<  "    " << toConst(type->msgs[i]->name).c_str() << 
            "=" << type->msgs[i]->id << ",\n";
  }
  out << "    " << toConst(type->msgs[i]->name).c_str() << 
         "=" << type->msgs[i]->id << "\n";

  out << "  };\n"
         "}\n\n";

  for (i = 0; i < type->msgs.size(); i++)
  {
    nwMessage* msg = type->msgs[i];

    out << "class " << msg->name.c_str() << "Message : public NetMessage\n"
           "{\n";

    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      writeParamDefinition(out, param);
    }

    out << "\n"
           "public:\n"
           "  " << msg->name.c_str ()<< "Message() : NetMessage(MESSAGES::" <<
           toConst(type->name).c_str() << "," << toConst(type->name).c_str() << 
           "::" << toConst(msg->name).c_str() << ")\n"
           "  {\n";
    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      if (param->type == nwParamType::LIST)
      {
        out << "    " << toVariable(param->name).c_str() << " = 0;\n";
      } 
/*
      else if (param->type == nwParamType::BOOL) 
      {
        out << "    " << toVariable(param->name).c_str() << " = false;\n";
      } 
      else if (param->type == nwParamType::UINT8 ||
                 param->type == nwParamType::UINT16 ||
                 param->type == nwParamType::UINT32) 
      {
        out << "    " << toVariable(param->name).c_str() << " = 0;\n";
      } 
      else if (param->type == nwParamType::FLOAT)
      {
        out << "    " << toVariable(param->name).c_str() << " = 0.0;\n";
      }
      else if (param->type == nwParamType::VECTOR3F)
      {
        out << "    " << toVariable(param->name).c_str() << "[0] = 0.0;\n";
        out << "    " << toVariable(param->name).c_str() << "[1] = 0.0;\n";
        out << "    " << toVariable(param->name).c_str() << "[2] = 0.0;\n";
      }
      else if (param->type == nwParamType::COLOUR24)
      {
        out << "    " << toVariable(param->name).c_str() << "[0] = \'\\0\';\n";
        out << "    " << toVariable(param->name).c_str() << "[1] = \'\\0\';\n";
        out << "    " << toVariable(param->name).c_str() << "[2] = \'\\0\';\n";
      }
      else if (param->type == nwParamType::TEXT)
      {
        out << "    " << toVariable(param->name).c_str() << " = \'\\0\';\n";
      }
      else if (param->type == nwParamType::COLOUR24)
      {
        out << "    " << toVariable(param->name).c_str() << "[0] = \'\\0\';\n";
        out << "    " << toVariable(param->name).c_str() << "[1] = \'\\0\';\n";
        out << "    " << toVariable(param->name).c_str() << "[2] = \'\\0\';\n";
      }
*/
    }

    out << "  }\n\n"
           "  ~" << msg->name.c_str ()<< "Message()\n" <<
           "  {\n";

    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      if (param->type == nwParamType::LIST)
      {
        out << "    delete [] " << toVariable(param->name).c_str() << ";\n";
      }
    }

    out << "  }\n\n"
           "  bool serialise(ByteStream* bs);\n"
           "  void deserialise(ByteStream* bs);\n\n";

    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      writeParamGetterSetter(out, param);
//      out << "  unsigned " << param->type.c_str() << " get" << param->name.c_str() 
//          << "() { return " << param->name.c_str() << "; }\n"
//          << "  void set" << param->name.c_str() << "(" << param->type.c_str() 
//          << " x) { " << param->name.c_str() << " = x; }\n\n";
    }

    out << "};\n\n";
  }

  out << "#endif // "<< toConst(type->name).c_str() <<"MESSAGES_H\n";
}

void nwWriter::writeTypeImpl(std::ofstream& out, nwType* type)
{
  writeLicenceHeader(out);

  out << "#include \"common/network/" << toVariable(type->name).c_str() << "messages.h\"\n"
      << "#include \"deserialiser.h\"\n"
      << "#include \"serialiser.h\"\n\n";

  for (size_t i = 0; i < type->msgs.size(); i++)
  {
    nwMessage* msg = type->msgs[i];

    out << "bool " << msg->name.c_str ()<< "Message::serialise(ByteStream* bs)\n"
           "{\n"
           "  Serialiser serial(bs);\n"
           "  serial.setInt8(type);\n"
           "  serial.setInt8(id);\n";

    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      writeParamSerialisation(out, param);
    }
    out << "  return serial.isValid();\n"
           "}\n"
           "\n"
           "void " << msg->name.c_str ()<< "Message::deserialise(ByteStream* bs)\n"
           "{\n"
           "  Deserialiser serial(bs);\n"
           "  type = serial.getInt8();\n"
           "  id = serial.getInt8();\n";

    for (size_t j = 0; j < msg->params.size(); j++)
    {
      nwParams* param = msg->params[j];
      writeParamDeserialisation(out, param);
    }

    out << "}\n\n";
  }
}

void nwWriter::writeHandler(std::ofstream& out, nwPeer* peer, nwType* type)
{
  writeLicenceHeader(out);

  out << "#ifndef " << toConst(type->name).c_str() << "HANDLER_H\n";
  out << "#define " << toConst(type->name).c_str() << "HANDLER_H\n\n";

  out << "#include \"common/network/nwtypes.h\"\n\n";
  out << "#include \"common/network/" << toVariable(type->name).c_str() << "messages.h\"\n\n";

  //out << "class " << peer->name.c_str() << ";\n\n";

  out << "class " << type->name.c_str() << "Handler : public MessageHandler\n"
      << "{\n"
      //<< "private:\n"
      //<< "  " << peer->name.c_str() << "* " << toVariable(peer->name).c_str() << ";\n\n"

      << "public:\n"
      << "  " << type->name.c_str() << "Handler(" /* << peer->name.c_str() << "* " 
      << toVariable(peer->name).c_str() */ << ")\n"
      //<< "  : " << toVariable(peer->name).c_str() << "(" << toVariable(peer->name).c_str() << ")\n"
      << "  {\n"
      << "  }\n\n"

      << "  char getType() { return MESSAGES::" << toConst(type->name).c_str() << "; }\n\n"

      << "  void handle(GenericMessage* msg)\n"
      << "  {\n"
      << "    char type = msg->getMsgType();\n"
      << "    if (type != MESSAGES::" << toConst(type->name).c_str()
      << ") assert(\"wrong message type\");\n";

  for (size_t i = 0, n = 0; i < peer->recvMsg.size(); i++)
  {
    nwMessage* msg = peer->recvMsg[i];
    if (!msg || msg->type != type)
      continue;

    if (n == 0)
    {
      out << "    char id = msg->getMsgId();\n\n";

      out << "    if (id == " << toConst(type->name).c_str() 
          << "::" << toConst(msg->name).c_str() << ") handle" 
          << msg->name.c_str() << "(msg);\n";
    }
    else
    {
      out << "    else if (id == " << toConst(type->name).c_str()
          << "::" << toConst(msg->name).c_str() << ") handle" 
          << msg->name.c_str() << "(msg);\n";
    }

    n++;
  }

  out << "  }\n\n";

  for (size_t i = 0; i < peer->recvMsg.size(); i++)
  {
    nwMessage* msg = peer->recvMsg[i];
    if (!msg || msg->type != type)
      continue;

    out << "  void handle" << msg->name.c_str() << "(GenericMessage* msg);\n";
  }

  out << "};\n\n";

  out << "#endif // " << toConst(type->name).c_str() << "HANDLER_H\n";
}
