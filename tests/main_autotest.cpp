/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "../src/github.h"

// Qt include.
#include <QtTest/QtTest>

using namespace GHRelease;

//
// TestGitHubRelease
//

class TestGitHubRelease final : public QObject
{
    Q_OBJECT

private slots:
    void test_majorMinorPatchCompare()
    {
        QVERIFY(!majorMinorPatchCompare(QStringLiteral("1.0.0"), QStringLiteral("1.0.0")));
        QVERIFY(!majorMinorPatchCompare(QStringLiteral("1.1.0"), QStringLiteral("1.1.0")));
        QVERIFY(!majorMinorPatchCompare(QStringLiteral("1.1.1"), QStringLiteral("1.1.1")));
        QVERIFY(majorMinorPatchCompare(QStringLiteral("1.0.0"), QStringLiteral("1.0.1")));
        QVERIFY(majorMinorPatchCompare(QStringLiteral("1.0.0"), QStringLiteral("1.1.0")));
        QVERIFY(majorMinorPatchCompare(QStringLiteral("1.0.0"), QStringLiteral("2.0.0")));
        QVERIFY(!majorMinorPatchCompare(QStringLiteral("1.0.0"), QString()));
        QVERIFY(!majorMinorPatchCompare(QString(), QStringLiteral("1.0.0")));
        QVERIFY(!majorMinorPatchCompare(QStringLiteral("1.0.0.0"), QStringLiteral("1.0.0.1")));
        QVERIFY(!majorMinorPatchCompare(QString(), QString()));
    }
}; // class TestGitHubRelease

QTEST_MAIN(TestGitHubRelease)

#include "main_autotest.moc"
