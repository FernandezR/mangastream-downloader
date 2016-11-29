#ifndef WAYBACK_H
#define WAYBACK_H

#include <QObject>
#include <QStringList>
#include <QString>

class WaybackMachine: public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList listOfMementos READ getListOfMementos WRITE setListOfMementos NOTIFY listOfMementosChanged)
    Q_PROPERTY(QString selectedUrl READ getSelectedUrl WRITE setSelectedUrl NOTIFY selectedUrlChanged)
public:
    Q_INVOKABLE QStringList getPreviousVersions(const QString url);

    void setListOfMementos(QStringList mementos);
    QStringList getListOfMementos();

    QString getSelectedUrl();
    void setSelectedUrl(QString url);
private:
    QStringList m_ret;
    QString m_selected;
signals:
    void listOfMementosChanged();
    void selectedUrlChanged();
};

#endif // WAYBACK_H
