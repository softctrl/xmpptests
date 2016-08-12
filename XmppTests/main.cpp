#include <QCoreApplication>

#include <qxmpp/QXmppClient.h>
#include <qxmpp/QXmppLogger.h>
#include <qxmpp/QXmppConfiguration.h>

#include <QFile>
#include <QStringList>
#include <QDebug>

#include <sc_xmpp_client_boot.h>
#include <sc_xmpp_thread_boot.h>

#include <QThread>

#include <stdio.h>

using namespace std;

void help(){

    qInfo() << "____  ___                   ___________              __";
    qInfo() << "\\   \\/  / _____ ______ _____\\__    ___/___   _______/  |_  ______";
    qInfo() << " \\     / /     \\\\____ \\\\____ \\|    |_/ __ \\ /  ___/\\   __\\/  ___/";
    qInfo() << " /     \\|  Y Y  \\  |_> >  |_> >    |\\  ___/ \\___ \\  |  |  \\___ \\";
    qInfo() << "/___/\\  \\__|_|  /   __/|   __/|____| \\___  >____  > |__| /____  >";
    qInfo() << "      \\_/     \\/|__|   |__|              \\/     \\/            \\/" << endl;
    qInfo() << "Author: carlostimoshenkorodrigueslopes@gmail.com";
    qInfo() << "Usage:";
    qInfo() << "\tXmppTests <-u/-U>=JID <-p/-P>=PASSWORD" << endl;
    qInfo() << "Parameters:";
    qInfo() << "\t-u/-U\t-Jid User.";
    qInfo() << "\t-p/-P\t-Password.";
    qInfo() << "\t-h/-H\t-Hostname, 127.0.0.1 default.";
    qInfo() << "\t-o/-O\t-Port number, 5222 default.";
    qInfo() << "\t-r/-R\t-Resource Name, SC_XMPP_TESTS default.";
    //qInfo() << "\t-h/-H\t-Shows this help information." << endl << endl;
    qInfo() << "\t-s/-S\t-Seconds value, 5 seconds default.";
    qInfo() << "\t-rtsm/-RTSM\t-A list of comma separated roster values to send test messages. Eg.: 23456@xmpp.com;34567@xmpp.com" << endl;
    qInfo() << "Sample";
    qInfo() << "\t\tXmppTests -u=123456@xmpp.com -p=password";
    qInfo() << "\t\tWill connect as user 123456." << endl;
    qInfo() << "\t\tXmppTests -u=123456@xmpp.com -p=password -rtsm=abcde@xmpp.com;bcdef@xmpp.com;cdefg@xmpp.com";
    qInfo() << "\t\tWill connect as user 123456 and it will send messages for all this jid informed on the rtsm parameter." << endl;


}


///
/// \brief arguments
/// \param _argc
/// \param _argv
/// \return
///
QStringList loadArguments(int _argc, char *_argv[]) {
    QStringList list;
    const int ac = _argc;
    char ** const av = _argv;
    for (int idx = 1; idx < ac; ++idx) {
        list << QString::fromLocal8Bit(av[idx]);
    }
    return list;
}

///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{

    if (argc < 3) {
        help();
        return 0;
    }

    QString jid;
    QString password;
    QString hostname("127.0.0.1");
    QString resource("SC_XMPP_TESTS");
    int port = 5222;
    int seconds = 5;
    bool verbose = false;

    QStringList rosterToSendMessage;


    QStringList arguments = loadArguments(argc, argv);
    int length = arguments.length();

    for (int idx=0; idx < length; idx++) {
        QStringList param = QString(arguments.at(idx)).split("=");
        QString p = QString(param.at(0)).replace("-", "");
        if (0==p.compare("U", Qt::CaseInsensitive)) { // User
            jid = param.at(1);
            if (jid.isEmpty()) {
                qInfo() << "You need to inform a valid user.";
                help();
                return 1;
            }
        } else if (0==p.compare("P", Qt::CaseInsensitive)) { // Password
            password =  QString(param.at(1)).replace("\n", "");
            if (password.isEmpty()) {
                qInfo() << "You need to inform a valid password.";
                help();
                return 1;
            }
        } else if (0==p.compare("H", Qt::CaseInsensitive)) { // Hostname server
            hostname = param.at(1);
            if (hostname.isEmpty()) {
                qInfo() << "You need to inform a valid hostname.";
                help();
                return 1;
            }
        } else if (0==p.compare("O", Qt::CaseInsensitive)) { // Port number
            port = QString(param.at(1)).toInt();
            if ((port < 0) || (port > 65635)) {
                qInfo() << "You need to inform a valid port number.";
                help();
                return 1;
            }
        } else if (0==p.compare("R", Qt::CaseInsensitive)) { // Resource name
            resource = param.at(1);
            if (resource.isEmpty()) {
                qInfo() << "You need to inform a valid resource name.";
                help();
                return 1;
            }
        } else if (0==p.compare("S", Qt::CaseInsensitive)) { // Seconds
            seconds = QString(param.at(1)).toInt();
            if (seconds < 1) {
                qInfo() << "You need to inform a valid seconds value.";
                help();
                return 1;
            }
        } else if (0==p.compare("RTSM", Qt::CaseInsensitive)) { // Roster to send message
            rosterToSendMessage = QString(param.at(1)).split(";");
            if (rosterToSendMessage.isEmpty()) {
                qInfo() << "You do not inform a valid roster list for tests purposes.";
                help();
                return 1;
            }
        } else if (0==p.compare("V", Qt::CaseInsensitive)) { // Enable verbose model.
            verbose = true;
        }
    }

    QCoreApplication app(argc, argv);

    if (jid.isEmpty() || password.isEmpty()) {
        printf("You need to inform valid jid user and password.");
        help();
        return 1;
    }

    qDebug() <<"+++Start: " << jid << "-" << password << endl;

    SCXmppClientBoot client;
    if (verbose) {
        client.logger()->setLoggingType(QXmppLogger::StdoutLogging);
    }
    if (!rosterToSendMessage.isEmpty()) {
        client.setRosters(rosterToSendMessage);
    }
    client.login(jid, password, hostname, port, resource);

    SCXmppThreadBoot thread(client);
    thread.setSeconds(seconds);
    thread.start();

    return app.exec();
}
