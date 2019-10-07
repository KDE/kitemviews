/**
  * This file is part of the KDE project
  * Copyright 2019 David Redondo <kde@david-redondo.de>
  * Copyright (C) 2007, 2009 Rafael Fernández López <ereslibre@kde.org>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Library General Public
  * License as published by the Free Software Foundation; either
  * version 2 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Library General Public License for more details.
  *
  * You should have received a copy of the GNU Library General Public License
  * along with this library; see the file COPYING.LIB.  If not, write to
  * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  * Boston, MA 02110-1301, USA.
  */

#include "kcategorydrawer.h"

#include <QPainter>
#include <QStyleOption>
#include <QApplication>

#include <kcategorizedview.h>
#include <kcategorizedsortfilterproxymodel.h>

class KCategoryDrawerPrivate
{
public:
    KCategoryDrawerPrivate(KCategorizedView *view)
        : view(view)
    {
    }

    ~KCategoryDrawerPrivate()
    {
    }

    KCategorizedView *view;
};

KCategoryDrawer::KCategoryDrawer(KCategorizedView *view)
    : QObject(view)
    , d(new KCategoryDrawerPrivate(view))
{
}

KCategoryDrawer::~KCategoryDrawer()
{
    delete d;
}

void KCategoryDrawer::drawCategory(const QModelIndex &index,
                                   int /*sortRole*/,
                                   const QStyleOption &option,
                                   QPainter *painter) const
{
    // Keep this in sync with Kirigami.ListSectionHeader
    painter->setRenderHint(QPainter::Antialiasing);

    const QString category = index.model()->data(index, KCategorizedSortFilterProxyModel::CategoryDisplayRole).toString();
    const QRect optRect = option.rect;
    QFont font(QApplication::font());
    // Match Heading with level 3
    font.setPointSizeF(font.pointSize() * 1.20);
    const QFontMetrics fontMetrics = QFontMetrics(font);

    QColor backgroundColor = option.palette.window().color();

    //BEGIN: background
    {
        QRect backgroundRect(option.rect);
        backgroundRect.setHeight(categoryHeight(index, option));
        painter->save();
        painter->setBrush(backgroundColor);
        painter->setPen(Qt::NoPen);
        painter->drawRect(backgroundRect);
        painter->restore();
    }
    //END: background

    //BEGIN: text
    {
        //  Kirgami.Units.{small/large}Spacing respectively
        constexpr int topPadding = 4;
        constexpr int sidePadding = 8;
        QRect textRect(option.rect);
        textRect.setTop(textRect.top() + topPadding);
        textRect.setLeft(textRect.left() + sidePadding);
        textRect.setHeight(fontMetrics.height());
        textRect.setRight(textRect.right() - sidePadding);

        painter->save();
        painter->setFont(font);
        QColor penColor(option.palette.text().color());
        painter->setPen(penColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, category);
        painter->restore();
    }
    //END: text
}

int KCategoryDrawer::categoryHeight(const QModelIndex &index, const QStyleOption &option) const
{
    Q_UNUSED(index);
    Q_UNUSED(option)

    QFont font(QApplication::font());
    font.setPointSizeF(font.pointSize() * 1.20);
    QFontMetrics fontMetrics(font);

    const int height = fontMetrics.height() + 8;
    return height;
}

int KCategoryDrawer::leftMargin() const
{
    return 0;
}

int KCategoryDrawer::rightMargin() const
{
    return 0;
}

KCategorizedView *KCategoryDrawer::view() const
{
    return d->view;
}

void KCategoryDrawer::mouseButtonPressed(const QModelIndex &, const QRect &, QMouseEvent *event)
{
    event->ignore();
}

void KCategoryDrawer::mouseButtonReleased(const QModelIndex &, const QRect &, QMouseEvent *event)
{
    event->ignore();
}

void KCategoryDrawer::mouseMoved(const QModelIndex &, const QRect &, QMouseEvent *event)
{
    event->ignore();
}

void KCategoryDrawer::mouseButtonDoubleClicked(const QModelIndex &, const QRect &, QMouseEvent *event)
{
    event->ignore();
}

void KCategoryDrawer::mouseLeft(const QModelIndex &, const QRect &)
{
}

