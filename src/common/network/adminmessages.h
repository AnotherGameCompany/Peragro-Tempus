/*
    Copyright (C) 2005 Development Team of Peragro Tempus

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

// Note: This code is generated by a script, to edit/create messages, have a look in data/generate/network

#ifndef _ADMINMESSAGES_H_
#define _ADMINMESSAGES_H_

#include "netmessage.h"

namespace ADMIN
{
  enum MESSAGES
  {
    CREATESECTOR=0,
    CREATEITEM=1,
    REMOVEALL=2,
    CREATENPC=3
  };
}

class CreateSectorMessage : public NetMessage
{
  unsigned short sectorid;
  ptString name;
  ptString region;

public:
  CreateSectorMessage() : NetMessage(MESSAGES::ADMIN,ADMIN::CREATESECTOR)
  {
  }

  ~CreateSectorMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned short getSectorId() { return sectorid; }
  void setSectorId(unsigned short x) { sectorid = x; }

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getRegion() { return region; }
  void setRegion(ptString x) { region = x; }

};

class CreateItemMessage : public NetMessage
{
  unsigned int itemid;
  ptString name;
  ptString icon;
  ptString description;
  ptString file;
  ptString mesh;
  float weight;
  ptString equiptype;

public:
  CreateItemMessage() : NetMessage(MESSAGES::ADMIN,ADMIN::CREATEITEM)
  {
  }

  ~CreateItemMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemId() { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getIcon() { return icon; }
  void setIcon(ptString x) { icon = x; }

  ptString getDescription() { return description; }
  void setDescription(ptString x) { description = x; }

  ptString getFile() { return file; }
  void setFile(ptString x) { file = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  float getWeight() { return weight; }
  void setWeight(float x) { weight = x; }

  ptString getEquipType() { return equiptype; }
  void setEquipType(ptString x) { equiptype = x; }

};

class RemoveAllMessage : public NetMessage
{
  ptString datatype;

public:
  RemoveAllMessage() : NetMessage(MESSAGES::ADMIN,ADMIN::REMOVEALL)
  {
  }

  ~RemoveAllMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getDataType() { return datatype; }
  void setDataType(ptString x) { datatype = x; }

};

class CreateNpcMessage : public NetMessage
{
  ptString name;
  ptString mesh;
  float pos[3];
  float rotation;
  unsigned short sectorid;
  ptString race;
  unsigned char haircolour[3];
  unsigned char skincolour[3];
  unsigned char decalcolour[3];
  unsigned short dialog;
  ptString ai;
  class ListAiSetting
  {
  public:
    ptString key;
    ptString value;
  };

  unsigned char aisettingcount;
  ListAiSetting* aisetting;


public:
  CreateNpcMessage() : NetMessage(MESSAGES::ADMIN,ADMIN::CREATENPC)
  {
    aisetting = 0;
  }

  ~CreateNpcMessage()
  {
    delete [] aisetting;
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  float* getPos() { return pos; }
  void setPos(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }
  void setPos(const float* x)
  {
    setPos(x[0], x[1], x[2]);
  }

  float getRotation() { return rotation; }
  void setRotation(float x) { rotation = x; }

  unsigned short getSectorId() { return sectorid; }
  void setSectorId(unsigned short x) { sectorid = x; }

  ptString getRace() { return race; }
  void setRace(ptString x) { race = x; }

  unsigned char* getHairColour() { return haircolour; }
  void setHairColour(unsigned char r, unsigned char g, unsigned char b)
  {
    haircolour[0] = r;
    haircolour[1] = g;
    haircolour[2] = b;
  }
  void setHairColour(const unsigned char* x)
  {
    setHairColour(x[0], x[1], x[2]);
  }

  unsigned char* getSkinColour() { return skincolour; }
  void setSkinColour(unsigned char r, unsigned char g, unsigned char b)
  {
    skincolour[0] = r;
    skincolour[1] = g;
    skincolour[2] = b;
  }
  void setSkinColour(const unsigned char* x)
  {
    setSkinColour(x[0], x[1], x[2]);
  }

  unsigned char* getDecalColour() { return decalcolour; }
  void setDecalColour(unsigned char r, unsigned char g, unsigned char b)
  {
    decalcolour[0] = r;
    decalcolour[1] = g;
    decalcolour[2] = b;
  }
  void setDecalColour(const unsigned char* x)
  {
    setDecalColour(x[0], x[1], x[2]);
  }

  unsigned short getDialog() { return dialog; }
  void setDialog(unsigned short x) { dialog = x; }

  ptString getAi() { return ai; }
  void setAi(ptString x) { ai = x; }

  unsigned char getAiSettingCount() { return aisettingcount; }
  void setAiSettingCount(unsigned char ic)
  {
    aisettingcount = ic;
    delete [] aisetting;
    aisetting = new ListAiSetting[ic];
  }

  // --- begin ListAiSetting Getter and Setter ---

  ptString getKey(size_t i) { return aisetting[i].key; }
  void setKey(size_t i, ptString x) { aisetting[i].key = x; }

  ptString getValue(size_t i) { return aisetting[i].value; }
  void setValue(size_t i, ptString x) { aisetting[i].value = x; }

  // --- end ListAiSetting Getter and Setter ---

};

#endif // _ADMINMESSAGES_H_
