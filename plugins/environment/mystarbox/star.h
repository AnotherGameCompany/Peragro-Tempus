/*
    Copyright (C) 2008 by Mogue Carpenter

    This file is part of mystarbox plugin for crystalspace.

    mystarbox is free software; you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    mystarbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with mystarbox; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 * star.h
 *
 * A this class holds the stars information
 *
 */

#ifndef __STARBOX_SYSTEM_STAR_H
#define __STARBOX_SYSTEM_STAR_H

#include <cssysdef.h>
#include <crystalspace.h>

#include <string>
#include <cstdlib>

class System;

// --------------------------------------------------------------------------------//
// Star, stores all the information about a star
// --------------------------------------------------------------------------------//
class Star {

	private:
		std::string name;
		std::string classification;
		float luminosity ;
		System* system;

		float mass ;
		int starcolor;

	public:  

		//Functions 
		Star (   std::string star_name, 
					std::string new_classification,
					float new_luminosity,
					int color,
					System* parent_system ) ;

		~Star();

		std::string Get_Name () { return ( name ); } ;

		float Get_Luminosity () { return (luminosity ); } ;
		float Get_Mass () { return ( mass ); };
		float Get_Color () { return ( starcolor ); };

};

#endif