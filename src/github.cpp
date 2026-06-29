/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "github.h"

namespace GHRelease
{

//
// NewVersionAvailableButton
//

NewVersionAvailableButton::NewVersionAvailableButton(QWidget *parent)
    : QToolButton(parent)
{
}

NewVersionAvailableButton::~NewVersionAvailableButton() = default;

} /* namespace GHRelease */
