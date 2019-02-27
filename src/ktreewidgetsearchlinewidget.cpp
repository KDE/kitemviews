/* This file is part of the KDE libraries
   Copyright (c) 2003 Scott Wheeler <wheeler@kde.org>
   Copyright (c) 2005 Rafal Rzepecki <divide@users.sourceforge.net>
   Copyright (c) 2006 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "ktreewidgetsearchlinewidget.h"
#include "ktreewidgetsearchline.h"

#include <QHBoxLayout>
#include <QTreeWidget>

class Q_DECL_HIDDEN KTreeWidgetSearchLineWidget::Private
{
public:
    Private()
        : treeWidget(nullptr),
          searchLine(nullptr)
    {
    }

    QTreeWidget *treeWidget;
    KTreeWidgetSearchLine *searchLine;
};

KTreeWidgetSearchLineWidget::KTreeWidgetSearchLineWidget(QWidget *parent, QTreeWidget *treeWidget)
    : QWidget(parent), d(new Private)
{
    d->treeWidget = treeWidget;

    // can't call createWidgets directly because it calls virtual functions
    // that might not work if called directly from here due to how inheritance works
    QMetaObject::invokeMethod(this, "createWidgets", Qt::QueuedConnection);
}

KTreeWidgetSearchLineWidget::~KTreeWidgetSearchLineWidget()
{
    delete d;
}

KTreeWidgetSearchLine *KTreeWidgetSearchLineWidget::createSearchLine(QTreeWidget *treeWidget) const
{
    return new KTreeWidgetSearchLine(const_cast<KTreeWidgetSearchLineWidget *>(this), treeWidget);
}

void KTreeWidgetSearchLineWidget::createWidgets()
{
    searchLine()->show();

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->searchLine);
    setFocusProxy(searchLine());
}

KTreeWidgetSearchLine *KTreeWidgetSearchLineWidget::searchLine() const
{
    if (!d->searchLine) {
        d->searchLine = createSearchLine(d->treeWidget);
    }

    return d->searchLine;
}
