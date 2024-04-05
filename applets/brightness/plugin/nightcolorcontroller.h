/*
 * SPDX-FileCopyrightText: 2019 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <qqmlregistration.h>

class NightColorControllerPrivate;

/**
 * The Monitor provides a way for monitoring the state of Night Color.
 */
class NightColorController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    /**
     * This property holds a value to indicate if Night Color is available.
     */
    Q_PROPERTY(bool available READ isAvailable NOTIFY availableChanged)

    /**
     * This property holds a value to indicate if Night Color is enabled.
     */
    Q_PROPERTY(bool enabled READ isEnabled NOTIFY enabledChanged)

    /**
     * This property holds a value to indicate if Night Color is running.
     */
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)

    /**
     * This property holds a value to indicate if Night Color is on day mode.
     */
    Q_PROPERTY(bool daylight READ isDaylight NOTIFY daylightChanged)

    /**
     * This property holds a value to indicate which mode is set for transitions (0 - automatic location, 1 - manual location, 2 - manual timings, 3 - constant)
     */
    Q_PROPERTY(int mode READ mode NOTIFY modeChanged)

    /**
     * This property holds a value to indicate currently applied color temperature.
     */
    Q_PROPERTY(int currentTemperature READ currentTemperature NOTIFY currentTemperatureChanged)

    /**
     * This property holds a value to indicate currently applied color temperature.
     */
    Q_PROPERTY(int targetTemperature READ targetTemperature NOTIFY targetTemperatureChanged)

    /**
     * This property holds a value to indicate the end time of the previous color transition in msec since epoch.
     */
    Q_PROPERTY(quint64 currentTransitionEndTime READ currentTransitionEndTime NOTIFY currentTransitionEndTimeChanged)

    /**
     * This property holds a value to indicate the start time of the next color transition in msec since epoch.
     */
    Q_PROPERTY(quint64 scheduledTransitionStartTime READ scheduledTransitionStartTime NOTIFY scheduledTransitionStartTimeChanged)

    /**
     * This property holds a value to indicate the current state of the inhibitor.
     */
    Q_PROPERTY(InhibitionState inhibitionState READ inhibitionState NOTIFY inhibitionStateChanged)

public:
    explicit NightColorController(QObject *parent = nullptr);
    ~NightColorController() override;

    /**
     * This enum type is used to specify the state of the inhibitor.
     */
    enum InhibitionState {
        Inhibiting, ///< Night Color is being inhibited.
        Inhibited, ///< Night Color is inhibited.
        Uninhibiting, ///< Night Color is being uninhibited.
        Uninhibited, ///< Night Color is uninhibited.
    };
    Q_ENUM(InhibitionState)

    /**
     * Returns @c true if Night Color is available; otherwise @c false.
     */
    bool isAvailable() const;

    /**
     * Returns @c true if Night Color is enabled; otherwise @c false.
     */
    bool isEnabled() const;

    /**
     * Returns @c true if Night Color is running; otherwise @c false.
     */
    bool isRunning() const;

    /**
     * Returns @c true if Night Color is on day mode; otherwise @c false.
     */
    bool isDaylight() const;

    /**
     * Returns 0 if automatic location, 1 if manual location, 2 if manual timings, 3 if constant
     */
    int mode() const;

    /**
     * Returns currently applied screen color temperature.
     */
    int currentTemperature() const;

    /**
     * Returns currently applied screen color temperature.
     */
    int targetTemperature() const;

    /**
     * Returns the time of the end of the previous color transition in msec since epoch.
     */
    quint64 currentTransitionEndTime() const;

    /**
     * Returns the time of the start of the next color transition in msec since epoch.
     */
    quint64 scheduledTransitionStartTime() const;

    /**
     * Returns the current state of the inhibitor.
     */
    InhibitionState inhibitionState() const;

public Q_SLOTS:
    /**
     * Attempts to temporarily disable Night Color.
     *
     * After calling this method, the inhibitor will enter the Inhibiting state.
     * Eventually, the inhibitor will enter the Inhibited state when the inhibition
     * request has been processed successfully by the Night Color manager.
     *
     * This method does nothing if the inhibitor is in the Inhibited state.
     */
    void inhibit();

    /**
     * Attempts to undo the previous call to inhibit() method.
     *
     * After calling this method, the inhibitor will enter the Uninhibiting state.
     * Eventually, the inhibitor will enter the Uninhibited state when the uninhibition
     * request has been processed by the Night Color manager.
     *
     * This method does nothing if the inhibitor is in the Uninhibited state.
     */
    void uninhibit();

Q_SIGNALS:
    /**
     * This signal is emitted when Night Color becomes (un)available.
     */
    void availableChanged();

    /**
     * Emitted whenever Night Color is enabled or disabled.
     */
    void enabledChanged();

    /**
     * Emitted whenever Night Color starts or stops running.
     */
    void runningChanged();

    /**
     * Emitted whenever Night Color changes between day and night time.
     */
    void daylightChanged();

    /**
     * Emitted whenever Night Color timings mode changes.
     */
    void modeChanged();

    /**
     * Emitted whenever the current screen color temperature has changed.
     */
    void currentTemperatureChanged();

    /**
     * Emitted whenever the current screen color temperature has changed.
     */
    void targetTemperatureChanged();

    /**
     * Emitted when the end time of the previous color transition has changed.
     */
    void currentTransitionEndTimeChanged();

    /**
     * Emitted when the end time of the next color transition has changed.
     */
    void scheduledTransitionStartTimeChanged();
    /**
     * Emitted whenever the state of the inhibitor has changed.
     */
    void inhibitionStateChanged();

private:
    NightColorControllerPrivate *d;
};
