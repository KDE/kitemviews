add_library(KF6ItemViews)
add_library(KF6::ItemViews ALIAS KF6ItemViews)

set_target_properties(KF6ItemViews PROPERTIES
    VERSION     ${KITEMVIEWS_VERSION}
    SOVERSION   ${KITEMVIEWS_SOVERSION}
    EXPORT_NAME ItemViews
)

ecm_create_qm_loader(KF6ItemViews kitemviews6_qt)

target_sources(KF6ItemViews PRIVATE
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

ecm_qt_declare_logging_category(KF6ItemViews
    HEADER kitemviews_debug.h
    IDENTIFIER KITEMVIEWS_LOG
    CATEGORY_NAME kf.itemviews
    DESCRIPTION "KItemViews"
    EXPORT KITEMVIEWS
)

ecm_generate_export_header(KF6ItemViews
    BASE_NAME KItemViews
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    USE_VERSION_HEADER
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

ecm_generate_qdoc(KF6ItemViews kitemviews.qdocconf)

target_include_directories(KF6ItemViews INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KItemViews>")

target_link_libraries(KF6ItemViews PUBLIC Qt6::Widgets)

ecm_generate_headers(KItemViews_HEADERS
  HEADER_NAMES
  KCategorizedSortFilterProxyModel
  KCategorizedView
  KCategoryDrawer
  KExtendableItemDelegate
  KListWidgetSearchLine
  KTreeWidgetSearchLine
  KTreeWidgetSearchLineWidget
  KWidgetItemDelegate

  REQUIRED_HEADERS KItemViews_HEADERS
)

install(TARGETS KF6ItemViews EXPORT KF6ItemViewsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kitemviews_export.h
  ${KItemViews_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KItemViews COMPONENT Devel
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

ecm_qt_install_logging_categories(
    EXPORT KITEMVIEWS
    FILE kitemviews.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)
