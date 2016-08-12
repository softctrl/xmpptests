# xmpptests
Just a program to try to test and stress the Xmpp protocol 
```
____  ___                   ___________              __
\   \/  / _____ ______ _____\__    ___/___   _______/  |_  ______
 \     / /     \\____ \\____ \|    |_/ __ \ /  ___/\   __\/  ___/
 /     \|  Y Y  \  |_> >  |_> >    |\  ___/ \___ \  |  |  \___ \
/___/\  \__|_|  /   __/|   __/|____| \___  >____  > |__| /____  >
      \_/     \/|__|   |__|              \/     \/            \/ 


Author: carlostimoshenkorodrigueslopes@gmail.com
Usage:


	XmppTests <-u/-U>=JID <-p/-P>=PASSWORD 


Parameters:
	-u/-U	-Jid User.
	-p/-P	-Password.
	-h/-H	-Hostname, 127.0.0.1 default.
	-o/-O	-Port number, 5222 default.
	-r/-R	-Resource Name, SC_XMPP_TESTS default.
	-s/-S	-Seconds value, 5 seconds default.
	-rtsm/-RTSM	-A list of comma separated roster values to send test messages. Eg.: 23456@xmpp.com;34567@xmpp.com 

Sample
		XmppTests -u=123456@xmpp.com -p=password

		Will connect as user 123456. 

		XmppTests -u=123456@xmpp.com -p=password -rtsm=abcde@xmpp.com;bcdef@xmpp.com;cdefg@xmpp.com

		Will connect as user 123456 and it will send messages for all this jid informed on the rtsm parameter. 
```
