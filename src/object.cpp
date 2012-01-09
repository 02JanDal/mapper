/*
 *    Copyright 2011 Thomas Schöps
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


#include "object.h"

#include "symbol.h"
#include "symbol_point.h"
#include "util.h"

Object::Object(Map* map, Object::Type type, Symbol* symbol) : type(type), symbol(symbol), map(map)
{
	output_dirty = true;
	path_closed = false;
	extent = QRectF();
}
Object::~Object()
{
	int size = (int)output.size();
	for (int i = 0; i < size; ++i)
		delete output[i];
}

bool Object::update(bool force)
{
	if (!force && !output_dirty)
		return false;
	
	bool had_output_before = !output.empty();
	clearOutput();
	if (map && had_output_before)
		map->removeRenderablesOfObject(this, false);
	
	// Calculate float coordinates
	MapCoordVectorF coordsF;
	int size = coords.size();
	coordsF.resize(size);
	for (int i = 0; i < size; ++i)
		coordsF[i] = MapCoordF(coords[i].xd(), coords[i].yd());
	
	// Create renderables
	symbol->createRenderables(this, coordsF, output);
	
	// Calculate extent and set this object as creator of the renderables
	RenderableVector::const_iterator end = output.end();
	RenderableVector::const_iterator it = output.begin();
	if (it != end)
	{
		(*it)->setCreator(this);
		extent = (*it)->getExtent();
		assert(extent.right() < 999999);	// assert if bogus values are returned
		for (++it; it != end; ++it)
		{
			(*it)->setCreator(this);
			rectInclude(extent, (*it)->getExtent());
			assert(extent.right() < 999999);	// assert if bogus values are returned
		}
	}
	else
		extent = QRectF();
	
	output_dirty = false;
	
	if (map)
		map->insertRenderablesOfObject(this);
	
	if (extent.isValid())
		map->setObjectAreaDirty(extent);
	
	return true;
}
void Object::clearOutput()
{
	if (extent.isValid())
		map->setObjectAreaDirty(extent);
	
	int size = output.size();
	for (int i = 0; i < size; ++i)
		delete output[i];
	
	output.clear();
	output_dirty = true;
}

bool Object::setSymbol(Symbol* new_symbol)
{
	if (new_symbol && symbol)
	{
		if ((new_symbol->getType() == Symbol::Point || symbol->getType() == Symbol::Point) && !(new_symbol->getType() == Symbol::Point && symbol->getType() == Symbol::Point))
			return false;	// Changing something from or to point is not allowed
		if ((new_symbol->getType() == Symbol::Text || symbol->getType() == Symbol::Text) && !(new_symbol->getType() == Symbol::Text && symbol->getType() == Symbol::Text))
			return false;	// Changing something from or to text is not allowed
	}
	
	symbol = new_symbol;
	setOutputDirty();
	return true;
}

// ### PathObject ###

PathObject::PathObject(Map* map, Symbol* symbol) : Object(map, Object::Path, symbol)
{
	assert(!symbol || (symbol->getType() == Symbol::Line || symbol->getType() == Symbol::Area || symbol->getType() == Symbol::Combined));
}

// ### PointObject ###

PointObject::PointObject(Map* map, MapCoord position, Symbol* symbol) : Object(map, Object::Point, symbol)
{
	assert(!symbol || (symbol->getType() == Symbol::Point));
	rotation = 0;
	coords.push_back(position);
}
void PointObject::setPosition(MapCoord position)
{
	coords[0] = position;
	setOutputDirty();
}
MapCoord PointObject::getPosition()
{
	return coords[0];
}
void PointObject::setRotation(float new_rotation)
{
	PointSymbol* point = reinterpret_cast<PointSymbol*>(symbol);
	assert(point && point->isRotatable());
	
	rotation = new_rotation;
}
