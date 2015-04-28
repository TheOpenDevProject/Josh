#include <QCoreApplication>
#include "listener.h"
#include <QTextStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Listener *Josh = new Listener();
    Josh->Listen("irc.freenode.net",6667,"","","","");
    QTextStream io(stdin);
    while(1){
        Josh->sendMessage(io.readLine(),"bot-battle");
        io.flush();
    }
    return a.exec();
}
