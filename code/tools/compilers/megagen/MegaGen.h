/*
===========================================================================

IcedTech GPL Source Code

Copyright (C) 2019 Real Vector Math Studios(Justin Marshall).
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 

This file is part of the IcedTech GPL Source Code ("IcedTech GPL Source Code").  

IcedTech GPL Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IcedTech GPL Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IcedTech GPL Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the IcedTech GPL Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the IcedTech GPL Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#pragma once

//
// MegaLayerImage_t
//
struct MegaLayerImage_t {
	MegaLayerImage_t()
	{
		width = -1;
		height = -1;
		data = nullptr;
	}
	
	~MegaLayerImage_t()
	{
		if (data != nullptr)
		{
			Mem_Free(data);
			data = nullptr;
		}
	}

	int width;
	int height;
	byte *data;
};

//
// MegaLayer
//
struct MegaLayer {
	MegaLayerImage_t albedoImage;
	MegaLayerImage_t maskImage;
};

//
// rvmMegaProject
//
class rvmMegaProject {
public:
	rvmMegaProject();
	~rvmMegaProject();

	// Parsers the project.
	bool ParseProject(idParser &parser);

	// Returns the megalayer given idx.
	MegaLayer *GetMegaLayer(int idx) { return megaLayers[idx]; }

	// Returns the number of mega layers in the project.
	int GetNumMegaLayers(void) const { return megaLayers.Num(); }
private:
	// Parses each layer.
	bool ParseLayer(MegaLayer *layer, idStr &layerStr);

private:
	idList<MegaLayer *>	megaLayers;
};

void R_LoadTGA(const char *name, byte **pic, int *width, int *height, ID_TIME_T *timestamp);
