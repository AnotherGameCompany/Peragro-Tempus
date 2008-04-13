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

//  !! This file was automatically generated by a network code generator   !!
//  !! Do not change this file since all changes will be overwritten later !!
//  !! Instead please change the source files here: peragro/data/generate  !!

#ifndef ENTITYMESSAGES_H
#define ENTITYMESSAGES_H

#include "netmessage.h"

namespace ENTITY
{
  enum MESSAGES
  {
    ADDNPCENTITY=0,
    ADDITEMENTITY=1,
    ADDDOORENTITY=2,
    ADDPLAYERENTITY=3,
    ADDMOUNTENTITY=4,
    REMOVEENTITY=5,
    MOVE=6,
    MOVEREQUEST=7,
    MOVETO=8,
    MOVETOREQUEST=9,
    PICKREQUEST=10,
    PICKRESPONSE=11,
    DROPREQUEST=12,
    DROPRESPONSE=13,
    EQUIP=14,
    RELOCATE=15,
    TELEPORTREQUEST=16,
    TELEPORTRESPONSE=17,
    DRUPDATEREQUEST=18,
    DRUPDATE=19,
    MOUNTREQUEST=20,
    MOUNT=21,
    UNMOUNTREQUEST=22,
    UNMOUNT=23,
    POSEREQUEST=24,
    POSE=25
  };
}

class AddNpcEntityMessage : public NetMessage
{
  ptString name;
  ptString mesh;
  unsigned short meshid;
  float pos[3];
  float rotation;
  unsigned short sectorid;
  unsigned int entityid;
  unsigned char poseid;
  class ListEquipment
  {
  public:
    unsigned int itemid;
    unsigned int variation;
    ptString file;
    ptString mesh;
  };

  unsigned char equipmentcount;
  ListEquipment* equipment;


public:
  AddNpcEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDNPCENTITY)
  {
    equipment = 0;
  }

  ~AddNpcEntityMessage()
  {
    delete [] equipment;
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  unsigned short getMeshId() { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

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

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getPoseId() { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

  unsigned char getEquipmentCount() { return equipmentcount; }
  void setEquipmentCount(unsigned char ic)
  {
    equipmentcount = ic;
    delete [] equipment;
    equipment = new ListEquipment[ic];
  }

  // --- begin ListEquipment Getter and Setter ---

  unsigned int getItemId(size_t i) { return equipment[i].itemid; }
  void setItemId(size_t i, unsigned int x) { equipment[i].itemid = x; }

  unsigned int getVariation(size_t i) { return equipment[i].variation; }
  void setVariation(size_t i, unsigned int x) { equipment[i].variation = x; }

  ptString getFile(size_t i) { return equipment[i].file; }
  void setFile(size_t i, ptString x) { equipment[i].file = x; }

  ptString getMesh(size_t i) { return equipment[i].mesh; }
  void setMesh(size_t i, ptString x) { equipment[i].mesh = x; }

  // --- end ListEquipment Getter and Setter ---

};

class AddItemEntityMessage : public NetMessage
{
  unsigned int itemid;
  unsigned int variation;
  ptString name;
  ptString file;
  ptString mesh;
  float pos[3];
  unsigned short sectorid;
  unsigned int entityid;

public:
  AddItemEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDITEMENTITY)
  {
  }

  ~AddItemEntityMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemId() { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getFile() { return file; }
  void setFile(ptString x) { file = x; }

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

  unsigned short getSectorId() { return sectorid; }
  void setSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

};

class AddDoorEntityMessage : public NetMessage
{
  unsigned short doorid;
  bool isopen;
  bool islocked;
  unsigned int entityid;
  ptString name;
  ptString mesh;
  unsigned short sectorid;
  ptString animation;

public:
  AddDoorEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDDOORENTITY)
  {
  }

  ~AddDoorEntityMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned short getDoorId() { return doorid; }
  void setDoorId(unsigned short x) { doorid = x; }

  bool getIsOpen() { return isopen; }
  void setIsOpen(bool x) { isopen = x; }

  bool getIsLocked() { return islocked; }
  void setIsLocked(bool x) { islocked = x; }

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  unsigned short getSectorId() { return sectorid; }
  void setSectorId(unsigned short x) { sectorid = x; }

  ptString getAnimation() { return animation; }
  void setAnimation(ptString x) { animation = x; }

};

class AddPlayerEntityMessage : public NetMessage
{
  ptString name;
  ptString mesh;
  unsigned short meshid;
  float pos[3];
  float rotation;
  unsigned char haircolour[3];
  unsigned char skincolour[3];
  unsigned char decalcolour[3];
  unsigned short sectorid;
  unsigned int entityid;
  unsigned char poseid;
  class ListEquipment
  {
  public:
    unsigned int itemid;
    unsigned int variation;
    ptString file;
    ptString mesh;
  };

  unsigned char equipmentcount;
  ListEquipment* equipment;


public:
  AddPlayerEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDPLAYERENTITY)
  {
    equipment = 0;
  }

  ~AddPlayerEntityMessage()
  {
    delete [] equipment;
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  unsigned short getMeshId() { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

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

  unsigned short getSectorId() { return sectorid; }
  void setSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getPoseId() { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

  unsigned char getEquipmentCount() { return equipmentcount; }
  void setEquipmentCount(unsigned char ic)
  {
    equipmentcount = ic;
    delete [] equipment;
    equipment = new ListEquipment[ic];
  }

  // --- begin ListEquipment Getter and Setter ---

  unsigned int getItemId(size_t i) { return equipment[i].itemid; }
  void setItemId(size_t i, unsigned int x) { equipment[i].itemid = x; }

  unsigned int getVariation(size_t i) { return equipment[i].variation; }
  void setVariation(size_t i, unsigned int x) { equipment[i].variation = x; }

  ptString getFile(size_t i) { return equipment[i].file; }
  void setFile(size_t i, ptString x) { equipment[i].file = x; }

  ptString getMesh(size_t i) { return equipment[i].mesh; }
  void setMesh(size_t i, ptString x) { equipment[i].mesh = x; }

  // --- end ListEquipment Getter and Setter ---

};

class AddMountEntityMessage : public NetMessage
{
  ptString name;
  ptString mesh;
  unsigned short meshid;
  float pos[3];
  float rotation;
  unsigned short sectorid;
  unsigned int entityid;
  unsigned int inventoryid;

public:
  AddMountEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDMOUNTENTITY)
  {
  }

  ~AddMountEntityMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

  unsigned short getMeshId() { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

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

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned int getInventoryId() { return inventoryid; }
  void setInventoryId(unsigned int x) { inventoryid = x; }

};

class RemoveEntityMessage : public NetMessage
{
  unsigned int entityid;

public:
  RemoveEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::REMOVEENTITY)
  {
  }

  ~RemoveEntityMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

};

class MoveMessage : public NetMessage
{
  float turn;
  float walk;
  unsigned int entityid;
  bool run;
  bool jump;

public:
  MoveMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOVE)
  {
  }

  ~MoveMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  float getTurn() { return turn; }
  void setTurn(float x) { turn = x; }

  float getWalk() { return walk; }
  void setWalk(float x) { walk = x; }

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  bool getRun() { return run; }
  void setRun(bool x) { run = x; }

  bool getJump() { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveRequestMessage : public NetMessage
{
  unsigned char turn;
  unsigned char walk;
  bool run;
  bool jump;

public:
  MoveRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOVEREQUEST)
  {
  }

  ~MoveRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getTurn() { return turn; }
  void setTurn(unsigned char x) { turn = x; }

  unsigned char getWalk() { return walk; }
  void setWalk(unsigned char x) { walk = x; }

  bool getRun() { return run; }
  void setRun(bool x) { run = x; }

  bool getJump() { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveToMessage : public NetMessage
{
  float from[3];
  float to[3];
  float speed;
  unsigned int entityid;
  bool run;
  unsigned char turn;
  bool jump;

public:
  MoveToMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOVETO)
  {
  }

  ~MoveToMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  float* getFrom() { return from; }
  void setFrom(float x, float y, float z)
  {
    from[0] = x;
    from[1] = y;
    from[2] = z;
  }
  void setFrom(const float* x)
  {
    setFrom(x[0], x[1], x[2]);
  }

  float* getTo() { return to; }
  void setTo(float x, float y, float z)
  {
    to[0] = x;
    to[1] = y;
    to[2] = z;
  }
  void setTo(const float* x)
  {
    setTo(x[0], x[1], x[2]);
  }

  float getSpeed() { return speed; }
  void setSpeed(float x) { speed = x; }

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  bool getRun() { return run; }
  void setRun(bool x) { run = x; }

  unsigned char getTurn() { return turn; }
  void setTurn(unsigned char x) { turn = x; }

  bool getJump() { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveToRequestMessage : public NetMessage
{
  float to[3];
  bool run;
  bool backwards;
  unsigned char turn;
  bool jump;

public:
  MoveToRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOVETOREQUEST)
  {
  }

  ~MoveToRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  float* getTo() { return to; }
  void setTo(float x, float y, float z)
  {
    to[0] = x;
    to[1] = y;
    to[2] = z;
  }
  void setTo(const float* x)
  {
    setTo(x[0], x[1], x[2]);
  }

  bool getRun() { return run; }
  void setRun(bool x) { run = x; }

  bool getBackwards() { return backwards; }
  void setBackwards(bool x) { backwards = x; }

  unsigned char getTurn() { return turn; }
  void setTurn(unsigned char x) { turn = x; }

  bool getJump() { return jump; }
  void setJump(bool x) { jump = x; }

};

class PickRequestMessage : public NetMessage
{
  unsigned int itementityid;
  unsigned char slot;

public:
  PickRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::PICKREQUEST)
  {
  }

  ~PickRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemEntityId() { return itementityid; }
  void setItemEntityId(unsigned int x) { itementityid = x; }

  unsigned char getSlot() { return slot; }
  void setSlot(unsigned char x) { slot = x; }

};

class PickResponseMessage : public NetMessage
{
  unsigned int itemid;
  unsigned int variation;
  unsigned char slotid;
  ptString name;
  ptString icon;
  ptString description;
  float weight;
  ptString equiptype;
  ptString error;

public:
  PickResponseMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::PICKRESPONSE)
  {
  }

  ~PickResponseMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemId() { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  unsigned char getSlotId() { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  ptString getName() { return name; }
  void setName(ptString x) { name = x; }

  ptString getIcon() { return icon; }
  void setIcon(ptString x) { icon = x; }

  ptString getDescription() { return description; }
  void setDescription(ptString x) { description = x; }

  float getWeight() { return weight; }
  void setWeight(float x) { weight = x; }

  ptString getEquipType() { return equiptype; }
  void setEquipType(ptString x) { equiptype = x; }

  ptString getError() { return error; }
  void setError(ptString x) { error = x; }

};

class DropRequestMessage : public NetMessage
{
  unsigned char slot;
  unsigned int inventoryid;

public:
  DropRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::DROPREQUEST)
  {
  }

  ~DropRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getSlot() { return slot; }
  void setSlot(unsigned char x) { slot = x; }

  unsigned int getInventoryId() { return inventoryid; }
  void setInventoryId(unsigned int x) { inventoryid = x; }

};

class DropResponseMessage : public NetMessage
{
  unsigned char slotid;
  ptString error;

public:
  DropResponseMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::DROPRESPONSE)
  {
  }

  ~DropResponseMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getSlotId() { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  ptString getError() { return error; }
  void setError(ptString x) { error = x; }

};

class EquipMessage : public NetMessage
{
  unsigned int entityid;
  unsigned int itemid;
  unsigned int variation;
  unsigned char slotid;
  ptString file;
  ptString mesh;

public:
  EquipMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::EQUIP)
  {
  }

  ~EquipMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned int getItemId() { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  unsigned char getSlotId() { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  ptString getFile() { return file; }
  void setFile(ptString x) { file = x; }

  ptString getMesh() { return mesh; }
  void setMesh(ptString x) { mesh = x; }

};

class RelocateMessage : public NetMessage
{

public:
  RelocateMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::RELOCATE)
  {
  }

  ~RelocateMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

};

class TeleportRequestMessage : public NetMessage
{
  unsigned int entityid;
  float pos[3];
  float rotation;
  unsigned short sectorid;

public:
  TeleportRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::TELEPORTREQUEST)
  {
  }

  ~TeleportRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

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

};

class TeleportResponseMessage : public NetMessage
{
  unsigned int entityid;
  float pos[3];
  float rotation;
  unsigned short sectorid;

public:
  TeleportResponseMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::TELEPORTRESPONSE)
  {
  }

  ~TeleportResponseMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

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

};

class DrUpdateRequestMessage : public NetMessage
{
  float pos[3];
  float rotation;
  unsigned short sectorid;

public:
  DrUpdateRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::DRUPDATEREQUEST)
  {
  }

  ~DrUpdateRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

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

};

class DrUpdateMessage : public NetMessage
{
  float pos[3];
  float rotation;
  unsigned short sectorid;
  unsigned int entityid;

public:
  DrUpdateMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::DRUPDATE)
  {
  }

  ~DrUpdateMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

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

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

};

class MountRequestMessage : public NetMessage
{
  unsigned int mountentityid;

public:
  MountRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOUNTREQUEST)
  {
  }

  ~MountRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getMountEntityId() { return mountentityid; }
  void setMountEntityId(unsigned int x) { mountentityid = x; }

};

class MountMessage : public NetMessage
{
  unsigned int playerentityid;
  unsigned int mountentityid;
  bool cancontrol;

public:
  MountMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOUNT)
  {
  }

  ~MountMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getPlayerEntityId() { return playerentityid; }
  void setPlayerEntityId(unsigned int x) { playerentityid = x; }

  unsigned int getMountEntityId() { return mountentityid; }
  void setMountEntityId(unsigned int x) { mountentityid = x; }

  bool getCanControl() { return cancontrol; }
  void setCanControl(bool x) { cancontrol = x; }

};

class UnmountRequestMessage : public NetMessage
{
  unsigned int mountentityid;

public:
  UnmountRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::UNMOUNTREQUEST)
  {
  }

  ~UnmountRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getMountEntityId() { return mountentityid; }
  void setMountEntityId(unsigned int x) { mountentityid = x; }

};

class UnmountMessage : public NetMessage
{
  unsigned int playerentityid;
  unsigned int mountentityid;

public:
  UnmountMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::UNMOUNT)
  {
  }

  ~UnmountMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getPlayerEntityId() { return playerentityid; }
  void setPlayerEntityId(unsigned int x) { playerentityid = x; }

  unsigned int getMountEntityId() { return mountentityid; }
  void setMountEntityId(unsigned int x) { mountentityid = x; }

};

class PoseRequestMessage : public NetMessage
{
  unsigned char poseid;

public:
  PoseRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::POSEREQUEST)
  {
  }

  ~PoseRequestMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getPoseId() { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

};

class PoseMessage : public NetMessage
{
  unsigned int entityid;
  unsigned char poseid;

public:
  PoseMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::POSE)
  {
  }

  ~PoseMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getPoseId() { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

};

#endif // ENTITYMESSAGES_H
