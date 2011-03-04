/****************************************************************************
** Meta object code from reading C++ file 'ScriptFile.h'
**
** Created: Fri Mar 4 20:11:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/scriptClasses/ScriptFile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptFile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptFile[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   17,   12,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      56,   48,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptFile[] = {
    "ScriptFile\0\0bool\0fileName\0open(QString)\0"
    "close()\0content\0write(QString)\0"
};

const QMetaObject ScriptFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptFile,
      qt_meta_data_ScriptFile, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptFile))
        return static_cast<void*>(const_cast< ScriptFile*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = open((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: close(); break;
        case 2: write((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
