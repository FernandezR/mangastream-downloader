#include "headers/wayback.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QLocale>
#include <QRegularExpression>
#include <QDateTime>

QStringList WaybackMachine::getPreviousVersions(const QString url) {
    m_ret.clear();
    QLocale english(QLocale::English, QLocale::UnitedStates);
    QRegularExpression regexDate("datetime=\"(.*)\"");
    QRegularExpression regexUrl("<(.*)>");

    QUrl apiUrl("http://web.archive.org/web/timemap/link/"+url);
    QNetworkRequest request(apiUrl);
    QNetworkAccessManager mgr;

    QNetworkReply *reply = mgr.get(request);

    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QStringList result(QString(reply->readAll()).split("\n"));

    for(int i = 0; i < result.length(); i++) {
        QString line = result.at(i);
        if(line.contains("memento")) {
            QString tmp(regexDate.match(line).captured(1).replace(" GMT",""));
            QString date = english.toDateTime(tmp, "ddd, dd MMM yyyy hh:mm:ss").toString(tr("yyyy-MM-dd hh:mm:ss"));
            QString url = regexUrl.match(line).captured(1);
            m_ret << date << url;
        }
    }

    emit listOfMementosChanged();
    return m_ret;
}

void WaybackMachine::setListOfMementos(QStringList mementos) {
    m_ret = mementos;
    emit listOfMementosChanged();
}

QStringList WaybackMachine::getListOfMementos() {
    return m_ret;
}

QString WaybackMachine::getSelectedUrl() {
    return m_selected;
}

void WaybackMachine::setSelectedUrl(QString url) {
    m_selected = url;
    emit selectedUrlChanged();
}
