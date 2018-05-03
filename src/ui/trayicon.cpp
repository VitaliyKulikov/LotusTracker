#include "trayicon.h"
#include "../arenatracker.h"
#include "../macros.h"
#include "../mtg/mtgalogparser.h"
#include "../mtg/mtgcards.h"

#include <QAction>
#include <QApplication>
#include <QMenu>

TrayIcon::TrayIcon(QObject *parent) : QObject(parent)
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        setupTrayIcon();
    }
}

void TrayIcon::setupTrayIcon()
{
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::TrayIconActivated);
    QMenu *trayMenu = new QMenu();
    trayIcon->setContextMenu(trayMenu);

#if defined Q_OS_MAC
    QIcon icon;
    icon.addFile(":/res/icons/icon_black.png");
    icon.addFile(":/res/icons/icon_black@2x.png");
    icon.setIsMask(true);
#elif defined Q_OS_WIN
    QIcon icon = QIcon(":/res/icons/icon.ico");
#endif
    trayIcon->setIcon(icon);

    QAction *settingsAction = new QAction(tr("Preferences"), this);
    connect(settingsAction, &QAction::triggered, this, &TrayIcon::openPreferences);
    trayMenu->addAction(settingsAction);
#ifdef QT_DEBUG
    QMenu* testMenu = trayMenu->addMenu(tr("Tests"));
    configTestMenu(testMenu);
#endif
    QAction *quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayMenu->addAction(quitAction);

    trayIcon->show();
}

void TrayIcon::TrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
#ifdef Q_OS_WIN
    if (reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
        openPreferences();
    }
#else
    UNUSED(reason);
#endif
}

void TrayIcon::openPreferences()
{
    ArenaTracker *arenaTracker = (ArenaTracker*) qApp->instance();
    arenaTracker->showPreferences();
}

void TrayIcon::configTestMenu(QMenu* testMenu)
{
    QAction *loadDeckAction = new QAction(tr("Load Deck"), this);
    connect(loadDeckAction, &QAction::triggered, this, [this](){
        MtgArena* mtgArena = ((ArenaTracker*) qApp->instance())->mtgArena;
        MtgCards* mtgCards = ((ArenaTracker*) qApp->instance())->mtgCards;
        QMap<Card*, int> cards;
        cards[mtgCards->findCard(65663)] = 2;
        cards[mtgCards->findCard(65769)] = 4;
        Deck deck("Grixis control", cards);
        emit mtgArena->getLogParser()->sgnPlayerDeckSelected(deck);
    });
    testMenu->addAction(loadDeckAction);
}
