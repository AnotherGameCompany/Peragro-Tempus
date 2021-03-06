/*
    Copyright (C) 2009 Development Team of Peragro Tempus

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
/**
 * @file resourcemanager.h
 *
 * @basic Manages the game objects.
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <cssysdef.h>
#include <csutil/ref.h>

#include <wfmath/axisbox.h>

#include <string>
#include <map>
#include "common/world/world.h"

struct iObjectRegistry;
struct iVFS;
struct iDocumentNode;

class ResourceManager
{
private:
  iObjectRegistry* object_reg;
  Common::World::WorldManager* worldManager;

  csRef<iVFS> vfs;

   /// Handles reporting warnings and errors.
  void Report(int severity, const char* msg, ...);

private:
  std::vector<Common::World::Factory> FindMeshFacts(const std::string& file, bool returnAll = false);
  std::vector<Common::World::Object> FindMeshObjects(const std::string& file);
  WFMath::AxisBox<3> GetBB(iDocumentNode* node);

public:
  /// Constructor.
  ResourceManager(iObjectRegistry* object_reg, Common::World::WorldManager* worldManager);
  /// Destructor.
  ~ResourceManager();

  bool Initialize();

  void ScanFactories(const std::string& path);

  void ScanObjects(const std::string& path);

  void AddTestObjects();
};


#endif //RESOURCEMANAGER_H
