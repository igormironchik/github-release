/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "github.h"

namespace GHRelease
{

static const QChar s_dot = QLatin1Char('.');

bool majorMinorPatchCompare(const QString &current, const QString &latest)
{
    const auto currentArray = current.split(s_dot, Qt::SkipEmptyParts);
    const auto latestArray = latest.split(s_dot, Qt::SkipEmptyParts);

    if (currentArray.size() != 3 && currentArray.size() != latestArray.size()) {
        return false;
    }

    if (latestArray[0].toInt() > currentArray[0].toInt()) {
        return true;
    }

    if (latestArray[0].toInt() == currentArray[0].toInt()) {
        if (latestArray[1].toInt() > currentArray[1].toInt()) {
            return true;
        }

        if (latestArray[1].toInt() == currentArray[1].toInt()) {
            if (latestArray[2].toInt() > currentArray[2].toInt()) {
                return true;
            }
        }
    }

    return false;
}

//
// NewVersionAvailableButton
//

NewVersionAvailableButton::NewVersionAvailableButton(QWidget *parent)
    : QToolButton(parent)
{
}

NewVersionAvailableButton::~NewVersionAvailableButton() = default;

} /* namespace GHRelease */
