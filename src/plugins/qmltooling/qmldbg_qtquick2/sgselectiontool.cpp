/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "sgselectiontool.h"

#include "sghighlight.h"
#include "sgviewinspector.h"

#include <QtGui/QMouseEvent>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

namespace QmlJSDebugger {
namespace QtQuick2 {

SGSelectionTool::SGSelectionTool(SGViewInspector *inspector) :
    AbstractTool(inspector),
    m_hoverHighlight(new SGHoverHighlight(inspector->overlay()))
{
}

void SGSelectionTool::leaveEvent(QEvent *)
{
    m_hoverHighlight->setVisible(false);
}

void SGSelectionTool::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (QQuickItem *item = inspector()->topVisibleItemAt(event->pos()))
            inspector()->setSelectedItems(QList<QQuickItem*>() << item);
    } else if (event->button() == Qt::RightButton) {
        // todo: Show context menu
    }
}

void SGSelectionTool::hoverMoveEvent(QMouseEvent *event)
{
    QQuickItem *item = inspector()->topVisibleItemAt(event->pos());
    if (!item) {
        m_hoverHighlight->setVisible(false);
    } else {
        m_hoverHighlight->setItem(item);
        m_hoverHighlight->setVisible(true);
    }
}

SGViewInspector *SGSelectionTool::inspector() const
{
    return static_cast<SGViewInspector*>(AbstractTool::inspector());
}

} // namespace QtQuick2
} // namespace QmlJSDebugger
