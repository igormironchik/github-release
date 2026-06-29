/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

#pragma once

// Qt include.
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QString>
#include <QToolButton>
#include <QVariantAnimation>

namespace GHRelease
{

//! Compare versions of type "Major.Minor.Patch".
bool majorMinorPatchCompare(const QString &current,
                            const QString &latest);

//! Check for updates.
template<class CompareVersion>
bool isUpdateAvailable(const QString &user,
                       const QString &project,
                       const QString &currentVersion,
                       CompareVersion cv,
                       QString &newVersionUrl,
                       QString &newVersionTag)
{
    QNetworkAccessManager net;
    QNetworkRequest req;
    req.setUrl(QUrl(QStringLiteral("https://api.github.com/repos/%1/%2/releases/latest").arg(user, project)));
    req.setRawHeader("User-Agent", "github-release-tool");
    req.setRawHeader("Accept", "application/vnd.github+json");

    auto reply = net.get(req);

    QEventLoop loop;

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    QByteArray responseData;
    bool ret = false;

    if (reply->error() == QNetworkReply::NoError) {
        responseData = reply->readAll();

        const auto json = QJsonDocument::fromJson(responseData);

        if (!json.isNull()) {
            const auto obj = json.object();

            static const QString s_tagName = QStringLiteral("tag_name");
            static const QString s_htmlUrlName = QStringLiteral("html_url");

            if (obj.contains(s_tagName)) {
                newVersionTag = obj.value(s_tagName).toString();

                if (obj.contains(s_htmlUrlName)) {
                    newVersionUrl = obj.value(s_htmlUrlName).toString();

                    if (cv(currentVersion, newVersionTag)) {
                        ret = true;
                    }
                }
            }
        }
    }

    reply->deleteLater();

    return ret;
}

//
// NewVersionAvailableButton
//

//! Tool button indicating new version is available.
class NewVersionAvailableButton : public QToolButton
{
    Q_OBJECT

public:
    //! Default behaviour.
    enum DefaultBehaviour {
        DoNothing,
        OpenUrlOnClick
    };

    explicit NewVersionAvailableButton(const QString &url,
                                       DefaultBehaviour behaviour = DoNothing,
                                       QWidget *parent = nullptr);
    ~NewVersionAvailableButton() override;

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    void onAnimationStep(const QVariant &value);
    void onAnimationFinished();
    void onStartAnimation();

private:
    QString m_url;
    QVariantAnimation *m_anim;
    QImage m_bgGradient;
    QImage m_textGradient;
    qreal m_animProgress = 0.0;
}; // class NewVersionAvailableButton

} /* namespace GHRelease */
