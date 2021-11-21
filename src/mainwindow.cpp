#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <iostream>
#include <fstream>
#include  <QRegularExpression>
#include   <QMessageBox>
#include <strstream>
#include <string>
#include <QtWidgets>
#include "PPLine.h"
#include <shellapi.h>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QMessageBox mb;
    ui->setupUi(this);
    QDir dir;
    QString myRootFolderPath = dir.absolutePath();
    myRootFolderPath += "/PartMachineMap.txt";
    ui->plainTextEditMessages->setPlainText(myRootFolderPath);

    QString mysettingFileStr = dir.absolutePath();
    mysettingFileStr += "/DE_PartMachineMapSettings.txt";
    QFile mySettingFile (mysettingFileStr);
    //mb.setText(mysettingFileStr);
    //mb.exec();
    mySettingFile.open(QFile::ReadOnly | QFile::Text);
    if (mySettingFile.isOpen())
    {
        int maxsize = 1000;
        char temp[maxsize];
        //char delim('\n');
        std::map<QString,QString> settingMap;
        while (mySettingFile.atEnd() == false)
        {
            mySettingFile.readLine(temp,maxsize);
            QString mykey (temp);
            mySettingFile.readLine(temp,maxsize);
            QString myvalue (temp);
            m_settings[mykey] = myvalue;
        }
    }
    else
    {
        mb.setText("dosya acilamadi");
        mb.exec();
    }

    //std::map<QString,QString>::iterator iii = m_settings.begin();
    //std::map<QString,QString>::iterator eee = m_settings.end();
    //for (iii;iii!=eee;++iii)
    //{
     //   mb.setText(iii->first + ":" + iii->second);
      //  mb.exec();
    //}

    std::map<QString,QString>::iterator fi = m_settings.find("EditorPath\n");
    if (fi != m_settings.end())
    {
        ui->plainTextEditEditor->setPlainText(fi->second);
    }
    std::map<QString,QString>::iterator fj = m_settings.find("WorkDirectory\n");
    if (fj != m_settings.end())
    {
        ui->plainTextEditWorkDirectory->setPlainText(fj->second);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void SplitString (const std::string &src, const char seperator, std::vector<std::string> &result)
{
    size_t mysize = src.length();
    std::string s;
    int quotCounter = 0;
    for (size_t i=0;i<mysize;++i)
    {
        char myc = src[i];
        if (myc == '\"')
            ++quotCounter;
        if (myc == seperator && quotCounter % 2 == 0)
        {
            if (s.length())
            {
                result.push_back(s);
                s.clear();
            }
        }
        else
        {
            s+=myc;
        }
    }
    if (s.length())
        result.push_back(s);
}
//int mycounter = 0;
void SplitOneLine (const std::string &line , std::vector<std::string> &wordVec)
{
    std::string temp;
    for (size_t ci = 0;ci<line.length();++ci)
    {
        const char &curc = line.at(ci);
        if (curc != ' ' && curc != '\t' && curc != '\n' && curc != '\r')
        {
            temp+=curc;
        }
        else
        {
            if (temp.length()>0)
            {
                wordVec.push_back(temp);
                temp = std::string("");
            }
        }
    }
    if (temp.length()> 0)
        wordVec.push_back(temp);
    //  ++mycounter;
    //if (mycounter < 5)
    //{
    //    QMessageBox mybox;
    //    mybox.setText(line.c_str());
    //    mybox.exec();
    //    for (size_t i=0;i<wordVec.size();++i)
     //   {
     //       mybox.setText(wordVec.at(i).c_str());
     //       mybox.exec();
     //   }
    //}
}
void MainWindow::on_toolButton_clicked()
{
    try
    {
        QDir dir;
        QString myRootFolderPath = dir.absolutePath();
        myRootFolderPath += "/PartMachineMap.txt";
        std::ifstream f(myRootFolderPath.toStdString());
        QMessageBox mybox0;
        mybox0.setText(myRootFolderPath);
        //mybox0.exec();
        ui->plainTextEditMessages->setPlainText(myRootFolderPath);

        if(f.is_open() == false)
        {
            mybox0.setText("file not opened");
            mybox0.exec();
        }

        std::map<std::string,std::string> partMachineMap;
        int maxsize = 1000;
        char temp[maxsize];
        char delim('\n');

        while (f.eof() == false)
        {
            f.getline(temp,maxsize,delim);
            //QString myline (temp);
            //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
            std::vector<std::string> myWordList;
            std::string singleLine(temp);
            SplitOneLine(singleLine,myWordList);
            if (myWordList.size() >= 2)
            {
                partMachineMap[myWordList.at(1)] = myWordList.at(0);
                //mybox0.setText(myWordList.at(0));
                //mybox0.exec();
                //mybox0.setText(myWordList.at(1));
                //mybox0.exec();
                //mybox0.setText(myWordList.at(2));
                //mybox0.exec();
            }
            else
            {
                QString qs = QVariant(myWordList.size()).toString();
                mybox0.setText(qs);
                mybox0.exec();
                throw std::exception();
            }
            //mybox0.setText(tempstr2.c_str());
            //mybox0.exec();
        }
        QString mymess = QVariant(partMachineMap.size()).toString();
        //mybox0.setText();
        //mybox0.exec();
        ui->plainTextEditMessages->setPlainText(QString("Map file parsed successfully. map size:") +mymess);
        f.close();


         QString fileName = QFileDialog::getOpenFileName(this);
         std::ifstream file(fileName.toStdString());
         //if (!file.open(QFile::ReadOnly | QFile::Text))
         if (file.is_open() == false)
         {
             QMessageBox::warning(this, tr("Application"),
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(QDir::toNativeSeparators(fileName), " can not be opened"));//file.errorString()));
             return;
         }
        std::vector<PPLine> allLines;
        //mycounter = 0;
         while (file.eof() == false)
         {
             file.getline(temp,maxsize,delim);
             //QString myline (temp);
             //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
             std::vector<std::string> myWordList;
             std::string myline (temp);
             SplitOneLine(myline,myWordList);
             if (myWordList.size() > 7)
             {
                 PPLine curLine(partMachineMap);
                 for (int i=3;i<9;++i)
                 {
                    curLine.SetColumn(myWordList.at(i),i-3);
                 }
                 allLines.push_back(curLine);
             }
         }
         std::string miraeFilePathStr = fileName.toStdString()+std::string(".MIRAE.txt");
         std::string panasonicFilePathStr = fileName.toStdString()+std::string(".PANASONIC.txt");
         std::string noneFilePathStr = fileName.toStdString()+std::string(".NONE.txt");
         std::ofstream fMirae(miraeFilePathStr);
         std::ofstream fPanasonic(panasonicFilePathStr);
         std::ofstream fNone(noneFilePathStr);
         std::vector<PPLine>::iterator pi = allLines.begin();
         std::vector<PPLine>::iterator pe = allLines.end();

         int miraePartCounter=0;
         int panasonicPartCounter = 0;
         int nonePartCounter = 0;
         for (;pi!=pe;++pi)
         {
             int curMachineNo = (*pi).GetMachineNo();
            switch (curMachineNo)
            {
            case 0:
                (*pi).WriteTo(fNone);
                ++nonePartCounter;
                break;
            case 1:
                (*pi).WriteTo((fMirae));
                ++miraePartCounter;
                break;
            case 2:
                (*pi).WriteTo((fPanasonic));
                ++panasonicPartCounter;
                break;
            }
         }
         QString finalMessageStr;
         finalMessageStr += "Mirae part count:";
         finalMessageStr += QVariant(miraePartCounter).toString();
         finalMessageStr += "\n";
         finalMessageStr += "Panasonic part count:";
         finalMessageStr += QVariant(panasonicPartCounter).toString();
         finalMessageStr += "\n";
         finalMessageStr += "None part count:";
         finalMessageStr += QVariant(nonePartCounter).toString();
         finalMessageStr += "\n";

         size_t mycompareNum (32);
         std::string editorPathStr = ui->plainTextEditEditor->toPlainText().toStdString();
         //mybox0.setText(editorPathStr.c_str());
         //mybox0.exec();
         fMirae.close();
         fPanasonic.close();
         fNone.close();
         if (miraePartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE miraeOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),miraeFilePathStr.c_str(),NULL,SW_SHOW);

             if ((size_t)miraeOpenStatus <= mycompareNum)
             {
                    finalMessageStr += "Mirae file could not be opened\n";
                    mybox0.setText(editorPathStr.c_str());
                    mybox0.exec();
                    mybox0.setText(miraeFilePathStr.c_str());
                    mybox0.exec();
             }
             else
             {
                 finalMessageStr += "Mirae file successfully opened\n";
             }
         }
         if (panasonicPartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE panasonicOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),panasonicFilePathStr.c_str(),NULL,SW_SHOW);

             if (((size_t)panasonicOpenStatus) <= mycompareNum)
             {
                finalMessageStr += "Panasonic file could not be opened\n";
             }
             else
             {
                 finalMessageStr += "Panasonic file successfully opened\n";
             }
         }
         if (nonePartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE noneOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),noneFilePathStr.c_str(),NULL,SW_SHOW);

             if (((size_t)noneOpenStatus) <= mycompareNum)
             {
                    finalMessageStr += "None file could not be opened\n";
             }
             else
             {
                 finalMessageStr += "None file successfully opened\n";
             }
         }
         mybox0.setText(finalMessageStr);
         //mybox0.exec();
         ui->plainTextEditMessages->setPlainText(finalMessageStr);
         SaveSettings();
    }
    catch (...)
    {
        QMessageBox mybox;
        mybox.setText("MainWindow::on_toolButton_clicked exception");
        mybox.exec();
    }

}

void MainWindow::SaveSettings()
{
    QDir dir;
    QString mysettingFileStr = dir.absolutePath();
    mysettingFileStr += "/DE_PartMachineMapSettings.txt";
    QFile mySettingFile (mysettingFileStr);
    mySettingFile.open(QFile::WriteOnly | QFile::Text);
    //mySettingFile.write("EditorPath\n");
    m_settings["EditorPath\n"] = ui->plainTextEditEditor->toPlainText();
    m_settings["WorkDirectory\n"] = ui->plainTextEditWorkDirectory->toPlainText();
    for (std::map<QString,QString>::iterator i = m_settings.begin();i!=m_settings.end();++i)
    {
        mySettingFile.write(i->first.toStdString().c_str(),i->first.length());
        mySettingFile.write(i->second.toStdString().c_str(),i->second.length());
    }
    mySettingFile.close();
}

void MainWindow::on_pushButtonAltiumPart2Machines_clicked()
{
    try
    {
        QDir dir;
        QString myRootFolderPath = dir.absolutePath();
        myRootFolderPath += "/PartMachineMap.txt";
        std::ifstream f(myRootFolderPath.toStdString());
        QMessageBox mybox0;
        mybox0.setText(myRootFolderPath);
        //mybox0.exec();
        ui->plainTextEditMessages->setPlainText(myRootFolderPath);

        if(f.is_open() == false)
        {
            mybox0.setText(myRootFolderPath + "file not opened");
            mybox0.exec();
        }

        std::map<std::string,std::string> partMachineMap;
        int maxsize = 1000;
        char temp[maxsize];
        char delim('\n');

        while (f.eof() == false)
        {
            f.getline(temp,maxsize,delim);
            //QString myline (temp);
            //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
            std::vector<std::string> myWordList;
            std::string singleLine(temp);
            SplitOneLine(singleLine,myWordList);
            if (myWordList.size() >= 2)
            {
                partMachineMap[myWordList.at(1)] = myWordList.at(0);
                //mybox0.setText(myWordList.at(0));
                //mybox0.exec();
                //mybox0.setText(myWordList.at(1));
                //mybox0.exec();
                //mybox0.setText(myWordList.at(2));
                //mybox0.exec();
            }
            else
            {
                QString qs = QVariant(myWordList.size()).toString();
                mybox0.setText(qs);
                mybox0.exec();
                throw std::exception();
            }
            //mybox0.setText(tempstr2.c_str());
            //mybox0.exec();
        }
        QString mymess = QVariant(partMachineMap.size()).toString();
        //mybox0.setText();
        //mybox0.exec();
        ui->plainTextEditMessages->setPlainText(QString("Map file parsed successfully. map size:") +mymess);
        f.close();


         QString fileName = QFileDialog::getOpenFileName(this);
         std::ifstream file(fileName.toStdString());
         //if (!file.open(QFile::ReadOnly | QFile::Text))
         if (file.is_open() == false)
         {
             QMessageBox::warning(this, tr("Application"),
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(QDir::toNativeSeparators(fileName), " can not be opened"));//file.errorString()));
             return;
         }
        std::vector<PPLine> allLines;
        //mycounter = 0;
        std::map<int,int> altiumMap;
        altiumMap[3] = 0;   // designator
        altiumMap[4] = 10;  // part name
        altiumMap[5] = 2;   //  x pos
        altiumMap[6] = 3;   // y pos
        altiumMap[7] = 9;   // rot
        altiumMap[8] = 8;   // layer
        QString errormsg;
        while (file.eof() == false)
         {
             file.getline(temp,maxsize,delim);
             //QString myline (temp);
             //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
             std::vector<std::string> myWordList;
             std::string myline (temp);
             SplitOneLine(myline,myWordList);
             if (myWordList.size() > 9)
             {
                 PPLine curLine(partMachineMap);
                 for (int i=3;i<9;++i)
                 {
                    curLine.SetColumn(myWordList.at(altiumMap[i]),i-3);
                 }
                 allLines.push_back(curLine);
             }
             else
             {
                 errormsg += "line format unexpected : ";
                 errormsg += myline.c_str();
                 errormsg += "\n";
             }

         }
         if (errormsg.length() == 0)
         {
             errormsg += "file successfully parsed";
         }
         else
         {
             errormsg += "file parsed with some errors listed above";
         }
         QString prevErrorMsg = ui->plainTextEditEditor->toPlainText();
         prevErrorMsg += "\n";
         ui->plainTextEditMessages->setPlainText(prevErrorMsg + errormsg);
         std::string miraeFilePathStr = fileName.toStdString()+std::string(".MIRAE.txt");
         std::string panasonicFilePathStr = fileName.toStdString()+std::string(".PANASONIC.txt");
         std::string noneFilePathStr = fileName.toStdString()+std::string(".NONE.txt");
         std::ofstream fMirae(miraeFilePathStr);
         std::ofstream fPanasonic(panasonicFilePathStr);
         std::ofstream fNone(noneFilePathStr);
         std::vector<PPLine>::iterator pi = allLines.begin();
         std::vector<PPLine>::iterator pe = allLines.end();

         int miraePartCounter=0;
         int panasonicPartCounter = 0;
         int nonePartCounter = 0;
         for (;pi!=pe;++pi)
         {
             int curMachineNo = (*pi).GetMachineNo();
            switch (curMachineNo)
            {
            case 0:
                (*pi).WriteTo(fNone);
                ++nonePartCounter;
                break;
            case 1:
                (*pi).WriteTo((fMirae));
                ++miraePartCounter;
                break;
            case 2:
                (*pi).WriteTo((fPanasonic));
                ++panasonicPartCounter;
                break;
            }
         }
         QString finalMessageStr;
         finalMessageStr += "Mirae part count:";
         finalMessageStr += QVariant(miraePartCounter).toString();
         finalMessageStr += "\n";
         finalMessageStr += "Panasonic part count:";
         finalMessageStr += QVariant(panasonicPartCounter).toString();
         finalMessageStr += "\n";
         finalMessageStr += "None part count:";
         finalMessageStr += QVariant(nonePartCounter).toString();
         finalMessageStr += "\n";

         size_t mycompareNum (32);
         std::string editorPathStr = ui->plainTextEditEditor->toPlainText().toStdString();
         //mybox0.setText(editorPathStr.c_str());
         //mybox0.exec();
         fMirae.close();
         fPanasonic.close();
         fNone.close();
         if (miraePartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE miraeOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),miraeFilePathStr.c_str(),NULL,SW_SHOW);

             if ((size_t)miraeOpenStatus <= mycompareNum)
             {
                    finalMessageStr += "Mirae file could not be opened\n";
                    mybox0.setText(editorPathStr.c_str());
                    mybox0.exec();
                    mybox0.setText(miraeFilePathStr.c_str());
                    mybox0.exec();
             }
             else
             {
                 finalMessageStr += "Mirae file successfully opened\n";
             }
         }
         if (panasonicPartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE panasonicOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),panasonicFilePathStr.c_str(),NULL,SW_SHOW);

             if (((size_t)panasonicOpenStatus) <= mycompareNum)
             {
                finalMessageStr += "Panasonic file could not be opened\n";
             }
             else
             {
                 finalMessageStr += "Panasonic file successfully opened\n";
             }
         }
         if (nonePartCounter > 0)
         {
             //std::string operationStr("edit");
             HINSTANCE noneOpenStatus = ShellExecuteA(NULL,NULL,editorPathStr.c_str(),noneFilePathStr.c_str(),NULL,SW_SHOW);

             if (((size_t)noneOpenStatus) <= mycompareNum)
             {
                    finalMessageStr += "None file could not be opened\n";
             }
             else
             {
                 finalMessageStr += "None file successfully opened\n";
             }
         }
         mybox0.setText(finalMessageStr);
         //mybox0.exec();
         prevErrorMsg = ui->plainTextEditEditor->toPlainText();
         prevErrorMsg += "\n";
         ui->plainTextEditMessages->setPlainText(prevErrorMsg + finalMessageStr);
         SaveSettings();
    }
    catch (...)
    {
        QMessageBox mybox;
        mybox.setText("MainWindow::on_toolButton_clicked exception");
        mybox.exec();
    }
}


void MainWindow::on_pushButtonPanasonicCoordsToOriginal_clicked()
{
    try
    {
        int maxsize = 1000;
        char temp[maxsize];
        char delim('\n');
        std::map<std::string,std::string> dummyPartMachineMap;
        QString fileName = QFileDialog::getOpenFileName(this,tr("Select Altium Design CAD file for Part"),ui->plainTextEditWorkDirectory->toPlainText(),tr("Text files (*.txt)"));
        std::ifstream file(fileName.toStdString());
        //if (!file.open(QFile::ReadOnly | QFile::Text))
        if (file.is_open() == false)
        {
            QMessageBox::warning(this, tr("Application"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), " can not be opened"));//file.errorString()));
            return;
        }
        std::map<std::string,PPLine *> designatorLinesMap;
        //mycounter = 0;
        std::map<int,int> altiumMap;
        altiumMap[3] = 0;   // designator
        altiumMap[4] = 10;  // part name
        altiumMap[5] = 2;   //  x pos
        altiumMap[6] = 3;   // y pos
        altiumMap[7] = 9;   // rot
        altiumMap[8] = 8;   // layer
        QString errormsg;
        while (file.eof() == false)
         {
             file.getline(temp,maxsize,delim);
             //QString myline (temp);
             //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
             std::vector<std::string> myWordList;
             std::string myline (temp);
             SplitOneLine(myline,myWordList);
             if (myWordList.size() > 9)
             {
                 PPLine *curLine = new PPLine(dummyPartMachineMap);
                 for (int i=3;i<9;++i)
                 {
                    curLine->SetColumn(myWordList.at(altiumMap[i]),i-3);
                 }
                 designatorLinesMap[myWordList.at(0)] = curLine;
             }
             else
             {
                 errormsg += "line format unexpected : ";
                 errormsg += myline.c_str();
                 errormsg += "\n";
             }

         }
         if (errormsg.length() == 0)
         {
             errormsg += "file successfully parsed";
         }
         else
         {
             errormsg += "file parsed with some errors listed above";
         }
         QString prevErrorMsg = ui->plainTextEditEditor->toPlainText();
         prevErrorMsg += "\n";
         ui->plainTextEditMessages->setPlainText(prevErrorMsg + errormsg);

         QString panasonicFileName = QFileDialog::getOpenFileName(this,"Select panasonic file",ui->plainTextEditWorkDirectory->toPlainText(),"Text files (*.txt)");
         std::ifstream panasonicfile(panasonicFileName.toStdString());
         //if (!file.open(QFile::ReadOnly | QFile::Text))
         if (panasonicfile.is_open() == false)
         {
             QMessageBox::warning(this, tr("Application"),
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(QDir::toNativeSeparators(fileName), " panasonic file can not be opened"));//file.errorString()));
             return;
         }
         QString errormsg2;
         std::list<PPLine *> panasonicLinesList;
         while (panasonicfile.eof() == false)
          {
              panasonicfile.getline(temp,maxsize,delim);
              //QString myline (temp);
              //QStringList myWordList = myline.split(QRegularExpression("\\s+"));
              std::vector<std::string> myWordList;
              std::string myline (temp);
              SplitOneLine(myline,myWordList);
              if (myWordList.size() > 5)
              {
                  PPLine *curLine = new PPLine(dummyPartMachineMap);
                  for (int i=0;i<6;++i)
                  {
                     curLine->SetColumn(myWordList.at(i),i);
                  }
                  std::map<std::string,PPLine *>::iterator fi = designatorLinesMap.find(myWordList.at(0));
                  if (fi != designatorLinesMap.end())
                  {
                      curLine->SetXPos(fi->second->GetXPos());
                      curLine->SetYPos(fi->second->GetYPos());
                    panasonicLinesList.push_back(curLine);
                  }
                  else
                  {
                      errormsg2 += myWordList.at(0).c_str();
                      errormsg2 += " designator not found in Altium file\n";
                  }
              }
              else
              {
                  errormsg2 += "line format unexpected : ";
                  errormsg2 += myline.c_str();
                  errormsg2 += "\n";
              }

          }
          if (errormsg2.length() == 0)
          {
              errormsg2 += "Panasonic file successfully parsed and modified";
          }
          else
          {
              errormsg2 += "file parsed with some errors listed above";
          }
          QString prevErrorMsg2 = ui->plainTextEditEditor->toPlainText();
          prevErrorMsg2 += "\n";
          ui->plainTextEditMessages->setPlainText(prevErrorMsg2 + errormsg2);

          QString outFileName (panasonicFileName + "XYposAltium.txt");
          std::ofstream fout (outFileName.toStdString());
          if (fout.is_open() == false)
          {
              QMessageBox::warning(this, tr("Application"),
                                   tr("Cannot write file %1:\n%2.")
                                   .arg(QDir::toNativeSeparators(outFileName), " modified panasonic file can not be opened"));//file.errorString()));
              return;
          }
          std::list<PPLine *>::iterator li = panasonicLinesList.begin();
          std::list<PPLine *>::iterator le = panasonicLinesList.end();
          for (;li!=le;++li)
          {
              (*li)->WriteTo(fout);
          }
          fout.close();
    }
    catch(...)
    {

    }
}

