void MainWindow::ping()
{
    const QString host_address=mySocket->peerAddress().toString();
    if(host_address.isEmpty())
    {
        ui->textEdit->append("ping:address.isempty");
        if(mySocket->isOpen())
            mySocket->close();
    }

#ifdef DEBUG
        qDebug()<<"core: trying to ping host:"<<host_address;
#endif

        bool boolRESULT=false;

        int ping_timeout=500;
        QString exe_path;
        #ifdef Q_OS_WIN32
            exe_path="C:\\Windows\\system32\\ping.exe";
        #endif
        #ifdef Q_OS_LINUX
            exe_path="/bin/ping";
        #endif

        if(!QFile::exists(exe_path))
        {
#ifdef DEBUG
            qDebug()<<"core: ERROR:"<<exe_path<<"not found!";
#endif
            ui->textEdit->append("core: ERROR:"+exe_path+"not found!");
            boolRESULT=false;
        }
        else
        {
            QStringList arguments;
             #ifdef Q_OS_WIN
                //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("cp-866"));
                arguments<<host_address;
            #endif
            #ifdef Q_OS_LINUX
               // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
                arguments<<host_address<<"-c 1";
            #endif

            QProcess myProcess;
            myProcess.start(exe_path,arguments);
            if(myProcess.waitForFinished(ping_timeout))
            {
                QStringList strlstPingResults;
                strlstPingResults<<myProcess.readAll();


                QString strResult="";
                for (int i=0;i<=strlstPingResults.count()-1;i++)
                {
    #ifdef DEBUG
                    qDebug()<<"core: ping results:"<<strlstPingResults[i];
    #endif
                    strResult='\n'+strlstPingResults[i];
                    boolRESULT=strlstPingResults[i].contains("ttl",Qt::CaseInsensitive);
                    if (boolRESULT)
                        break;
                }
                myProcess.close();
                myProcess.deleteLater();
            }
        }

        if (!boolRESULT)
        {
            ui->textEdit->append("no ping");
            if(mySocket->isOpen())
                mySocket->close();
        }
        else
        {
             //ui->textEdit->append("ping:result true");
        }

}
