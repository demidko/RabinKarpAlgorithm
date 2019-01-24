#include "SmartStream/SmartStream.h"
#include "RandomInt.h"

namespace Logic
{
    class HashSession
    {
    private:
        int Q, X;

    public:
        size_t CalculateHash(const std::string_view &s)
        {
            size_t res = 0;
            for (size_t i = 0; i < size(s); ++i) 
            {
                res += int(s[i]) * pow(X, size(s) - i - 1);
            }
            return res % Q;
        }

        HashSession()
        {
            Q = RandomInt(1, 10000);
            X = RandomInt(0, Q - 1);
        }
    };
}

namespace UI
{
    std::pair<std::string, std::string> ReadTextAndPatten()
    {
        using namespace SmartStream;
        std::string text, pattern;
        ((io << "Основная строка: ").ReadLine(text) << "Строка для поика: ").ReadLine(pattern);
        return { text, pattern };
    }

    void ShowAllOccurrences(const std::string_view &text, const std::string_view &pattern)
    {
        using namespace SmartStream;
        io << "Процедура поиска всех вхождений подстроки:" << tabl;
        Logic::HashSession session;
        auto textHash = session.CalculateHash(text.substr(0, size(pattern)));
        const auto patternHash = session.CalculateHash(pattern.substr(0, size(pattern)));
        for (size_t i = 0; i <= size(text) - size(pattern); ++i)
        {
            if (textHash == patternHash)
            {
                io << "Найдено вхождение подстроки с символа №" << i + 1 << endl;
            }
            textHash = session.CalculateHash(text.substr(i + 1, size(pattern)));
        }
        io << untab;
    }
}

int main()
{
    while (true)
    {
        const auto[str, sub] = UI::ReadTextAndPatten();
        UI::ShowAllOccurrences(str, sub);
    }
}