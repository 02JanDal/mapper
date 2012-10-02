/*
 *    Copyright 2012 Thomas Schöps
 *
 *    This file is part of OpenOrienteering.
 *
 *    OpenOrienteering is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    OpenOrienteering is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with OpenOrienteering.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "global.h"

#include <mapper_config.h>

#include "file_format_native.h"
#include "file_format_ocad8.h"
#include "file_format_xml.h"
#include "tool.h"

void doStaticInitializations()
{
	// Register the supported file formats
	FileFormats.registerFormat(new NativeFileFormat());
#ifdef Mapper_XML_FORMAT
	FileFormats.registerFormat(new XMLFileFormat());
#endif
	FileFormats.registerFormat(new OCAD8FileFormat());
	
	// Load resources
	MapEditorTool::loadPointHandles();
}
