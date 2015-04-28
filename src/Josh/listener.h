#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMap>
#include <functional>
class Listener: public QObject

{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = 0);
    void Listen(QString server, int port, QString nickname, QString realname, QString channel, QString username);
    void sendMessage(QString message,QString channel);
    ~Listener();
protected:
    void sendNick(QString nickname);
    void sendUser(QString username, QString realname);
    void sendJoin(QString channel);
private:

    QMap<QString,std::function<void()>> commandMap();
    QTcpSocket *SpookySocket;

   private slots:
    void connected();
    void disconnected();
    void readyRead();
};

#endif // LISTENER_H
