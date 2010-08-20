#ifndef REPORTBACKHOME_H
#define REPORTBACKHOME_H

#include <QtGui>
#include <QPointer>
#include <QMessageBox>

#include <qmessage.h>
#include <qmessagemanager.h>
#include <qnmeapositioninfosource.h>
#include <qgeopositioninfosource.h>
#include <qgeosatelliteinfosource.h>
#include <qgeopositioninfo.h>
#include <qgeosatelliteinfo.h>
// QtMobility namespace
QTM_USE_NAMESPACE

class ReportBackHome : public QMainWindow
{
    Q_OBJECT

public:
    ReportBackHome(QWidget *parent = 0);

private slots:
    void processIncomingSMS();
    // Listening signals from QMessageManager
    void messageAdded(const QMessageId&,
                      const QMessageManager::NotificationFilterIdSet&);

    void startReporting();
    void performReport();

private:
    QPointer<QMessageManager> m_manager;
    QMessageManager::NotificationFilterIdSet m_notifFilterSet;
    QMessageId m_messageId;

    QGeoPositionInfoSource *positionSource;
    QTimer *reportTimer;
};

#endif // REPORTBACKHOME_H
