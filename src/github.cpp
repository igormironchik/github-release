/*
    SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
    SPDX-License-Identifier: MIT
*/

// github-release include.
#include "github.h"

// Qt include.
#include <QDesktopServices>
#include <QPalette>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QStylePainter>
#include <QTimer>

namespace GHRelease
{

static const QChar s_dot = QLatin1Char('.');

bool majorMinorPatchCompare(const QString &current,
                            const QString &latest)
{
    const auto currentArray = current.split(s_dot, Qt::SkipEmptyParts);
    const auto latestArray = latest.split(s_dot, Qt::SkipEmptyParts);

    if (currentArray.size() != 3 || currentArray.size() != latestArray.size()) {
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

NewVersionAvailableButton::NewVersionAvailableButton(const QString &url,
                                                     DefaultBehaviour behaviour,
                                                     QWidget *parent)
    : QToolButton(parent)
    , m_url(url)
    , m_anim(new QVariantAnimation(this))
    , m_bgGradient(1000,
                   5,
                   QImage::Format_ARGB32)
    , m_textGradient(1000,
                     5,
                     QImage::Format_ARGB32)
{
    switch (behaviour) {
    case OpenUrlOnClick: {
        connect(this, &QToolButton::clicked, [this]() {
            QDesktopServices::openUrl(this->m_url);
        });
    } break;

    default:
        break;
    }

    {
        QLinearGradient bg(m_bgGradient.rect().topLeft(), m_bgGradient.rect().topRight());
        bg.setColorAt(0.0, palette().color(QPalette::Button));
        bg.setColorAt(0.5, palette().color(QPalette::Highlight));
        bg.setColorAt(1.0, palette().color(QPalette::Button));

        QPainter p(&m_bgGradient);
        p.fillRect(m_bgGradient.rect(), bg);
    }

    {
        QLinearGradient text(m_textGradient.rect().topLeft(), m_textGradient.rect().topRight());
        text.setColorAt(0.0, palette().color(QPalette::ButtonText));
        text.setColorAt(0.5, palette().color(QPalette::HighlightedText));
        text.setColorAt(1.0, palette().color(QPalette::ButtonText));

        QPainter p(&m_textGradient);
        p.fillRect(m_textGradient.rect(), text);
    }

    m_anim->setStartValue(0.0);
    m_anim->setEndValue(1.0);
    m_anim->setDuration(600);

    connect(m_anim, &QVariantAnimation::valueChanged, this, &NewVersionAvailableButton::onAnimationStep);
    connect(m_anim, &QVariantAnimation::finished, this, &NewVersionAvailableButton::onAnimationFinished);
    onStartAnimation();

    setText(tr("Update"));
}

NewVersionAvailableButton::~NewVersionAvailableButton() = default;

void NewVersionAvailableButton::onAnimationStep(const QVariant &value)
{
    m_animProgress = value.toReal();
    update();
}

void NewVersionAvailableButton::onAnimationFinished()
{
    QTimer::singleShot(1000 * 60, this, &NewVersionAvailableButton::onStartAnimation);
}

void NewVersionAvailableButton::onStartAnimation()
{
    m_anim->start();
}

void NewVersionAvailableButton::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    opt.palette.setColor(
        QPalette::Button,
        m_bgGradient.pixelColor(qMin(qRound(m_bgGradient.width() * m_animProgress), m_bgGradient.width() - 1), 1));
    opt.palette.setColor(
        QPalette::ButtonText,
        m_textGradient.pixelColor(qMin(qRound(m_textGradient.width() * m_animProgress), m_textGradient.width() - 1),
                                  1));
    p.drawComplexControl(QStyle::CC_ToolButton, opt);
}

} /* namespace GHRelease */
