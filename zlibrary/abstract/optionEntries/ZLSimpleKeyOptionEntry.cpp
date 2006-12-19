/*
 * Copyright (C) 2004-2006 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <ZLKeyBindings.h>

#include "ZLSimpleKeyOptionEntry.h"

void ZLSimpleKeyOptionEntry::CodeIndexBimap::insert(int code) {
	IndexByCode[code] = CodeByIndex.size();
	CodeByIndex.push_back(code);
}

int ZLSimpleKeyOptionEntry::CodeIndexBimap::indexByCode(int code) const {
	std::map<int,int>::const_iterator it = IndexByCode.find(code);
	return (it != IndexByCode.end()) ? it->second : 0;
}

int ZLSimpleKeyOptionEntry::CodeIndexBimap::codeByIndex(int index) const {
	if ((index < 0) || (index >= (int)CodeByIndex.size())) {
		return 0;
	}
	return CodeByIndex[index];
}

ZLSimpleKeyOptionEntry::ZLSimpleKeyOptionEntry(ZLKeyBindings &bindings) : ZLKeyOptionEntry(""), myBindings(bindings) {
}

void ZLSimpleKeyOptionEntry::onAccept() {
	for (std::map<std::string,int>::const_iterator it = myChangedCodes.begin(); it != myChangedCodes.end(); ++it) {
		myBindings.bindKey(it->first, it->second);
	}
	myBindings.saveCustomBindings();
}

int ZLSimpleKeyOptionEntry::actionIndex(const std::string &key) {
	std::map<std::string,int>::const_iterator it = myChangedCodes.find(key);
	return codeIndexBimap().indexByCode((it != myChangedCodes.end()) ? it->second : (int)myBindings.getBinding(key));
}

void ZLSimpleKeyOptionEntry::onValueChanged(const std::string &key, int index) {
	myChangedCodes[key] = codeIndexBimap().codeByIndex(index);
}
