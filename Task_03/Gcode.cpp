#include "Gcode.h"

int Gcode::m_x = 0;
int Gcode::m_y = 0;
int Gcode::m_z = 0;

void Gcode::parse_string(const std::string& st)
{
    std::string temp, is_correct; // is_correct переменная для проверки текущего элемента что он является числом
    int tx{ 0 }, ty{ 0 }, tz{ 0 }; // временные переменные для возврата к исходным значениям в случае ошибки

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
                        // проверка на символы в числе(например когда на входе "X-1w0;Y-2-0;Z-2w0;"; и тд)
                    {
                        is_correct = st[i];
                        stoi(is_correct); // в случае ошибки выбрасывается exception stoi
                    }
                    else
                    {
                        if (st[i - 1] != 'X')   // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
                }
                m_x += std::stoi(temp);
                tx = stoi(temp); // в случае ошибки выбрасывается exception stoi
                temp.erase();   // очистка временной переменной для следующих итераций
                break;
            }

            case 'Y':
            {
                ++i;
                while (st[i] != ';')
                {
                    if (st[i] != '-')
                        // проверка на символы в числе(например когда на входе "X-1w0;Y-2-0;Z-2w0;"; и тд)
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != 'Y') // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number ");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
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
                    if (st[i] != '-')   // проверка на символы в числе
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != 'Z') // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
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
                    if (st[i] != '-')   // проверка на символы в числе
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[0] != '-') // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
                }
                m_x += std::stoi(temp);
                tx = stoi(temp);
                temp.erase();

                ++i; // сдвиг на след символ
                while (st[i] != ' ')
                {
                    if (st[i] != '-')   // проверка на символы в числе
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != ' ') // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
                }
                m_y += std::stoi(temp);
                ty = stoi(temp);
                temp.erase();
                ++i; // сдвиг на след символ
                while (st[i] != '\0')
                {
                    if (st[i] != '-')   // проверка на символы в числе
                    {
                        is_correct = st[i];
                        stoi(is_correct);
                    }
                    else
                    {
                        if (st[i - 1] != ' ') // проверка на знак - если он не перед числом то выбрасываю исключение
                            throw  std::invalid_argument("incorrect number");
                    }
                    temp += st[i];
                    ++i; // сдвиг на след символ
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
        // возврат к предыдущему результату
        m_x -= tx;
        m_y -= ty;
        m_z -= tz;

        std::cout << std::endl;
        print();
        std::cout << "ERROR SCRIPT" << std::endl;
        
        //исключение для parse_string(const std::vector<std::string>& vstring)
        throw  std::invalid_argument("incorrect number");
    }
}

void Gcode::parse_string(const std::vector<std::string>& vstring)
{
    for(const auto &elem : vstring)
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
