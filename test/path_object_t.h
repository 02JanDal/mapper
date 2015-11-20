/*
 *    Copyright 2013 Thomas Schöps
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


#ifndef _OPENORIENTEERING_PATH_OBJECT_T_H
#define _OPENORIENTEERING_PATH_OBJECT_T_H

#include <QtTest/QtTest>

#include "../src/object.h"


/**
 * Tests PathObject. Still very incomplete (TODO).
 */
class PathObjectTest : public QObject
{
Q_OBJECT
public:
	/** Constructor */
	explicit PathObjectTest(QObject* parent = NULL);
	
private slots:
	void initTestCase();
	
	/** Tests finding intersections with calcAllIntersectionsWith(). */
	void calcIntersectionsTest();
	void calcIntersectionsTest_data();
	
};

#endif
