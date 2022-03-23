#include "Gcode.h"

int Gcode::m_x = 0;
int Gcode::m_y = 0;
int Gcode::m_z = 0;

void Gcode::parse_string(const std::string& st)
{
    std::string temp, is_correct; // is_correct ���������� ��� �������� �������� �������� ��� �� �������� ������
    int tx{ 0 }, ty{ 0 }, tz{ 0 }; // ��������� ���������� ��� �������� � �������� ��������� � ������ ������

    try
    {
        for (int i = 0; i < st.size(); ++i)
        {
            switch (st[i])
            {
            case 'X':
            {
                ++i;
                while (st[i] != ';')
                {
                    if (st[i] != '-')
                        // �������� �� ������� � �����(�������� ����� �� ����� "X-1w0;Y-2-0;Z-2w0;"; � ��)
                    {
                        is_correct = st[i];
                        stoi(is_correct); // � ������ ������ ������������� exception stoi
                    }
                    else
                    {
                        if (st[i - 1] != 'X')   // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_x += std::stoi(temp);
                tx = stoi(temp); // � ������ ������ ������������� exception stoi
                temp.erase();   // ������� ��������� ���������� ��� ��������� ��������
                break;
            }

            case 'Y':
            {
                ++i;
                while (st[i] != ';')
                {
                    if (st[i] != '-')
                        // �������� �� ������� � �����(�������� ����� �� ����� "X-1w0;Y-2-0;Z-2w0;"; � ��)
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != 'Y') // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number ");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_y += std::stoi(temp);
                ty = stoi(temp);
                temp.erase();
                break;
            }

            case 'Z':
            {
                ++i;
                while (st[i] != ';')
                {
                    if (st[i] != '-')   // �������� �� ������� � �����
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != 'Z') // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_z += std::stoi(temp);
                tz = stoi(temp);
                temp.erase();
                break;
            }

            default:
            {
                while (st[i] != ' ')
                {
                    if (st[i] != '-')   // �������� �� ������� � �����
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[0] != '-') // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_x += std::stoi(temp);
                tx = stoi(temp);
                temp.erase();

                ++i; // ����� �� ���� ������
                while (st[i] != ' ')
                {
                    if (st[i] != '-')   // �������� �� ������� � �����
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != ' ') // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_y += std::stoi(temp);
                ty = stoi(temp);
                temp.erase();
                ++i; // ����� �� ���� ������
                while (st[i] != '\0')
                {
                    if (st[i] != '-')   // �������� �� ������� � �����
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != ' ') // �������� �� ���� - ���� �� �� ����� ������ �� ���������� ����������
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // ����� �� ���� ������
                }
                m_z += std::stoi(temp);
                tz = stoi(temp);
                temp.erase();
                break;
            }
            }
        }
    }
    catch (const std::exception&)
    {
        // ������� � ����������� ����������
        m_x -= tx;
        m_y -= ty;
        m_z -= tz;

        std::cout << std::endl;
        print();
        std::cout << "ERROR SCRIPT" << std::endl;
        
        //���������� ��� parse_string(const std::vector<std::string>& vstring)
        throw  std::invalid_argument("incorrect number");
    }
}

void Gcode::parse_string(const std::vector<std::string>& vstring)
{
    for(auto elem : vstring)
    {
        try
        {
            Gcode::parse_string(elem);
        }
        catch (const std::exception&)
        {
            return;
        }
    }
    Gcode::print();
}

void Gcode::print()
{
    std::cout << m_x << " " << m_y << " " << m_z << std::endl;
}

void Gcode::reset()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}
