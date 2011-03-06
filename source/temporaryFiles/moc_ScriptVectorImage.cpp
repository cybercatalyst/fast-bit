/****************************************************************************
** Meta object code from reading C++ file 'ScriptVectorImage.h'
**
** Created: Sun Mar 6 16:40:54 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/scriptClasses/ScriptVectorImage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScriptVectorImage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptVectorImage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   19,   18,   18, 0x0a,
      61,   18,   54,   18, 0x0a,
      69,   18,   54,   18, 0x0a,
      83,   18,   78,   18, 0x0a,
     107,  101,   18,   18, 0x0a,
     162,  132,   18,   18, 0x0a,
     236,  211,   18,   18, 0x0a,
     283,  101,   18,   18, 0x0a,
     304,  300,   18,   18, 0x0a,
     327,   18,   18,   18, 0x0a,
     343,   18,   18,   18, 0x0a,
     368,  359,  354,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptVectorImage[] = {
    "ScriptVectorImage\0\0width,height\0"
    "resize(double,double)\0double\0width()\0"
    "height()\0uint\0backgroundColor()\0color\0"
    "setBackgroundColor(uint)\0"
    "x1,y1,x2,y2,strokeWidth,color\0"
    "addLine(double,double,double,double,double,uint)\0"
    "x1,y1,width,height,color\0"
    "addRectangle(double,double,double,double,uint)\0"
    "addPolygon(uint)\0x,y\0polygon(double,double)\0"
    "finishPolygon()\0optimize()\0bool\0"
    "fileName\0saveAsSvg(QString)\0"
};

const QMetaObject ScriptVectorImage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptVectorImage,
      qt_meta_data_ScriptVectorImage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptVectorImage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptVectorImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptVectorImage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptVectorImage))
        return static_cast<void*>(const_cast< ScriptVectorImage*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptVectorImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: resize((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: { double _r = width();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 2: { double _r = height();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 3: { uint _r = backgroundColor();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 4: setBackgroundColor((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: addLine((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< uint(*)>(_a[6]))); break;
        case 6: addRectangle((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        case 7: addPolygon((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 8: polygon((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 9: finishPolygon(); break;
        case 10: optimize(); break;
        case 11: { bool _r = saveAsSvg((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
