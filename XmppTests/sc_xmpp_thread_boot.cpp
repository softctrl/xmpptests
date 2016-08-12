#include "sc_xmpp_thread_boot.h"
#include <sc_xmpp_client_boot.h>
#include <qxmpp/QXmppConfiguration.h>
#include <qxmpp/QXmppLogger.h>
#include <QDebug>
#include <QDateTime>

///
/// \brief SCXmppThreadBoot::SCXmppThreadBoot
/// \param _jid
/// \param _password
///
SCXmppThreadBoot::SCXmppThreadBoot(SCXmppClientBoot &_client) : client(_client), sec(5), jid(_client.configuration().jid()) {
    qDebug() << "## Constructor";
    this->setSeconds(5);
}

///
/// \brief SCXmppThreadBoot::~SCXmppThreadBoot
///
SCXmppThreadBoot::~SCXmppThreadBoot() {
    qDebug() << "## Destructor";
    if (this->client.isConnected() && this->client.isAuthenticated()) {
        qDebug() << "## Destructor - Disconnecting";
        this->client.disconnectFromServer();
    }
}

///
/// \brief SCXmppThreadBoot::setSeconds
/// \param _sec
///
void SCXmppThreadBoot::setSeconds(int _sec) {
    this->sec = _sec;
}

///
/// \brief SCXmppThreadBoot::newMessage
/// \param _to_jid
/// \return
///
QString SCXmppThreadBoot::newMessage(QString& _to_jid) {
    return QString("Message from <%1> to <%2> at[%3]").arg(this->jid, _to_jid, QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss"));
}

///
/// \brief SCXmppThreadBoot::run
///
void SCXmppThreadBoot::run() {

    QStringList rosters = this->client.getRosters();
    int length = rosters.length();
    bool messageTests = (length > 0);
    while(true) {
        if (messageTests) {
            for (int idx=0; idx < length; idx++) {
                QString roster = rosters.at(idx);
                QString message = newMessage(roster);
                this->client.sendMessage(roster, message);
                qDebug() << "#-" << message;
            }
        }
        QThread::sleep(this->sec);
    }

}
