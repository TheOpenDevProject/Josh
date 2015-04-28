#include "listener.h"
#include <QDebug>
Listener::Listener(QObject *parent):SpookySocket(new QTcpSocket(this))
{
    qDebug() << "Be ware, You're headed down a long and twisted path.";

}

void Listener::Listen(QString server, int port, QString nickname, QString realname, QString channel, QString username)
{
    connect(SpookySocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(SpookySocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(SpookySocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    SpookySocket->connectToHost(server,port);
    //Check to see if IRC let us connect :) T-30=DEF
    if(!SpookySocket->waitForConnected()){
        qDebug() << "This connection was 2pooky and died";
    }else{
    qDebug() << "This connection was brave and is now LIVE!";
    }
}

void Listener::sendMessage(QString message,QString channel)
{
    QByteArray package;
    package.append("PRIVMSG #");
    package.append(channel);
    package.append(" :");
    package.append(message);
    package.append("\r\n");
    SpookySocket->write(package);
    SpookySocket->flush();
}

Listener::~Listener()
{

}

void Listener::sendNick(QString nickname)
{
    QByteArray package;
    package.append("NICK ");
    package.append(nickname);
    package.append("\r\n");
    SpookySocket->write(package);
    SpookySocket->flush();
}

void Listener::sendUser(QString username,QString realname)
{
    QByteArray package;
    package.append("USER ");
    package.append(username);
    package.append(" 8 *: ");
    package.append(realname);
    package.append("\r\n");
    SpookySocket->write(package);
    SpookySocket->flush();
}

void Listener::sendJoin(QString channel)
{
    QByteArray package;
    package.append("JOIN #");
    package.append(channel);
    package.append("\r\n");
    SpookySocket->write(package);
    SpookySocket->flush();
}

void Listener::connected()
{
    this->sendNick("Yos3mityz");
    this->sendUser("Yos3mityz","Yos3mityz");
    this->sendJoin("bot-battle");
    this->sendMessage("My name is Josh","bot-battle");
}

void Listener::disconnected()
{

}

void Listener::readyRead()
{

    QByteArray array;
   while( !(array = SpookySocket->readLine()).isNull()){
       qDebug() << array;
   }
}

