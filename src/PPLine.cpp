// PPLine.cpp

#include "PPLine.h"
#include <iostream>
#include <fstream>
#include <QVariant>

PPLine::PPLine(const std::map<std::string,std::string> &partMachineMap)
    :m_partMachineMap(partMachineMap)
{
    m_lineColumns.resize(6);
    for(size_t i=0;i<6;++i)
         m_lineColumns[i] = "0";
}

void PPLine::SetColumn(const std::string &val,int columni)
{
    if (columni >= 0 && columni < 6)
    {
        m_lineColumns.at(columni) = val;
    }
    else
    {
        throw std::exception();
    }
}
const std::string & PPLine::GetColumn(int i)const
{
    if (i >= 0 && i < 6)
    {
        return m_lineColumns.at(i);
    }
    else
    {
        throw std::exception();
    }
}
void PPLine::WriteTo (std::ofstream &f)
{
    for(int i=0;i<5;++i)
    {
        f << m_lineColumns.at(i).c_str() << "   ";
    }
    f << m_lineColumns.at(5).c_str() << "\n";
}
int PPLine::GetMachineNo()const
{
    const std::string &pn = m_lineColumns.at(1);
    std::map<std::string,std::string>::const_iterator fi = m_partMachineMap.find(pn);
    if (fi == m_partMachineMap.end())
        return 0;
    else if (fi->second == "MIRAE")
        return 1;
    else if (fi->second == "PANASONIC")
        return 2;
    else
        return 0;
}

double PPLine::GetXPos() const
{
    QVariant var(m_lineColumns[2].c_str());
    return var.toDouble();
}

double PPLine::GetYPos() const
{
    QVariant var(m_lineColumns[3].c_str());
    return var.toDouble();
}

void PPLine::SetXPos(double xPos)
{
    QVariant var(xPos);
    m_lineColumns[2] = var.toString().toStdString();
}
void PPLine::SetYPos(double yPos)
{
    QVariant var(yPos);
    m_lineColumns[3] = var.toString().toStdString();
}
