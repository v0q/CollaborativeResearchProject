#pragma once

#include <QtCore/QString>
#include <QtCore/QVariant>

/// @brief Node Editor
/// Dimitry Pinaev.
/// [Accessed November 2016]. Available from: https://github.com/paceholder/nodeeditor

namespace std
{
template<>
struct hash<QString>
{
  inline std::size_t
  operator()(QString const &s) const
  {
    return qHash(s);
  }
};
}
