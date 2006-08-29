/*
   Copyright (C) 2003 George Staikos <staikos@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#include "kwalletpopup.h"
#include <kstdaction.h>
#include <kactioncollection.h>
#include <kaction.h>
#include <kdebug.h>
#include <k3iconview.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kwallet.h>
#include <kstdguiitem.h>

KWalletPopup::KWalletPopup(const QString& wallet, QWidget *parent, const char *name)
: KMenu(parent), _walletName(wallet) {
	addTitle(wallet);
	setObjectName(name);
	KActionCollection *ac = new KActionCollection(this/*, "kwallet context actions"*/);
	ac->setObjectName("kwallet context actions");
	KAction *act;

	act = new KAction(i18n("&New Wallet..."), ac, "wallet_create");
	connect(act, SIGNAL(triggered(bool)), SLOT(createWallet()));
	addAction( act );

	act = new KAction(i18n("&Open..."), ac, "wallet_open");
	connect(act, SIGNAL(triggered(bool)), SLOT(openWallet()));
	act->setShortcut(Qt::Key_Return);
	addAction( act );

	act = new KAction(i18n("Change &Password..."), ac, "wallet_password");
	connect(act, SIGNAL(triggered(bool)), SLOT(changeWalletPassword()));
	addAction( act );

	QStringList ul = KWallet::Wallet::users(wallet);
	if (!ul.isEmpty()) {
		KMenu *pm = new KMenu(this);
		pm->setObjectName("Disconnect Apps");
		int id = 7000;
		for (QStringList::Iterator it = ul.begin(); it != ul.end(); ++it) {
			_appMap[id] = *it;
			pm->insertItem(*it, this, SLOT(disconnectApp(int)), 0, id);
			pm->setItemParameter(id, id);
			id++;
		}

		insertItem(i18n("Disconnec&t"), pm);
	}

	act = KStdAction::close( this,
			SLOT(closeWallet()), ac, "wallet_close");
	// FIXME: let's track this inside the manager so we don't need a dcop
	//        roundtrip here.
	act->setEnabled(KWallet::Wallet::isOpen(wallet));
	addAction( act );

	act = new KAction(i18n("&Delete"), ac, "wallet_delete");
	connect(act, SIGNAL(triggered(bool)), SLOT(deleteWallet()));
	act->setShortcut(Qt::Key_Delete);
	addAction( act );
}


KWalletPopup::~KWalletPopup() {
}


void KWalletPopup::openWallet() {
	emit walletOpened(_walletName);
}


void KWalletPopup::deleteWallet() {
        emit walletDeleted(_walletName);
}


void KWalletPopup::closeWallet() {
	emit walletClosed(_walletName);
}


void KWalletPopup::changeWalletPassword() {
	emit walletChangePassword(_walletName);
}


void KWalletPopup::createWallet() {
	emit walletCreated();
}


void KWalletPopup::disconnectApp(int id) {
	KWallet::Wallet::disconnectApplication(_walletName, _appMap[id].toLatin1());
}

#include "kwalletpopup.moc"

