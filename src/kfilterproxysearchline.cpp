/*
    SPDX-FileCopyrightText: 2007-2008 Omat Holding B.V. <info@omat.nl>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kfilterproxysearchline.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QTimer>

#if KITEMVIEWS_BUILD_DEPRECATED_SINCE(5, 50)

/**
 * KFilterProxySearchLinePrivate class that helps to provide binary compatibility between releases.
 * @internal
 */
//@cond PRIVATE
class KFilterProxySearchLinePrivate
{
public:
    KFilterProxySearchLinePrivate(KFilterProxySearchLine *parent)
        : q(parent)
    {
        timer = new QTimer(q);
        timer->setSingleShot(true);
        QObject::connect(timer, SIGNAL(timeout()), q, SLOT(slotSearchLineActivate()));
    }
    QTimer *timer;
    KFilterProxySearchLine *const q;
    QSortFilterProxyModel *proxy = nullptr;
    QLineEdit *searchLine = nullptr;

    void slotSearchLineChange(const QString &newText);
    void slotSearchLineActivate();
};

void KFilterProxySearchLinePrivate::slotSearchLineChange(const QString &)
{
    timer->start(300);
}

void KFilterProxySearchLinePrivate::slotSearchLineActivate()
{
    if (!proxy) {
        return;
    }

    proxy->setFilterKeyColumn(-1);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterFixedString(searchLine->text());
}
//@endcond

KFilterProxySearchLine::KFilterProxySearchLine(QWidget *parent)
    : QWidget(parent)
    , d(new KFilterProxySearchLinePrivate(this))
{
    d->searchLine = new QLineEdit(this);
    d->searchLine->setClearButtonEnabled(true);
    d->searchLine->setPlaceholderText(tr("Search...", "@info:placeholder"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->searchLine);

    connect(d->searchLine, SIGNAL(textChanged(QString)), SLOT(slotSearchLineChange(QString)));
}

KFilterProxySearchLine::~KFilterProxySearchLine() = default;

void KFilterProxySearchLine::setText(const QString &text)
{
    d->searchLine->setText(text);
    d->slotSearchLineActivate();
}

void KFilterProxySearchLine::setProxy(QSortFilterProxyModel *proxy)
{
    d->proxy = proxy;
}

QLineEdit *KFilterProxySearchLine::lineEdit() const
{
    return d->searchLine;
}

#include "moc_kfilterproxysearchline.cpp"

#endif
