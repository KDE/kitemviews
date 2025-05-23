/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2003 Scott Wheeler <wheeler@kde.org>
    SPDX-FileCopyrightText: 2005 Rafal Rzepecki <divide@users.sourceforge.net>
    SPDX-FileCopyrightText: 2006 Hamish Rodda <rodda@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KTREEWIDGETSEARCHLINE_H
#define KTREEWIDGETSEARCHLINE_H

#include <QLineEdit>
#include <kitemviews_export.h>
#include <memory>

class QModelIndex;
class QTreeWidget;
class QTreeWidgetItem;

/*!
 * \class KTreeWidgetSearchLine
 * \inmodule KItemViews
 *
 * \brief This class makes it easy to add a search line for filtering the items in
 * listviews based on a simple text search.
 *
 * No changes to the application other than instantiating this class with
 * appropriate QTreeWidgets should be needed.
 */
class KITEMVIEWS_EXPORT KTreeWidgetSearchLine : public QLineEdit
{
    Q_OBJECT

    /*!
     * \property KTreeWidgetSearchLine::caseSensitity
     */
    Q_PROPERTY(Qt::CaseSensitivity caseSensitity READ caseSensitivity WRITE setCaseSensitivity NOTIFY caseSensitivityChanged)

    /*!
     * \property KTreeWidgetSearchLine::keepParentsVisible
     */
    Q_PROPERTY(bool keepParentsVisible READ keepParentsVisible WRITE setKeepParentsVisible NOTIFY keepParentsVisibleChanged)

public:
    /*!
     * Constructs a KTreeWidgetSearchLine with \a treeWidget being the QTreeWidget to
     * be filtered.
     *
     * If \a treeWidget is null then the widget will be disabled until listviews
     * are set with setTreeWidget(), setTreeWidgets() or added with addTreeWidget().
     */
    explicit KTreeWidgetSearchLine(QWidget *parent = nullptr, QTreeWidget *treeWidget = nullptr);

    /*!
     * Constructs a KTreeWidgetSearchLine with \a treeWidgets being the list of
     * pointers to QTreeWidgets to be filtered.
     *
     * If \a treeWidgets is empty then the widget will be disabled until listviews
     * are set with setTreeWidget(), setTreeWidgets() or added with addTreeWidget().
     */
    KTreeWidgetSearchLine(QWidget *parent, const QList<QTreeWidget *> &treeWidgets);

    ~KTreeWidgetSearchLine() override;

    /*!
     * Returns true if the search is case sensitive.  This defaults to false.
     *
     * \sa setCaseSensitivity()
     */
    Qt::CaseSensitivity caseSensitivity() const;

    /*!
     * Returns the current list of columns that will be searched.  If the
     * returned list is empty all visible columns will be searched.
     *
     * \sa setSearchColumns
     */
    QList<int> searchColumns() const;

    /*!
     * If this is true (the default) then the parents of matched items will also
     * be shown.
     *
     * \sa setKeepParentsVisible()
     */
    bool keepParentsVisible() const;

    /*!
     * Returns the listview that is currently filtered by the search.
     * If there are multiple listviews filtered, it returns 0.
     *
     * \sa setTreeWidget(), treeWidgets()
     */
    QTreeWidget *treeWidget() const;

    /*!
     * Returns the list of pointers to listviews that are currently filtered by
     * the search.
     *
     * \sa setTreeWidgets(), addTreeWidget(), treeWidget()
     */
    QList<QTreeWidget *> treeWidgets() const;

Q_SIGNALS:
    /*!
     * This signal is emitted whenever an item gets hidden or unhidden due
     * to it not matching or matching the search string.
     */
    void hiddenChanged(QTreeWidgetItem *, bool);

    /*!
     * This signal is emitted when user finished entering filter text or
     * when he made a pause long enough, after the QTreeWidget items got filtered
     *
     * \a searchString is the text currently entered by the user
     * \since 5.0
     */
    void searchUpdated(const QString &searchString);

    /*!
     *
     */
    void caseSensitivityChanged(Qt::CaseSensitivity caseSensitivity);

    /*!
     *
     */
    void keepParentsVisibleChanged(bool keepParentsVisible);

public Q_SLOTS:
    /*!
     * Adds a QTreeWidget to the list of listviews filtered by this search line.
     * If \a treeWidget is null then the widget will be disabled.
     *
     * \sa treeWidget(), setTreeWidgets(), removeTreeWidget()
     */
    void addTreeWidget(QTreeWidget *treeWidget);

    /*!
     * Removes a QTreeWidget from the list of listviews filtered by this search
     * line. Does nothing if \a treeWidget is 0 or is not filtered by the quick search
     * line.
     *
     * \sa setTreeWidgets(), addTreeWidget()
     */
    void removeTreeWidget(QTreeWidget *treeWidget);

    /*!
     * Updates search to only make visible the items that match \a pattern.  If
     * \a s is null then the line edit's text will be used.
     */
    virtual void updateSearch(const QString &pattern = QString());

    /*!
     * Make the search case sensitive or case insensitive.
     *
     * \sa caseSensitivity()
     */
    void setCaseSensitivity(Qt::CaseSensitivity caseSensitivity);

    /*!
     * When a search is active on a list that's organized into a tree view if
     * a parent or ancesestor of an item is does not match the search then it
     * will be hidden and as such so too will any children that match.
     *
     * If this is set to true (the default) then the parents of matching items
     * will be shown.
     *
     * \warning setKeepParentsVisible(true) does not have the expected effect
     * on items being added to or removed from the view while a search is active.
     * When a new search starts afterwards the behavior will be normal.
     *
     * \sa keepParentsVisible
     */
    void setKeepParentsVisible(bool value);

    /*!
     * Sets the list of columns to be searched.  The default is to search all,
     * visible columns which can be restored by passing \a columns as an empty
     * list.
     * If listviews to be filtered have different numbers or labels of columns
     * this method has no effect.
     *
     * \sa searchColumns
     */
    void setSearchColumns(const QList<int> &columns);

    /*!
     * Sets the QTreeWidget that is filtered by this search line, replacing any
     * previously filtered listviews.  If \a treeWidget is null then the widget will be
     * disabled.
     *
     * \sa treeWidget(), setTreeWidgets()
     */
    void setTreeWidget(QTreeWidget *treeWidget);

    /*!
     * Sets QTreeWidgets that are filtered by this search line, replacing any
     * previously filtered listviews.  If \a treeWidgets is empty then the widget will
     * be disabled.
     *
     * \sa treeWidgets(), addTreeWidget(), setTreeWidget()
     */
    void setTreeWidgets(const QList<QTreeWidget *> &treeWidgets);

protected:
    /*!
     * Returns true if \a item matches the search \a pattern.  This will be evaluated
     * based on the value of caseSensitive().  This can be overridden in
     * subclasses to implement more complicated matching schemes.
     */
    virtual bool itemMatches(const QTreeWidgetItem *item, const QString &pattern) const;

    void contextMenuEvent(QContextMenuEvent *) override;

    /*!
     * Updates search to only make visible appropriate items in \a treeWidget.
     *
     * If \a treeWidget is null then nothing is done.
     */
    virtual void updateSearch(QTreeWidget *treeWidget);

    /*!
     * Connects signals of this listview to the appropriate slots of the search
     * line.
     */
    virtual void connectTreeWidget(QTreeWidget *);

    /*!
     * Disconnects signals of a listviews from the search line.
     */
    virtual void disconnectTreeWidget(QTreeWidget *);

    /*!
     * Checks columns in all listviews and decides whether choosing columns to
     * filter on makes any sense.
     *
     * Returns false if either of the following is true:
     * * there are no listviews connected,
     * * the listviews have different numbers of columns,
     * * the listviews have only one column,
     * * the listviews differ in column labels.
     *
     * Otherwise it returns true.
     *
     * \sa setSearchColumns()
     */
    virtual bool canChooseColumnsCheck();

    bool event(QEvent *event) override;

private:
    friend class KTreeWidgetSearchLinePrivate;
    std::unique_ptr<class KTreeWidgetSearchLinePrivate> const d;

    Q_PRIVATE_SLOT(d, void _k_rowsInserted(const QModelIndex &, int, int) const)
    Q_PRIVATE_SLOT(d, void _k_treeWidgetDeleted(QObject *))
    Q_PRIVATE_SLOT(d, void _k_slotColumnActivated(QAction *))
    Q_PRIVATE_SLOT(d, void _k_slotAllVisibleColumns())
    Q_PRIVATE_SLOT(d, void _k_queueSearch(const QString &))
    Q_PRIVATE_SLOT(d, void _k_activateSearch())
};

#endif
