/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/
#include "qg_dlgcircle.h"


#include "rs_circle.h"
#include "rs_graphic.h"
#include "rs_math.h"
//#include "rs_debug.h"

/*
 *  Constructs a QG_DlgCircle as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
QG_DlgCircle::QG_DlgCircle(QWidget* parent, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setModal(modal);
    setupUi(this);

}

/*
 *  Destroys the object and frees any allocated resources
 */
QG_DlgCircle::~QG_DlgCircle()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void QG_DlgCircle::languageChange()
{
    retranslateUi(this);
}

void QG_DlgCircle::setCircle(RS_Circle& c) {
    circle = &c;

    RS_Graphic* graphic = circle->getGraphic();
    if (graphic) {
        cbLayer->init(*(graphic->getLayerList()), false, false);
    }
    RS_Layer* lay = circle->getLayer(false);
    if (lay) {
        cbLayer->setLayer(*lay);
    }

    wPen->setPen(circle->getPen(false), lay, "Pen");
    QString s;
    s.setNum(circle->getCenter().x);
    leCenterX->setText(s);
    s.setNum(circle->getCenter().y);
    leCenterY->setText(s);
    s.setNum(circle->getRadius());
//	RS_DEBUG->print(RS_Debug::D_ERROR,"QG_DlgCircle::setCircle, leRadius->setText '%s'",qPrintable(s));
    leRadius->setText(s);
}

void QG_DlgCircle::updateCircle() {
    circle->setCenter(RS_Vector(RS_Math::eval(leCenterX->text()),
                                  RS_Math::eval(leCenterY->text())));
//	RS_DEBUG->print(RS_Debug::D_ERROR,"QG_DlgCircle::updateCircle, setRadius '%s'",qPrintable(leRadius->text()));
    circle->setRadius(RS_Math::eval(leRadius->text()));
    circle->setPen(wPen->getPen());
    circle->setLayer(cbLayer->currentText());
    circle->calculateBorders();
}

