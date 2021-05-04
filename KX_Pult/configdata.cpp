#include "configdata.h"

QT_USE_NAMESPACE




ConfigData::ConfigData(const QString & config, QObject *parent): QObject(parent),standardOutput(stdout), dataFile(config),jmax(0)

{
  QString readData;

  data.macadress = "";
  data.ipadress = "";

  data.device = "";
  data.calibration = "";

  data.sender_ip = "";
  data.receiver_ip = "";

  data.device_frequency = 1;

  data.baudRate = 9600;

  data.sender_port = 0;
  data.receiver_port = 0;

  data.sender_frequency = 0;
  data.receiver_frequency = 0;

  list.clear();

  if (!dataFile.open(QIODevice::ReadOnly))
      {
       standardOutput << QObject::tr("Failed to open ") << dataFile.fileName() << QObject::tr(" for reading")  << endl;
      }
  else
      {
       do
          {
           readData = dataFile.readLine();
           if (readData[0] != '#')
               {
                list += readData;
                jmax++;
               }
          }
       while (!dataFile.atEnd());

       dataFile.close();
      }

}

ConfigData::ConfigData(const QString & config, const QString & name, QObject *parent) : QObject(parent),standardOutput(stdout), dataFile(config),jmax(0)

{
  QString readData;

  data.device = "";
  data.calibration = "";

  data.sender_ip = "";
  data.receiver_ip = "";

  data.device_frequency = 1;

  data.baudRate = 9600;

  data.sender_port = 0;
  data.receiver_port = 0;

  data.sender_frequency = 0;
  data.receiver_frequency = 0;

  list.clear();

  if (!dataFile.open(QIODevice::ReadOnly))
      {
       standardOutput << QObject::tr("Failed to open ") << dataFile.fileName() << QObject::tr(" for reading")  << endl;
      }
  else
      {
       do
          {
           readData = dataFile.readLine();
           if (readData[0] != '#')
               {
                list += readData;
                jmax++;
               }
          }
       while (!dataFile.atEnd());

       dataFile.close();
      }


  getValue(name);

}

void ConfigData::getValue(const QString & name)
    {
     QStringList tmplist;
     QString tmp;
     QString tmpstr;
     int beginpos, endpos, imax = 0;
     bool ok = false;

     for (int i = 0; i < jmax; i++)
          {
           if (list[i].contains(name))
               {
                tmplist += list[i];
                imax++;
               }
          }
      for (int i = 0; i < imax; i++)
           {
            tmpstr = (tmplist.at(i)).simplified();
            if (tmpstr.contains("ifconfig"))
                {
                 beginpos = tmpstr.indexOf('.');
                 endpos = tmpstr.indexOf(" =");
                 data.macadress = tmpstr.mid((beginpos + 1),(endpos - beginpos - 1));
                 beginpos = tmpstr.lastIndexOf("= ");
                 tmp = tmpstr.mid((beginpos + 2));
                 data.ipadress = tmp.mid(0, tmp.indexOf(' '));
                }
            else
                {
                 beginpos = tmpstr.indexOf("= ");
                 tmp = tmpstr.mid((beginpos + 2));
                 endpos = tmp.indexOf(' ');
                 if (tmpstr.contains("device"))
                     {
                      if (tmpstr.contains("frequency"))
                          data.device_frequency = (qint32)(tmp.mid(0, endpos)).toInt();
                      else
                         data.device = tmp.mid(0, endpos);
                     }
                 if (tmpstr.contains("speed"))
                     data.baudRate = (qint32)(tmp.mid(0, endpos)).toInt();
                 if (tmpstr.contains("calibration"))
                     data.calibration = tmp.mid(0, endpos);
                 if (tmpstr.contains("receiver"))
                     {
                      if (tmpstr.contains("ip"))
                          data.receiver_ip = tmp.mid(0, endpos);
                      else
                      if (tmpstr.contains("port"))
                          data.receiver_port = (qint32)(tmp.mid(0, endpos)).toInt();
                      else
                      if (tmpstr.contains("frequency"))
                          data.receiver_frequency = (qint32)(tmp.mid(0, endpos)).toInt();
                     }
                 if (tmpstr.contains("sender"))
                     {
                      if (tmpstr.contains("ip"))
                          data.sender_ip = tmp.mid(0, endpos);
                      else
                      if (tmpstr.contains("port"))
                          data.sender_port = (qint32)(tmp.mid(0, endpos)).toInt();
                      else
                      if (tmpstr.contains("frequency"))
                          data.sender_frequency = (qint32)(tmp.mid(0, endpos)).toInt();
                     }

                 if (tmpstr.contains("type"))
                     data.type = (quint16)(tmp.mid(2, endpos-2)).toUShort(&ok,16);

                 if (tmpstr.contains("addr_x"))
                     data.addr_x = (quint16)(tmp.mid(2, endpos-2)).toUShort(&ok,16);

                 if (tmpstr.contains("addr_k"))
                     data.addr_k = (quint16)(tmp.mid(2, endpos-2)).toUShort(&ok,16);

                 if (tmpstr.contains("addr_pult"))
                     data.addr_pult = (quint16)(tmp.mid(2, endpos-2)).toUShort(&ok,16);

                 if (tmpstr.contains("count"))
                     data.count = (quint16)(tmp.mid(0, endpos)).toUShort();

                 if (tmpstr.contains("file"))
                     data.ki_file = tmp.mid(0, endpos);
                }
           }
     }

ConfigData::~ConfigData()
{

 list.clear();
}
