/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

#pragma once

// Qt include.
#include <QString>
#include <QToolButton>

namespace GHRelease
{

template<class CompareVersion>
bool isUpdateAvailable(const QString &user,
                       const QString &project,
                       const QString &currentVersion,
                       CompareVersion cv,
                       QString &newVersionUrl)
{
    return false;
}

//
// NewVersionAvailableButton
//

class NewVersionAvailableButton : public QToolButton
{
    Q_OBJECT

public:
    explicit NewVersionAvailableButton(QWidget *parent);
    ~NewVersionAvailableButton() override;
}; // class NewVersionAvailableButton

} /* namespace GHRelease */
