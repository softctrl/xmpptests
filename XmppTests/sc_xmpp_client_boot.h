/*
 *
 * Author:
 *  Carlos Timoshenko
 *  carlostimoshenkorodrigueslopes@gmail.com
 *
 * Source:
 *  https://github.com/softctrl/xmpptests
 *
 * This file is a part of XmppTests project.
 *
 * This project is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */
#ifndef SCXMPPCLIENTBOOT_H
#define SCXMPPCLIENTBOOT_H

#include "qxmpp/QXmppClient.h"

class SCXmppClientBoot : public QXmppClient {
    QStringList rosters;

    Q_OBJECT
    public:

        SCXmppClientBoot(QObject *parent = 0);
        ~SCXmppClientBoot();
        void setRosters(QStringList&);
        QStringList getRosters();
        void login(const QString&, const QString&, const QString&, const int&, const QString&);
    public slots:
        /// This signal is emitted when the client connects successfully to the XMPP
        /// server i.e. when a successful XMPP connection is established.
        /// XMPP Connection involves following sequential steps:
        ///     - TCP socket connection
        ///     - Client sends start stream
        ///     - Server sends start stream
        ///     - TLS negotiation (encryption)
        ///     - Authentication
        ///     - Resource binding
        ///     - Session establishment
        ///
        /// After all these steps a successful XMPP connection is established and
        /// connected() signal is emitted.
        ///
        /// After the connected() signal is emitted QXmpp will send the roster request
        /// to the server. On receiving the roster, QXmpp will emit
        /// QXmppRosterManager::rosterReceived(). After this signal, QXmppRosterManager object gets
        /// populated and you can use rosterManager() to get the handle of QXmppRosterManager object.
        ///
        void connected();

        /// This signal is emitted when the XMPP connection disconnects.
        ///
        void disconnected();

        /// Notifies that an XMPP message stanza is received. The QXmppMessage
        /// parameter contains the details of the message sent to this client.
        /// In other words whenever someone sends you a message this signal is
        /// emitted.
        void messageReceived(const QXmppMessage&);

        /// This signal is emitted when the XMPP connection encounters any error.
        /// The QXmppClient::Error parameter specifies the type of error occurred.
        /// It could be due to TCP socket or the xml stream or the stanza.
        /// Depending upon the type of error occurred use the respective get function to
        /// know the error.
        void error(QXmppClient::Error);

        /// Notifies that an XMPP presence stanza is received. The QXmppPresence
        /// parameter contains the details of the presence sent to this client.
        /// This signal is emitted when someone login/logout or when someone's status
        /// changes Busy, Idle, Invisible etc.
        void presenceReceived(const QXmppPresence&);

};

#endif // SCXMPPCLIENTBOOT_H
