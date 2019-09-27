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

#include "precompiled.h"

#include "MegaGen.h"

/*
======================
rvmMegaProject::rvmMegaProject
======================
*/
rvmMegaProject::rvmMegaProject()
{

}

/*
======================
rvmMegaProject::~rvmMegaProject
======================
*/
rvmMegaProject::~rvmMegaProject()
{
	for (int i = 0; i < megaLayers.Num(); i++)
	{
		delete megaLayers[i];
	}
	megaLayers.Clear();
}

/*
======================
rvmMegaProject::ParseLayer
======================
*/
bool rvmMegaProject::ParseLayer(MegaLayer *layer, idStr &layerStr) {
	idParser parser;
	idToken token;

	if (!parser.LoadMemory(layerStr, layerStr.Size(), "MegaLayer"))
		return false;

	parser.SetFlags(DECL_LEXER_FLAGS);

	if (!parser.ExpectTokenString("{")) {
		common->Warning("MegaLayer expected opening {");
		return false;
	}

	// Parse until EOF
	while (true)
	{
		if (parser.EndOfFile())
		{
			common->Warning("Unexpected EOF in MegaLayer!");
			return false;
		}

		parser.ReadToken(&token);

		if (token == "}")
		{
			break;
		}

		// Load in the albedo image for this layer.
		if (token == "albedo")
		{
			parser.ReadToken(&token);
			R_LoadTGA(token, &layer->albedoImage.data, &layer->albedoImage.width, &layer->albedoImage.height, nullptr);
			if (layer->albedoImage.data == NULL)
			{
				common->Warning("Failed to load albedo image %s\n", token.c_str());
				return false;
			}
		}
		else if (token == "mask")
		{
			parser.ReadToken(&token);
			R_LoadTGA(token, &layer->maskImage.data, &layer->maskImage.width, &layer->maskImage.height, nullptr);
			if (layer->maskImage.data == NULL)
			{
				common->Warning("Failed to load albedo image %s\n", token.c_str());
				return false;
			}
		}
		else
		{
			common->Warning("While parsing layer, unknown token %s\n", token.c_str());
			return false;
		}
	}

	return true;
}

/*
======================
rvmMegaProject::ParseProject
======================
*/
bool rvmMegaProject::ParseProject(idParser &parser) {
	int numLayers;

	// Check how many layers we have.
	if (!parser.ExpectTokenString("numlayers"))
	{
		parser.Warning("Expected numlayers token");
		return false;
	}
	numLayers = parser.ParseInt();

	// Parse the layers.
	for (int i = 0; i < numLayers; i++)
	{
		MegaLayer *megaLayer = new MegaLayer();
		idStr layerStr;

		// Check the layer name.
		if (!parser.ExpectTokenString(va("layer_%d", i)))
		{
			parser.Warning("Layer name invalid or unexpected token!");
			return false;
		}

		// Extract the text in the braced section.
		parser.ParseBracedSectionExact(layerStr);

		// Parse the layer.
		if (!ParseLayer(megaLayer, layerStr))
		{
			parser.Warning("Failed to parse megalayer");
			return false;
		}

		// Add the layer to the list.
		megaLayers.Append(megaLayer);
	}

	return true;
}