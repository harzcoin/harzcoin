// Copyright (c) 2011-2014 The Harzcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HARZCOIN_QT_HARZCOINADDRESSVALIDATOR_H
#define HARZCOIN_QT_HARZCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class HarzcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HarzcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Harzcoin address widget validator, checks for a valid harzcoin address.
 */
class HarzcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HarzcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // HARZCOIN_QT_HARZCOINADDRESSVALIDATOR_H
