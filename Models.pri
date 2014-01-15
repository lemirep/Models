
SOURCES +=	$$PWD/ListModel.cpp \
		$$PWD/ListItem.cpp \
		$$PWD/SubListedListModel.cpp \
                $$PWD/JSONListItemBinder.cpp

HEADERS += 	$$PWD/ListItem.h \
		$$PWD/ListModel.h \
		$$PWD/SubListedListItem.h \
		$$PWD/SubListedListModel.h \
                $$PWD/JSONListItemBinder.h

CONFIG(sql) {
    SOURCES +=  $$PWD/SQLiteListItemBinder.cpp
    HEADERS +=  $$PWD/SQLiteListItemBinder.h
}

INCLUDEPATH += $$PWD
