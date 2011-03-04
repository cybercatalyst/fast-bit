/****************************************************************************
** Meta object code from reading C++ file 'ScriptEngine.h'
**
** Created: Fri Mar 4 20:10:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/ScriptEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptEngine[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   38,   13,   13, 0x0a,
      75,   67,   13,   13, 0x0a,
      91,   14,   13,   13, 0x0a,
     119,  113,  108,   13, 0x0a,
     129,  113,  108,   13, 0x0a,
     141,  113,  108,   13, 0x0a,
     158,  152,  108,   13, 0x0a,
     186,  178,  108,   13, 0x0a,
     221,  219,  212,   13, 0x0a,
     233,  219,  212,   13, 0x0a,
     245,  219,  212,   13, 0x0a,
     264,  257,   13,   13, 0x08,
     298,  288,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ScriptEngine[] = {
    "ScriptEngine\0\0message\0output(QString)\0"
    "includeFile\0include(QString)\0command\0"
    "system(QString)\0writeln(QString)\0uint\0"
    "color\0red(uint)\0green(uint)\0blue(uint)\0"
    "r,g,b\0rgb(uint,uint,uint)\0r,g,b,a\0"
    "rgba(uint,uint,uint,uint)\0double\0x\0"
    "sin(double)\0cos(double)\0tan(double)\0"
    "script\0evaluateScript(QString)\0exception\0"
    "handleException(QScriptValue)\0"
};

const QMetaObject ScriptEngine::staticMetaObject = {
    { &QScriptEngine::staticMetaObject, qt_meta_stringdata_ScriptEngine,
      qt_meta_data_ScriptEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptEngine))
        return static_cast<void*>(const_cast< ScriptEngine*>(this));
    return QScriptEngine::qt_metacast(_clname);
}

int ScriptEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScriptEngine::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: output((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: include((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: system((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: writeln((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { uint _r = red((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 5: { uint _r = green((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 6: { uint _r = blue((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 7: { uint _r = rgb((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 8: { uint _r = rgba((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 9: { double _r = sin((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { double _r = cos((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: { double _r = tan((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 12: evaluateScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: handleException((*reinterpret_cast< const QScriptValue(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ScriptEngine::output(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
