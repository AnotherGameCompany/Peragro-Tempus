/*
    Copyright (C) 2008 Development Team of Peragro Tempus

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
  ptString entityname;
  unsigned short meshid;
  ptString meshname;
  ptString filename;
  WFMath::Point<3> pos;
  float rotation;
  unsigned short sectorid;
  unsigned int entityid;
  class ListEquipment
  {
  public:
    unsigned int slotid;
    unsigned int itemid;
    unsigned int variation;
    unsigned short meshid;
    ptString meshname;
    ptString filename;
  };

  unsigned int equipmentcount;
  ListEquipment* equipment;

  unsigned char poseid;

public:
  AddNpcEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDNPCENTITY)
  {
    equipment = 0;
  }

  ~AddNpcEntityMessage()
  {
    delete [] equipment;
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getEntityName() const { return entityname; }
  void setEntityName(ptString x) { entityname = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getEquipmentCount() const { return equipmentcount; }
  void setEquipmentCount(unsigned char ic)
  {
    equipmentcount = ic;
    delete [] equipment;
    equipment = new ListEquipment[ic];
  }

  // --- begin ListEquipment Getter and Setter ---

  unsigned int getSlotId(size_t i) { return equipment[i].slotid; }
  void setSlotId(size_t i, unsigned int x) { equipment[i].slotid = x; }

  unsigned int getItemId(size_t i) { return equipment[i].itemid; }
  void setItemId(size_t i, unsigned int x) { equipment[i].itemid = x; }

  unsigned int getVariation(size_t i) { return equipment[i].variation; }
  void setVariation(size_t i, unsigned int x) { equipment[i].variation = x; }

  unsigned short getMeshId(size_t i) { return equipment[i].meshid; }
  void setMeshId(size_t i, unsigned short x) { equipment[i].meshid = x; }

  ptString getMeshName(size_t i) { return equipment[i].meshname; }
  void setMeshName(size_t i, ptString x) { equipment[i].meshname = x; }

  ptString getFileName(size_t i) { return equipment[i].filename; }
  void setFileName(size_t i, ptString x) { equipment[i].filename = x; }

  // --- end ListEquipment Getter and Setter ---

  unsigned char GetPositioneId() const { return poseid; }
  void SetPositioneId(unsigned char x) { poseid = x; }

};

class AddItemEntityMessage : public NetMessage
{
  unsigned int itemid;
  unsigned int variation;
  ptString entityname;
  unsigned short meshid;
  ptString meshname;
  ptString filename;
  WFMath::Point<3> pos;
  float rotation;
  unsigned short sectorid;
  unsigned int entityid;

public:
  AddItemEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDITEMENTITY)
  {
  }

  ~AddItemEntityMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemId() const { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() const { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  ptString getEntityName() const { return entityname; }
  void setEntityName(ptString x) { entityname = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

};

class AddDoorEntityMessage : public NetMessage
{
  unsigned short doorid;
  bool isopen;
  bool islocked;
  unsigned int entityid;
  ptString entityname;
  unsigned short meshid;
  ptString meshname;
  ptString filename;
  unsigned short sectorid;
  ptString animationname;

public:
  AddDoorEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDDOORENTITY)
  {
  }

  ~AddDoorEntityMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned short getDoorId() const { return doorid; }
  void setDoorId(unsigned short x) { doorid = x; }

  bool getIsOpen() const { return isopen; }
  void setIsOpen(bool x) { isopen = x; }

  bool getIsLocked() const { return islocked; }
  void setIsLocked(bool x) { islocked = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  ptString getEntityName() const { return entityname; }
  void setEntityName(ptString x) { entityname = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  ptString getAnimationName() const { return animationname; }
  void setAnimationName(ptString x) { animationname = x; }

};

class AddPlayerEntityMessage : public NetMessage
{
  ptString entityname;
  unsigned short meshid;
  ptString meshname;
  ptString filename;
  WFMath::Point<3> pos;
  float rotation;
  unsigned char haircolour[3];
  unsigned char skincolour[3];
  unsigned char decalcolour[3];
  unsigned short sectorid;
  unsigned int entityid;
  class ListEquipment
  {
  public:
    unsigned int slotid;
    unsigned int itemid;
    unsigned int variation;
    unsigned short meshid;
    ptString meshname;
    ptString filename;
  };

  unsigned int equipmentcount;
  ListEquipment* equipment;

  unsigned char poseid;

public:
  AddPlayerEntityMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::ADDPLAYERENTITY)
  {
    equipment = 0;
  }

  ~AddPlayerEntityMessage()
  {
    delete [] equipment;
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getEntityName() const { return entityname; }
  void setEntityName(ptString x) { entityname = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

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

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getEquipmentCount() const { return equipmentcount; }
  void setEquipmentCount(unsigned char ic)
  {
    equipmentcount = ic;
    delete [] equipment;
    equipment = new ListEquipment[ic];
  }

  // --- begin ListEquipment Getter and Setter ---

  unsigned int getSlotId(size_t i) { return equipment[i].slotid; }
  void setSlotId(size_t i, unsigned int x) { equipment[i].slotid = x; }

  unsigned int getItemId(size_t i) { return equipment[i].itemid; }
  void setItemId(size_t i, unsigned int x) { equipment[i].itemid = x; }

  unsigned int getVariation(size_t i) { return equipment[i].variation; }
  void setVariation(size_t i, unsigned int x) { equipment[i].variation = x; }

  unsigned short getMeshId(size_t i) { return equipment[i].meshid; }
  void setMeshId(size_t i, unsigned short x) { equipment[i].meshid = x; }

  ptString getMeshName(size_t i) { return equipment[i].meshname; }
  void setMeshName(size_t i, ptString x) { equipment[i].meshname = x; }

  ptString getFileName(size_t i) { return equipment[i].filename; }
  void setFileName(size_t i, ptString x) { equipment[i].filename = x; }

  // --- end ListEquipment Getter and Setter ---

  unsigned char getPoseId() const { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

};

class AddMountEntityMessage : public NetMessage
{
  ptString entityname;
  unsigned short meshid;
  ptString meshname;
  ptString filename;
  WFMath::Point<3> pos;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  ptString getEntityName() const { return entityname; }
  void setEntityName(ptString x) { entityname = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned int getInventoryId() const { return inventoryid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

};

class MoveMessage : public NetMessage
{
  WFMath::Point<3> movedirection;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> getMoveDirection() { return movedirection; }
  void setMoveDirection(const WFMath::Point<3>& x)
  {
    movedirection = x;
  }
  void setMoveDirection(float x, float y, float z)
  {
    movedirection[0] = x;
    movedirection[1] = y;
    movedirection[2] = z;
  }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  bool getRun() const { return run; }
  void setRun(bool x) { run = x; }

  bool getJump() const { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveRequestMessage : public NetMessage
{
  WFMath::Point<3> movedirection;
  bool run;
  bool jump;

public:
  MoveRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::MOVEREQUEST)
  {
  }

  ~MoveRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> getMoveDirection() { return movedirection; }
  void setMoveDirection(const WFMath::Point<3>& x)
  {
    movedirection = x;
  }
  void setMoveDirection(float x, float y, float z)
  {
    movedirection[0] = x;
    movedirection[1] = y;
    movedirection[2] = z;
  }

  bool getRun() const { return run; }
  void setRun(bool x) { run = x; }

  bool getJump() const { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveToMessage : public NetMessage
{
  WFMath::Point<3> from;
  WFMath::Point<3> to;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> getFrom() { return from; }
  void setFrom(const WFMath::Point<3>& x)
  {
    from = x;
  }
  void setFrom(float x, float y, float z)
  {
    from[0] = x;
    from[1] = y;
    from[2] = z;
  }

  WFMath::Point<3> getTo() { return to; }
  void setTo(const WFMath::Point<3>& x)
  {
    to = x;
  }
  void setTo(float x, float y, float z)
  {
    to[0] = x;
    to[1] = y;
    to[2] = z;
  }

  float getSpeed() const { return speed; }
  void setSpeed(float x) { speed = x; }

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  bool getRun() const { return run; }
  void setRun(bool x) { run = x; }

  unsigned char getTurn() const { return turn; }
  void setTurn(unsigned char x) { turn = x; }

  bool getJump() const { return jump; }
  void setJump(bool x) { jump = x; }

};

class MoveToRequestMessage : public NetMessage
{
  WFMath::Point<3> to;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> getTo() { return to; }
  void setTo(const WFMath::Point<3>& x)
  {
    to = x;
  }
  void setTo(float x, float y, float z)
  {
    to[0] = x;
    to[1] = y;
    to[2] = z;
  }

  bool getRun() const { return run; }
  void setRun(bool x) { run = x; }

  bool getBackwards() const { return backwards; }
  void setBackwards(bool x) { backwards = x; }

  unsigned char getTurn() const { return turn; }
  void setTurn(unsigned char x) { turn = x; }

  bool getJump() const { return jump; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemEntityId() const { return itementityid; }
  void setItemEntityId(unsigned int x) { itementityid = x; }

  unsigned char getSlot() const { return slot; }
  void setSlot(unsigned char x) { slot = x; }

};

class PickResponseMessage : public NetMessage
{
  unsigned int itemid;
  unsigned int variation;
  unsigned char slotid;
  ptString name;
  ptString iconname;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getItemId() const { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() const { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  unsigned char getSlotId() const { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  ptString getName() const { return name; }
  void setName(ptString x) { name = x; }

  ptString getIconName() const { return iconname; }
  void setIconName(ptString x) { iconname = x; }

  ptString getDescription() const { return description; }
  void setDescription(ptString x) { description = x; }

  float getWeight() const { return weight; }
  void setWeight(float x) { weight = x; }

  ptString getEquipType() const { return equiptype; }
  void setEquipType(ptString x) { equiptype = x; }

  ptString getError() const { return error; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getSlot() const { return slot; }
  void setSlot(unsigned char x) { slot = x; }

  unsigned int getInventoryId() const { return inventoryid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getSlotId() const { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  ptString getError() const { return error; }
  void setError(ptString x) { error = x; }

};

class EquipMessage : public NetMessage
{
  unsigned int entityid;
  unsigned int itemid;
  unsigned int variation;
  unsigned char slotid;
  unsigned short meshid;
  ptString meshname;
  ptString filename;

public:
  EquipMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::EQUIP)
  {
  }

  ~EquipMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned int getItemId() const { return itemid; }
  void setItemId(unsigned int x) { itemid = x; }

  unsigned int getVariation() const { return variation; }
  void setVariation(unsigned int x) { variation = x; }

  unsigned char getSlotId() const { return slotid; }
  void setSlotId(unsigned char x) { slotid = x; }

  unsigned short getMeshId() const { return meshid; }
  void setMeshId(unsigned short x) { meshid = x; }

  ptString getMeshName() const { return meshname; }
  void setMeshName(ptString x) { meshname = x; }

  ptString getFileName() const { return filename; }
  void setFileName(ptString x) { filename = x; }

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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

};

class TeleportRequestMessage : public NetMessage
{
  unsigned int entityid;
  WFMath::Point<3> pos;
  float rotation;
  unsigned short sectorid;

public:
  TeleportRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::TELEPORTREQUEST)
  {
  }

  ~TeleportRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

};

class TeleportResponseMessage : public NetMessage
{
  unsigned int entityid;
  WFMath::Point<3> pos;
  float rotation;
  unsigned short sectorid;

public:
  TeleportResponseMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::TELEPORTRESPONSE)
  {
  }

  ~TeleportResponseMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

};

class DrUpdateRequestMessage : public NetMessage
{
  WFMath::Point<3> pos;
  float rotation;
  unsigned short sectorid;

public:
  DrUpdateRequestMessage() : NetMessage(MESSAGES::ENTITY,ENTITY::DRUPDATEREQUEST)
  {
  }

  ~DrUpdateRequestMessage()
  {
  }

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

};

class DrUpdateMessage : public NetMessage
{
  WFMath::Point<3> pos;
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  WFMath::Point<3> GetPosition() { return pos; }
  void SetPosition(const WFMath::Point<3>& x)
  {
    pos = x;
  }
  void SetPosition(float x, float y, float z)
  {
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
  }

  float GetRotation() const { return rotation; }
  void SetRotation(float x) { rotation = x; }

  unsigned short GetSectorId() const { return sectorid; }
  void SetSectorId(unsigned short x) { sectorid = x; }

  unsigned int getEntityId() const { return entityid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getMountEntityId() const { return mountentityid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getPlayerEntityId() const { return playerentityid; }
  void setPlayerEntityId(unsigned int x) { playerentityid = x; }

  unsigned int getMountEntityId() const { return mountentityid; }
  void setMountEntityId(unsigned int x) { mountentityid = x; }

  bool getCanControl() const { return cancontrol; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getMountEntityId() const { return mountentityid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getPlayerEntityId() const { return playerentityid; }
  void setPlayerEntityId(unsigned int x) { playerentityid = x; }

  unsigned int getMountEntityId() const { return mountentityid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned char getPoseId() const { return poseid; }
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

  bool serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getEntityId() const { return entityid; }
  void setEntityId(unsigned int x) { entityid = x; }

  unsigned char getPoseId() const { return poseid; }
  void setPoseId(unsigned char x) { poseid = x; }

};

#endif // ENTITYMESSAGES_H
