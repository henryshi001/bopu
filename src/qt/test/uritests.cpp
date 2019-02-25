// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("bopu://BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=100&label=Some Example&message=Some Example Message&IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?amount=100&label=Some Example&message=Some Example Message&IS=Something Invalid"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));
    QVERIFY(rv.message == QString("Some Example Message"));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?IS=1"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend == 1);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb?IS=0"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);

    uri.setUrl(QString("bopu:BLq8Ve94JhpVSngCW3wS2ffLRDev3nqfSb"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.fUseInstantSend != 1);
}
