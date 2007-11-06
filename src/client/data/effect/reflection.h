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

#ifndef REFLECTION_H
#define REFLECTION_H

#include <cssysdef.h>
#include <csutil/ref.h>
#include <csutil/refarr.h>
#include <csutil/parray.h>
#include <csutil/csbaseeventh.h>
#include <cstool/csapplicationframework.h>
#include <iengine/engine.h>
#include <iengine/camera.h>
#include <iutil/vfs.h>
#include <iutil/pluginconfig.h>
#include <iutil/virtclk.h>
#include <ivideo/graph3d.h>
#include <iengine/mesh.h>
#include <ivaria/view.h>

namespace PT
{
  namespace Reflection
  {
    class ReflectionUtils
    {
    friend class ReflectionRenderer;
    public:
      /**
       * Connects a ReflectionRenderer callback to any mesh that defines the
       * shader variable 'reflection_enable=(INT)1'. The callback produces up
       * to six reflection buffers, creating a cube map around the mesh object
       * using it's bounding box.
       * 
       * Here's the basic idea as ASCII art:
       *
       *<pre>
                    /<-- actual camera
                   .
               +--------------------------+  <-- reflective surface
               |   .                      |
               |    \<-- reflection cam   |
               |                          | <-- world bounding box
               |                          |
               +--------------------------+
       </pre>
       *
       * The sides of the cube are drawn if the particualar side is specified
       * in the 'reflection_sides' shader variable. This variable is an array
       * of integers. There should be up to six items in this array, with a
       * value of 1 (one) if the side is reflective, 0 (zero) otherwise. The
       * mapping of array indices to world space is shown below.
       *
       *<pre>
                     max-Z
                      [4]
                       \
                        \
               +-----------------+
               |\                 \
               | \                 \
               |  \                 \
               |   \      max-Y      \
               |    \       [0]       \    
               |     \                 \
               |      \                 \-- max-X
               |       \                 \   [2]
               + min-x  \                 \
               \  [3]    +-----------------+
                \        |                 |
                 \       |                 |
                  \      |                 |
                   \     |     min-z       |
                    \    |      [5]        |
                     \   |                 |
                      \  |                 |
                       \ |                 |
                        \+-----------------+
                                  \
                                   \
                                  min-y
                                   [1]
       </pre>
       *
       * This function creates a set of shader variables attached to the mesh
       * called 'reflection_texture_x', that holds up to 6 textures x=[0-5],
       * the sides specified in 'reflection_sides'. NOTE: Only the [0] index
       * reflection_texture_0 the max-Y plane is currently supported!
       */
      static void ApplyReflection(csRef<iView>, csRef<iObjectRegistry>);

      /**
       * Render all reflections previously applied via ApplyReflection(),
       * to their cubemaps.
       */
      static void RenderReflections(csRef<iView> view);

      /**
       * Configure the RenderReflections function to skip some number of
       * frames, since it is an expensive operation.
       * @param skip The number of frames to skip. For example, a value of
       * '2' means draw reflections on every other frame or 1/2 frames.
       */
      static void SetFrameSkip(size_t skip);

    private:
      static inline void Render2Texture(
	csRef<iView>& view,
        iGraphics3D*& g3d,
        iCamera*& cam,
        iMeshWrapper*& m,
        csOrthoTransform& oldcamera,
        csOrthoTransform& newcamera,
        csPlane3& nearclip,
        iTextureHandle*& texture,
        bool mirror
      );
      static size_t frame, frameskip;
      static csArray<iMeshWrapper*> reflective_meshes, refractive_meshes;
      static csStringID reflection_resolution_str, reflection_enable_str;
      static csStringID reflection_sides_str, reflection_texture0_str;
      static csStringID refraction_enable_str, refraction_texture_str;
    };

  } // Reflection namespace

} // PT namespace

#endif // REFLECTION_H