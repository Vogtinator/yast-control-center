 /****************************************************************************
|
| Copyright (c) 2011 Novell, Inc.
| All Rights Reserved.
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of version 2 of the GNU General Public License as
| published by the Free Software Foundation.
|
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; if not, contact Novell, Inc.
|
| To contact Novell about this file by physical or electronic mail,
| you may find current contact information at www.novell.com
|
 \***************************************************************************/


#include <QTemporaryFile>
#include <QProcess>
#include <QDebug>

#include "yccmoduleinfoprovider.h"

YCCModuleInfoProvider::YCCModuleInfoProvider()
{
}

YCCModuleInfoProvider::~YCCModuleInfoProvider()
{
}

//if defined $X-SuSE-YaST-AutoInst  && $X-SuSE-YaST-AutoInst != none
// X-SuSE-YaST-AutoInst=all
QString YCCModuleInfoProvider::provideInfo( const YQModulesModel *model, const QModelIndex &module ) const
{    
///sbin/yast2 get_status foo_auto /tmp/status
    QString ret;
    
    QString autoinst = model->propertyValue( module, "X-SuSE-YaST-AutoInst" ).toString();
    if ( ! autoinst.isEmpty() && ( autoinst != "none" ) )
    {
        //QTemporaryFile file;
        
        //if ( ! file.open() )
        //{
        //    qDebug() << "Can't create temporary file";
        //    return QString();
        //}
        
        QStringList arguments;
        QString modcall = model->propertyValue( module, "X-SuSE-YaST-Call" ).toString();
        if ( ! modcall.isEmpty() )
        {
            QProcess yast2;
            QString autoinstclient = model->propertyValue( module, "X-SuSE-YaST-AutoInstClient" ).toString(); 
            if ( autoinstclient.isEmpty() )
            {
                autoinstclient = modcall + "_auto";
            }

            QStringList args;
            //args << (autoinstclient) << file.fileName();
            args << "get_status" << (autoinstclient) << "/tmp/ycc_status";
            qDebug() << "Executing yast2 " << args;
            
            yast2.start("/sbin/yast2", args );
            
            if ( ! yast2.waitForFinished() )
            {
                qDebug() << "bad yast2 exit";
                return QString();
            }

            //QFile data(file.fileName());
            QFile data("/tmp/ycc_status");
            if ( data.open( QIODevice::ReadOnly ) )
            {
                QTextStream in(&data);
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    ret += line;
                }
            }
            else
                qDebug() << "can't read from temporary file" << ret;
        }
        else
        {
            qDebug() << "no info to call";            
        }
        
    }
    else
    {
        qDebug() << "no info to call";
    }
    return ret;
}

