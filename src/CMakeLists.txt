add_library(KF5ItemViews)
add_library(KF5::ItemViews ALIAS KF5ItemViews)

set_target_properties(KF5ItemViews PROPERTIES
    VERSION     ${KITEMVIEWS_VERSION}
    SOVERSION   ${KITEMVIEWS_SOVERSION}
    EXPORT_NAME ItemViews
)

ecm_create_qm_loader(KF5ItemViews kitemviews5_qt)

target_sources(KF5ItemViews PRIVATE
    kcategorizedsortfilterproxymodel.cpp
    kcategorizedsortfilterproxymodel.h
    kcategorizedsortfilterproxymodel_p.h
    kcategorizedview.cpp
    kcategorizedview.h
    kcategorizedview_p.h
    kcategorydrawer.cpp
    kcategorydrawer.h
    kextendableitemdelegate.cpp
    kextendableitemdelegate.h
    kfilterproxysearchline.cpp
    kfilterproxysearchline.h
    klistwidgetsearchline.cpp
    klistwidgetsearchline.h
    ktreewidgetsearchline.cpp
    ktreewidgetsearchline.h
    ktreewidgetsearchlinewidget.cpp
    ktreewidgetsearchlinewidget.h
    kwidgetitemdelegate.cpp
    kwidgetitemdelegate.h
    kwidgetitemdelegate_p.h
    kwidgetitemdelegatepool.cpp
    kwidgetitemdelegatepool_p.h

)

ecm_qt_declare_logging_category(KF5ItemViews
    HEADER kitemviews_debug.h
    IDENTIFIER KITEMVIEWS_LOG
    CATEGORY_NAME kf.itemviews
    DESCRIPTION "KItemViews"
    EXPORT KITEMVIEWS
)

ecm_generate_export_header(KF5ItemViews
    BASE_NAME KItemViews
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 4.2 4.4 5.0 5.50
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)


target_include_directories(KF5ItemViews INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KItemViews>")

target_link_libraries(KF5ItemViews PUBLIC Qt${QT_MAJOR_VERSION}::Widgets)

ecm_generate_headers(KItemViews_HEADERS
  HEADER_NAMES
  KCategorizedSortFilterProxyModel
  KCategorizedView
  KCategoryDrawer
  KExtendableItemDelegate
  KFilterProxySearchLine
  KListWidgetSearchLine
  KTreeWidgetSearchLine
  KTreeWidgetSearchLineWidget
  KWidgetItemDelegate

  REQUIRED_HEADERS KItemViews_HEADERS
)

install(TARGETS KF5ItemViews EXPORT KF5ItemViewsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kitemviews_export.h
  ${KItemViews_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KItemViews COMPONENT Devel
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

if(BUILD_QCH)
    ecm_add_qch(
        KF5ItemViews_QCH
        NAME KItemViews
        BASE_NAME KF5ItemViews
        VERSION ${KF_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KItemViews_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt5Widgets_QCH
            Qt5Gui_QCH
            Qt5Core_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KITEMVIEWS_EXPORT
            KITEMVIEWS_DEPRECATED
            KITEMVIEWS_DEPRECATED_EXPORT
            "KITEMVIEWS_DEPRECATED_VERSION(x, y, t)"
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

include(ECMGeneratePriFile)
ecm_generate_pri_file(BASE_NAME KItemViews LIB_NAME KF5ItemViews DEPS "widgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/KItemViews)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

ecm_qt_install_logging_categories(
    EXPORT KITEMVIEWS
    FILE kitemviews.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)
