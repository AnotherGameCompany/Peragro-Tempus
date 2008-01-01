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

//  !! This file was automatically generated by networkcodegenerator.sh    !!
//  !! Do not change this file since all changes will be overwritten later !!
//  !! Instead please change the source files here: peragro/data/generate  !!

#include "common/network/questmessages.h"
#include "deserialiser.h"
#include "serialiser.h"

void NpcDialogMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(dialogid);
  serial.setString(dialogtext);
  serial.setInt8(answerscount);
  for ( size_t i = 0; i < answerscount ; i++ )
  {
    serial.setInt32(answers[i].answerid);
    serial.setString(answers[i].answertext);
  };

}

void NpcDialogMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  dialogid = (unsigned int) serial.getInt32();
  serial.getString(dialogtext);
  answerscount = (unsigned char) serial.getInt8();
  setAnswersCount(answerscount);
  for ( size_t i = 0; i < answerscount ; i++ )
  {
    answers[i].answerid = (unsigned int) serial.getInt32();
    serial.getString(answers[i].answertext);
  };

}

void NpcDialogAnswerMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(dialogid);
  serial.setInt32(answerid);
}

void NpcDialogAnswerMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  dialogid = (unsigned int) serial.getInt32();
  answerid = (unsigned int) serial.getInt32();
}

void NpcStartDialogMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(npcid);
}

void NpcStartDialogMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  npcid = (unsigned int) serial.getInt32();
}

void NpcEndDialogMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt32(npcid);
}

void NpcEndDialogMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  npcid = (unsigned int) serial.getInt32();
}

void SetupDialogsMessage::serialise(ByteStream* bs)
{
  Serialiser serial(bs);
  serial.setInt8(type);
  serial.setInt8(id);
  serial.setInt8(deleteexisting?1:0);
  serial.setInt8(dialogscount);
  for ( size_t i = 0; i < dialogscount ; i++ )
  {
    serial.setInt32(dialogs[i].dialogid);
    serial.setString(dialogs[i].action);
    serial.setString(dialogs[i].value);
    serial.setInt8(dialogs[i].isstartdialog?1:0);
  };


  serial.setInt8(answerscount);
  for ( size_t i = 0; i < answerscount ; i++ )
  {
    serial.setInt32(answers[i].answerdialogid);
    serial.setInt32(answers[i].answerid);
    serial.setString(answers[i].answertext);
    serial.setInt32(answers[i].answerlink);
    serial.setInt8(answers[i].isendanswer?1:0);
  };

}

void SetupDialogsMessage::deserialise(ByteStream* bs)
{
  Deserialiser serial(bs);
  type = serial.getInt8();
  id = serial.getInt8();
  deleteexisting = serial.getInt8() != 0;
  dialogscount = (unsigned char) serial.getInt8();
  setDialogsCount(dialogscount);
  for ( size_t i = 0; i < dialogscount ; i++ )
  {
    dialogs[i].dialogid = (unsigned int) serial.getInt32();
    dialogs[i].action = serial.getString();
    serial.getString(dialogs[i].value);
    dialogs[i].isstartdialog = serial.getInt8() != 0;
  };


  answerscount = (unsigned char) serial.getInt8();
  setAnswersCount(answerscount);
  for ( size_t i = 0; i < answerscount ; i++ )
  {
    answers[i].answerdialogid = (unsigned int) serial.getInt32();
    answers[i].answerid = (unsigned int) serial.getInt32();
    serial.getString(answers[i].answertext);
    answers[i].answerlink = (unsigned int) serial.getInt32();
    answers[i].isendanswer = serial.getInt8() != 0;
  };

}
