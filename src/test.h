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


#ifndef _OPENORIENTEERING_TEST_H_
#define _OPENORIENTEERING_TEST_H_

#include <QtTest/QtTest>

class Map;
class Format;

/// Ensures that maps contain the same information before and after saving them and loading them again.
class TestFileFormats : public QObject
{
Q_OBJECT
private slots:
	void saveAndLoad_data();
	void saveAndLoad();
	
private:
	Map* saveAndLoadMap(Map* input, const Format* format);
	bool compareMaps(Map* a, Map* b, QString& error);
};

/// Ensures that duplicates of symbols and objects are equal to their originals.
class TestDuplicateEqual : public QObject
{
Q_OBJECT
private slots:
	void symbols_data();
	void symbols();
	
	void objects_data();
	void objects();
};


#endif
