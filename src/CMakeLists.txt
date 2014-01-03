
set(kitemviews_SRCS
  kcategorizedsortfilterproxymodel.cpp
  kcategorizedview.cpp
  kcategorydrawer.cpp
  kextendableitemdelegate.cpp
  kfilterproxysearchline.cpp
  klistwidgetsearchline.cpp
  ktreewidgetsearchline.cpp
  ktreewidgetsearchlinewidget.cpp
  kwidgetitemdelegate.cpp
  kwidgetitemdelegatepool.cpp
)

add_library(KF5ItemViews ${kitemviews_SRCS})
generate_export_header(KF5ItemViews BASE_NAME KItemViews)
add_library(KF5::ItemViews ALIAS KF5ItemViews)


target_include_directories(KF5ItemViews INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KItemViews>")

target_link_libraries(KF5ItemViews PUBLIC Qt5::Widgets)

set_target_properties(KF5ItemViews PROPERTIES VERSION   ${KITEMVIEWS_VERSION_STRING}
                                              SOVERSION ${KITEMVIEWS_SOVERSION}
                                              EXPORT_NAME ItemViews
)

ecm_generate_headers(
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
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/KItemViews DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

install(TARGETS KF5ItemViews EXPORT KF5ItemViewsTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kitemviews_export.h
  ${KItemViews_HEADERS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/KItemViews COMPONENT Devel
)
