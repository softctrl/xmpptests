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
