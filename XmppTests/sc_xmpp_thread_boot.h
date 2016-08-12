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
#ifndef SCXMPPTHREADBOOT_H
#define SCXMPPTHREADBOOT_H

#include <QThread>
#include <qxmpp/QXmppClient.h>
#include <sc_xmpp_client_boot.h>

class SCXmppThreadBoot : public QThread  {
    SCXmppClientBoot &client;
    int sec;
    QString jid;
    public:
        SCXmppThreadBoot(SCXmppClientBoot&);
        ~SCXmppThreadBoot();
        void setSeconds(int);
    private:
        void run();
        QString newMessage(QString&);
};

#endif // SCXMPPTHREADBOOT_H
