include(ECMAddQtDesignerPlugin)

ecm_qtdesignerplugin_widget(KCategorizedView
    TOOLTIP "Categorized Item View (KF5)"
    WHATSTHIS "Item view for listing items in a categorized fashion optionally."
    GROUP "Views (KF5)"
)
ecm_qtdesignerplugin_widget(KFilterProxySearchLine
    TOOLTIP "Filter proxy search line"
    WHATSTHIS "A search line widget which works on a QSortFilterProxyModel"
    GROUP "Input (KF5 - Deprecated)"
)
ecm_qtdesignerplugin_widget(KListWidgetSearchLine
    TOOLTIP "QListWidget Search Line (KF5)"
    GROUP "Input (KF5)"
)
ecm_qtdesignerplugin_widget(KTreeWidgetSearchLine
    TOOLTIP "QTreeWidget Search Line (KF5)"
    GROUP "Input (KF5)"
)
ecm_qtdesignerplugin_widget(KTreeWidgetSearchLineWidget
    TOOLTIP "QTreeWidget Search Line Widget (KF5)"
    GROUP "Input (KF5)"
)

ecm_add_qtdesignerplugin(kitemviewswidgets
    NAME KItemViewsWidgets
    OUTPUT_NAME kitemviews5widgets
    WIDGETS
        KCategorizedView
        KFilterProxySearchLine
        KListWidgetSearchLine
        KTreeWidgetSearchLine
        KTreeWidgetSearchLineWidget
    LINK_LIBRARIES
        KF5::ItemViews
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
