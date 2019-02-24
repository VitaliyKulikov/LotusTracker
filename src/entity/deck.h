#ifndef DECK_H
#define DECK_H

#include "card.h"

#include <QString>
#include <QMap>

class Deck
{
private:
    QString _arch;
    QString _colorIdentity;
    QMap<Card*, int> cardsInitial;
    QMap<Card*, int> cardsSideboardingInitial;
    QMap<Card*, int> cardsCurrent;
    QMap<Card*, int> cardsSideboard;

public:
    QString id;
    QString name;
    bool showOnlyRemainingCards;

    explicit Deck(QString id = "", QString name = "",
         QMap<Card*, int> cards = {}, QMap<Card*, int> sideboard = {});
    QString arch();
    QMap<Card*, int> cards(bool ignoreCardsWithSideboard = false);
    QMap<Card*, int> sideboard();
    QMap<Card*, int> currentCards();
    int totalCards();
    int totalCardsLand();
    int totalCardsOfQtd(int qtd);
    int totalCardsOfMore();

    void updateCards(QMap<Card*, int> cards, QMap<Card*, int> sideboard);
    void updateTitle(QString title);
    void clear();
    void reset();
    bool isReseted();

    QString colorIdentity(bool useStartCalc = true, bool includeLands = false);
    bool drawCard(Card *card);
    void insertCard(Card *card);
    void setCardQtd(Card *card, int qtd);

    static QString calcColorIdentity(QMap<Card*, int> cards, bool includeLands);

};

#endif // DECK_H
