
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-shellprivate.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-shellprivate.h)

set(plasmashellprivateplugin_SRCS
    widgetexplorer/kcategorizeditemsviewmodels.cpp
    widgetexplorer/plasmaappletitemmodel.cpp
    widgetexplorer/widgetexplorer.cpp
    shellprivateplugin.cpp
)

add_library(plasmashellprivateplugin SHARED ${plasmashellprivateplugin_SRCS})
target_link_libraries(plasmashellprivateplugin
        Qt::Core
        Qt::Quick
        Qt::Qml
        Qt::Gui
        Qt::Widgets
        Qt::Quick
        Qt::Qml
        Plasma::Plasma
        Plasma::PlasmaQuick
        KF6::I18n
        KF6::NewStuffWidgets
        KF6::KIOFileWidgets
        KF6::WindowSystem
        Plasma::Activities
        KF6::TextWidgets
        KF6::Package
)

install(TARGETS plasmashellprivateplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/shell)
install(FILES
    wallpaperplugin.knsrc
    widgetexplorer/plasmoids.knsrc
    DESTINATION ${KDE_INSTALL_KNSRCDIR}
)

install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/private/shell)

