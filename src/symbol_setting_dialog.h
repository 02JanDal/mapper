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


#ifndef _OPENORIENTEERING_SYMBOL_SETTING_DIALOG_H_
#define _OPENORIENTEERING_SYMBOL_SETTING_DIALOG_H_

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTextEdit;
class QCheckBox;
QT_END_NAMESPACE

class Map;
class Symbol;
class MainWindow;
class PointSymbol;
class PointSymbolEditorWidget;

class SymbolSettingDialog : public QDialog
{
Q_OBJECT
public:
	SymbolSettingDialog(Symbol* symbol, Map* map, QWidget* parent);
	
	void updatePreview();
	
protected slots:
	void numberChanged(QString text);
	void nameChanged(QString text);
	void descriptionChanged();
	void helperSymbolClicked(bool checked);
	
private:
	//void createPreviewMap();
	//void createPointSymbolEditor(PointSymbol* point);
	PointSymbolEditorWidget* createPointSymbolEditor();
	
	void updateNumberEdits();
	void updateOkButton();
	void updateWindowTitle();
	
	Symbol* symbol;
	
	QLineEdit** number_edit;
	QLineEdit* name_edit;
	QTextEdit* description_edit;
	QCheckBox* helper_symbol_check;
	
	MainWindow* preview_widget;
	Map* preview_map;
	
	QPushButton* ok_button;
};

#endif
