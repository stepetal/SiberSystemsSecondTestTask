#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <QMetaType>
#include <QString>
#include <QByteArray>

namespace SYS
{
    class Error : public std::exception
    {
    public:
        explicit Error(const QString& message) noexcept
            : charArray(message.toUtf8()) {}
        ~Error() noexcept {}

        const char *what() const noexcept {
            return charArray.data();
        }

    private:
        QByteArray charArray;
    };
}

#endif // EXCEPTIONS_H
