#ifndef MTGALOGPARSER_H
#define MTGALOGPARSER_H

#include "../entity/deck.h"
#include "../entity/user.h"

#include <QObject>
#include <QTimer>

class MtgaLogParser : public QObject
{
    Q_OBJECT

private:
    QList<int> msgResponseNumbers;
    void parseMsg(QPair<QString, QString> msg);
    void parsePlayerInventory(QString json);
    void parsePlayerInventoryUpdate(QString json);
    void parsePlayerCollection(QString json);
    void parsePlayerDecks(QString json);
    void parseOpponentInfo(QString json);
    void parseMatchInfo(QString json);
    void parsePlayerRankInfo(QString json);
    void parsePlayerDeckSelected(QString json);
    void parsePlayerMulliganInfo(QString json);
    void parsePlayerMatchState(QString json);

public:
    explicit MtgaLogParser(QObject *parent = nullptr);
    void parse(QString logNewContent);

signals:
    void sgnPlayerInventory(PlayerInventory playerInventory);
    void sgnPlayerInventoryUpdate(QList<int> newCards);
    void sgnPlayerDeckSelected(Deck deck);

public slots:
};

#endif // MTGALOGPARSER_H