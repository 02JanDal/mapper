/*
 *    Copyright 2014 Kai Pastor
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

#ifndef _OPENORIENTEERING_MAP_PART_UNDO_H_
#define _OPENORIENTEERING_MAP_PART_UNDO_H_

#include "undo.h"

class MapPart;

/**
 * @brief A map part undo step handles addition, deletion and renaming of map parts.
 */
class MapPartUndoStep : public UndoStep
{
public:
	/**
	 * Types of map part changes.
	 */
	enum MapPartChange
	{
		AddMapPart      = 1,
		RemoveMapPart   = 2,
		ModifyMapPart   = 3,
		UndefinedChange = 0
	};
	
	/**
	 * Constructs a particular undo step for the given part.
	 */
	MapPartUndoStep(Map* map, MapPartChange change, const MapPart* part);
	
	/**
	 * Constructs a particular undo step for the part specified by index.
	 */
	MapPartUndoStep(Map* map, MapPartChange change, int index);
	
	/**
	 * Constructs an incomplete undo step of type UndefinedChange.
	 * 
	 * This is to be used with loadImpl().
	 */
	MapPartUndoStep(Map* map);
	
	virtual ~MapPartUndoStep();
	
	/**
	 * Returns true unless this step's type is UndefinedChange.
	 */
	virtual bool isValid() const;
	
	virtual UndoStep* undo();

	virtual bool getModifiedParts(PartSet& out) const;
	
	virtual void getModifiedObjects(int part_index, ObjectSet& out) const;
	
	/**
	 * Not implemented.
	 * 
	 * @deprecated Legacy file format.
	 */
	virtual bool load(QIODevice* file, int version);
	
protected:
	virtual void saveImpl(QXmlStreamWriter& xml) const;
	
	virtual void loadImpl(QXmlStreamReader& xml, SymbolDictionary& symbol_dict);
	
	MapPartChange change;
	
	int index;
	
	QString name;
};

#endif // MAP_PART_UNDO_H
