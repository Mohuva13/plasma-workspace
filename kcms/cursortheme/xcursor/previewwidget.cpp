/*
    SPDX-FileCopyrightText: 2003-2007 Fredrik Höglund <fredrik@kde.org>

    SPDX-License-Identifier: GPL-2.0-only
*/

#include <QMouseEvent>
#include <QPainter>
#include <QQuickRenderControl>
#include <QQuickWindow>

#include <KWindowSystem>

#include "previewwidget.h"

#include "config-X11.h"
#include "cursortheme.h"

namespace
{
// Preview cursors
const char *const cursor_names[] = {
    "left_ptr",
    "left_ptr_watch",
    "wait",
    "pointer",
    "help",
    "ibeam",
    "size_all",
    "size_fdiag",
    "cross",
    "split_h",
    "size_ver",
    "size_hor",
    "size_bdiag",
    "split_v",
};

const int numCursors = 9; // The number of cursors from the above list to be previewed
constexpr int cursorSpacing = 14 * 2; // Spacing between preview cursors
const qreal widgetMinWidth = 10; // The minimum width of the preview widget
const qreal widgetMinHeight = 48; // The minimum height of the preview widget
}

class PreviewCursor
{
public:
    PreviewCursor(const CursorTheme *theme, const QString &name, int size);

    const QPixmap &pixmap() const
    {
        return m_pixmap;
    }
    int width() const
    {
        return m_pixmap.width();
    }
    int height() const
    {
        return m_pixmap.height();
    }
    int boundingSize() const
    {
        return m_boundingSize;
    }
    inline QRectF rect() const;
    void setPosition(const QPoint &p)
    {
        m_pos = p;
    }
    void setPosition(int x, int y)
    {
        m_pos = QPoint(x, y);
    }
    QPoint position() const
    {
        return m_pos;
    }
    operator const QPixmap &() const
    {
        return pixmap();
    }
    const std::vector<CursorTheme::CursorImage> &images() const
    {
        return m_images;
    }

private:
    int m_boundingSize;
    QPixmap m_pixmap;
    std::vector<CursorTheme::CursorImage> m_images;
    QPoint m_pos;
};

PreviewCursor::PreviewCursor(const CursorTheme *theme, const QString &name, int size)
    : m_boundingSize(size > 0 ? size : theme->defaultCursorSize())
    , m_images(theme->loadImages(name, size))
{
    if (m_images.empty())
        return;

    m_pixmap = QPixmap::fromImage(m_images.front().image);
}

QRectF PreviewCursor::rect() const
{
    return QRectF(m_pos, m_pixmap.size()).adjusted(-(cursorSpacing / 2), -(cursorSpacing / 2), cursorSpacing / 2, cursorSpacing / 2);
}

// ------------------------------------------------------------------------------

PreviewWidget::PreviewWidget(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_currentIndex(-1)
    , m_currentSize(0)
{
    setAcceptHoverEvents(true);
    current = nullptr;
    connect(&m_animationTimer, &QTimer::timeout, this, [this] {
        Q_ASSERT(current);
        setCursor(QCursor(QPixmap::fromImage(current->images().at(nextAnimationFrame).image)));
        m_animationTimer.setInterval(current->images().at(nextAnimationFrame).delay);
        nextAnimationFrame = (nextAnimationFrame + 1) % current->images().size();
    });
}

PreviewWidget::~PreviewWidget()
{
    qDeleteAll(list);
    list.clear();
}

void PreviewWidget::setThemeModel(SortProxyModel *themeModel)
{
    if (m_themeModel == themeModel) {
        return;
    }

    m_themeModel = themeModel;
    Q_EMIT themeModelChanged();
}

SortProxyModel *PreviewWidget::themeModel()
{
    return m_themeModel;
}

void PreviewWidget::setCurrentIndex(int idx)
{
    if (m_currentIndex == idx) {
        return;
    }

    m_currentIndex = idx;
    Q_EMIT currentIndexChanged();

    if (!m_themeModel) {
        return;
    }
    const CursorTheme *theme = m_themeModel->theme(m_themeModel->index(idx, 0));
    setTheme(theme, m_currentSize);
}

int PreviewWidget::currentIndex() const
{
    return m_currentIndex;
}

void PreviewWidget::setCurrentSize(int size)
{
    if (m_currentSize == size) {
        return;
    }

    m_currentSize = size;
    Q_EMIT currentSizeChanged();

    if (!m_themeModel) {
        return;
    }
    const CursorTheme *theme = m_themeModel->theme(m_themeModel->index(m_currentIndex, 0));
    setTheme(theme, size);
}

int PreviewWidget::currentSize() const
{
    return m_currentSize;
}

void PreviewWidget::refresh()
{
    if (!m_themeModel) {
        return;
    }

    const CursorTheme *theme = m_themeModel->theme(m_themeModel->index(m_currentIndex, 0));
    setTheme(theme, m_currentSize);
}

void PreviewWidget::updateImplicitSize()
{
    qreal totalWidth = 0;
    qreal maxHeight = 0;

    for (const auto *c : std::as_const(list)) {
        totalWidth += c->width();
        maxHeight = qMax(c->height(), (int)maxHeight);
    }

    totalWidth += (list.count() - 1) * cursorSpacing;
    maxHeight = qMax(maxHeight, widgetMinHeight);

    setImplicitWidth(qMax(totalWidth, widgetMinWidth));
    setImplicitHeight(qMax(height(), maxHeight));
}

void PreviewWidget::layoutItems()
{
    if (!list.isEmpty()) {
        double deviceCoordinateWidth = width();
#if HAVE_X11
        if (KWindowSystem::isPlatformX11()) {
            deviceCoordinateWidth *= window()->devicePixelRatio();
        }
#endif
        const int spacing = cursorSpacing / 2;
        int nextX = spacing;
        int nextY = spacing;

        for (auto *c : std::as_const(list)) {
            c->setPosition(nextX, nextY);
            const int boundingSize = c->boundingSize();
            nextX += boundingSize + spacing;
            if (nextX + boundingSize > deviceCoordinateWidth) {
                nextX = spacing;
                nextY += boundingSize + spacing;
            }
        }
    }

    needLayout = false;
}

void PreviewWidget::setTheme(const CursorTheme *theme, const int size)
{
    qDeleteAll(list);
    list.clear();

    if (theme) {
        for (int i = 0; i < numCursors; i++)
            list << new PreviewCursor(theme, cursor_names[i], size);

        needLayout = true;
        updateImplicitSize();
    }

    current = nullptr;
    m_animationTimer.stop();
    update();
}

void PreviewWidget::paint(QPainter *painter)
{
    if (needLayout)
        layoutItems();

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    // for cursor themes we must ignore the native scaling,
    // as they will be rendered by X11/KWin, ignoring whatever Qt
    // scaling
    double devicePixelRatio = 1;
#if HAVE_X11
    if (KWindowSystem::isPlatformX11()) {
        devicePixelRatio = window()->devicePixelRatio();
    }
    painter->scale(1 / devicePixelRatio, 1 / devicePixelRatio);
#endif
    for (const auto *c : std::as_const(list)) {
        if (c->pixmap().isNull())
            continue;

        painter->drawPixmap(c->position(), *c);
    }
}

void PreviewWidget::hoverMoveEvent(QHoverEvent *e)
{
    e->ignore(); // Propagate hover event to parent

    if (needLayout)
        layoutItems();

    double devicePixelRatio = 1.0;
#if HAVE_X11
    if (KWindowSystem::isPlatformX11()) {
        devicePixelRatio = window()->devicePixelRatio();
    }
#endif
    auto it = std::find_if(list.cbegin(), list.cend(), [e, devicePixelRatio](const PreviewCursor *c) {
        return c->rect().contains(e->position() * devicePixelRatio);
    });
    const PreviewCursor *cursor = it != list.cend() ? *it : nullptr;

    if (cursor == std::exchange(current, cursor)) {
        return;
    }
    m_animationTimer.stop();

    if (current == nullptr) {
        setCursor(Qt::ArrowCursor);
        return;
    }

    if (current->images().size() <= 1) {
        setCursor(QCursor(current->pixmap()));
        return;
    }

    nextAnimationFrame = 0;
    m_animationTimer.setInterval(0);
    m_animationTimer.start();
}

void PreviewWidget::hoverLeaveEvent(QHoverEvent *e)
{
    m_animationTimer.stop();
    unsetCursor();

    e->ignore(); // Propagate hover event to parent
}

void PreviewWidget::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(newGeometry)
    Q_UNUSED(oldGeometry)
    if (!list.isEmpty()) {
        needLayout = true;
    }
}
