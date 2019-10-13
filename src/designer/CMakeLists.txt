include(ECMAddQtDesignerPlugin)

set(deprecated_widgets)

ecm_qtdesignerplugin_widget(KCategorizedView
    TOOLTIP "Categorized Item View (KF5)"
    WHATSTHIS "Item view for listing items in a categorized fashion optionally."
    GROUP "Views (KF5)"
)
if (NOT EXCLUDE_DEPRECATED_BEFORE_AND_AT STREQUAL "CURRENT" AND
    EXCLUDE_DEPRECATED_BEFORE_AND_AT VERSION_LESS 5.50.0)
    ecm_qtdesignerplugin_widget(KFilterProxySearchLine
        TOOLTIP "Filter proxy search line"
        WHATSTHIS "A search line widget which works on a QSortFilterProxyModel"
        GROUP "Input (KF5 - Deprecated)"
    )
    list(APPEND deprecated_widgets KFilterProxySearchLine)
endif()
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
        KListWidgetSearchLine
        KTreeWidgetSearchLine
        KTreeWidgetSearchLineWidget
        ${deprecated_widgets}
    LINK_LIBRARIES
        KF5::ItemViews
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
