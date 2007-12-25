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

#include <cssysdef.h>

#include "client/reporter/reporter.h"
#include "client/pointer/pointer.h"
#include "datamanager.h"

namespace PT
{
  namespace Data
  {
    DataManager::DataManager()
    {
      PointerLibrary* ptrlib = PointerLibrary::getInstance();
      oreg = ptrlib->getObjectRegistry();

      vfs = csQueryRegistry<iVFS> (oreg);
      if (!vfs) Report(PT::Error, "Failed to locate VFS!");
    }

    DataManager::~DataManager()
    {
    }

    bool DataManager::parse()
    {
      csRef<iDataBuffer> xmlfile = vfs->ReadFile (file.c_str());
      if (!xmlfile)
      {
        return Report(PT::Error, "Can't load file '%s'!", file.c_str());
      }

      csRef<iDocumentSystem> docsys (csQueryRegistry<iDocumentSystem> (oreg));

      csRef<iDocument> doc (docsys->CreateDocument());

      const char* error = doc->Parse (xmlfile, true);
      if (error)
      {
        Report(PT::Error, error);
        return false;
      }

      csRef<iDocumentNode> effectsXML = doc->GetRoot ()->GetNode (getRootName());

      if (!effectsXML.IsValid())
        return false;

      csRef<iDocumentNodeIterator> it (effectsXML->GetNodes (getElementName()));

      while (it->HasNext())
      {
        csRef<iDocumentNode> node (it->Next());
        if (!parseElement(node))
          return false;
      }
      return true;
    }
  } // Data namespace
} // PT namespace