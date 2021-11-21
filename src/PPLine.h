#ifndef PPLINE_H
#define PPLINE_H
#include <QString>
#include <map>
class PPLine
{
public:
    PPLine(const std::map<std::string,std::string> &partMachineMap);
    void SetColumn(const std::string &val,int columni);
    const std::string & GetColumn(int column)const;
    void WriteTo (std::ofstream &f);
    int GetMachineNo()const;
    double GetXPos()const;
    double GetYPos()const;
    void SetXPos(double xPos);
    void SetYPos(double yPos);
private:
    std::vector<std::string> m_lineColumns;
    const std::map<std::string,std::string> &m_partMachineMap;
};

#endif // PPLINE_H
