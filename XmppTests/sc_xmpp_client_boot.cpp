#include <QCoreApplication>

#include <qxmpp/QXmppLogger.h>
#include <qxmpp/QXmppMessage.h>
#include <qxmpp/QXmppRosterManager.h>

#include "sc_xmpp_client_boot.h"
#include <QDebug>

///
/// \brief SCXmppClientBoot::SCXmppClientBoot
/// \param parent
///
SCXmppClientBoot::SCXmppClientBoot(QObject *parent) : QXmppClient(parent) {

    bool check = connect(this, SIGNAL(messageReceived(QXmppMessage)), SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(check); Q_UNUSED(check);
    check = connect(this, SIGNAL(connected()), SLOT(connected()));
    Q_ASSERT(check); Q_UNUSED(check);
    check = connect(this, SIGNAL(disconnected()), SLOT(disconnected()));
    Q_ASSERT(check); Q_UNUSED(check);
    check = connect(this, SIGNAL(error(QXmppClient::Error)), SLOT(error(QXmppClient::Error)));
    Q_ASSERT(check); Q_UNUSED(check);
    check = connect(this, SIGNAL(presenceReceived(QXmppPresence)), SLOT(presenceReceived(QXmppPresence)));
    Q_ASSERT(check); Q_UNUSED(check);

}

///
/// \brief SCXmppClientBoot::~SCXmppClientBoot
///
SCXmppClientBoot::~SCXmppClientBoot() {
    if (this->isAuthenticated() && this->isConnected()) {
        this->disconnectFromServer();
        qDebug() << "[++++]-++disconnecting for the server....";
    }
}

///
/// \brief SCXmppClientBoot::setRosters
/// \param _rosters
///
void SCXmppClientBoot::setRosters(QStringList& _rosters) {
    this->rosters = _rosters;
}

///
/// \brief SCXmppClientBoot::getRosters
/// \return
///
QStringList SCXmppClientBoot::getRosters() {
    return this->rosters;
}

///
/// \brief SCXmppClientBoot::connected
///
void SCXmppClientBoot::connected() {
    qDebug() << "You eve being connected!!!" << endl;
}

///
/// \brief SCXmppClientBoot::disconnected
///
void SCXmppClientBoot::disconnected() {
    qDebug() << "You eve being disconnected!!!" << endl;
}

///
/// \brief SCXmppClientBoot::messageReceived
/// \param message
///
void SCXmppClientBoot::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg = message.body();
    qDebug() << "##(MR)##-Message received from [" << from << "] - <" << msg << ">" << endl;
}

///
/// \brief SCXmppClientBoot::error
///
void SCXmppClientBoot::error(QXmppClient::Error error) {

    QString message("Error not identified.");
    switch (error) {
    case NoError:
        message = "No error.";
        break;
    case SocketError:
        message = "Error due to TCP socket.";
        break;
    case KeepAliveError:
        message = "Error due to no response to a keep alive.";
        break;
    case XmppStreamError:
        message = "Error due to XML stream.";
        break;
    }
    qDebug() << "##(ER)##-Error detected: <" << message << ">" << endl;

}

///
/// \brief SCXmppClientBoot::presenceReceived
/// \param presence
///
void SCXmppClientBoot::presenceReceived(const QXmppPresence &presence) {
    qDebug() << "##(PR)##-Presence Received From:" << presence.from() << endl;
}

///
/// \brief SCXmppClientBoot::login
/// \param _jid
/// \param _password
/// \param _hostname
/// \param _port
/// \param _resource
///
void SCXmppClientBoot::login(const QString& _jid, const QString& _password,
                             const QString& _hostname, const int& _port,
                             const QString& _resource) {

    QXmppConfiguration config;
    config.setHost(_hostname);
    config.setPort(_port);
    config.setIgnoreSslErrors(true);
    config.setJid(_jid);
    config.setPassword(_password);
    config.setResource(_resource);
    connectToServer(config);

}
