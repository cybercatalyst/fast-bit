/****************************************************************************
** Meta object code from reading C++ file 'ScriptImage.h'
**
** Created: Fri Mar 4 20:11:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/scriptClasses/ScriptImage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptImage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptImage[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   51,   46,   12, 0x0a,
      80,   70,   12,   12, 0x0a,
     116,  103,   12,   12, 0x0a,
     132,   12,   46,   12, 0x0a,
     140,   12,   46,   12, 0x0a,
     155,  149,   12,   12, 0x0a,
     180,  171,  166,   12, 0x0a,
     194,   12,   12,   12, 0x0a,
     204,   12,   12,   12, 0x0a,
     227,  149,   12,   12, 0x0a,
     242,   12,   12,   12, 0x0a,
     252,   12,   12,   12, 0x0a,
     274,   12,   12,   12, 0x0a,
     290,   12,   12,   12, 0x0a,
     307,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptImage[] = {
    "ScriptImage\0\0image,title\0show(QImage,QString)\0"
    "uint\0x,y\0pixel(int,int)\0x,y,color\0"
    "setPixel(int,int,uint)\0width,height\0"
    "resize(int,int)\0width()\0height()\0value\0"
    "scale(int)\0bool\0fileName\0load(QString)\0"
    "display()\0brightnessCorrection()\0"
    "threshold(int)\0laPlace()\0detectZeroCrossings()\0"
    "convertToGray()\0grayValueSplay()\0"
    "dilatation()\0"
};

const QMetaObject ScriptImage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptImage,
      qt_meta_data_ScriptImage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptImage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptImage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptImage))
        return static_cast<void*>(const_cast< ScriptImage*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: show((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: { uint _r = pixel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 2: setPixel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 3: resize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: { uint _r = width();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 5: { uint _r = height();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 6: scale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { bool _r = load((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: display(); break;
        case 9: brightnessCorrection(); break;
        case 10: threshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: laPlace(); break;
        case 12: detectZeroCrossings(); break;
        case 13: convertToGray(); break;
        case 14: grayValueSplay(); break;
        case 15: dilatation(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ScriptImage::show(QImage _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
