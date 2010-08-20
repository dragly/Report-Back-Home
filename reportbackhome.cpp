#include "reportbackhome.h"

#include <QTimer>

ReportBackHome::ReportBackHome(QWidget *parent)
    : QMainWindow(parent)
{
    // Manager for listening messages
    m_manager = new QMessageManager(this);

    // Listen new added messages
    connect(m_manager, SIGNAL(messageAdded(const QMessageId&,
                              const QMessageManager::NotificationFilterIdSet&)),
            this, SLOT(messageAdded(const QMessageId&,
                       const QMessageManager::NotificationFilterIdSet&)));

    // Create 2 filers set for filtering messages
    // - SMS filter
    // - InboxFolder filter
    m_notifFilterSet.insert(m_manager->registerNotificationFilter(
        QMessageFilter::byType(QMessage::Sms) &
        QMessageFilter::byStandardFolder(QMessage::InboxFolder)));
    positionSource = QGeoPositionInfoSource::createDefaultSource(this);
    connect(positionSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));
    connect(positionSource, SIGNAL(updateTimeout()),
            this, SLOT(updateTimeout()));
    connect(reportTimer, SIGNAL(timeout()), SLOT(performReport()));
}

void ReportBackHome::messageAdded(const QMessageId& id,
    const QMessageManager::NotificationFilterIdSet& matchingFilterIds)
{
    // Message added...
    if (matchingFilterIds.contains(m_notifFilterSet)) {
        // ...and it fits into our filters, lets process it
        m_messageId = id;
        QTimer::singleShot(0, this, SLOT(processIncomingSMS()));
    }
}

void ReportBackHome::processIncomingSMS()
{
    QMessage message = m_manager->message(m_messageId);
    // SMS message body
    QString messageString = message.textContent();
    // Show message to user
    qDebug() << "Incoming SMS" << messageString;
    // Remove message from inbox
    m_manager->removeMessage(m_messageId);

    if(messageString.toLower() == "report back home") {
        QTimer::singleShot(0, this, SLOT(startReporting()));
    }
}

void ReportBackHome::startReporting() {
    qDebug() << "Reporting started";
    reportTimer->start(60); // report every minute

    //TODO: Get position
    //TODO: Save position
    //TODO: Send last position on report
}

void ReportBackHome::performReport() {
    // Prepare QMessage with address & body
    QMessage message;
    message.setType(QMessage::Sms);
    QString address = "97752893";
    QString body = "Bla bla bla";
    message.setTo(QMessageAddress(address, QMessageAddress::Phone));
    message.setBody(body);

    if (iMessageServiceAction.send(message)) {
        sendId = message.id();
        }
    else {
        // message sending failed
        }
    }
}
