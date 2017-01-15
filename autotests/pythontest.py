#!/usr/bin/env python
#-*- coding: utf-8 -*-

from __future__ import print_function

import sys

sys.path.append(sys.argv[1])

from PyQt5 import QtCore
from PyQt5 import QtWidgets

from PyKF5 import KItemViews

def main():
    app = QtWidgets.QApplication(sys.argv)

    model = QtCore.QStringListModel(("1", "2", "3"))

    proxy = QtCore.QSortFilterProxyModel()
    proxy.setSourceModel(model)

    assert(proxy.rowCount() == 3)

    filterLine = KItemViews.KFilterProxySearchLine()
    filterLine.setProxy(proxy)

    filterLine.setText("1");

    print(proxy.rowCount(), proxy.filterRegExp())

    assert(proxy.rowCount() == 1)

if __name__ == '__main__':
    sys.exit(main())
