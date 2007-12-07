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

#ifndef _QUESTMESSAGES_H_
#define _QUESTMESSAGES_H_

#include "netmessage.h"

namespace QUEST
{
  enum MESSAGES
  {
    NPCDIALOG=0,
    NPCDIALOGANSWER=1,
    NPCSTARTDIALOG=2,
    NPCENDDIALOG=3,
    SETUPDIALOGS=4
  };
}

class NpcDialogMessage : public NetMessage
{
  unsigned int dialogid;
  const char* dialogtext;
  class ListAnswers
  {
  public:
    unsigned int answerid;
    const char* answertext;
  };

  unsigned char answerscount;
  ListAnswers* answers;


public:
  NpcDialogMessage() : NetMessage(MESSAGES::QUEST,QUEST::NPCDIALOG)
  {
    answers = 0;
  }

  ~NpcDialogMessage()
  {
    delete [] answers;
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDialogId() { return dialogid; }
  void setDialogId(unsigned int x) { dialogid = x; }

  const char* getDialogText() { return dialogtext; }
  void setDialogText(const char* x) { dialogtext = x; }

  unsigned char getAnswersCount() { return answerscount; }
  void setAnswersCount(unsigned char ic)
  {
    answerscount = ic;
    delete [] answers;
    answers = new ListAnswers[ic];
  }

  // --- begin ListAnswers Getter and Setter ---

  unsigned int getAnswerId(size_t i) { return answers[i].answerid; }
  void setAnswerId(size_t i, unsigned int x) { answers[i].answerid = x; }

  const char* getAnswerText(size_t i) { return answers[i].answertext; }
  void setAnswerText(size_t i, const char* x) { answers[i].answertext = x; }

  // --- end ListAnswers Getter and Setter ---

};

class NpcDialogAnswerMessage : public NetMessage
{
  unsigned int dialogid;
  unsigned int answerid;

public:
  NpcDialogAnswerMessage() : NetMessage(MESSAGES::QUEST,QUEST::NPCDIALOGANSWER)
  {
  }

  ~NpcDialogAnswerMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getDialogId() { return dialogid; }
  void setDialogId(unsigned int x) { dialogid = x; }

  unsigned int getAnswerId() { return answerid; }
  void setAnswerId(unsigned int x) { answerid = x; }

};

class NpcStartDialogMessage : public NetMessage
{
  unsigned int npcid;

public:
  NpcStartDialogMessage() : NetMessage(MESSAGES::QUEST,QUEST::NPCSTARTDIALOG)
  {
  }

  ~NpcStartDialogMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getNpcId() { return npcid; }
  void setNpcId(unsigned int x) { npcid = x; }

};

class NpcEndDialogMessage : public NetMessage
{
  unsigned int npcid;

public:
  NpcEndDialogMessage() : NetMessage(MESSAGES::QUEST,QUEST::NPCENDDIALOG)
  {
  }

  ~NpcEndDialogMessage()
  {
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  unsigned int getNpcId() { return npcid; }
  void setNpcId(unsigned int x) { npcid = x; }

};

class SetupDialogsMessage : public NetMessage
{
  bool deleteexisting;
  class ListDialogs
  {
  public:
    unsigned int dialogid;
    ptString action;
    const char* value;
    bool isstartdialog;
  };

  unsigned char dialogscount;
  ListDialogs* dialogs;

  class ListAnswers
  {
  public:
    unsigned int answerdialogid;
    unsigned int answerid;
    const char* answertext;
    unsigned int answerlink;
    bool isendanswer;
  };

  unsigned char answerscount;
  ListAnswers* answers;


public:
  SetupDialogsMessage() : NetMessage(MESSAGES::QUEST,QUEST::SETUPDIALOGS)
  {
    dialogs = 0;
    answers = 0;
  }

  ~SetupDialogsMessage()
  {
    delete [] dialogs;
    delete [] answers;
  }

  void serialise(ByteStream* bs);
  void deserialise(ByteStream* bs);

  bool getDeleteExisting() { return deleteexisting; }
  void setDeleteExisting(bool x) { deleteexisting = x; }

  unsigned char getDialogsCount() { return dialogscount; }
  void setDialogsCount(unsigned char ic)
  {
    dialogscount = ic;
    delete [] dialogs;
    dialogs = new ListDialogs[ic];
  }

  // --- begin ListDialogs Getter and Setter ---

  unsigned int getDialogId(size_t i) { return dialogs[i].dialogid; }
  void setDialogId(size_t i, unsigned int x) { dialogs[i].dialogid = x; }

  ptString getAction(size_t i) { return dialogs[i].action; }
  void setAction(size_t i, ptString x) { dialogs[i].action = x; }

  const char* getValue(size_t i) { return dialogs[i].value; }
  void setValue(size_t i, const char* x) { dialogs[i].value = x; }

  bool getIsStartDialog(size_t i) { return dialogs[i].isstartdialog; }
  void setIsStartDialog(size_t i, bool x) { dialogs[i].isstartdialog = x; }

  // --- end ListDialogs Getter and Setter ---

  unsigned char getAnswersCount() { return answerscount; }
  void setAnswersCount(unsigned char ic)
  {
    answerscount = ic;
    delete [] answers;
    answers = new ListAnswers[ic];
  }

  // --- begin ListAnswers Getter and Setter ---

  unsigned int getAnswerDialogId(size_t i) { return answers[i].answerdialogid; }
  void setAnswerDialogId(size_t i, unsigned int x) { answers[i].answerdialogid = x; }

  unsigned int getAnswerId(size_t i) { return answers[i].answerid; }
  void setAnswerId(size_t i, unsigned int x) { answers[i].answerid = x; }

  const char* getAnswerText(size_t i) { return answers[i].answertext; }
  void setAnswerText(size_t i, const char* x) { answers[i].answertext = x; }

  unsigned int getAnswerLink(size_t i) { return answers[i].answerlink; }
  void setAnswerLink(size_t i, unsigned int x) { answers[i].answerlink = x; }

  bool getIsEndAnswer(size_t i) { return answers[i].isendanswer; }
  void setIsEndAnswer(size_t i, bool x) { answers[i].isendanswer = x; }

  // --- end ListAnswers Getter and Setter ---

};

#endif // _QUESTMESSAGES_H_
